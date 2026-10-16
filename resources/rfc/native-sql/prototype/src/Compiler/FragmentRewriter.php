<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Compiler;

/**
 * The only "parsing" the native path does: a single left-to-right scan over a raw SQL fragment
 * (a find() condition, order, group, having or columns string) that rewrites the few
 * Phalcon-specific spellings and leaves every other byte alone, so any SQL the database
 * understands passes through.
 *
 * Rewritten:
 *   :name:            -> :name                  PHQL named placeholder
 *   ?0                -> :0                     PHQL numeric placeholder (same as PHQL's own output)
 *   {name}            -> :name
 *   {name:array}      -> :name0, :name1, ...    one per element of bind[name]; the Pdo adapter
 *                                               expands the array value (same as PHQL)
 *   [Fully\Model]     -> the model's table      only for the model being queried
 *   property          -> column                 only when the model has a columnMap, and only for
 *   alias.property    -> alias.column           a bare identifier that is a mapped property, not
 *                                               followed by "(" (function) and not after AS
 *
 * Never touched: string literals ('...'), quoted identifiers ("..." `...`), numbers, operators,
 * keywords, function names, `::` casts, anything not listed above.
 *
 * Deliberately NOT done (these need a grammar, see RFC "What is lost"): implicit joins, ambiguity
 * checks, qualifying unqualified columns, orm.enable_literals enforcement.
 */
final class FragmentRewriter
{
    /**
     * @param array<string, string>|null $propertyToColumn reverse columnMap of the model, or null
     * @param list<string>               $domains          names that refer to the model: source,
     *                                                     alias, and the bracketed class name
     */
    public function __construct(
        private readonly ?array $propertyToColumn,
        private readonly array $domains,
        private readonly string $modelClass,
        private readonly string $source,
    ) {
    }

    /**
     * @param array<int|string, mixed> $bind used to expand {name:array}
     */
    public function rewrite(string $fragment, array $bind = []): string
    {
        $out    = '';
        $length = strlen($fragment);
        $i      = 0;

        while ($i < $length) {
            $c = $fragment[$i];

            // '...' string literal, '' is an escaped quote
            if ($c === "'") {
                $end = $this->closing($fragment, $i, "'");
                $out .= substr($fragment, $i, $end - $i + 1);
                $i    = $end + 1;
                continue;
            }

            // "..." or `...` quoted identifier: the user already wrote the real name
            if ($c === '"' || $c === '`') {
                $end = $this->closing($fragment, $i, $c);
                $out .= substr($fragment, $i, $end - $i + 1);
                $i    = $end + 1;
                continue;
            }

            // [Fully\Qualified\Model] -> table of the queried model
            if ($c === '[' && preg_match('/\G\[([A-Za-z_\\\\][A-Za-z0-9_\\\\]*)\]/', $fragment, $m, 0, $i)) {
                $name = ltrim($m[1], '\\');
                $out .= $name === ltrim($this->modelClass, '\\') ? $this->source : $m[0];
                $i   += strlen($m[0]);
                continue;
            }

            // :name:  (but not the ':' of a '::' cast)
            if ($c === ':' && ($fragment[$i + 1] ?? '') !== ':'
                && preg_match('/\G:([A-Za-z_][A-Za-z0-9_-]*):(?!:)/', $fragment, $m, 0, $i)) {
                $out .= ':' . $m[1];
                $i   += strlen($m[0]);
                continue;
            }

            // ?0
            if ($c === '?' && preg_match('/\G\?(\d+)/', $fragment, $m, 0, $i)) {
                $out .= ':' . $m[1];
                $i   += strlen($m[0]);
                continue;
            }

            // {name}, {name:type}, {name:array}
            if ($c === '{' && preg_match('/\G\{([A-Za-z_][A-Za-z0-9_-]*)(?::([a-z]+))?\}/', $fragment, $m, 0, $i)) {
                $name = $m[1];
                if (($m[2] ?? '') === 'array') {
                    $count = is_array($bind[$name] ?? null) ? count($bind[$name]) : 0;
                    if ($count === 0) {
                        throw new \InvalidArgumentException("Bind value for {{$name}:array} must be a non-empty array");
                    }
                    $out .= implode(', ', array_map(static fn (int $n): string => ':' . $name . $n, range(0, $count - 1)));
                } else {
                    $out .= ':' . $name;
                }
                $i += strlen($m[0]);
                continue;
            }

            // identifiers and alias.identifier
            if (ctype_alpha($c) || $c === '_') {
                preg_match('/\G[A-Za-z_][A-Za-z0-9_]*/', $fragment, $m, 0, $i);
                $word = $m[0];
                $out .= $this->identifier($fragment, $i, $word, $out);
                $i   += strlen($word);
                continue;
            }

            $out .= $c;
            $i++;
        }

        return $out;
    }

    private function identifier(string $fragment, int $at, string $word, string $before): string
    {
        if ($this->propertyToColumn === null) {
            return $word;
        }

        $after = substr($fragment, $at + strlen($word));

        // function call: COUNT( / json_object(
        if (preg_match('/^\s*\(/', $after)) {
            return $word;
        }

        // a column alias: ... AS name
        if (preg_match('/\bAS\s+$/i', $before)) {
            return $word;
        }

        // part of a qualified name: only rewrite when the domain is the queried model
        if (str_ends_with($before, '.')) {
            preg_match('/([A-Za-z_][A-Za-z0-9_]*|"[^"]*"|`[^`]*`)\.$/', $before, $d);
            $domain = trim($d[1] ?? '', '"`');
            if (!in_array($domain, $this->domains, true)) {
                return $word;
            }
        }

        return $this->propertyToColumn[$word] ?? $word;
    }

    private function closing(string $fragment, int $start, string $quote): int
    {
        $length = strlen($fragment);
        for ($j = $start + 1; $j < $length; $j++) {
            if ($fragment[$j] === $quote) {
                if (($fragment[$j + 1] ?? '') === $quote) {
                    $j++;
                    continue;
                }

                return $j;
            }
        }

        throw new \InvalidArgumentException("Unterminated {$quote} in SQL fragment: {$fragment}");
    }
}
