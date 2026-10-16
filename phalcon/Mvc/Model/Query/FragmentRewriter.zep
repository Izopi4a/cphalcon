
/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Mvc\Model\Query;

use Phalcon\Db\Column;
use Phalcon\Db\DialectInterface;
use Phalcon\Mvc\Model\Exception;
use Phalcon\Mvc\Model\ManagerInterface;
use Phalcon\Mvc\Model\MetaDataInterface;
use Phalcon\Mvc\ModelInterface;
use Phalcon\Support\Settings;

/**
 * Phalcon\Mvc\Model\Query\FragmentRewriter
 *
 * The only "parsing" the native compiler does. A raw SQL fragment (a
 * condition, order, group, having, join condition or column) is scanned once,
 * left to right, and only Phalcon's own spellings are rewritten:
 *
 * - `:name:` becomes `:name`, `?0` becomes `:0`
 * - `{name}` and `{name:type}` become `:name` (the type is recorded as a bind
 *   type); `{name:array}` expands to one placeholder per bound element
 * - `[Fully\Qualified\Model]` (or the unbracketed namespaced name) becomes
 *   the model's alias in the query, or its table when it is not part of the
 *   query (subqueries)
 * - `[identifier]` becomes an escaped identifier
 * - a model property becomes its column, through the model's column map
 *
 * String literals, quoted identifiers, keywords, operators, function names and
 * `::` casts are never touched, so any SQL the database understands passes
 * through.
 */
class FragmentRewriter
{
    /**
     * Column maps (property => column) of the queried models, in query order
     *
     * @var array
     */
    protected bareMaps = [];

    /**
     * Bind parameters, used to expand array placeholders
     *
     * @var array
     */
    protected bindParams = [];

    /**
     * Bind types collected from typed placeholders ({name:int})
     *
     * @var array
     */
    protected bindTypes = [];

    /**
     * @var bool
     */
    protected columnRenaming = true;

    /**
     * @var DialectInterface
     */
    protected dialect;

    /**
     * Names that can qualify a column: alias / source / model class
     *
     * @var array
     */
    protected domains = [];

    /**
     * @var bool
     */
    protected literals = true;

    /**
     * @var ManagerInterface
     */
    protected manager;

    /**
     * @var MetaDataInterface
     */
    protected metaData;

    /**
     * Model class => table expression, for models referenced as tables
     *
     * @var array
     */
    protected tables = [];

    /**
     * Phalcon\Mvc\Model\Query\FragmentRewriter constructor
     */
    public function __construct(
        <ManagerInterface> manager,
        <MetaDataInterface> metaData,
        <DialectInterface> dialect,
        array bindParams = []
    ) {
        let this->manager        = manager,
            this->metaData       = metaData,
            this->dialect        = dialect,
            this->bindParams     = bindParams,
            this->literals       = (bool) Settings::get("orm.enable_literals"),
            this->columnRenaming = (bool) Settings::get("orm.column_renaming");
    }

    /**
     * Registers a model taking part in the query under its SQL alias (the
     * table alias, or the table name when there is no alias)
     */
    public function addModel(
        string modelName,
        <ModelInterface> model,
        string sqlAlias,
        bool hasAlias = false
    ) -> <FragmentRewriter> {
        var className, map, info, schema, source;

        let map = this->getReverseMap(model),
            info = [
                "alias": sqlAlias,
                "map":   map
            ];

        if hasAlias {
            let this->domains[sqlAlias] = info;
        } else {
            let source = model->getSource();

            if !isset this->domains[source] {
                let this->domains[source] = info;
            }
        }

        let className = ltrim(modelName, "\\");

        if !isset this->domains[className] {
            let this->domains[className] = info;
        }

        if !isset this->tables[className] {
            let source = model->getSource(),
                schema = model->getSchema();

            if schema {
                let this->tables[className] = this->dialect->getSqlTable([source, schema]);
            } else {
                let this->tables[className] = this->dialect->getSqlTable(source);
            }
        }

        if typeof map == "array" {
            let this->bareMaps[] = map;
        }

        return this;
    }

    /**
     * Escapes an identifier with the dialect's escape character
     */
    public function escape(string identifier) -> string
    {
        return this->dialect->escape(identifier);
    }

    /**
     * Bind types collected from typed placeholders
     */
    public function getBindTypes() -> array
    {
        return this->bindTypes;
    }

    /**
     * Resolves a column reference (`name`, `alias.name`, `[Model].[name]`) to
     * the escaped SQL column, through the column map
     */
    public function qualify(string domain, string property) -> string
    {
        var info, map, column;

        if !fetch info, this->domains[domain] {
            let info = this->lazyDomain(domain);
        }

        if typeof info != "array" {
            return this->escape(domain) . "." . this->escape(property);
        }

        let map = info["map"];

        if typeof map != "array" || !fetch column, map[property] {
            let column = property;
        }

        return this->escape(info["alias"]) . "." . this->escape(column);
    }

    /**
     * Rewrites a fragment and returns a Dialect expression: a `literal`, or
     * a `list` of literals and expanded placeholders when the fragment uses
     * array placeholders
     */
    public function rewrite(string fragment) -> array
    {
        var tokens, token, kind, text, name, info, next, prev, before,
            domainOf, pieces, bindType, bindValue, map, column, typeParts,
            nextIndex, prevIndex;
        string output;
        int total, i;

        let tokens   = self::tokenize(fragment),
            total    = count(tokens),
            output   = "",
            pieces   = [],
            domainOf = [],
            i        = 0;

        while i < total {
            let token = tokens[i],
                kind  = token[0],
                text  = token[1];

            switch kind {
                case "str":
                case "num":
                    if unlikely !this->literals {
                        throw new Exception(
                            "Literals are disabled in PHQL statements"
                        );
                    }

                    let output .= text;
                    break;

                case "spl":
                    let output .= substr(text, 0, -1);
                    break;

                case "npl":
                    let output .= ":" . substr(text, 1);
                    break;

                case "bpl":
                    let name = substr(text, 1, -1);

                    if !memstr(name, ":") {
                        let output .= ":" . name;
                        break;
                    }

                    let typeParts = explode(":", name, 2),
                        name      = typeParts[0],
                        bindType  = typeParts[1];

                    switch bindType {
                        case "str":
                            let this->bindTypes[name] = Column::BIND_PARAM_STR;
                            break;

                        case "int":
                            let this->bindTypes[name] = Column::BIND_PARAM_INT;
                            break;

                        case "double":
                            let this->bindTypes[name] = Column::BIND_PARAM_DECIMAL;
                            break;

                        case "bool":
                            let this->bindTypes[name] = Column::BIND_PARAM_BOOL;
                            break;

                        case "blob":
                            let this->bindTypes[name] = Column::BIND_PARAM_BLOB;
                            break;

                        case "null":
                            let this->bindTypes[name] = Column::BIND_PARAM_NULL;
                            break;

                        case "array":
                        case "array-str":
                        case "array-int":
                            if unlikely !fetch bindValue, this->bindParams[name] {
                                throw new Exception(
                                    "Bind value is required for array type placeholder: " . name
                                );
                            }

                            if unlikely typeof bindValue != "array" {
                                throw new Exception(
                                    "Bind type requires an array in placeholder: " . name
                                );
                            }

                            if unlikely count(bindValue) < 1 {
                                throw new Exception(
                                    "At least one value must be bound in placeholder: " . name
                                );
                            }

                            let pieces[] = [
                                "type":  "literal",
                                "value": output
                            ];

                            let pieces[] = [
                                "type":     "placeholder",
                                "value":    ":" . name,
                                "rawValue": name,
                                "times":    count(bindValue)
                            ];

                            let output = "";
                            break;

                        default:
                            throw new Exception("Unknown bind type: " . bindType);
                    }

                    if !starts_with(bindType, "array") {
                        let output .= ":" . name;
                    }

                    break;

                case "id":
                case "br":
                    if kind == "br" {
                        let name = substr(text, 1, -1);
                    } else {
                        let name = text;
                    }

                    let nextIndex = self::significant(tokens, i, 1),
                        prevIndex = self::significant(tokens, i, -1),
                        next      = "",
                        prev      = "";

                    if nextIndex >= 0 {
                        let next = tokens[nextIndex][1];
                    }

                    if prevIndex >= 0 {
                        let prev = tokens[prevIndex][1];
                    }

                    /**
                     * A type after a cast, a function name or a column alias
                     */
                    if prev == "::" || (kind == "id" && next == "(") || strtoupper(prev) == "AS" {
                        if kind == "br" {
                            let output .= this->escape(name);
                        } else {
                            let output .= text;
                        }

                        break;
                    }

                    /**
                     * A domain: alias.column / [Model].column
                     */
                    if next == "." {
                        if !fetch info, this->domains[ltrim(name, "\\")] {
                            let info = this->lazyDomain(name);
                        }

                        let domainOf[i] = info;

                        if typeof info == "array" {
                            let output .= this->escape(info["alias"]);
                        } elseif kind == "br" {
                            let output .= this->escape(name);
                        } else {
                            let output .= text;
                        }

                        break;
                    }

                    /**
                     * A qualified column: the map of its domain applies
                     */
                    if prev == "." {
                        let before = self::significant(tokens, prevIndex, -1),
                            info   = null;

                        if before >= 0 {
                            fetch info, domainOf[before];
                        }

                        if typeof info == "array" {
                            let map = info["map"];

                            if typeof map == "array" && fetch column, map[name] {
                                let output .= this->escape(column);
                                break;
                            }
                        }

                        if kind == "br" {
                            let output .= this->escape(name);
                        } else {
                            let output .= text;
                        }

                        break;
                    }

                    /**
                     * A model referenced as a table (subqueries)
                     */
                    if kind == "br" || memstr(name, "\\") {
                        let column = this->modelTable(name);

                        if column !== null {
                            let output .= column;
                            break;
                        }
                    }

                    /**
                     * A bare column: the first queried model mapping it wins
                     */
                    let column = this->bareColumn(name);

                    if column !== null {
                        let output .= this->escape(column);
                    } elseif kind == "br" {
                        let output .= this->escape(name);
                    } else {
                        let output .= text;
                    }

                    break;

                default:
                    let output .= text;
                    break;
            }

            let i++;
        }

        if empty pieces {
            return [
                "type":  "literal",
                "value": output
            ];
        }

        if output !== "" {
            let pieces[] = [
                "type":  "literal",
                "value": output
            ];
        }

        return [
            "type":        "list",
            "value":       pieces,
            "separator":   "",
            "parentheses": false
        ];
    }

    /**
     * Rewrites a fragment that must stay a plain string (no array
     * placeholders)
     */
    public function rewriteString(string fragment) -> string
    {
        var expression;

        let expression = this->rewrite(fragment);

        if unlikely expression["type"] != "literal" {
            throw new Exception(
                "Array placeholders are not allowed in this clause: " . fragment
            );
        }

        return expression["value"];
    }

    /**
     * Splits a SQL list on the commas that are not inside parentheses,
     * quotes or brackets
     */
    public static function splitList(string sql) -> array
    {
        var token, parts;
        string buffer;
        int depth;

        let parts  = [],
            buffer = "",
            depth  = 0;

        for token in self::tokenize(sql) {
            if token[0] == "ch" {
                if token[1] == "(" {
                    let depth++;
                } elseif token[1] == ")" {
                    let depth--;
                } elseif token[1] == "," && depth == 0 {
                    let parts[] = trim(buffer),
                        buffer  = "";

                    continue;
                }
            }

            let buffer .= token[1];
        }

        if trim(buffer) !== "" {
            let parts[] = trim(buffer);
        }

        return parts;
    }

    /**
     * Splits `expr AS alias`, `expr [alias]` and `expr alias` into the
     * expression and the alias (null when there is none)
     */
    public static function splitAlias(string item) -> array
    {
        var tokens, last, prev, alias, keywords, lastIndex, prevIndex,
            expression;
        int total, i, depth;
        

        let tokens = self::tokenize(trim(item)),
            total  = count(tokens);

        let lastIndex = self::significant(tokens, total, -1);

        if lastIndex < 1 {
            return [trim(item), null];
        }

        let last = tokens[lastIndex];

        if last[0] != "id" && last[0] != "br" && last[0] != "qid" {
            return [trim(item), null];
        }

        let prevIndex = self::significant(tokens, lastIndex, -1),
            prev      = tokens[prevIndex];

        /**
         * The alias must be at the top level
         */
        let depth = 0;

        for i in range(0, lastIndex - 1) {
            if tokens[i][0] == "ch" {
                if tokens[i][1] == "(" {
                    let depth++;
                } elseif tokens[i][1] == ")" {
                    let depth--;
                }
            }
        }

        if depth != 0 {
            return [trim(item), null];
        }

        if last[0] == "br" || last[0] == "qid" {
            let alias = substr(last[1], 1, -1);
        } else {
            let alias = last[1];
        }

        if prev[0] == "id" && strtoupper(prev[1]) == "AS" {
            let expression = self::joinTokens(tokens, 0, prevIndex);

            return [trim(expression), alias];
        }

        /**
         * Implicit alias: `COUNT(*) total`, `COUNT(*) [rowcount]`
         */
        let keywords = [
            "AND", "AS", "ASC", "BETWEEN", "CASE", "DESC", "DISTINCT", "ELSE",
            "END", "FALSE", "IN", "IS", "LIKE", "NOT", "NULL", "OR", "THEN",
            "TRUE", "WHEN"
        ];

        if last[0] == "id" && in_array(strtoupper(last[1]), keywords) {
            return [trim(item), null];
        }

        if prev[0] == "ch" && prev[1] != ")" {
            return [trim(item), null];
        }

        if prev[0] == "id" && in_array(strtoupper(prev[1]), keywords) {
            return [trim(item), null];
        }

        if prev[0] == "cast" || prev[0] == "spl" || prev[0] == "npl" || prev[0] == "bpl" {
            return [trim(item), null];
        }

        let expression = self::joinTokens(tokens, 0, lastIndex);

        return [trim(expression), alias];
    }

    /**
     * Splits a fragment into tokens: [kind, text]
     */
    public static function tokenize(string fragment) -> array
    {
        var matches, match, kind, tokens;
        array kinds;

        let kinds = [
            "cm", "str", "qid", "br", "cast", "spl", "pdo", "npl", "bpl",
            "id", "num", "ws", "ch"
        ];

        let matches = null,
            tokens  = [];

        preg_match_all(
            "/(?<cm>--[^\\n]*|\\/\\*.*?\\*\\/)|(?<str>'(?:[^']|'')*')|(?<qid>\"(?:[^\"]|\"\")*\"|`[^`]*`)|(?<br>\\[[A-Za-z_\\\\][A-Za-z0-9_\\\\]*\\])|(?<cast>::)|(?<spl>:[A-Za-z_][A-Za-z0-9_-]*:(?!:))|(?<pdo>:[A-Za-z_][A-Za-z0-9_]*)|(?<npl>\\?[0-9]+)|(?<bpl>\\{[A-Za-z_][A-Za-z0-9_-]*(?::[a-z-]+)?\\})|(?<id>\\\\?[A-Za-z_][A-Za-z0-9_]*(?:\\\\[A-Za-z_][A-Za-z0-9_]*)*)|(?<num>[0-9]+(?:\\.[0-9]+)?(?:[eE][-+]?[0-9]+)?)|(?<ws>\\s+)|(?<ch>.)/s",
            fragment,
            matches,
            PREG_SET_ORDER | PREG_UNMATCHED_AS_NULL
        );

        for match in matches {
            for kind in kinds {
                if isset match[kind] {
                    let tokens[] = [kind, match[kind]];
                    break;
                }
            }
        }

        return tokens;
    }

    /**
     * Column of a bare property, searching the queried models in order
     */
    protected function bareColumn(string name) -> string | null
    {
        var map, column;

        for map in this->bareMaps {
            if fetch column, map[name] {
                return column;
            }
        }

        return null;
    }

    /**
     * Reverse column map (property => column) of a model, when column
     * renaming is on and the model has a column map
     */
    protected function getReverseMap(<ModelInterface> model) -> array | null
    {
        var map;

        if !this->columnRenaming {
            return null;
        }

        let map = this->metaData->getReverseColumnMap(model);

        if typeof map != "array" {
            return null;
        }

        return map;
    }

    /**
     * Whether a name refers to a model class. Only namespaced names are
     * autoloaded, so `[name]` does not hit the autoloader.
     */
    protected function isModel(string name) -> bool
    {
        var className;

        let className = ltrim(name, "\\");

        if memstr(className, "\\") {
            if !class_exists(className) {
                return false;
            }
        } elseif !class_exists(className, false) {
            return false;
        }

        return is_subclass_of(className, "Phalcon\\Mvc\\ModelInterface");
    }

    /**
     * Registers a model that is not part of the query but is used as a
     * domain (`[Other\Model].column` in a subquery)
     */
    protected function lazyDomain(string name) -> array | null
    {
        var className, model, info, source;

        let className = ltrim(name, "\\");

        if !this->isModel(className) {
            return null;
        }

        let model = this->manager->load(className),
            source = model->getSource();

        let info = [
            "alias": source,
            "map":   this->getReverseMap(model)
        ];

        let this->domains[className] = info;

        return info;
    }

    /**
     * Table of a model referenced by class name, or null if the name is not
     * a model
     */
    protected function modelTable(string name) -> string | null
    {
        var className, table, model, schema;

        let className = ltrim(name, "\\");

        if fetch table, this->tables[className] {
            return table;
        }

        if !this->isModel(className) {
            return null;
        }

        let model  = this->manager->load(className),
            schema = model->getSchema();

        if schema {
            let table = this->dialect->getSqlTable([model->getSource(), schema]);
        } else {
            let table = this->dialect->getSqlTable(model->getSource());
        }

        let this->tables[className] = table;

        return table;
    }

    /**
     * Joins token texts from start (inclusive) to end (exclusive)
     */
    protected static function joinTokens(array tokens, int start, int end) -> string
    {
        string output;
        int i;

        let output = "",
            i      = start;

        while i < end {
            let output .= tokens[i][1];
            let i++;
        }

        return output;
    }

    /**
     * Index of the nearest significant token (not whitespace or comment) in
     * the given direction, or -1
     */
    protected static function significant(array tokens, int from, int direction) -> int
    {
        var kind;
        int i, total;

        let total = count(tokens),
            i     = from + direction;

        while i >= 0 && i < total {
            let kind = tokens[i][0];

            if kind != "ws" && kind != "cm" {
                return i;
            }

            let i += direction;
        }

        return -1;
    }
}
