
/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Mvc\View\Engine\Volt;

/**
 * Template inheritance resolved on the AST, before anything is compiled.
 *
 * The chain leaf -> ... -> root is loaded as ASTs, the blocks of every level
 * are collected by name (at any depth: inside blocks, if, for, switch), and the
 * root's statements are expanded: each {% block %} node becomes the statements
 * of its most derived definition, recursively, and {{ super() }} becomes the
 * next definition up the chain. {{ block("name") }} renders a block again and
 * {% embed %} resolves its body as an anonymous child of the embedded template.
 *
 * The result is one flat statement list without extends, block or embed nodes,
 * which Compiler::statementList() compiles as before: one PHP file per rendered
 * template and no block dispatch at run time.
 */
class Resolver
{
    /**
     * Node type of raw PHP emitted by the resolver (scope wrappers, dynamic
     * extends). Compiler::statementList() outputs its "code" as it is.
     */
    const PHP_NODE = "volt:php";

    /**
     * @var array
     */
    protected collected = [];

    /**
     * @var Compiler
     */
    protected compiler;

    /**
     * Blocks being expanded, "name@level" => true (cycle guard)
     *
     * @var array
     */
    protected expanding = [];

    /**
     * Leaf first, root last: [["path" => string, "blocks" => [name => node]]]
     *
     * @var array
     */
    protected levels = [];

    public function __construct(<Compiler> compiler)
    {
        let this->compiler = compiler;
    }

    /**
     * A node holding raw PHP for the compiled output
     */
    public static function php(string code) -> array
    {
        return [
            "type": self::PHP_NODE,
            "code": code,
            "file": "",
            "line": 0
        ];
    }

    /**
     * Statements with no extends, block or embed nodes
     */
    public function resolve(array ast, string path) -> array
    {
        var extendsNode, override;

        let extendsNode = this->findExtends(ast);

        if extendsNode !== null && !this->isLiteral(extendsNode["path"]) {
            let override = this->compiler->takeExtendsOverride();

            if override === null {
                return this->dynamicExtends(extendsNode, path);
            }

            let ast = this->withExtendsPath(ast, override);
        }

        /**
         * Nothing to resolve: the common case of a plain template
         */
        if extendsNode === null && !this->hasInheritanceNodes(ast) {
            return ast;
        }

        return this->resolveChain(ast, path);
    }

    /**
     * Loads the chain from ast up to the root and expands the root
     */
    public function resolveChain(array ast, string path) -> array
    {
        var current, currentPath, extendsNode, parentPath;
        array seen;

        let this->levels = [],
            seen         = [],
            current      = ast,
            currentPath  = path;

        let seen[path] = true;

        loop {
            let this->levels[] = [
                "path":   currentPath,
                "blocks": this->collectBlocks(current, currentPath)
            ];

            let extendsNode = this->findExtends(current);

            if extendsNode === null {
                break;
            }

            if unlikely !this->isLiteral(extendsNode["path"]) {
                throw this->error("Only the rendered template may extend a variable", extendsNode);
            }

            let parentPath = this->compiler->resolveTemplatePath(extendsNode["path"]["value"], currentPath);

            if unlikely isset seen[parentPath] {
                throw this->error("Circular inheritance: " . parentPath, extendsNode);
            }

            let seen[parentPath] = true;

            let current     = this->compiler->parseFile(parentPath),
                currentPath = parentPath;
        }

        return this->expand(current, null);
    }

    /**
     * All blocks of one template, at any depth, except those inside an embed
     * body: those belong to the embedded template
     */
    protected function collectBlocks(array statements, string path) -> array
    {
        let this->collected = [];

        this->collectInto(statements, path);

        return this->collected;
    }

    protected function collectInto(array statements, string path) -> void
    {
        var statement, type, name, existing, key, children;

        for statement in statements {
            if typeof statement != "array" || !fetch type, statement["type"] {
                continue;
            }

            if type == PHVOLT_T_EMBED {
                continue;
            }

            if type == PHVOLT_T_BLOCK {
                let name = statement["name"];

                if unlikely fetch existing, this->collected[name] {
                    throw this->error(
                        sprintf(
                            "Block '%s' is defined twice in %s (lines %d and %d)",
                            name,
                            path,
                            existing["line"],
                            statement["line"]
                        ),
                        statement
                    );
                }

                let this->collected[name] = statement;
            }

            for key in ["block_statements", "true_statements", "false_statements", "case_clauses", "caller"] {
                if fetch children, statement[key] {
                    if typeof children == "array" {
                        this->collectInto(children, path);
                    }
                }
            }
        }
    }

    /**
     * {% extends layoutVar %}: the parent is only known at render time. The
     * template compiles to a call that compiles (once per parent) and runs the
     * child against that parent.
     */
    protected function dynamicExtends(array extendsNode, string path) -> array
    {
        return [
            self::php(
                "<?php $this->renderDynamicExtends("
                . this->compiler->expression(extendsNode["path"])
                . ", " . var_export(path, true) . ", get_defined_vars()); ?>"
            )
        ];
    }

    protected function error(string message, array node) -> <Exception>
    {
        var file, line;

        if !fetch file, node["file"] {
            let file = "?";
        }

        if !fetch line, node["line"] {
            let line = 0;
        }

        return new Exception(sprintf("%s in %s on line %d", message, file, line));
    }

    protected function expand(array statements, var context) -> array
    {
        var statement, type, key, children, item, expr;
        array out;

        let out = [];

        for statement in statements {
            if typeof statement != "array" || !fetch type, statement["type"] {
                let out[] = statement;
                continue;
            }

            if type == PHVOLT_T_EXTENDS {
                continue;
            }

            if type == PHVOLT_T_BLOCK {
                for item in this->expandBlock(statement["name"], statement) {
                    let out[] = item;
                }

                continue;
            }

            if type == PHVOLT_T_EMBED {
                for item in this->expandEmbed(statement) {
                    let out[] = item;
                }

                continue;
            }

            if type == PHVOLT_T_ECHO && fetch expr, statement["expr"] {
                if this->isCall(expr, "super") {
                    for item in this->expandSuper(context, statement) {
                        let out[] = item;
                    }

                    continue;
                }

                if this->isCall(expr, "block") {
                    for item in this->expandBlockFunction(expr) {
                        let out[] = item;
                    }

                    continue;
                }
            }

            for key in ["block_statements", "true_statements", "false_statements", "case_clauses", "caller"] {
                if fetch children, statement[key] {
                    if typeof children == "array" {
                        let statement[key] = this->expand(children, context);
                    }
                }
            }

            let out[] = statement;
        }

        return out;
    }

    /**
     * A {% block %} node: the most derived definition of that name
     */
    protected function expandBlock(string name, array node) -> array
    {
        var index, level;

        for index, level in this->levels {
            if isset level["blocks"][name] {
                return this->expandBlockAt(name, index);
            }
        }

        throw this->error("Block '" . name . "' is not defined", node);
    }

    protected function expandBlockAt(string name, int index) -> array
    {
        var key, block, statements, result;

        let key   = name . "@" . index,
            block = this->levels[index]["blocks"][name];

        if unlikely isset this->expanding[key] {
            throw this->error("Block '" . name . "' renders itself", block);
        }

        if !fetch statements, block["block_statements"] || typeof statements != "array" {
            let statements = [];
        }

        let this->expanding[key] = true;

        let result = this->expand(
            statements,
            [
                "name":  name,
                "level": index
            ]
        );

        unset this->expanding[key];

        return result;
    }

    /**
     * {{ block("name") }}: render a block again elsewhere (<title> and <h1>)
     */
    protected function expandBlockFunction(array call) -> array
    {
        var arguments, argument;

        if !fetch arguments, call["arguments"] || typeof arguments != "array" || count(arguments) != 1 {
            throw this->error("block() takes one string literal: {{ block(\"name\") }}", call);
        }

        let argument = arguments[0];

        if unlikely !this->isLiteral(argument["expr"]) {
            throw this->error("block() takes one string literal: {{ block(\"name\") }}", call);
        }

        return this->expandBlock(argument["expr"]["value"], call);
    }

    /**
     * {% embed "card.volt" with [...] %}{% block body %}...{% endblock %}{% endembed %}
     *
     * The body is an anonymous child template of "card.volt", resolved on its
     * own, inlined here and run in a scope of its own.
     */
    protected function expandEmbed(array node) -> array
    {
        var child, statements, params, statement, sub, item;
        array out;

        if unlikely !this->isLiteral(node["path"]) {
            throw this->error("embed needs a string literal template name", node);
        }

        let child = [
            [
                "type": PHVOLT_T_EXTENDS,
                "path": node["path"],
                "file": node["file"],
                "line": node["line"]
            ]
        ];

        if fetch statements, node["block_statements"] {
            if typeof statements == "array" {
                for statement in statements {
                    let child[] = statement;
                }
            }
        }

        let sub = new self(this->compiler);

        if fetch params, node["params"] {
            let params = this->compiler->expression(params);
        } else {
            let params = "[]";
        }

        let out = [
            self::php("<?php (function (array $__volt_scope) { extract($__volt_scope); ?>")
        ];

        for item in sub->resolveChain(child, this->levels[0]["path"]) {
            let out[] = item;
        }

        let out[] = self::php("<?php })(array_merge(get_defined_vars(), " . params . ")); ?>");

        return out;
    }

    /**
     * {{ super() }}: the definition of the current block one level up
     */
    protected function expandSuper(var context, array node) -> array
    {
        var name;
        int index, total;

        if unlikely typeof context != "array" {
            throw this->error("super() can only be used inside a block", node);
        }

        let name  = context["name"],
            total = count(this->levels),
            index = (int) context["level"] + 1;

        while index < total {
            if isset this->levels[index]["blocks"][name] {
                return this->expandBlockAt(name, index);
            }

            let index++;
        }

        throw this->error("super() in block '" . name . "': no parent template defines it", node);
    }

    protected function findExtends(array statements) -> array | null
    {
        var statement, type;

        for statement in statements {
            if typeof statement == "array" && fetch type, statement["type"] {
                if type == PHVOLT_T_EXTENDS {
                    return statement;
                }
            }
        }

        return null;
    }

    /**
     * Whether a template uses blocks, embed, block() or super() anywhere
     */
    protected function hasInheritanceNodes(array statements) -> bool
    {
        var statement, type, key, children, expr;

        for statement in statements {
            if typeof statement != "array" || !fetch type, statement["type"] {
                continue;
            }

            if type == PHVOLT_T_BLOCK || type == PHVOLT_T_EMBED {
                return true;
            }

            if type == PHVOLT_T_ECHO && fetch expr, statement["expr"] {
                if this->isCall(expr, "block") || this->isCall(expr, "super") {
                    return true;
                }
            }

            for key in ["block_statements", "true_statements", "false_statements", "case_clauses", "caller"] {
                if fetch children, statement[key] {
                    if typeof children == "array" && this->hasInheritanceNodes(children) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    protected function isCall(var expr, string name) -> bool
    {
        var type, nameNode;

        if typeof expr != "array" || !fetch type, expr["type"] || type != PHVOLT_T_FCALL {
            return false;
        }

        if !fetch nameNode, expr["name"] || typeof nameNode != "array" {
            return false;
        }

        return isset nameNode["type"] && nameNode["type"] == PHVOLT_T_IDENTIFIER
            && isset nameNode["value"] && nameNode["value"] === name;
    }

    protected function isLiteral(var expr) -> bool
    {
        var type;

        return typeof expr == "array" && fetch type, expr["type"] && type == PHVOLT_T_STRING;
    }

    protected function withExtendsPath(array statements, string path) -> array
    {
        var index, statement, type;

        for index, statement in statements {
            if typeof statement == "array" && fetch type, statement["type"] {
                if type == PHVOLT_T_EXTENDS {
                    let statements[index]["path"] = [
                        "type":  PHVOLT_T_STRING,
                        "value": path
                    ];

                    break;
                }
            }
        }

        return statements;
    }
}
