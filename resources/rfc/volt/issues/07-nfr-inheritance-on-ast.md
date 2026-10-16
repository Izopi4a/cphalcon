**Is your feature request related to a problem? Please describe.**

Volt resolves template inheritance by splicing compiled pieces. When a child is compiled, the parent is compiled in "extends mode" into a serialized map of `name => block AST` and `int => compiled text` (the `layout.volt%%e%%.php` cache file). `compileSource()` then walks that map and swaps in the child's compiled blocks (`Compiler.zep:2403-2450`, `:2880-2916`).

That model has one flat level of block names and a single `currentBlock`. Several long-standing requests fail on it, not on missing syntax:

- **#17145**, nested blocks (2013, the most-voted entry on #14608). `base.c:655` refuses a block while `block_level > 0`. `if`/`for`/`switch` increment the same counter, so a block inside an `if` fails with the same message.
- **#17271**, `{% extends variable %}`. In your words, it "needs a refactor in the compiler"; today the variable name is used as a file name (`Compiler.zep:2884-2888`).
- `{{ block("name") }}` (printing a block twice) and components with overridable blocks (Twig's `embed`) have no place to live in a flat map.
- The compiled child does not know which files were inlined into it, so editing a parent or a static include leaves the child stale.
- The inheritance state lives on the compiler (`blocks`, `extendedBlocks`, `currentBlock`, `extended`) and has to be reset carefully between templates, as the CP-17668 reset change shows.

This ticket is only the refactor. It changes no output. The features above are separate tickets that build on it.

**Describe the solution you'd like**

Resolve inheritance on the AST, before anything is compiled:

1. Load the chain leaf → … → root as ASTs, following `extends`.
2. Collect every level's blocks by name, at any depth.
3. Expand the root's statements. A block node becomes the statements of its most derived definition, expanded recursively, and `{{ super() }}` becomes the next definition up the chain.

The result is a flat statement list with no `extends` or block nodes. The existing `statementList()` compiles it unchanged, so the output model stays as it is: one PHP file per rendered template, with no block dispatch at run time.

```
page.volt:   {% extends "layout.volt" %}{% block title %}Orders{% endblock %}{% block content %}{{ count }} open{% endblock %}
layout.volt: <h1>{% block title %}Shop{% endblock %}</h1>{% block content %}{% endblock %}

today:      layout.volt%%e%%.php (serialized map) + page.volt.php
proposed:   page.volt.php only
both:       <h1>Orders</h1><?= $count ?> open
```

Prototype (plain PHP over the 5.23.0 extension, overriding `compileSource()`):
- **All 50 templates of the upstream Volt fixtures** (`tests/support/assets/views`, including the three-level `extends/nested/*` and the themes) compile **byte-identical** to the stock compiler: https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/tests/Prototype/ParityTest.php
- the resolver is ~300 lines with comments: https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/src/Inheritance/Resolver.php
- each stage, today vs proposed, with real data: https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/walkthrough.md (sections 1 and 3)

It also gives clear errors where today's behaviour is silent:
- a block name defined twice in one template (today the last one wins);
- `super()` with no parent definition;
- a block that renders itself;
- circular `extends`.

Each error names the file and line.

**Describe alternatives you've considered**

- **Extending the splice model:** nested name maps and a stack of current blocks inside compiled strings, plus the `base.c` change. It is more state on the compiler, and it still has no place for `block()`, `embed` or dynamic `extends`.
- **Twig-style runtime inheritance:** a class per template, with blocks dispatched at render time. It is the most flexible, but it replaces the one-file output model and adds a call per block at run time. Resolving on the AST keeps Volt's compile-time model.

**Additional context**

BC: none in output. The extends-mode compile path and the `%%e%%` files go away. Code that reads the compiler's protected `blocks` / `extendedBlocks` / `currentBlock` state, or the e-files, would break.

Follow-ups that build on this, each its own ticket:
- nested blocks and blocks in `if`/`for` (#17145). With the resolver in place, the parser side is a 12-line change in `base.c`: https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/patches/01-nested-blocks.patch
- `{{ block("name") }}`
- `{% embed %}`
- `{% extends variable %}` (#17271)
- recompiling when an inlined file changes. The resolver knows every file it loaded.

The full picture, if useful: https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/volt-rfc.md. Drafted with Claude Code assisting; the prototype runs with `./build.sh` and `./run.sh test` in `resources/rfc/volt/prototype/`.
