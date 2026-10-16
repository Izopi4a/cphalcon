Rewrites the "Extending Volt" part of the Volt page (Functions, Filters, Extensions) so it explains how the API actually works in 5.x. No behaviour changes; it documents what the compiler does today.

What the current text leaves out, and what users keep tripping on (#1239, #2810, #1176, #697, #1907, D#15527 "the documentation is shallow"):

- **The compile-time model.** A closure given to `addFunction()` / `addFilter()` runs once, when the template is compiled. It receives the arguments as PHP source and must return PHP source, which is written into the compiled file. `fn () => date('Y')` freezes the year into the cache.
- **What `$resolvedArgs` and `$exprArgs` contain**, with a node reference for the AST types.
- **Common mistakes**, with the code each one compiles to: returning a value instead of code, first-class callables being called as code generators, array callables being rejected, typos compiling to `callMacro()`, and `'name': value` producing invalid PHP for functions.
- **How generated code reaches a service:** `$this` is the engine, so use `$this->getDI()->getShared(...)`, or `service.method()`, which is decided at compile time.
- **Autoescape and HTML returned by functions.** There is no `raw` filter and no safe flag; how to work around it.
- **Filters:** the filtered value comes first in `$resolvedArgs`, and `$exprArgs` is `null` without arguments.
- **Tests:** there is no registration API, unknown tests compile to `==`, and `is not` is `!=`; how to add a test with `resolveExpression`.
- **Every extension hook** with its real signature, including `initialize()` and the third `$exprArgs` argument; the call order; and "the first extension returning a string wins".
- **When changes are recompiled:** with `stat` on, changes to parents, static includes, function definitions or DI services are not picked up.

Every snippet was checked against the 5.23.0 extension: https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/tests/Today/DocsDraftTest.php (source text: https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/docs-extending-volt.md).

Separately, the examples in the "Tests" section use `[1: 'Apple', …]`, which does not parse, because hash keys must be quoted strings. I can fix those in this PR too.
