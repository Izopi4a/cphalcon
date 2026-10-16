# Extending Volt (draft for docs.phalcon.io, Phalcon 5.x)

Draft replacement for the "Extending Volt", "Functions", "Filters" and "Extensions" sections of
the Volt page. It documents the API **as it works today**, so it can be published without waiting
for the NFR. Every snippet is checked by `prototype/tests/Today/DocsDraftTest.php` against the
5.23.0 extension. The last section shows what the NFR (`volt-rfc.md`) would add.

---

## The one thing to know first

Volt compiles a template to PHP **once**, writes the result to the compiled path, and from then on
only runs that PHP file. Functions and filters that you add to the compiler take part in that
compilation step:

- they run **when the template is compiled**, not when it is rendered;
- they receive the arguments as **PHP source code**, not values;
- they return **PHP source code**, which is written into the compiled file.

```php
$compiler->addFunction('year', fn () => date('Y'));
// {{ year() }} compiles to:   <?= 2026 ?>
// The year is frozen into the compiled file until it is compiled again.

$compiler->addFunction('year', fn () => 'date("Y")');
// {{ year() }} compiles to:   <?= date("Y") ?>
// Correct: the returned string is PHP code, evaluated on every render.
```

If you remember one rule: **return code, not values.**

## Choosing how to extend

| you need | use |
|---|---|
| call an existing PHP function or static method | `addFunction('name', 'php_function')` or `addFunction('name', 'App\Helper::method')` |
| generate different code depending on the arguments | `addFunction('name', function (string $resolvedArgs, ?array $exprArgs): string { … })` |
| call a service from the DI container | generate code that reaches it through `$this` (see [Services](#calling-a-service)) |
| transform a value with `|name` | `addFilter()`, same rules as functions |
| a custom `is` test, or to change how a statement compiles | an extension object (see [Extensions](#extensions)) |

## Functions

### A PHP function or a static method

A string is used as the name of the PHP function to call. The compiled arguments are put between
the parentheses:

```php
$compiler = $volt->getCompiler();

$compiler->addFunction('shuffle', 'str_shuffle');
// {{ shuffle("abc") }}             →  <?= str_shuffle('abc') ?>

$compiler->addFunction('money', 'App\Money::format');
// {{ money(total, "EUR") }}        →  <?= App\Money::format($total, 'EUR') ?>
```

Only a string is accepted for this form. An array callable (`[Money::class, 'format']`) or an
invokable object throws `InvalidUserFunctionDefinition`.

### A closure that generates code

A closure is called by the compiler with two arguments:

| argument | contains | example for `{{ money(total, "EUR") }}` |
|---|---|---|
| `string $resolvedArgs` | the arguments, already compiled to PHP and joined with `, ` | `"$total, 'EUR'"` |
| `?array $exprArgs` | the arguments as parsed nodes (see [Node reference](#node-reference)), `null` when there are none | `[['expr' => ['type' => 265, 'value' => 'total', …]], ['expr' => ['type' => 260, 'value' => 'EUR', …]]]` |

It must return a PHP expression as a string:

```php
$compiler->addFunction(
    'money',
    function (string $resolvedArgs, ?array $exprArgs): string {
        return '\App\Money::format(' . $resolvedArgs . ')';
    }
);
// {{ money(total, "EUR") }}        →  <?= \App\Money::format($total, 'EUR') ?>
```

Use `$exprArgs` when the generated code depends on what was written in the template. To compile
one argument, pass its node to the compiler:

```php
$compiler->addFunction(
    'repeat',
    function (string $resolvedArgs, ?array $exprArgs) use ($compiler): string {
        $text  = $compiler->expression($exprArgs[0]['expr']);
        $times = $exprArgs[1]['expr']['value'] ?? '2'; // a literal written in the template

        return 'str_repeat(' . $text . ', ' . (int) $times . ')';
    }
);
// {{ repeat(name, 3) }}            →  <?= str_repeat($name, 3) ?>
```

### Common mistakes

| you write | compiled | why |
|---|---|---|
| `fn () => date('Y')` | `<?= 2026 ?>` | the closure ran at compile time and returned a value |
| `fn ($args) => 'Hello ' . $args` | `<?= Hello $name ?>` | not PHP; fails when the compiled file is loaded |
| `App\Html::bold(...)` (first-class callable) | `<?= <b>$name</b> ?>` | a first-class callable is a closure, so it is called as a code generator with `"$name"` |
| `{{ mony(total) }}` (typo) | `<?= $this->callMacro('mony', [$total]) ?>` | unknown names compile to a macro call and fail only when rendered |
| `{{ money('currency': 'EUR', 'amount': total) }}` | `<?= App\Money::format('currency' => 'EUR', 'amount' => $total) ?>` | `'name': value` is for macros; for functions it produces invalid PHP |

### Calling a service

The compiled template runs inside the Volt engine, so `$this` in the generated code is the engine.
The engine is injection-aware, which gives two ways to reach a service:

```php
$compiler->addFunction(
    'price',
    fn (string $args): string => '$this->getDI()->getShared("prices")->format(' . $args . ')'
);
// {{ price(total) }}  →  <?= $this->getDI()->getShared("prices")->format($total) ?>
```

Without registering anything, `service.method()` compiles to a property read on the engine when
`service` is registered in the container **at compile time**:

```twig
{{ prices.format(total) }}   {# → <?= $this->prices->format($total) ?> #}
```

The compiled code depends on the container's contents when the template was compiled. A view
variable with the same name as a service is shadowed in `name.method()` form.

### HTML returned by a function

With `autoescape` on, every `{{ … }}` is wrapped in `$this->escaper->html()`, including function
calls and escaping filters:

```php
// autoescape on
{{ badge(user) }}   →  <?= $this->escaper->html(badge($user)) ?>
{{ name|e }}        →  <?= $this->escaper->html($this->escaper->html($name)) ?>
```

There is no `raw` filter and no way to mark a function as returning safe HTML. To print HTML,
disable escaping around it:

```twig
{% autoescape false %}{{ badge(user) }}{% endautoescape %}
```

## Filters

Filters follow the same rules as functions. The filtered value is compiled and put first in
`$resolvedArgs`:

```php
$compiler->addFilter('money', 'App\Money::format');
// {{ total|money }}         →  <?= App\Money::format($total) ?>
// {{ total|money("USD") }}  →  <?= App\Money::format($total, 'USD') ?>

$compiler->addFilter(
    'money',
    fn (string $resolvedArgs, ?array $exprArgs): string => '\App\Money::format(' . $resolvedArgs . ')'
);
// {{ total|money("USD") }}: $resolvedArgs === "$total, 'USD'"
// {{ total|money }}:        $resolvedArgs === "$total", $exprArgs === null
```

## Tests

`{% if value is name %}` has no registration API. Built-in tests are `defined`, `empty`, `even`,
`odd`, `numeric`, `scalar`, `iterable`, `divisibleby(n)`, `sameas(x)` and `type(t)`.

Any other name compiles to a loose comparison with a variable of that name:

```twig
{% if user is premium %}   {# → <?php if ($user == $premium) { ?> #}
{% if value is null %}     {# → <?php if ($value == null) { ?>, true for 0, '' and [] #}
```

`is not` is read as `!=`, so it only works with the built-in tests that have their own syntax
(`is not defined`, `is not empty`, …). Use `!=` or `!(…)` with the others. To add a test, use the
`resolveExpression` hook of an extension (example below).

## Extensions

An extension is any object registered with `addExtension()`. The compiler calls the methods it
has, at compile time:

| method | called | return |
|---|---|---|
| `initialize(Compiler $compiler)` | once, by `addExtension()` | ignored; keep the compiler if you need it later |
| `compileFunction(string $name, string $resolvedArgs, ?array $exprArgs)` | for every function call, before `addFunction()` definitions and built-ins | PHP source to use it, anything else to let Volt continue |
| `compileFilter(string $name, string $resolvedArgs, ?array $exprArgs)` | for every filter, before `addFilter()` definitions and built-ins | same |
| `resolveExpression(array $expr)` | for every expression node | same |
| `compileStatement(array $statement)` | for every statement | the compiled statement, anything else to continue |

When several extensions are registered, the first one that returns a string wins.

A test, `is premium`:

```php
final class PremiumTest
{
    private Compiler $compiler;

    public function initialize(Compiler $compiler): void
    {
        $this->compiler = $compiler;
    }

    public function resolveExpression(array $expr)
    {
        // 311: "is" node, its right side is the identifier "premium"
        if ($expr['type'] === 311
            && $expr['right']['type'] === 265
            && $expr['right']['value'] === 'premium') {
            return '\App\Users::isPremium(' . $this->compiler->expression($expr['left']) . ')';
        }

        return null;
    }
}

$compiler->addExtension(new PremiumTest());
// {% if user is premium %}  →  <?php if (\App\Users::isPremium($user)) { ?>
```

### Node reference

`$exprArgs` and the hooks receive nodes as arrays with a `type`, `file` and `line`, plus:

| type | node | keys |
|---|---|---|
| 258 / 259 / 260 | integer / double / string literal | `value` |
| 261 / 262 / 263 | null / false / true | |
| 265 | identifier (variable or name) | `value` |
| 46 | `a.b` | `left`, `right` |
| 124 | `value\|filter` | `left`, `right` (an identifier, or a 350 node for a filter with arguments) |
| 350 | function call | `name` (a node), `arguments` (list of `['expr' => node]`, with `name` for `'name': value`) |
| 360 | array literal | `left` (list of `['expr' => node]`, with `name` for keys) |
| 311 | `a is b` | `left`, `right` |
| 273 | `a != b` and `a is not b` | `left`, `right` |
| 359 | `{{ … }}` statement | `expr` |

`$compiler->parse('{{ … }}')` prints the nodes of any template.

## Caching: when changes show up

| you change | recompiled with `stat => true` (default) | with `stat => false` |
|---|---|---|
| the template | yes, its mtime is newer | no |
| a template it `extends` or statically `include`s | **no**: parents and includes are copied into the compiled file | no |
| an `addFunction`/`addFilter` definition, an extension, `autoescape` | **no** | no |
| a service in the container (for `service.method()`) | **no** | no |

During development use `'always' => true`. After a deploy, delete the compiled files.

## Testing an extension

`compileString()` returns the generated PHP, which is the easiest thing to assert:

```php
$compiler = new Compiler();
$compiler->addFunction('money', 'App\Money::format');

assert($compiler->compileString('{{ money(1) }}') === '<?= App\Money::format(1) ?>');
```

Render through `View\Simple` to test the output.

---

## With the NFR (proposed, not in 5.x)

`volt-rfc.md` keeps everything above as the **compile-time** API and adds functions, filters and
tests that run at render time, with values:

```php
$volt->addFunction(new VoltFunction('price', ['prices', 'format']));            // service, resolved lazily
$volt->addFunction(new VoltFunction('badge', [Html::class, 'badge'], ['safe' => true]));
$volt->addFilter(new VoltFilter('money', Money::format(...)));
$volt->addTest(new VoltTest('premium', fn (User $u): bool => $u->isPremium()));
```

plus a `raw` filter, escaping filters that are not escaped again, named arguments, strict tests,
and recompilation when a parent, include, or the registry changes. See `examples.md` E5–E9.
