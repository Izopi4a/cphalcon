# Volt NFR, split into tickets

niden asked for one ticket per feature instead of the single NFR. `../volt-rfc.md` stays the map
(and the prototype the evidence); each ticket links to its slice: an example in `../examples.md`,
its tests, and its patch in `../prototype/patches/`.

**How to use:** each file in this directory holds only the ticket body. Open it on GitHub, click
"Raw", copy everything, and paste it into the issue. Titles and labels are below. After posting 07,
replace `#NFR-07` in 08 and 11 with its number.

## Wave 1: drafted

| # | file | where | title | labels to add |
|---|---|---|---|---|
| 01 | `01-bug-floor-division.md` | new issue | `[BUG]: Volt: {{ a // b }} compiles to modulo (a % b)` | (template: bug) |
| 02 | `02-bug-call-drops-body.md` | new issue | `[BUG]: Volt: {% call %}…{% endcall %} compiles to an empty string` | (template: bug) |
| 03 | `03-bug-cache-tag.md` | new issue | `[BUG]: Volt: {% cache %} still parses, then fails with "Unknown statement 314"` | (template: bug) |
| 04 | `04-bug-autoescape-double-escape.md` | new issue | `[BUG]: Volt: with autoescape, content() and \|e are escaped twice` | (template: bug) |
| 06 | `06-docs-pr.md` | PR to phalcon/documentation | `Volt: rewrite "Extending Volt" (functions, filters, extensions) for how 5.x actually works` | n/a |
| 07 | `07-nfr-inheritance-on-ast.md` | new issue | `[NFR]: Volt: resolve template inheritance on the AST (prerequisite for #17145, #17271)` | 7.0 |
| 08 | `08-comment-17145.md` | comment on #17145 | n/a | n/a |
| 11 | `11-comment-17271.md` | comment on #17271 | n/a | n/a |

Post 07 before 08 and 11. The docs PR (06) needs the text moved into
`src/content/docs-5.23/volt.mdx` in phalcon/documentation; `../docs-extending-volt.md` is the source.

## Wave 2: after niden reacts to wave 1

| # | where | title | depends on | evidence |
|---|---|---|---|---|
| 05 | new issue | `[BUG]: Volt: "is not <test>(…)" compiles to "!="` | its fix is the `is not` token (13) | `tests/Today/ExtensionApiTodayTest.php` |
| 12 | new issue | `[NFR]: Volt: recompile a template when a parent, include or embed it inlines changes` | none (works on today's compiler too) | E9, `tests/Prototype/CacheTest.php` |
| 13 | new issue | `[NFR]: Volt: functions, filters and tests that run at render time (callables, lazy DI services, named args)` | none | E5, E6, `tests/Prototype/RuntimeExtensionTest.php`, `03-is-not.patch`, `./run.sh bench` |
| 14 | new issue | `[NFR]: Volt: raw filter and a "safe" flag for functions/filters` | 13 for the flag | E7, `tests/Prototype/OutputTest.php` |

## Wave 3: syntax

| # | where | title | depends on | evidence |
|---|---|---|---|---|
| 09 | new issue | `[NFR]: Volt: {{ block("name") }} to print a block again` (also closes #12846, `article.block`) | 07 | E2, `02-block-function.patch` |
| 10 | new issue | `[NFR]: Volt: {% embed %} (components with overridable blocks)` | 07 | E4, `06-embed.patch`, `tests/Prototype/EmbedAndIncludeTest.php` |
| 15 | new issue | `[NFR]: Volt: null coalescing operator ??` | none | E8, `04-null-coalescing.patch` |
| 16 | new issue | `[NFR]: Volt: null-safe access ?.` | none | E8, `05-null-safe.patch` |
| 17 | new issue | `[NFR]: Volt: {% set x %}…{% endset %} capture` | none | `07-set-capture.patch` |
| 18 | new issue + comment on #17368 | `[NFR]: Volt: include … with in its own scope` | none | E10 |

## Mapping to the patch series

| patch | ticket |
|---|---|
| `01-nested-blocks.patch` (12 lines) | #17145 (08), on top of 07 |
| `02-block-function.patch` | 09 |
| `03-is-not.patch` | 13 (tests), fixes 05 |
| `04-null-coalescing.patch` | 15 |
| `05-null-safe.patch` | 16 |
| `06-embed.patch` | 10 |
| `07-set-capture.patch` | 17 |

The series applies in order (`../prototype/build.sh`); each prefix was checked with Lemon (0
conflicts after every step).
