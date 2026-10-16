# [NFR] v7 Volt: resolve inheritance on the AST (nested blocks, `block()`, `embed`, dynamic `extends`), add runtime functions/filters/tests, track what a compiled template depends on

Status: DRAFT for discussion. Target: v7, on top of current master (5.23.0), which has all the
2026 Volt work (verbatim, multi-path, #17294, CP-17668). One milestone (M0) fits 5.x.
Related: #17145 (nested blocks, 2013), #17271 (extends from a variable), #17368 (include
extension), #17053 (Tag → TagFactory + `TagTranslator`), #14608 (vote list), phalcon#274 (pass a
Compiler to the engine), #17652 / PR #17670 (trailing comma), #17425 (`->`).
Evidence:
- a PHP prototype over the built extension (`prototype/`), with a 232-line parser patch built into
  a second extension;
- 38 tests that pin today's behaviour on the stock build and 122 tests for the prototype on the
  patched build;
- all 50 templates of the upstream Volt fixtures compile **byte-identical** with the prototype;
- the upstream Volt suite passes on the patched parser (633/635; the 2 failures are an intended
  change);
- ten before/after examples with captured output (`examples.md`) and a reading guide
  (`walkthrough.md`);
- surveys of the issue history, the implementation and the Twig gap (`survey-*.md`);
- a rewritten "Extending Volt" docs page for today's API (`docs-extending-volt.md`).

## Problem

**1. Inheritance has one flat level.** A block inside a block, or inside `if`/`for`, is refused by
the parser:

```
{% block body %}<main>{% block content %}{% endblock %}</main>{% endblock %}
→ Embedding blocks into other blocks is not supported
```

This is #17145, opened in 2013 for the exact case of a.volt extends b.volt extends c.volt: "Otherwise
there's no profit to use inheritance more than one nesting level." With 22 👍 it is the most-voted
entry on #14608. It has 71 comments from 40 users, and six of them say they moved to Twig or Smarty
over it. It was scheduled for 2.0, 2.1, 4.0, 4.1 and 6.0, and is now labelled 7.0. The same model
also rules out:
- printing a block twice, as in `<title>` and `<h1>`: `{{ block("title") }}` is a syntax error;
- `{% extends layoutVar %}` (#17271). The variable name is used as a file name; niden: "needs a
  refactor in the compiler";
- components with overridable parts (Twig's `embed`).

The root cause is how inheritance works today (`walkthrough.md` §1). The parent is compiled into a
serialized name → piece map, and the child's compiled blocks are spliced into it. There is one
level of names and one `currentBlock`, and `base.c` refuses nesting before the compiler is reached.

**2. Declaring a function means writing a code generator.** A closure given to `addFunction()` runs
once, at compile time, receives the arguments as PHP source and must return PHP source, which is
frozen into the cache (`examples.md` E5):

```php
$compiler->addFunction('year', fn () => date('Y'));             // {{ year() }} → <?= 2026 ?>
$compiler->addFunction('greeting', fn ($args) => 'Hello ' . $args); // → <?= Hello $name ?>, a ParseError later
```

The same model shows up in many places:
- array callables and invokable objects are rejected;
- a first-class callable is called as a code generator;
- `'name': value` arguments produce invalid PHP for functions;
- an unknown function compiles to a runtime `callMacro()` that fails only when rendered;
- there is no test API, and an unknown test silently compiles to `==`, so `value is null` is true for
  `0`, `''` and `[]`;
- `is not` is lexed as `!=`, so negating a function test breaks;
- nothing can mark a function's output as HTML, so autoescape escapes it. Escaping filters get
  wrapped again (`|e` → `html(html($x))`, `|escape_js` → `html(js($x))`), and there is no `raw`.
  In practice teams turn autoescape off.

The docs say "you must return a valid PHP string expression" without explaining the compile-time
model. Users have been tripping on it since 2013 (#1239, #2810, #1176, #697, #1907, D#15527:
"the documentation is shallow").

**3. The cache does not know what was inlined into a template.** Parents and static includes are
copied into the compiled child, but `stat` compares only the child's own mtime. Editing a layout or
a partial changes nothing until the cache is cleared (`examples.md` E9). The docs admit it: "Volt
only checks for changes in the children templates". Changing a function definition, an extension
or `autoescape` is not picked up either.

**4. Everyday expressions are missing:**
- `??`: `|default` uses `empty()`, so `0` is replaced too;
- `?.` for nullable relations;
- `{% set x %}…{% endset %}`;
- `include … with` silently switches to a runtime partial that no longer sees the template's
  variables (`examples.md` E10).

`survey-twig-gap.md` has the full comparison with Twig 3.x. This NFR takes the items with the
biggest impact that fit Volt's design. The rest is under "Later".

## Why change the architecture instead of patching it

- **Nesting cannot be patched into the splice model.** It needs the chain resolved structurally.
  Doing that on the AST, before compiling, turns out to be the simpler model. The resolver
  (`prototype/src/Inheritance/Resolver.php`) loads the chain, collects blocks by name at any depth,
  and expands the root: a block node becomes its most derived definition, and `super()` becomes the
  next one up. The stock `statementList()` compiles the flat result unchanged. All 50 upstream
  fixture templates compile byte-identical, the `%%e%%` cache files go away, and `block()`, `embed`
  and dynamic `extends` fall out of the same expansion.
- **Compile-time code generation is a good advanced hook but the wrong default.** What people
  expect, from Twig and from PHP in general, is "register a callable". Making render-time callables
  the main path also brings the `safe` flag, named arguments and tests. It costs nothing where today
  is already fast: a function name or static method still compiles to the same direct call.
  `./run.sh bench`, 200k calls, clean PHP with JIT:

  | how the function is declared | compiled to | ns per call |
  |---|---|---|
  | today, `addFunction('fmt', 'number_format')` | `number_format($i)` | ~85 |
  | proposed, static callable | `\number_format($i)` | ~85 |
  | proposed, closure or `[service, method]` | `($this->runtime['function:fmt'] ??= …)($i)` | ~265 |
  | today's idiom for a service, `$this->getDI()->getShared("x")->fmt(…)` | as written | ~390 |

- **Three implementations.** Volt exists as the C scanner/parser, the Zephir compiler and the PHP
  port `phalcon/volt`, which is kept in sync ("Sync verbatim logic from cphalcon"). Every grammar
  change is paid three times. This proposal keeps grammar changes small: one 232-line patch over
  five hand-written C files, and the expansion handles nested blocks, block() and dynamic extends
  without new syntax. The runtime registry needs no grammar at all.
- **The v7 window.** #17271 and #17368 were deferred to v7 because they need compiler and interface
  changes. #17652 was deferred as "a parser fix and there are a few lined up there". phalcon#274
  says the engine/compiler constructor will change before v7. This NFR is that compiler change,
  done once.

## Proposed approach

### 1. Inheritance resolved on the AST

`Compiler::compileSource()` resolves the chain before compiling (`walkthrough.md` §3):

| feature | behaviour |
|---|---|
| nested blocks | any depth; a child overrides any block by name; `super()` works at every level |
| blocks in `if`/`for`/`switch` | allowed; as in Twig, the block is always defined, and the condition controls where it renders |
| `{{ block("name") }}` | prints the most derived definition again; `block` stays a statement keyword only right after `{%` (the way `default` already is) |
| `{% embed "card.volt" with [...] %}{% block body %}…{% endblock %}{% endembed %}` | the body is an anonymous child of `card.volt`, resolved on its own and inlined in a scope of its own (`examples.md` E4) |
| `{% extends expr %}` (#17271) | compiles to a call that compiles the child once per parent it is rendered with (`examples.md` E3) |
| errors | a block defined twice in one template, `super()` with no parent definition, a block that renders itself and circular inheritance all name the file and line |

The output model stays as it is: one PHP file per rendered template, with no block dispatch at run
time.

### 2. Parser changes

From `prototype/patches/volt-parser.patch`; Lemon reports 0 conflicts:

| change | files |
|---|---|
| allow `block` at any depth; `block` anywhere but right after `{%` is an identifier, so `{{ block("x") }}` and `{{ article.block }}` (#12846) parse | `base.c`, `scanner.re` |
| `??` (right-associative, below comparison), `?.` (same level as `.`) | `scanner.re`, `scanner.h`, `parser.php.lemon`, `base.c` |
| `is not` as its own token and node, distinct from `!=` | same |
| `{% embed %}…{% endembed %}`, `{% set x %}…{% endset %}` | same, plus two AST builders in `parser.php.inc.h` |

### 3. Runtime functions, filters and tests

```php
$volt->addFunction(new VoltFunction('price', ['prices', 'format']));          // DI service, resolved on first call
$volt->addFunction(new VoltFunction('stars', $closure, ['safe' => true]));    // returns HTML
$volt->addFilter(new VoltFilter('money', Money::format(...)));
$volt->addTest(new VoltTest('premium', fn (User $u): bool => $u->isPremium()));
$volt->addExtension(new ShopExtension());   // getFunctions(), getFilters(), getTests()
```

- Any callable: function name, static method, closure, first-class callable, invokable, or
  `[object, method]`. `[ServiceOrClass, method]` with a non-static method gets its instance from
  the container on first use, so compiling never touches the container.
- A function name or static method compiles to a direct call. Anything else compiles to a lookup
  memoized on the engine.
- `'name': value` becomes a PHP named argument.
- Options: `safe` (the result is HTML and autoescape leaves it alone) and `needsContext` (the
  template variables are passed first). Twig's other `needs_*` flags can follow if needed.
- `is <name>` with an unknown name is a compile error. `is null` and `is none` are built in. The
  option `strictTests => false` keeps today's `==` fallback.
- The compile-time API (`Compiler::addFunction/addFilter`, extension hooks) stays as it is for real
  code generators. It gets an explicit name ("compile-time functions") and an interface for the
  hook object. #17053's `TagTranslator` is exactly such a compile-time registry and could be its
  first built-in user.

### 4. Escaping

- A `raw` filter.
- Escaping filters (`e`, `escape`, `escape_js`, `escape_css`, `escape_attr`, `url_encode`) are not
  wrapped by autoescape again.
- `safe` runtime functions and filters, plus `content()` and `partial()`, are not escaped. A safe
  call inside a larger expression is still escaped as a whole (`tests/Prototype/OutputTest.php`).

### 5. Cache dependencies

Each compiled file gets a sidecar listing the files inlined into it (parents, embeds, static
includes, recursively) with their mtimes, plus a signature of the compiler configuration (the
runtime registry, `autoescape`). With `stat` on, a change to any of them recompiles the template.
With `stat` off nothing is checked, as today.

### 6. Statements and expressions

- `??`, `?.` and set capture, from §2.
- `include "x" with [...]` stays a compiled include, run in a scope that sees the includer's
  variables plus the parameters, instead of a runtime partial. Names resolve with or without
  `.volt` (#17368). Paths that are not Volt files keep using `partial()`.

### 7. Documentation

`docs-extending-volt.md` is a replacement for the "Extending Volt" section. It documents today's
5.x API correctly:
- it states the compile-time model;
- it explains `$resolvedArgs` and `$exprArgs`;
- it lists the common mistakes, how to reach services, the hooks and their order, a node reference,
  and when changes are recompiled.

Every snippet is tested on 5.23.0. It can be published independently of this NFR.

## Milestones

Each lands in cphalcon (C + Zephir) and phalcon/volt (PHP).

| | scope | BC |
|---|---|---|
| **M0** (5.x) | the docs page; separate bug issues for the compiler drift found along the way (`//` parsed as modulo, `{% call %}` dropping its body, `{% cache %}` parsing then failing, `\|e` escaped twice, `is not` with function tests) | none |
| **M1** | AST resolver replacing extends-mode compilation, plus the dependency sidecar. Gate: the 50-fixture parity test, the upstream suite | none in output |
| **M2** | parser: nested blocks, blocks in control structures, `block()`; then `embed`; then dynamic `extends` | new reserved words |
| **M3** | runtime registry, `safe`/`raw`, escaping filters, strict tests, the `is not` token | see BC |
| **M4** | `??`, `?.`, set capture, `include … with` scope | include-with semantics |

**Later**, deliberately not in this NFR:
- autoescape strategies (`js`, `css`, `url`, by file extension);
- macro `import`/`from` with template-local scope;
- a loader abstraction with namespaces (`@admin/…`) and string templates;
- runtime errors mapped to the template file and line;
- arrow functions with `map`, `filter` and `reduce`;
- array-aware `.` access.

Each of these is a separate discussion; `survey-twig-gap.md` has the details.

## Backward compatibility

- `a is not b` stops meaning `a != b`. It becomes a negated test, and with strict tests an unknown
  name is an error. Two upstream tests pin the old meaning.
- Unknown tests become compile errors (opt-out: `strictTests => false`). Today they compile to a
  loose comparison with a variable of that name.
- `embed`, `endembed` and `endset` become reserved words. `block` is only reserved right after
  `{%`, so `article.block` works (#12846).
- These become errors: a block name defined twice in one template (today the last one wins
  silently) and `super()` without a parent definition.
- `include "x" with [...]` sees the includer's variables. Today it sees only the View's.
- Parent templates are no longer compiled to `%%e%%` files. Code reading the protected `blocks`,
  `extendedBlocks` and `currentBlock` properties of the compiler, or the e-files, breaks.
- Output is unchanged for existing templates: 50 of 50 upstream fixtures compile byte-identical.

## Open questions

1. Naming: new `VoltFunction`/`VoltFilter`/`VoltTest` objects on the engine (as prototyped), or
   `Compiler::addFunction()` accepting a descriptor object next to today's string|Closure? The
   registry has to be reachable at render time (`$this` in compiled code is the engine), so the
   engine seems the right owner.
2. Strict tests on by default in v7?
3. Dynamic `extends`: a compiled variant per (child, parent) pair, as prototyped, keeping Volt's
   one-file model; or Twig-style runtime block dispatch, which is more flexible but slower and a
   bigger change?
4. Should `include … with` move to the compiled, scoped form, or stay a runtime partial with a new
   syntax for the scoped one?
5. For phalcon/volt: change it in lockstep per milestone, or treat the PHP port as the reference
   for the new parts and port them back to Zephir?
6. Does any of this collide with plans for #17053, phalcon#274, or the parser fixes already queued
   for v7 (#17652, #17425)?

## Prototype

`prototype/`, PHP over the built extension, for design validation only. It is not meant to be
merged. Everything real would be Zephir in `phalcon/` and C in `ext/phalcon/mvc/view/engine/volt/`.

- `./build.sh stock`, `./build.sh patched`: build HEAD's `ext/` as is, and with the parser patch.
- `./run.sh test`: `tests/Today` on the stock build, `tests/Prototype` on the patched build.
- `./run.sh tools/examples.php`: regenerates and checks `examples.md`. `tools/parity.php` runs the
  fixture parity, `tools/trace.php` prints the pipeline stages, `./run.sh bench` runs the timings.
