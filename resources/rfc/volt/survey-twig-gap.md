# Survey: Volt (Phalcon 5.23.0) vs Twig 3.x

Status: research input for the Volt NFR. Not a proposal.

## Sources and conventions

| Key | Meaning |
|---|---|
| **L** | `ext/phalcon/mvc/view/engine/volt/parser.php.lemon` (grammar) |
| **S** | `ext/phalcon/mvc/view/engine/volt/scanner.re` (lexer) |
| **B** | `ext/phalcon/mvc/view/engine/volt/base.c` (parser driver, hand-written C) |
| **H** | `ext/phalcon/mvc/view/engine/volt/scanner.h` (AST type constants) |
| **C** | `phalcon/Mvc/View/Engine/Volt/Compiler.zep` |
| **V** | `phalcon/Mvc/View/Engine/Volt.zep` |
| **probe** | Checked by running code, not just by reading it. The extension was built from this branch's `ext/` (`Version::get()` = `5.23.0`). Templates were compiled with `Compiler::compileString()` or rendered through `View\Simple`. Compiled output is quoted exactly. |
| **T/** | `https://twig.symfony.com/doc/3.x/`. Twig facts come from the 3.x branch CHANGELOG and the `doc/*.rst` files. The latest release is 3.30.0 (2026-09-25). |
| **PD** | Phalcon Volt docs, `https://docs.phalcon.io/latest/volt/`. The source is `phalcon/documentation` → `src/content/docs-5.23/volt.mdx`. |

Branch: `nfr-volt` (upstream master, 5.23.0). When the docs and the code disagree, the code is treated as correct.

---

## 1. Feature gap table

"Gap" rates real-world impact: **major** means it changes how you structure apps or causes bugs or security issues; **minor** means there is a workaround or it is rarely needed; **none** means parity; **bug** means Volt accepts the syntax but produces the wrong result.

### (a) Inheritance and reuse

| Feature | Twig | Volt (verified) | Gap | Notes |
|---|---|---|---|---|
| `extends` (static) | yes | yes. L:495. The parent is compiled and **inlined into the child** at compile time (C:2880-2916). It must be the first statement (B:765-772). | none | Because the parent is inlined, editing it can leave children stale. See (f). |
| `extends` dynamic / conditional / array fallback | yes ([T/tags/extends.html](https://twig.symfony.com/doc/3.x/tags/extends.html)) | **no**. The grammar accepts an `expr` (L:495), but the compiler only reads `path["value"]` (C:2884-2888). probe: `{% extends layout %}` gives `Template file …/views/layout does not exist`. A ternary or an array gives `Template file  does not exist` plus a PHP notice. | **major** | Per-request layouts (AJAX vs full page, themes, white-label sites) have to be handled at View level. |
| Nested blocks | yes | **no**. probe: `Embedding blocks into other blocks is not supported` (B:653-662). | **major** | Layouts can only have one level of overridable regions. |
| `block('name')`, `block('n','tpl')`, `block(..) is defined` | yes | **no**. `block` is a keyword (S:384). probe: `{{ block("title") }}` gives `Syntax error, unexpected token BLOCK`. | minor | Common use: printing a block twice, e.g. in `<title>` and `<h1>`. |
| `parent()` | yes | Called `super()` (C:1925-1962, echoed raw at C:663-668). probe: `parent()` compiles to `$this->callMacro('parent', [])`, which fails at runtime. | none | Only the name differs. |
| `use` (horizontal reuse) | yes, with `with a as b` | **no**. probe: syntax error. | minor | |
| `embed` | yes | **no**. probe: syntax error. | **major** | `embed` is how Twig does components: a card or modal with overridable slots. |
| `include` (static) | yes | yes. A string literal with no `with` is compiled and inlined (C:1023-1055). | none | |
| `include … with` | merges into the current context | Switches to a **runtime** `$this->partial(path, params)` (C:1061-1070). That merges with the *View's* params, not the current template's locals (`View::partial`, phalcon/Mvc/View.zep:586-591). probe: a `{% set local %}` variable was visible in a static include but `undef` in the same include with `with`. | **major** | Adding `with` silently changes the scope semantics. |
| `include … only` / `ignore missing` | yes | **no**. probe: syntax errors. | minor | |
| `include [a, b]` (first that exists) | yes | **no**. probe: compiles to `$this->partial(['a', 'b'])`, which fails at runtime. | minor | |
| `include()` function | yes (`with_context`, `ignore_missing`); `include_only()` since 3.29 | `partial()` instead (C:1918-1920). It runs at runtime and works across engines. No ignore-missing option. | minor | |
| `source()` | yes | **no**. probe: compiles to `$this->callMacro('source', ['x'])`. | minor | |
| Macros: define and call | yes | yes. A macro compiles to a closure stored in `$this->macros` (C:1080-1155). Named args use `'name': v` (C:1118-1123). | none | |
| Macros: `import` / `from` / `_self`, scoping | Imports are local to the template (works in its blocks and macros) | **no**. Macros live in a per-engine runtime registry. A macro exists only after the template that defines it has *executed*, so you must `include` that file first. Otherwise you get runtime `MacroNotFound` (V:61-70). probe: `[{{ hello("Bob") }}]` without the include gives `Macro 'hello' does not exist`. | **major** | No namespaces, behaviour depends on order, and two templates can clobber each other's macros at runtime. Duplicates are only detected within one file (C:1096-1098). |
| Macro default args | any expression | **literals only** (int, string, double, null, true, false; L:419-445). probe: `m(a = [])` is a syntax error. | minor | |
| Macro varargs | `...rest` (3.29); older `varargs` | **no** (probe). | minor | |
| `{% call %}…{% endcall %}` | not in Twig | Parsed (L:447-453), but `compileCall()` is `// Not implemented?` and returns `""` (C:568-572). probe: the body is **silently dropped**. | bug | |
| `set` block capture `{% set x %}…{% endset %}` | yes | **no**. probe: `unexpected token %}`. | minor | Often used. The workaround (a macro) is clumsy. |
| `with` tag scoping | yes (`with … only`) | **no**. `with` is only valid after `include` (L:503). | minor | |

### (b) Expressions

| Feature | Twig | Volt (verified) | Gap | Notes |
|---|---|---|---|---|
| `??` | yes | **no**. `QUESTION` only appears in the full ternary (L:731). probe: syntax error. | **major** | The only fallback is `\|default`, which uses `empty()` (C:2647-2650), so `0`, `"0"` and `false` are replaced too. |
| `?:` and `a ? b` (no else) | yes | **no** (probe). | minor | |
| Null-safe `?.` | 3.23 (short-circuits since 3.24) | **no**. probe: `unexpected token DOT`. | **major** | Needed for nullable relations, e.g. `invoice.customer?.name`. |
| `"#{expr}"` interpolation | yes | **no**. probe: `{{ "hello #{name}" }}` gives `<?= 'hello #{name}' ?>` (printed literally). | minor | |
| Arrow functions + `map` / `filter` / `reduce` / `sort(fn)` / `find` (3.11) / `invoke` (3.19) | yes | **no** arrow syntax and none of these filters. `sort` is a fixed `asort` (C:2690-2691, V:416). probe: `unexpected token ASSIGN`. | **major** | List shaping in templates ends up in controllers or macros. |
| Spread `...` | sequences/mappings 3.7, call args 3.15 | **no**. probe: `unexpected token RANGE`. | minor | |
| Named arguments | `f(name: v)` (3.12), `f(name=v)`; mapped to PHP parameter names | Only `f('name': v)` with a quoted key (L:795-797). It compiles to `'name' => v`. That works for macros, but for registered functions and filters it **emits invalid PHP**. probe: `App\Money::format('a' => $amount, 'c' => 'EUR')` is a ParseError when the compiled file is required. | **major** | Common in PHP 8 code. |
| Ranges `a..b` | yes; `range()` takes a step | `..` compiles to `range()` (L:587, C:1653-1655). No step. | none | |
| `in` / `not in` | yes | yes (L:687-693, V:150-169) | none | |
| `starts with` / `ends with` / `matches` | yes | **no** (probe) | minor | |
| `same as` / `===` | yes / 3.23 | `===` and `!==` (S:782-788); `sameas()` test (C:2256-2257) | none | |
| `is` test catalogue | defined, empty, even, odd, iterable, null/none, divisible by, same as, constant, sequence, mapping | defined, empty, even, odd, numeric, scalar, iterable (keyword tokens, L:595-649), plus `divisibleby()`, `sameas()`, `type()` (C:2253-2260). **No `null`, `none` or `constant`.** Any unknown test name **silently compiles to `==`** (C:2264-2267). probe: `a is null` gives `$a == null` (true for `0`, `''`, `[]`); `a is none` gives `$a == $none`; `a is constant("X")` gives `$a == constant('X')`. | **major** | Wrong results with no error. |
| `is not <fn-test>` | yes | **broken**. `is not` is lexed as the `!=` token (S:433-441). probe: `a is not divisibleby(3)` gives `$a != $this->callMacro('divisibleby', [3])`, and the same happens for `sameas`/`type`. | bug | |
| `**` | yes | yes, compiles to `pow()` (L:555, C:1543-1545) | none | |
| `//` floor division | yes | **wrong**: parsed as **modulo** (L:563-565 emits `PHVOLT_T_MOD`). probe: `{{ 7 // 2 }}` gives `<?= 7 % 2 ?>`, which is 1. | bug | |
| Bitwise `b-and` / `b-or` / `b-xor`, `xor` (3.15), `<=>`, `has some/every` (3.5) | yes | **no** (probe) | minor | |
| `.` attribute resolution | array key, then property, then `name()` / `getName()` / `isName()` / `hasName()`, then `__call` | Always compiles to `->` (C:275-283). probe: `user.name` on an array gives `Warning: Attempt to read property "name" on array`. Getters are never called; you must write `user['name']`. | **major** | Breaks with arrays, DTOs and read-models. Phalcon models only work because of `__get`. |
| Hash literal keys | `{a: 1}`, `{(expr): 1}` (any expression since 3.27), `{a}` shorthand | Quoted string keys only (L:763). probe: `[1: "a"]` and `{a: 1}` are syntax errors. | minor | PD's own Tests examples use `[1: 'Apple', …]` (volt.mdx:1085-1103), which does not parse. |
| Assignment in expressions / destructuring | `=` (3.23), `[a, b] = …` (3.23), renaming (3.24) | No. `set` does support `+= -= *= /=` and property or element targets (L:367-397). | minor | |

### (c) Output and escaping

| Feature | Twig | Volt (verified) | Gap | Notes |
|---|---|---|---|---|
| Autoescape strategies | `html`, `js`, `css`, `url`, `html_attr`, `html_attr_relaxed` (3.24); `name` picks a strategy from the file extension; callback; custom escapers via `EscaperRuntime::setEscaper()` (3.10) | One global boolean plus `{% autoescape true\|false %}` blocks (L:515-521, C:533-558). The strategy is **always** `$this->escaper->html()` (C:675-677). probe: `{% autoescape "js" %}` is a syntax error. | **major** | |
| Context filters vs autoescape | escaping filters mark their output safe, so it is not escaped twice | `e`, `escape_js`, `escape_css` and `escape_attr` exist (C:2651-2659), but autoescape **wraps them again**. probe: `{{ x\|e }}` gives `html(html($x))`; `{{ x\|escape_js }}` gives `html(js($x))`, which is wrong inside `<script>`; `{{ x\|e("js") }}` gives `html($x, 'js')`, silently using html. | **major** | |
| `is_safe` on functions/filters (`is_safe_callback`, `pre_escape`, `preserves_safety`) | yes | **no**. Every echoed expression except `super()` is wrapped (C:655-679). probe: a function returning `<b>…</b>` is escaped. | **major** | In practice teams turn autoescape off globally, which is an XSS risk. |
| `raw` filter | yes | **no** (built-in list at C:2640-2709). probe: `Unknown filter "raw"`. Registering your own `raw` filter does not help, because the whole echo is still wrapped. probe: `<?= $this->escaper->html($badge) ?>`. | **major** | |
| `apply` tag | yes | **no** (probe) | minor | |
| Sandbox | `SecurityPolicy`, `Sandbox` / `render_sandboxed()` (3.29); the `sandbox` tag is deprecated (3.15) | **no**. Compiled templates are plain PHP with full `$this` / DI access. Raw `<?php ?>` passes through untouched. | minor (major for user-editable templates) | CMS and email-template use cases. |

### (d) Whitespace control

| Feature | Twig | Volt (verified) | Gap | Notes |
|---|---|---|---|---|
| `-` modifiers | `{{- -}}`, `{%- -%}`, `{#- -#}` | `{{- -}}` and `{%- -%}` work (S:583-626). probe: `{#- -#}` is accepted but trims nothing. | minor | |
| `~` (trim but keep newlines) | yes | **no**. probe: `unexpected token ~`. | minor | |
| `spaceless` | the filter has been deprecated since 3.12 | no | none | |

### (e) Errors and debugging

| Feature | Twig | Volt (verified) | Gap | Notes |
|---|---|---|---|---|
| Template name + line in runtime errors | `RuntimeError` reports the template, line and (3.28) column via `getSourceContext()` / `getTemplateLine()` | **No mapping.** Exceptions point at the compiled cache file. probe: an error on template line 2, after an inlined 4-line include, was reported as `…%%views%%inh%%drift.volt.php:6`. Line drift also comes from inlined parents, macros and loop scaffolding. | **major** | The most visible day-to-day pain point. |
| Parse errors | `SyntaxError` with name, line and "did you mean" suggestions | Parse errors include file and line (`… in eval code on line 1`). Errors at end of file lose the line (`unexpected EOF in eval code`). | minor | |
| Unknown function | compile-time `SyntaxError` | **Silently compiles** to `$this->callMacro('name', …)` (C:2066-2069), which throws runtime `MacroNotFound`. probe: `{{ nosuchfn(1) }}` compiles fine. | **major** | Typos only show up when that code path runs. |
| Unknown filter | compile-time | compile-time `UnknownVoltFilter` with file and line (C:2709) | none | |
| `strict_variables` | yes | **no**. probe: an undefined variable produces PHP `Warning: Undefined variable $nope` and empty output. | minor | |
| `dump()` | `DebugExtension`; only active in debug mode | `dump()` compiles to `var_dump()` and is always on (C:2047-2049) | none | |
| Deprecations (`deprecated` tag, `deprecation_info`) | yes | **no** | minor | |

### (f) Loading and caching

| Feature | Twig | Volt (verified) | Gap | Notes |
|---|---|---|---|---|
| Loader abstraction | `LoaderInterface` (`getSourceContext`, `getCacheKey`, `isFresh`, `exists`); `FilesystemLoader` with `@ns/` namespaces; `ArrayLoader`; `ChainLoader`; custom loaders (DB) | **None.** Path resolution is hard-coded: views dir(s) → absolute → `./` / `../` (C:2478-2518). Templates must be files. | **major** | Affects modules, themes, packages, and CMS/DB templates. |
| String templates | `template_from_string()`, `createTemplate()`, `ArrayLoader` | `compileString()` returns PHP source (C:1310-1315). Rendering it means writing your own eval or temp file. | minor | |
| Auto-reload | `auto_reload`; `isFresh()` per template. Parents and includes are separate compiled classes, so each one is checked. | `stat` compares only the rendered template against its own compiled file (C:470-481). Parents and static includes are **inlined**, so editing them does not recompile children unless `always` is set. PD admits this: "Volt only checks for changes in the children templates" ([PD#multiple-inheritance](https://docs.phalcon.io/latest/volt/#multiple-inheritance), volt.mdx:1524). | **major** | |
| Cache key / invalidation | loader key + options hash (extension-set signature, Twig version, PHP major.minor, `debug`, `strict_variables`, `use_yield`) | Only a filename derived from the path (C:404-436). Changing `addFunction` / `addFilter` definitions, extensions, `autoescape`, or **DI contents** does **not** invalidate the cache, even though the compiled output depends on them (C:258-259, 2007-2023, 2677-2681). PD: "Every time you deploy … delete the pre-compiled `.volt` files" ([PD#compiling](https://docs.phalcon.io/latest/volt/#compiling)). | **major** | Leads to "my function change does nothing" during development. |
| Cache backends | `FilesystemCache`, `ChainCache`, `ReadOnlyFilesystemCache` (3.11) | filesystem `path` (string or closure, C:404-454) | minor | Both can be pre-compiled at deploy time. |

### (g) Extensibility

| Feature | Twig | Volt (verified) | Gap | Notes |
|---|---|---|---|---|
| Function registration | `new TwigFunction(name, callable, options)`; extension `getFunctions()`; `#[AsTwigFunction]` (3.21) | `addFunction(name, string\|Closure)` (C:218-223). A **string** is pasted into the source as `name(args)` (C:1886-1888). A **Closure is called at compile time** with `($resolvedArgs, $exprArgs)` and must return PHP source (C:1894-1900). Anything else throws `InvalidUserFunctionDefinition` (C:1903). probe: `[Money::class,'format']` and invokable objects throw; `Money::format(...)` (first-class callable, which *is* a Closure) gets called at compile time and emits `<?= $amount, 'EUR' Array ?>`. | **major** | See §2. |
| Filter registration | `TwigFilter` | `addFilter` has the same contract. The left operand is prepended to `$resolvedArgs`, except for `default` (C:2558-2587, 2614-2638). | **major** | |
| Test registration | `TwigTest` | **No API** (no `addTest`). Only possible by intercepting the AST in `resolveExpression`. PD still says "functions, tests, or filters". | **major** | |
| Runtime vs compile time | Callables run at render time. Compile-time hooks are opt-in (`node_class`, token parsers, visitors). | **Everything is compile-time code generation.** No runtime-callable concept. | **major** | This is the core DX complaint. |
| `needs_environment` / `needs_context` / `needs_charset` / `is_variadic` | yes | **none**. A closure can emit `$this` (the engine) or `get_defined_vars()` into the generated code by hand. | **major** | |
| Runtime loaders (lazy services) | `RuntimeLoaderInterface`, `FactoryRuntimeLoader`, `ContainerRuntimeLoader` (PSR-11) | No concept. You emit `$this->getDI()->getShared('svc')->m(…)` or rely on `Injectable::__get` (`$this->svc`). This works because the compiled file is `require`d inside `Volt::render()` (V:303). Undocumented. | minor | It works, but it is folklore. |
| Globals | `addGlobal()`, `GlobalsInterface` | Every DI service becomes an implicit global, decided at **compile time**, when used with `.` (C:258-259): `{{ session.get('x') }}` compiles to `$this->session->get('x')`. A view variable named like a service is shadowed in `a.b` form but not in `{{ a }}` form (C:1617-1619). | none (different) | Gotcha: the compiled output depends on DI contents. |
| Node visitors | yes | No AST pass. There are only per-node hooks, `compileFunction`, `compileFilter`, `resolveExpression` and `compileStatement`, plus an undocumented `initialize($compiler)` (C:186-188). The first extension that returns a string wins (C:1791-1820). | minor | |
| Custom tags | `TokenParser` + `Node` | **Impossible.** The grammar is compiled C (L:198-283), so an unknown tag is a syntax error. Existing statement types can only be overridden via `compileStatement`. | **major** | See §2(f) for the `call` hijack. |
| Custom operators | `getExpressionParsers()` (3.21) | no. `resolveExpression` can only remap existing node types. | minor | |
| `guard` (3.15), `types` (3.13), `deprecation_info` (3.15), `#[AsTwig*]` (3.21) | yes | no | minor | |

---

## 2. Declaring a function or filter, side by side

The examples use `{{ money(amount, 'EUR') }}` throughout. Every Volt "compiles to" line is probe output.

**How Volt works:** a Volt function is a *code generator*, not a callable. At compile time Volt gives you two things:

- `$resolvedArgs`: the arguments **already compiled to a string of PHP source** (`"$amount, 'EUR'"`).
- `$exprArgs`: the **parser AST** of the arguments.

You return **PHP source as a string**. That string is written into the cached compiled template and never re-evaluated until the cache is cleared.

### (a) Function mapping to a PHP callable

**Twig**
```php
final class MoneyExtension extends \Twig\Extension\AbstractExtension
{
    public function getFunctions(): array
    {
        return [new \Twig\TwigFunction('money', [Money::class, 'format'])]; // any callable
    }
}
$twig->addExtension(new MoneyExtension());
// one-off: $twig->addFunction(new TwigFunction('money', Money::format(...)));
// 3.21+:   #[AsTwigFunction('money')] on a static method + new AttributeExtension(Money::class)
```
```twig
{{ money(amount, 'EUR') }}   {{ money(currency: 'EUR', amount: amount) }}
```

**Volt**
```php
$compiler = $volt->getCompiler();
$compiler->addFunction('money', 'App\Money::format');     // the string is pasted into PHP source
// {{ money(amount, "EUR") }}  ->  <?= App\Money::format($amount, 'EUR') ?>

// Closure form: runs ONCE, at compile time, and returns PHP source
$compiler->addFunction('money', function (string $resolvedArgs, ?array $exprArgs): string {
    // $resolvedArgs === "$amount, 'EUR'"
    // $exprArgs     === [['expr' => ['type' => 265, 'value' => 'amount', 'file' => …, 'line' => 1], …],
    //                    ['expr' => ['type' => 260, 'value' => 'EUR', …], …]]
    return '\App\Money::format(' . $resolvedArgs . ')';
});
```

What goes wrong in Volt (all probed):

| You write | Result |
|---|---|
| `addFunction('money', [Money::class, 'format'])` | `InvalidUserFunctionDefinition` (C:1903) |
| `addFunction('money', new MoneyFormatter())` (invokable) | `InvalidUserFunctionDefinition` |
| `addFunction('money', Money::format(...))` | Treated as a code generator and **called at compile time**. Emits `<?= $amount, 'EUR' Array ?>`. |
| `{{ money('currency': 'EUR', 'amount': amount) }}` | Emits `App\Money::format('a' => $amount, 'c' => 'EUR')`, which is a PHP ParseError at render time. |
| `{{ mony(amount) }}` (typo) | Compiles to `$this->callMacro('mony', …)`; the error only appears at runtime (C:2069). |

### (b) Function that needs a DI or runtime service

**Twig:** the runtime is created lazily at render time. Compiling never touches the container.
```php
final class MoneyRuntime implements \Twig\Extension\RuntimeExtensionInterface
{
    public function __construct(private CurrencyConverter $fx) {}
    public function format(float $amount, string $currency): string { /* … */ }
}
// in MoneyExtension::getFunctions():
new TwigFunction('money', [MoneyRuntime::class, 'format']);
// wiring:
$twig->addRuntimeLoader(new \Twig\RuntimeLoader\ContainerRuntimeLoader($psr11));
// or new FactoryRuntimeLoader([MoneyRuntime::class => fn () => new MoneyRuntime($fx)])
```

**Volt:** emit code that reaches the container through `$this`.
```php
$compiler->addFunction('money', fn (string $args): string =>
    '$this->getDI()->getShared("money")->format(' . $args . ')');
// -> <?= $this->getDI()->getShared("money")->format($amount, 'EUR') ?>
```
- This works because the compiled template is `require`d inside `Volt::render()` (V:303), so `$this` is the engine, and the engine is `Injectable`. This is not documented anywhere.
- An idiom that needs no registration at all: `{{ money.format(amount, 'EUR') }}` compiles to `$this->money->format(...)`, as long as `money` is a DI service **at compile time** (C:258-259). This is lazy and arguably nicer than Twig, but it couples the compiled output to the DI contents (see §1f).

### (c) Function returning HTML that must not be double-escaped

**Twig**
```php
new TwigFunction('badge', [Html::class, 'badge'], ['is_safe' => ['html']]);
```
```twig
{{ badge(user) }}          {# not escaped #}
{{ '<' ~ badge(user) }}    {# the concatenation is escaped as a whole, which is correct #}
```

**Volt:** there is no way to declare safety. With `autoescape => true`:
```php
$compiler->addFunction('badge', fn ($a) => '\App\Html::badge(' . $a . ')');
// {{ badge(user) }}  ->  <?= $this->escaper->html(\App\Html::badge($user)) ?>    (double-escaped)
```

Workarounds:

1. Wrap each call site in `{% autoescape false %}…{% endautoescape %}`.
2. Turn autoescape off globally. This is common, and it is the XSS risk.
3. Use a `compileStatement` hack (probed). It only covers a bare `{{ badge(...) }}`. Inside a larger expression the call falls through to `callMacro`, so you must *also* `addFunction` it.

```php
final class SafeHtmlFunctions
{
    private const SAFE = ['badge' => '\App\Html::badge'];
    private Compiler $compiler;
    public function initialize(Compiler $compiler): void { $this->compiler = $compiler; } // undocumented hook
    public function compileStatement(array $statement)
    {
        $expr = $statement['expr'] ?? null;
        if ($statement['type'] === 359                       // PHVOLT_T_ECHO   (H:124)
            && ($expr['type'] ?? null) === 350               // PHVOLT_T_FCALL  (H:118)
            && isset(self::SAFE[$expr['name']['value'] ?? ''])) {
            $args = isset($expr['arguments']) ? $this->compiler->expression($expr['arguments']) : '';
            return '<?= ' . self::SAFE[$expr['name']['value']] . '(' . $args . ') ?>';
        }
        return null;                                         // fall back to Volt
    }
}
// {{ badge(user.name) }} -> <?= \App\Html::badge($user->name) ?>
```

### (d) Filter with extra arguments

**Twig**
```php
new TwigFilter('money', [Money::class, 'format']);  // {{ amount|money('EUR') }} -> format($amount, 'EUR')
```

**Volt:** this is the case where Volt does fine.
```php
$compiler->addFilter('money', 'App\Money::format');
// {{ amount|money("EUR") }} -> <?= App\Money::format($amount, 'EUR') ?>

$compiler->addFilter('money', fn (string $resolvedArgs, ?array $exprArgs) =>
    '\App\Money::format(' . $resolvedArgs . ')');
// $resolvedArgs === "$amount, 'EUR'"   (the left operand is prepended; C:2569-2584)
// {{ amount|money }}: $resolvedArgs === "$amount", $exprArgs === null
```
Undocumented quirk: for a filter named `default`, the left operand is *not* prepended (C:2562).

### (e) Custom test: `is premium`

**Twig**
```php
new TwigTest('premium', fn (User $u): bool => $u->isPremium());
// {% if user is premium %}   {% if user is not premium %}   (negation is free)
```

**Volt:** there is no API, and the failure is silent. `{% if user is premium %}` compiles to `<?php if ($user == $premium) { ?>` (C:2267).

The workaround intercepts the AST (probed). You must handle `is` (311) **and** `is not`, which is the `!=` node (273), separately.
```php
final class PremiumTest
{
    private Compiler $compiler;
    public function initialize(Compiler $compiler): void { $this->compiler = $compiler; }
    public function resolveExpression(array $expr)
    {
        $type = $expr['type'] ?? null;                         // 311 = IS (H:93), 273 = NOTEQUALS
        if (($type === 311 || $type === 273)
            && ($expr['right']['type'] ?? null) === 265        // IDENTIFIER (H:37)
            && $expr['right']['value'] === 'premium') {
            $code = '\App\Users::isPremium(' . $this->compiler->expression($expr['left']) . ')';
            return $type === 273 ? '!' . $code : $code;
        }
        return null;
    }
}
$compiler->addExtension(new PremiumTest());
// -> <?php if (\App\Users::isPremium($user)) { ?> … <?php if (!\App\Users::isPremium($user)) { ?>
```
A side effect: this extension also captures `user != premium`, which is a real comparison with a variable named `premium`. The two cannot be told apart in the AST.

### (f) Custom tag: `{% fragment 'sidebar' 60 %}…{% endfragment %}`

**Twig:** a `TokenParser` plus a `Node`. The docs call tags "the most complex extension point" and say to prefer functions or filters. For this exact case, `twig/cache-extra` already ships `{% cache 'sidebar' ttl(60) %}`.
```php
final class FragmentTokenParser extends \Twig\TokenParser\AbstractTokenParser
{
    public function parse(\Twig\Token $token): \Twig\Node\Node
    {
        $stream = $this->parser->getStream();
        $key = $this->parser->parseExpression();
        $ttl = $this->parser->parseExpression();
        $stream->expect(\Twig\Token::BLOCK_END_TYPE);
        $body = $this->parser->subparse(fn (\Twig\Token $t) => $t->test('endfragment'), true);
        $stream->expect(\Twig\Token::BLOCK_END_TYPE);
        return new FragmentNode($key, $ttl, $body, $token->getLine());
    }
    public function getTag(): string { return 'fragment'; }
}
// FragmentNode::compile(Compiler $c) emits PHP via $c->write()/subcompile()  (~30 lines, #[YieldReady])
$twig->addTokenParser(new FragmentTokenParser());
```

**Volt:** this **cannot be done.** The tag set is fixed in the C grammar (L:198-283), and `{% fragment %}` is a syntax error (probe). The only escape hatch is to hijack the parsed-but-unimplemented `{% call name(args) %}…{% endcall %}` (L:447-453, C:568-572) through `compileStatement`. Compiling the body then needs the **protected** `statementList()`, so it has to be smuggled through the public `compileIf()` (probed).
```php
final class FragmentCacheTag
{
    private Compiler $compiler;
    public function initialize(Compiler $compiler): void { $this->compiler = $compiler; }
    public function compileStatement(array $statement)
    {
        if ($statement['type'] !== 325 || $statement['name']['value'] !== 'cache_fragment') { // PHVOLT_T_CALL
            return null;
        }
        $args = $this->compiler->expression($statement['arguments']);          // "'sidebar', 60"
        $body = $this->compiler->compileIf([
            'expr' => ['type' => 263 /* PHVOLT_T_TRUE */],
            'true_statements' => $statement['caller'],
        ]);
        return '<?php if (!$this->fragments->start(' . $args . ')) { ?>' . $body
             . '<?php $this->fragments->end(); } ?>';
    }
}
// {% call cache_fragment("sidebar", 60) %}<b>{{ x }}</b>{% endcall %} ->
// <?php if (!$this->fragments->start('sidebar', 60)) { ?><?php if (true) { ?><b><?= $x ?></b><?php } ?><?php $this->fragments->end(); } ?>
```

### Summary of the declaration contract

| | Twig | Volt |
|---|---|---|
| What you register | a PHP callable (any form) | a PHP function-name string, or a Closure that **generates PHP source** |
| When your code runs | at render time, on every call | at compile time, once; the output is frozen in the cache |
| Arguments you receive | values | `$resolvedArgs` (a PHP source string) and `$exprArgs` (AST arrays with magic `type` ints from `scanner.h`) |
| Named args, variadics | yes, mapped to parameters | no (emits invalid PHP) |
| Escaping metadata | `is_safe`, `pre_escape`, `preserves_safety` | none |
| Context / env / charset injection | `needs_*` options | hand-written `$this->…` in the generated string |
| Lazy services | runtime loaders | `$this->getDI()` in the generated string (undocumented) |
| Tests | `TwigTest` | `resolveExpression` AST hack |
| Tags | `TokenParser` | impossible (only `call` hijack) |
| Cache invalidation when the definition changes | automatic (extension signature in the options hash) | manual (clear the compiled dir) |

---

## 3. Docs review: Phalcon "Extending Volt" vs Twig "Extending Twig"

What Twig's page ([T/advanced.html](https://twig.symfony.com/doc/3.x/advanced.html)) does:

- **It explains which extension point to pick**, e.g. "In fact, you rarely need to create tags; and that's good news because tags are the most complex extension point." ([#extending-twig](https://twig.symfony.com/doc/3.x/advanced.html#extending-twig)) and "If your tag generates some output, use a **function** instead." ([#tags](https://twig.symfony.com/doc/3.x/advanced.html#tags))
- **It separates definition from runtime**: "not recommended as it makes template compilation depend on runtime dependencies even if they are not needed" ([#definition-vs-runtime](https://twig.symfony.com/doc/3.x/advanced.html#definition-vs-runtime)), followed by the `RuntimeLoaderInterface` / `ContainerRuntimeLoader` recipe.
- **It documents every option**: `is_safe`, `needs_*`, `is_variadic`, `deprecation_info`, dynamic names, and the PHP attributes ("If all the methods are static … the class attributes will be scanned only when a template is compiled.").
- **It explains how to test extensions**: `IntegrationTestCase`.

What the Phalcon page ([PD#extending-volt](https://docs.phalcon.io/latest/volt/#extending-volt)) says, and what is wrong or missing:

| # | PD says | Problem (code wins) |
|---|---|---|
| 1 | "Unlike other template engines, Volt itself is not required to run the compiled templates. Once the templates are compiled there is no dependence on Volt." (volt.mdx:1580) | Misleading. The compiled code calls back into the engine and DI: `$this->callMacro` (C:2069), `$this->escaper->html` (C:676), `$this->isIncluded` (C:1749), `$this->slice` (C:1689), `$this->length` (C:2674), `$this->partial` (C:1919), `$this->getContent()` (C:1911). |
| 2 | "The Volt compiler allows you to extend it by adding more functions, tests, or filters" (:1582) | There is **no test API.** Tests can only be added through an undocumented AST hack (§2e). Unknown tests silently become `==`. |
| 3 | "Functions can be added using two options, returning a simple string or using an anonymous function. Whichever option you use, you must return a valid PHP string expression." ([PD#functions](https://docs.phalcon.io/latest/volt/#functions), :1586) | Never says **when** the closure runs: once, at compile time, with the result frozen in the cache. "Returning a simple string" is wrong: you *pass* a PHP function name. It does not say that array callables or invokables are rejected, or that `Foo::bar(...)` closures get executed as code generators. |
| 4 | "Here we use `$resolvedArgs` to pass the arguments exactly when calling the method from the view" (:1608) | It never says `$resolvedArgs` is a **string of compiled PHP** (`"$amount, 'EUR'"`), or that `$exprArgs` is the parser AST. The AST shape and the `type` integers (265 identifier, 260 string, 350 fcall, …) are only defined in `scanner.h`. `$compiler->expression($exprArgs[0]['expr'])` appears in an example (:1627) with no explanation. |
| 5 | The `contains_text` example uses `function_exists('mb_stripos')` inside the closure | Presented as a runtime check, but it is evaluated **at compile time**. A CLI pre-compile with different extensions bakes in the wrong branch. Nothing warns about this. |
| 6 | "Adding new filters is similar to the functions." | Missing: the left operand is prepended to `$resolvedArgs`, `$exprArgs` is `null` when there are no args, and `default` is special-cased (C:2558-2587). |
| 7 | Extensions: `compileFunction(string $name, string $arguments)` (2-param example); "Events in extensions must return valid PHP code…" (:1734) | A third `$exprArgs` argument is passed (C:1866-1869, 2599-2602). The `initialize(Compiler)` hook (C:186-188) is not documented. It does not say that the first extension returning a string wins and later ones are skipped (C:1797-1817). `resolveExpression` / `compileStatement` get one-line descriptions ([PD#events](https://docs.phalcon.io/latest/volt/#events), :2117-2120) and no node reference. |
| 8 | Nothing on escaping returned HTML | Missing: under `autoescape` every function result is escaped, there is no `raw` and no `is_safe`, and `\|e` / `\|escape_js` get double-escaped. The [Autoescape](https://docs.phalcon.io/latest/volt/#autoescape-mode) section is a 10-line example. |
| 9 | "Any registered service in the DI container is available in volt, with a variable having the same name…" ([PD#services](https://docs.phalcon.io/latest/volt/#services), :2124) | It does not say that this is decided **at compile time**, that it only applies to `a.b` access (it shadows view variables), or how a *function* should reach a service (`$this->getDI()` in the generated code). There is no runtime-function story at all. |
| 10 | "Every time you deploy … delete the pre-compiled `.volt` files" ([PD#compiling](https://docs.phalcon.io/latest/volt/#compiling), :2180) | It does not connect this to development: with `stat => true`, changing an `addFunction`/extension definition, `autoescape`, DI services, a parent template or a static include does **not** trigger a recompile. Only `always => true` does. |
| 11 | Compiler API: `compileCache` "(DEPRECATED)"; `compileCall` "Compiles calls to macros" (:1828-1842) | `{% cache %}` is **removed**: it parses, then compiling throws `Unknown statement 314` (C:2988-2989, probe). `compileCall` is a stub returning `""` (C:568-572). |
| 12 | The Tests examples use `[1: 'Apple', 2: 'Banana', …]` (:1085-1103) | Syntax error: hash keys must be quoted strings (L:763, probe). |
| 13 | (absent) | Undocumented: named-arg rules (`'name': v` only works for macros), the `.` → `->` rule (no array or getter resolution), `is not` + function tests being broken, and `//` meaning modulo. |

Overall, the page is mostly a copy of the Compiler's public method list (:1748-2110). The part a user needs, a mental model ("a Volt function is a compile-time code generator"), is never stated.

---

## 4. What Volt does that Twig does not

| Volt feature | Evidence | Twig |
|---|---|---|
| Lexer and parser in C (re2c + lemon), so compiling is fast | S, L | Pure PHP lexer and parser. After warm-up both execute cached PHP. No benchmark was run for this survey. |
| Leaner compiled code: `a.b` compiles straight to `$a->b`, and the loop context is generated only when `loop` is used (C:845-859) | probe | `CoreExtension::getAttribute()` runtime call for `.`; the flip side of Twig's flexible attribute lookup |
| `switch` / `case` / `default` | L:336-353, C:1324-1377 | no `switch` |
| `break` / `continue` | L:523-529, C:2939-2951 | none |
| `for … if cond` | L:323-334, C:784+ | removed in 3.0 |
| Compound assignment `+= -= *= /=`, `++` / `--`, assigning to properties and elements (`set a.b = 1`, `set a['k'] = v`) | L:367-397, L:699-705, probe `<?php $a->b = 1; ?>` | `=` only (3.23); names and destructuring only |
| Macros that return values (`{% return %}`) | L:511-513, C:1164-1179 | macros return rendered output only |
| Direct DI service access with no registration (`{{ flash.output() }}`, `{{ security.getToken() }}`) | C:258-259, PD#services | needs globals or functions |
| Built-in TagFactory / `Tag` helpers, `url()`, `static_url()`, `preload()` | C:1964-2037 | needs extensions (Symfony bridge) |
| `partial()`: runtime include of *any* engine's template (`.phtml`); `content()` for the View hierarchy | C:1907-1920 | Twig templates only |
| Extra tests: `numeric`, `scalar`, `type('…')` | C:2236-2239, 2258-2259 | none of these |
| Raw PHP passes through templates (escape hatch) | PD#usage, "The view files can also contain PHP and HTML" | no; sandboxable instead |
| `{% verbatim %}` | L:487-493 | parity |
| `{% cache %}` | **not available**: parses (L:471-485), but compiling throws `Unknown statement 314` | Twig has it (`twig/cache-extra`, 3.2) |
| Pre-compile at deploy, read-only cache dir | PD#compiling | parity (`ReadOnlyFilesystemCache`, 3.11) |

---

## Appendix: probe matrix (compile only, 5.23.0)

The output is abbreviated; the source of each case is shown with it.

```
{{ a ?? "x" }}                 ERR Syntax error, unexpected token QUESTION MARK
{{ a?.b }}                     ERR unexpected token DOT
{{ items|map(i => i.x) }}      ERR unexpected token ASSIGN
{{ [...a, 1] }}                ERR unexpected token RANGE
{{ strtoupper(s: "abc") }}     ERR unexpected token COLON
{{ 7 // 2 }}                   OK  <?= 7 % 2 ?>
{{ a is null }}                OK  <?= $a == null ?>
{{ user is premium }}          OK  <?= $user == $premium ?>
{{ a is not divisibleby(3) }}  OK  <?= $a != $this->callMacro('divisibleby', [3]) ?>
{% set h = [1: "a"] %}         ERR unexpected token COLON
{{ x|raw }}                    ERR Unknown filter "raw"
{{ nosuchfn(1) }}              OK  <?= $this->callMacro('nosuchfn', [1]) ?>
{% cache "k" 60 %}x{% endcache %}   ERR Unknown statement 314
{% call m(1) %}x{% endcall %}       OK  (empty string)
{% set x %}abc{% endset %}     ERR unexpected token %}
{% embed / use / import / from / apply / sandbox / with %}  ERR syntax error
{% include "x" only %} / ignore missing                     ERR syntax error
{% include ["a","b"] %}        OK  <?php $this->partial(['a', 'b']); ?>
{% extends layout %}           ERR Template file layout does not exist
{% macro m(a = []) %}          ERR unexpected token [
a {{~ x ~}} b                  ERR unexpected token ~
{% autoescape "js" %}          ERR unexpected token STRING(js)
autoescape on: {{ x|e }}       OK  <?= $this->escaper->html($this->escaper->html($x)) ?>
{{ user.name }}                OK  <?= $user->name ?>   (array -> "Attempt to read property on array")
nested {% block %}             ERR Embedding blocks into other blocks is not supported
```
