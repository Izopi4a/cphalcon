# Volt: user demand survey (GitHub issues, PRs, discussions)

Survey date: 2026-10-16. Reference code: `nfr-volt` = upstream `phalcon/cphalcon` master @ 33f1076a88 (v5.23.0).
Scope: what users have asked of Volt, what came of each request, and what is still missing on master.

## Method

| Source | Query | Hits | Notes |
|---|---|---|---|
| phalcon/cphalcon issues+PRs | `repo:phalcon/cphalcon volt` (title/body, all states) | 565 (451 issues, 114 PRs; 12 open) | Fetched in full through the REST search API (reactions included). 50 carry `new feature request`, 19 `enhancement`, 7 `wontfix`, 56 `stale`, 10 `7.0`. 90 were created 2020 or later. |
| phalcon/cphalcon, supplementary | `"template engine"`, `endblock`, `twig`, `"view engine"`, `partial in:title`, `macro in:title`, `template in:title` | 356 (82 not containing "volt") | About 6 of the 82 are relevant (#2140, #2452, #10615, #11868, #13050, #14815). All are closed and pre-2021. |
| phalcon/cphalcon | `label:7.0` | 38 | 8 are Volt items (all open) |
| phalcon/cphalcon | #14608 (NFR vote list) comments; #13855 body edit history (GraphQL `userContentEdits`) | - | The edit history recovers the numbered 2019 NFR list, so votes can be counted |
| phalcon/phalcon (v6 PHP port) | `volt`, plus `template`, `block`, `macro`, `view engine`, `twig`, `partial` | 17 + 308 | Most are dependabot. Relevant: #90, #137, #274, #538/#539, #730, #775 |
| phalcon/volt (PHP Volt package) | all issues/PRs | 121 | 1 relevant bug (#88); the rest are dependabot or sync PRs |
| phalcon/documentation (current docs) | `volt` | 3 | #50 |
| phalcon-orphanage/docs (former `phalcon/docs`, archived) | `volt` | 53 | Mostly typo PRs. Issues: #450, #1221, #1364, #1515, #2155, #2600, #3093 |
| Discussions | GraphQL `type: DISCUSSION`, `repo:<r> volt` | cphalcon 30, phalcon 2, volt 0, documentation 0 | Relevant: D#15284, D#15398, D#15527, D#16245, D#16386, D#16802, D#16021 |
| Current docs text | `phalcon/documentation` `src/content/docs-5.23/volt.mdx` | - | Checked for coverage of extensions and inheritance limits |

Caveats:
- **Renumbering.** Many pre-2019 NFRs were transferred to `phalcon/phalcon` in 2021, and some were moved back in 2026 under new numbers: #329 → #17145, #1253 → #17085, #14411 → #17269. Others stayed in phalcon/phalcon: #2349 → phalcon#137, #2700 → phalcon#274. Old numbers still redirect.
- **Reactions.** Transferred issues show few or no 👍 (#17145 shows 0). The best demand signals are the 👍 counts on the #14608 entries and the 2019 votes in #13855.
- **"Still relevant on master" checks.** These come from grepping `ext/phalcon/mvc/view/engine/volt/base.c`, `scanner.re`, `parser.php.lemon` and `phalcon/Mvc/View/Engine/Volt/Compiler.zep`. The extension is not installed locally, so nothing was executed.

## Themes ranked by demand

Demand columns: **VL** = 👍 on the #14608 vote-list entry. **V19** = votes in #13855 (2019). **Cmts** = total comments across the theme's issues.

### 1. Template inheritance: nested blocks, blocks inside control structures and partials
- **What users want**
  - `{% block %}` inside `{% block %}`, so that a middle layout can expose sub-blocks a grandchild overrides (a extends b extends c).
  - `{% block %}` inside `{% if %}` / `{% for %}`.
  - Blocks defined in an included or partial template that the extending child can override.
- **Issues:** #17145 (orig #329), duplicates #10914, #1138, #1636, #13155. Related: #12846, #2898, #12169, #2355.
- **Demand:** VL **22** (highest of every entry on the vote list; next are Embedded Forms 19 and HTTP rework 18). V19: 3 votes (item 59). #17145 has 71 comments from 40 distinct users. 11 of them mention Twig, Smarty or Blade as the workaround, and 6 say they switched for this reason (gsouf, redstrike, michanismus, krazzer, datanator, victorhramos).
- **Maintainer stance:** promised repeatedly, never scheduled firmly:
  - 1.3 → "Phalcon 2 with Zephir" (2014)
  - → 2.1 roadmap (2015)
  - → 4.0 milestone
  - → 4.1 project after the 2019 vote
  - → "when we start working on v6" (2021; the vote-list badge says "Scheduled 6.0")
  - → relabelled `7.0` and assigned to niden on 2026-06-13.
- **On master:** still rejected at parse time.
  - `base.c:655-656` raises `Embedding blocks into other blocks is not supported` whenever `block_level > 0`. IF, FOR and SWITCH also increment `block_level`, so a block inside an `if` or `for` fails too.
  - `Compiler::compileSource()` merges only the parent's top-level block names.
  - Related bug, probably still present: `{% for x in y if cond %}` increments `block_level` on the `if` token and never decrements it, so any later `{% block %}` fails (#1636, #13155).
  - docs-5.23 does not mention this limitation.

**Nested-block request, as asked.** #17145 was opened 2013-01-15 by applejohnny:
> "With inheritance of multiple files like a.volt extends b.volt extends c.volt, I have to use embedding blocks. Otherwise there's no profit to use inheritance more than one nesting level."

Follow-ups asked for the same thing in other places:
- a block inside an `if` (Raistlfiren 2013; erickmajor 2019: "blocks `{% block %}` under conditions `{% if %}` and `{% else %}`?")
- #10914 (2015): `{% block content %}{% block body %}…{% endblock %}…{% endblock %}`
- #1138 (2013): a layout → manage_layout → page chain with a sidebar sub-block.

Timeline of #17145:
- closed 2019-02-23 "in favor of #13855", reopened 2019-03-11 after the vote
- transferred to phalcon/phalcon 2021-10-01, moved again 2026-01-23
- moved back to cphalcon 2026-06-13; now labelled `new feature request` + `7.0`
- **Outcome: open, unimplemented.**

### 2. Flexible paths for `extends` / `include` / `partial`
- **What users want:** `extends` from a variable or expression (themes, AJAX layouts), absolute and template-relative paths, and the same extension rules for `include` and `partial()`.
- **Issues:**
  - #17269 (orig #14411; 1 👍 / 7 reactions; VL 1), #708 (9 comments, Twig cited), #11331, #2406, D#15284 (2021)
  - #11478 (wanted an extension hook to rewrite the extends path), #2702 (16 comments)
  - #804 → #17368 and phalcon#775, #2879, #10990, #10215, #208, #214
- **Demand:** Cmts 59 plus the discussion threads. Steady over 2013–2026.
- **Stance:** absolute and `./` `../` paths were delivered in 5.17.0 (#17272). Extends-from-variable "needs a refactor in the compiler" (#17271) and include-extension consistency needs interface changes (#17368); both are deferred to v7.
- **On master:** absolute and relative paths work. `{% extends %}` still takes only a string literal. `include` and `partial()` still differ on whether the `.volt` extension is required.

### 3. Literal / verbatim output and delimiter clashes (delivered)
- **Issues:** #17085 (orig #1253, 31 comments), #1838, #2031, #2032, #2290 (Angular), #12732 (Vue), #13243, #509.
- **Demand:** V19 3 votes (item 61). Cmts 58. "Pretty shocked that 61 isn't a feature yet" (xorinzor 2019).
- **Outcome:** `{% verbatim %}` shipped in 5.14.1 (#17086). Do not re-request.

### 4. Syntax ergonomics
- **What users want:**
  - trailing commas (#2021 in 2014, closed with "Why is this a bug?"; #17652 in 2026; PR #17670)
  - `->` for objects (#17425)
  - one access notation for arrays and objects (#2712, #10712 with 10 comments, #13941, #13942 with 7 reactions and `wontfix`)
  - property access through a variable (#1596)
  - lambdas (#10774), named `{% endblock name %}` (#1744), shorter filter aliases (#13940)
  - reserved words usable as property names: `article.block` (#12846), `travel.return` (#15156)
- **Demand:** Cmts 69. Small but recurring, with new reports in 2026.
- **Stance:**
  - trailing comma and `->`: accepted for v7
  - array dot notation: rejected in 2019 as too costly
  - reserved words: "`return` is a reserved word for Volt" (2024)
- **On master:**
  - The scanner turns only `set` and `is` after a `.` into identifiers (#14391, 2019). `default` is context-sensitive inside `switch` since 5.14.2.
  - `block`, `return` and other keywords are still reserved as property names.
  - The grammar has no named `endblock`.

### 5. Output post-processing: minify, spaceless, output filters
- **Issues:**
  - phalcon#137 (orig #2349, 2014; 11 comments)
  - #1924, #2769, #13816, #12133 (PR, `wontfix`), #2668 / #975 / #10952 (spaceless; 2 + 2 👍)
  - #952, #2615, #14375, #2823, D#16245 (2022, indentation)
- **Demand:** V19 **5 votes** for "Volt output filters" (item 60), the most-voted Volt item in 2019. Cmts 34 plus 11.
- **Stance:** "I don't think that Phalcon should perform this task … However we can come up with some sort of mechanism where we can attach a filter" (2019). That mechanism was never built. phalcon#137 was closed 2026-06-08 as not addressed ("new issue with more context or … incubator").
- **On master:** whitespace control `{%-` `-%}` `{{-` `-}}` exists (scanner.re). There is no spaceless tag and no compile-time output-filter hook.

### 6. Built-in filters, tags and functions (parity with Twig)
- **Issues:** #2668 (number_format, spaceless, embed; 2 👍), #1341 (merge; 8 comments), #1533 (escape_url), #11241 / #2605 (trans / gettext tag), #12201 (msgctxt; VL 1), #12239 (`{% set x %}…{% endset %}` capture), #11440, #12841 (PR to auto-expose PHP functions; closed unmerged).
- **Demand:** Cmts 41, 7 👍. All are old.
- **Stance:** the usual answer is "add it yourself with addFilter/addFunction", or the issue was closed for lack of reaction.
- **On master:** the built-in filters are abs, capitalize, convert_encoding, default, e/escape, escape_attr/css/js, format, join, json_encode/decode, keys, left_trim, length, lower(case), right_trim, slashes, slice, sort, stripslashes, striptags, trim, upper(case) and url_encode. There is no merge, number_format, spaceless or set-capture.

### 7. Compiler API and extensibility
- **Issues:**
  - phalcon#274 (orig #2700: pass a Compiler to the Volt engine; V19 1)
  - #2182 / #2487 (compile events; delivered in 4.0, #13824)
  - #2924, #11478 (`compileStatement` cannot rewrite a statement, only replace its output; Zephir has no by-reference parameters)
  - #3095 (custom tags), #14436 (Smarty-style block functions; VL 2), #14473 (`{% php %}`, rejected)
  - D#15527 (sandbox: forbid `this.`; no built-in way to do it)
  - #17564 and #17566 (API type defects; open, v7)
- **Demand:** low in votes. The same needs keep coming back through the documentation questions (see below).
- **Stance:** phalcon#274 was closed 2026-06-08 with "We can address this before v7 since there will be a need to change the interface/constructor."
- **On master:** `addExtension()` accepts any object. The hooks (`initialize`, `compileFunction`, `compileFilter`, `resolveExpression`, `compileStatement`) are found with `method_exists` and return PHP source strings. There is no interface, and no way to register new tags or tests.

### 8. Tag → TagFactory migration as seen from Volt helpers
- **Issues:** #15801, #16019 (20 comments; `form()` → `form_legacy`), #16005, #15959 (3 👍 / 19 comments), #15992, #16416, #16625, D#16021, D#16092, D#16272. Open: #17053 (v7: compile-time `TagTranslator` + `Defaults` service).
- **Demand:** Cmts 48. These were mostly upgrade pain in 2022–2025.

### 9. Macros
- **Feature asks:** #1592 (macros in child templates, stale), #1724 (cross or recursive macro calls, stale), #10615, and #3180 (call/caller). #3180 was closed in 2017 as "implemented", but on master `{% call %}…{% endcall %}` only parses: `Compiler::compileCall()` is a stub that returns `''`, and `CompileCallTest` asserts exactly that.
- **Bugs:** #1176, #2164, #10655, #11745, #11771, #13660; all fixed by 2018. Cmts 103, almost all on these bugs. Current demand is low.

### 10. Name collisions between services and view variables
- **Issues:** #1172 (2013), #1760, #15047 (2020), #15913 (2022).
- **On master:** in `name.attr` / `name.method()`, a `name` that is a DI service compiles to `$this->name` (Compiler.zep:258) and shadows a view variable with the same name. Stance: "there will always be a conflict" (2020).

### 11. Loop context needs a Countable iterable
- **Issues:** #14042 (2019, `wontfix`), D#16802 (2025, unanswered).
- **On master:** `loop` still emits `count($iterator)`, which fails for null or a generator.

### 12. Compiled-template storage and caching
- **Issues:** #13926 (Redis/Memcache; answer: use opcache), #3226 (hashed names; answer: closure workaround), #13798 (`{% nocache %}`: "might be difficult to implement, if at all possible"), #339.
- **Demand:** low.

Recurring bug clusters 2020+ (all fixed unless noted; not feature requests):
- string quoting and escaping in compiled PHP: #16005, #16019, #17002, #17046, 5.20.0
- path regressions after the 5.17 path work: #17426, #17606
- inheritance compile errors and segfaults: #15556, #16613, #17294, #17565, CP-17668 state leak
- PHP 8.x deprecations in generated code: #15984, #16263, #16305
- reserved-word collisions: #15156, #16003. Only `default`-in-switch is fixed.

## Open items table

| # | Title | Created | 👍 | Cmts | Ask | Maintainer response | On master |
|---|---|---|---|---|---|---|---|
| [#14608](https://github.com/phalcon/cphalcon/issues/14608) | [NFR]: Request List [VOTE] | 2019-12-09 | 11 | 33 | Vote list. Volt entries: nested blocks **22**, block functions 2, strict types 2, View::has 2, extends var/abs path 1, cache system 1, single quotes 0 | Curated by niden; latest entry added 2026-06-26 | - |
| [#17145](https://github.com/phalcon/cphalcon/issues/17145) | [VOLT] Support for embedding blocks into other blocks | 2013-01-15 (#329) | 0 (VL 22) | 71 | Nested blocks; blocks inside if/for | Labelled 7.0, assigned to niden 2026-06-13 | Rejected in base.c:655 |
| [#17271](https://github.com/phalcon/cphalcon/issues/17271) | [NFR]: Volt extends from variable | 2026-07-06 | 0 | 0 | `{% extends $dynamicLayout %}` | "needs a refactor in the compiler"; 7.0 | Literal paths only |
| [#17368](https://github.com/phalcon/cphalcon/issues/17368) | [NFR]: Volt include with/without extension .volt | 2026-07-17 | 0 | 2 | Same `.volt` rule for static include, include-with-params, dynamic include and partial | Needs Compiler/View interface change → v7 | Inconsistent |
| [#17425](https://github.com/phalcon/cphalcon/issues/17425) | [NFR]: "->" Notation for Objects in Volt | 2026-08-01 | 0 | 1 | `->` as an alternative to `.` | Objects are trivial, arrays are the problem → v7 | Not supported |
| [#17652](https://github.com/phalcon/cphalcon/issues/17652) | Dangling Comma In Partial Argument List | 2026-10-02 | 0 | 1 | Trailing comma in arrays and argument lists | Deferred to v7 ("a few lined up there") | Syntax error |
| [#17670](https://github.com/phalcon/cphalcon/pull/17670) (PR) | Volt: allow trailing comma in arrays, argument lists and macro parameters | 2026-10-15 | 0 | 1 | Grammar fix for #17652 (Izopi4a) | "We will have to check it"; v7 starts after the v6 stable release | Pending |
| [#17053](https://github.com/phalcon/cphalcon/issues/17053) | Deprecate Phalcon\Tag in favor of TagFactory + Volt TagTranslator + Defaults | 2026-05-24 | 0 | 0 | Compile-time helper translator, `defaults` service | Authored by niden; 7.0 | Pending |
| [#17564](https://github.com/phalcon/cphalcon/issues/17564) | Volt: dead closure prefix | 2026-09-04 | 0 | 0 | Support closure prefixes or drop the branch (both projects) | niden; 7.0 | Present |
| [#17566](https://github.com/phalcon/cphalcon/issues/17566) | Volt::compileString return type | 2026-09-04 | 0 | 0 | Declared `string`, but returns an array in extends mode | niden; 7.0 | Present (Compiler.zep:1310) |

Volt is mentioned only in passing in open #17106 (Embedded Forms RFC: Volt themes for widgets) and #17120 (stack trace).

## Closed-but-unresolved requests

| # | Title | Created → Closed | 👍/Cmts | Outcome | Ask | Still relevant on master |
|---|---|---|---|---|---|---|
| [phalcon#137](https://github.com/phalcon/phalcon/issues/137) | Volt output filters (orig #2349) | 2014-04 → 2026-06-08 | 0/11 (V19 5) | Closed, not addressed | Compile-time output filters (minify); `{% minify %}` | Yes |
| [phalcon#274](https://github.com/phalcon/phalcon/issues/274) | Allow Volt to accept a Compiler in the constructor (orig #2700) | 2014-08 → 2026-06-08 | 0/2 (V19 1) | Closed; "address before v7" | Configure one shared compiler for web and CLI | Yes |
| [#708](https://github.com/phalcon/cphalcon/issues/708) | Volt - dynamic inheritance support | 2013-06 → 2018-04 | 0/9 | Stale | Twig-style dynamic `extends` | Partly; the variable part is #17271 |
| [#2406](https://github.com/phalcon/cphalcon/issues/2406) | request.ajax extends like Twig | 2014-05 → 2017-08 | 0/2 | Redirected to the forum | `{% extends cond ? a : b %}` | Yes (#17271) |
| [#11331](https://github.com/phalcon/cphalcon/issues/11331) | Make the "extends" path selectable | 2016-01 → 2018-04 | 0/1 | Stale | Resolve extends from layoutsDir or an ExtendsDir option | Partly (relative paths in 5.17) |
| [#2898](https://github.com/phalcon/cphalcon/issues/2898) / [#12169](https://github.com/phalcon/cphalcon/issues/12169) | Blocks in partial/included files not inheritable | 2014 / 2016 → 2018 | 0/5, 1/4 | Stale | Override blocks defined in included templates | Yes |
| [#1636](https://github.com/phalcon/cphalcon/issues/1636) / [#13155](https://github.com/phalcon/cphalcon/issues/13155) | for…if hides ENDBLOCK / "Embedding blocks" false error | 2013 / 2017 | 0/2, 0/6 | Closed as a dup of #329 / stale | `for x in y if c` followed by a block | Probably still present (block_level not decremented) |
| [#12846](https://github.com/phalcon/cphalcon/issues/12846) | `block` used as a property triggers the block parser | 2017-05 → 2018-04 | 0/4 | Stale | Context-sensitive keywords | Yes |
| [#15156](https://github.com/phalcon/cphalcon/issues/15156) | `return` in a variable path | 2020-09 → 2024-01 | 0/2 | "reserved word" | Same | Yes |
| [#1744](https://github.com/phalcon/cphalcon/issues/1744) | Named block end-tags | 2013-12 → 2017-06 | 0/1 | Closed for lack of reaction | `{% endblock name %}` | Yes |
| [#1592](https://github.com/phalcon/cphalcon/issues/1592) | Allow macros in child templates | 2013-11 → 2018-04 | 0/3 | Stale | Macros inside extending templates | Not verified |
| [#1724](https://github.com/phalcon/cphalcon/issues/1724) | Cross macro calls | 2013-12 → 2018-04 | 0/2 | Stale | Mutually recursive macros | Not verified |
| [#3180](https://github.com/phalcon/cphalcon/issues/3180) | caller / call support for macros | 2015-01 → 2017-06 | 0/1 | Closed as "implemented" | Jinja/Twig-style `{% call %}` with `caller()` | Yes (`compileCall()` returns `''`) |
| [#12239](https://github.com/phalcon/cphalcon/issues/12239) | set/endset block capture | 2016-09 → 2016-09 | 0/6 | Closed; "use a macro" | Capture rendered markup into a variable | Yes (no ENDSET) |
| [#2668](https://github.com/phalcon/cphalcon/issues/2668) / [#10952](https://github.com/phalcon/cphalcon/issues/10952) | number_format, spaceless, embed | 2014 / 2015 → 2018 | 2/1, 2/2 | Stale / dup | Built-in filters and tags | Yes |
| [#1341](https://github.com/phalcon/cphalcon/issues/1341) | merge filter | 2013-10 → 2017-06 | 0/8 | Closed for lack of reaction | `|merge` | Yes |
| [#13816](https://github.com/phalcon/cphalcon/issues/13816) | Volt setMinify() | 2019-02 → 2019-03 | 0/7 | Closed; "framework should not minify" | Minify on compile | Yes |
| [#13942](https://github.com/phalcon/cphalcon/issues/13942) | Remove single quotes from Volt names | 2019-04 → 2019-05 | 0(7 reactions)/5 | `wontfix` | `data[name]` | Rejected |
| [#2712](https://github.com/phalcon/cphalcon/issues/2712) / [#10712](https://github.com/phalcon/cphalcon/issues/10712) | Unified dot notation for arrays | 2014 / 2015 → 2018 | 0/3, 0/10 | Stale | `item.title` for arrays | Yes (overlaps #17425) |
| [#2021](https://github.com/phalcon/cphalcon/issues/2021) | Trailing comma in arrays | 2014-02 → 2014-02 | 0/6 | Closed by the author after "Why is this a bug?" | `[1,2,3,]` | Yes → #17652 / PR #17670 |
| [#14436](https://github.com/phalcon/cphalcon/issues/14436) | Volt: Block functions | 2019-09 → 2019-12 | 1/3 (VL 2) | Moved to the vote list | Smarty-style block plugins | Yes |
| [#2924](https://github.com/phalcon/cphalcon/issues/2924) / [#11478](https://github.com/phalcon/cphalcon/issues/11478) | compileStatement cannot override the statement | 2014 / 2016 | 0/1, 0/1 | Stale / Zephir limitation | Rewrite the AST node in an extension | Yes |
| [#13798](https://github.com/phalcon/cphalcon/issues/13798) | Partial NoCache | 2019-02 → 2019-02 | 0/5 | Moved to the vote list | `{% nocache %}` | Yes |
| [#13926](https://github.com/phalcon/cphalcon/issues/13926) | Volt cache system | 2019-04 → 2019-09 | 0/1 (VL 1) | Closed; "use opcache" | Non-filesystem compiled cache | n/a |
| [#12841](https://github.com/phalcon/cphalcon/pull/12841) (PR) | hasFunction / auto-include PHP functions | 2017-05 → 2018-05 | 1/6 | Closed unmerged | Expose PHP functions without registering each one | Yes (extension workaround only) |
| [#804](https://github.com/phalcon/cphalcon/issues/804) | Consistent file names for include/partial() | 2013-07 → 2018-04 | 0/6 | Stale | Accept the extension in both | Yes → #17368 |
| [#2879](https://github.com/phalcon/cphalcon/issues/2879) / [#10990](https://github.com/phalcon/cphalcon/issues/10990) | include_partial builtin / partial-vs-include by environment | 2014 / 2015 → 2018 | 0/5, 0/2 | Stale | Compile-time include that honours partialsDir | Yes |
| [#12201](https://github.com/phalcon/cphalcon/issues/12201) | Gettext msgctxt | 2016-09 → 2019-02 | 2/4 (VL 1) | Moved to the vote list | Translation context | Translate, not Volt |
| [#14042](https://github.com/phalcon/cphalcon/issues/14042) | count() warning in for-loop | 2019-05 → 2019-10 | 0/9 | `wontfix` | Guard `loop.length` for non-Countable values | Yes |
| [#15047](https://github.com/phalcon/cphalcon/issues/15047) | Variable name vs service name conflict | 2020-05 → 2020-08 | 1/3 | Stale | Variables take precedence, or a service prefix | Yes |
| [#14473](https://github.com/phalcon/cphalcon/issues/14473) | Volt PHP block | 2019-10 | 0/4 | Rejected ("no value") | `{% php %}` | n/a |

## Delivered recently (2025–2026). Do not re-request

| Version (date) | Change | Ref |
|---|---|---|
| 5.12.0 (2026-04-29) | `AbstractEngine` is events-aware; `Compiler::setOptions()` returns `$this` | #16890, #16891 |
| 5.12.1 (2026-04-30) | `statementList()` returned null for block-only templates | #16613 / #16951 |
| 5.13.0 (2026-05-18) | Escaped single quote inside a single-quoted literal | #17002 / #17003 |
| 5.14.0 (2026-06-04) | Volt exception classes split (`UnknownVoltStatement`, …); double-quoted strings containing `'` | #17046 / #17048 |
| 5.14.1 (2026-06-08) | `{% verbatim %}…{% endverbatim %}`; unfinished `{% raw %}` removed | #17085 / #17086 |
| 5.14.2 (2026-06-12) | `default` filter inside `{% switch %}` | #16003 / #17118 |
| 5.15.0 (2026-06-18) | `join` filter compiled through `expression()` | changelog |
| 5.17.0 (2026-07-17) | Absolute (Unix, Windows drive, UNC) and `./` `../` template-relative paths in `extends`/`include` | #17269 / #17272 |
| 5.17.0 | SIGSEGV with multi-level `extends` where an inherited block calls `partial()` | #17294 / #17295 |
| 5.18.1 (2026-08-02) | `View::partial()`/`render()` with absolute paths | #17426 / #17430 |
| 5.20.0 (2026-08-22) | Single-quoted string emission in the compiler | changelog |
| 5.20.3 (2026-08-26) | Scanner out-of-bounds read on a trailing backslash; linear-time list parsing; leak of the syntax-error buffer; class-restricted unserialize of the extends cache; Windows backslash traversal | changelog |
| 5.21.0 (2026-09-18) | `preload()` without a container; `compileSource()` returned null in extends mode | #17565 / #17567 |
| 5.22.1 (2026-10-01) | `..` segments in `partial()` / `Simple::render()`; Windows absolute detection | #17606 / #17607 |
| 5.23.0 (2026-10-15) | Faster View and Volt rendering and compilation; compiler no longer reuses an earlier template's blocks/extends state | #17668 / #17669 |
| phalcon/volt (v6 PHP port) | Parser aligned with cphalcon (Apr 2026); verbatim and switch-default synced; SVG-in-string scanning fix | volt#68–#72, #83, #84, #88; phalcon#730 |

Present before 2025, also not to request: switch/case (3.3, #13107), compile events (4.0, #13824), `is not empty` / `is not defined`, `loop.self`, whitespace control, `include … with`, `{% autoescape %}`.

Not actually present, despite appearances:
- `{% call %}…{% endcall %}` parses but compiles to an empty string (`compileCall()` stub).
- `{% cache %}` was removed from the compiler in 4.0 (#14907, commit cd036561c5), but the grammar and scanner still accept it.

Pending, not delivered: trailing comma (PR #17670).

## Documentation complaints

- **Nested-block limitation is undocumented.** docs-5.23 `volt.mdx` covers "Multiple Inheritance" but never says that blocks cannot be nested or placed inside `if`/`for`. ebuildy on #1636 (2014): "It should be removed from the doc and disable if it can cause trouble, just lost 1 hour to find it". [link](https://github.com/phalcon/cphalcon/issues/1636#issuecomment-47340812)
- **Extensions are thin.**
  - The "Extensions" section is about 35 lines with one `compileFunction` example. The events table names `compileFilter`, `resolveExpression` and `compileStatement`, but gives no argument shapes and no IR reference.
  - rafaphp, D#15527 (2021): "I'm studying how to use this with extensions and events, but the documentation is shallow".
  - #11440 (2016): "What would be the best practice to extend volt? … Some examples appreciated" (redirected to the forum).
- **Compile-time vs runtime confusion with addFunction/addFilter** (they return PHP source, not a value). Recurring since 2013: #1239, #2810, #1176, #697, #1907. The current docs say "you must return a valid PHP string expression" but do not explain the compile-time model.
- **Outdated service setup or wrong examples:**
  - orphanage#2600 (2019, VoltService closure signature after #13839; fixed)
  - orphanage#1515 (service injection wording)
  - #2641, #2149, #10969 (wrong `link_to` / `number_field` examples)
  - orphanage#3093 (2022, `form()` example invalid after the TagFactory switch)
  - D#16386 (2023): "lack of documention for Phalcon 5"
- **Missing content, now done:** #214 (2012, root for template paths), orphanage#1364 (switch-case docs), documentation#50 (compileSet example; resolved 2023), orphanage#2155 (v4 rewrite).
- **Behaviour changes not flagged as breaking:** #17606 (2026): the `..` path change "should to be documented as a potential code breaking change". #2574 / #2863 (2014): an xdebug segfault with custom functions; "this info should be added somewhere in the documentation".

## Maintainer stance quotes worth citing

**Nested blocks (#17145):**
- phalcon (2014-01-14): "This will be implemented in Phalcon 2 with Zephir". [link](https://github.com/phalcon/cphalcon/issues/17145#issuecomment-4698814126)
- andresgutierrez (2015-06-11): "I'll be addressing this soon". [link](https://github.com/phalcon/cphalcon/issues/17145#issuecomment-4698814222)
- Jurigag (2016-08-25): "Obviously to having any progress someone have to work on this, if you have any idea or want to implement this feel free to do PR." [link](https://github.com/phalcon/cphalcon/issues/17145#issuecomment-4698814365)
- niden (2019-02-23): "Closing in favor of phalcon/cphalcon#13855. Will revisit if the community votes for it, or in later versions." [link](https://github.com/phalcon/cphalcon/issues/17145#issuecomment-4698814644)
- niden (2021-09-22): "This will be addressed when we start working on v6 … There is no deadline as of yet and it has not been abandoned." [link](https://github.com/phalcon/cphalcon/issues/17145#issuecomment-4698814667)

**Voting:**
- niden (2019-03-11, #13855): "Issues with more than 2 votes have been added to the 4.1 project." [link](https://github.com/phalcon/cphalcon/issues/13855#issuecomment-471571820)

**Volt's future and the v7 window:**
- Jeckerson (2021-02-08, phalcon#90): "Volt will continue to exist. It probably will be separated into own repository to add in project when you are using it". [link](https://github.com/phalcon/phalcon/issues/90#issuecomment-775216799)
- niden (2026-09-17, #17368): "We will need interface changes in the Compiler and View. The fix is easy to make but the interface changes will break compatibility. I am moving this to v7". [link](https://github.com/phalcon/cphalcon/issues/17368#issuecomment-5722407280)
- niden (2026-08-01, #17425): "The problem is not "->" being the same as "." for objects. That is the 3 line change. The issue is the arrays". [link](https://github.com/phalcon/cphalcon/issues/17425#issuecomment-5153478540)
- niden (2026-10-07, #17652): "I am going to defer this to v7, It is a parser fix and there are a few lined up there." [link](https://github.com/phalcon/cphalcon/issues/17652#issuecomment-6041651821)
- niden (2026-10-15, #17670): "the v7 branch is quite far back from v5 and for v7 work to start we have to release v6. I expect by next weekend to release v6 stable and "freeze" v5". [link](https://github.com/phalcon/cphalcon/pull/17670#issuecomment-6202800547)
- niden (2026-06-08, phalcon#274): "We can address this before v7 since there will be a need to change the interface/constructor. I did not see any traffic in the vote issue though so closing it." [link](https://github.com/phalcon/phalcon/issues/274#issuecomment-4654599154)

**Output filters and minifying:**
- niden (2026-06-08, phalcon#137): "This has not been addressed forever - sad to write this. If this is still required we can either get a new issue with more context or implement it in the incubator." [link](https://github.com/phalcon/phalcon/issues/137#issuecomment-4654588794)
- niden (2019-02-16, #13816): "Honestly I don't think that Phalcon should perform this task i.e. minify JS/CSS or HTML. However we can come up with some sort of mechanism where we can attach a filter". [link](https://github.com/phalcon/cphalcon/issues/13816#issuecomment-464351195)
- niden (2026-06-07, phalcon#70): "This is available in v6 but will not be in v5 since we are not going to rewrite a library in C." [link](https://github.com/phalcon/phalcon/issues/70#issuecomment-4641432925)

**BC cost and rejected changes:**
- niden (2019-05-16, #13942): "would require significant changes to the volt parser and would pretty much require all existing applications to be fully rewritten … The reward by doing this is not justifying the effort". [link](https://github.com/phalcon/cphalcon/issues/13942#issuecomment-493110655)
- phalcon (2013-07-08, #804): "The framework is designed to work with multiple template engines, changing that behavior in partial would break applications that already use this functionality." [link](https://github.com/phalcon/cphalcon/issues/804#issuecomment-20637455)

**Collisions and reserved words:**
- niden (2020-05-21, #15047): "there will always be a conflict between a service and a variable with the same name." [link](https://github.com/phalcon/cphalcon/issues/15047#issuecomment-632066054)
- niden (2024-01-06, #15156): "`return` is a reserved word for Volt. You can use a different name for the variable so as to avoid collisions." [link](https://github.com/phalcon/cphalcon/issues/15156#issuecomment-1879866245)

**Partial caching:**
- niden (2019-02-10, #13798): "It might be difficult to implement, if at all possible." [link](https://github.com/phalcon/cphalcon/issues/13798#issuecomment-462147449)

Note for the RFC: phalcon/volt (the PHP parser used by v6) was aligned with the cphalcon grammar in April 2026. niden's #17564 and #17566 are written against "both projects", so any grammar or API change needs to land in cphalcon and phalcon/volt together.
