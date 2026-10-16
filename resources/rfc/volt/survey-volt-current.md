# Volt: how it works today (survey for the Volt NFR)

**Baseline.** Branch `nfr-volt`, which is upstream `phalcon/cphalcon` master @ `33f1076a88` (2026-10-16, Phalcon 5.23.0). The stale v7 branch is `upstream/7.0.x`, forked at `18a6c1efb9` on 2026-04-23.

**Method.** I read the code, and I also compiled and rendered several hundred probe templates. For that I built the extension from `HEAD`'s `ext/` in a scratch directory, using an unmodified `phpize && ./configure && make`; it loads as `phalcon 5.23.0`. A **(probe)** tag marks every behaviour claim that was run this way, not only read. No source file in the repository was changed.

**Path abbreviations** used in the file:line references:

| Short | File |
|---|---|
| `C:` | `phalcon/Mvc/View/Engine/Volt/Compiler.zep` |
| `V:` | `phalcon/Mvc/View/Engine/Volt.zep` |
| `E:` | `phalcon/Mvc/View/Engine/Volt/Exception.zep` and `Volt/Exceptions/*.zep` |
| `S:` | `ext/phalcon/mvc/view/engine/volt/scanner.re` |
| `SH:` | `ext/phalcon/mvc/view/engine/volt/scanner.h` |
| `G:` | `ext/phalcon/mvc/view/engine/volt/parser.php.lemon` |
| `H:` | `ext/phalcon/mvc/view/engine/volt/parser.php.inc.h` (AST node builders) |
| `B:` | `ext/phalcon/mvc/view/engine/volt/base.c` |
| `T:` | `tests/unit/Mvc/View/Engine/Volt/` |
| `A:` | `tests/support/assets/views/` |

---

## 0. Key findings

1. **Nested blocks are not supported at all.** They fail at **parse time** (`B:654-663`), whether the template is a parent, a child or a standalone file. The same error, with the same misleading message, is raised for a block inside `if`, `for` or `switch`. A block inside `macro` or `autoescape` does parse, but when that template is used as a parent its output is **silently scrambled**. Details are in section 2.5.
2. **There is no dependency tracking.** With `stat=true`, changing a parent or a statically included template does not recompile its children (probe). No test covers it. Separately, a caching issue with `stat=false` and inheritance was reported to the maintainers privately on 2026-10-16; details are left out of this file (section 2.7).
3. The **extension API is compile-time only and duck-typed.** Hooks and closures return PHP source strings that are baked into the cached file. There is no runtime-callable registration, no interface, and no "safe HTML" marking. Section 4 has the details.
4. **Grammar and compiler disagree in several places:**
   - `cache` parses, then fails to compile.
   - `call` parses, then compiles to nothing.
   - `++` and `--` parse, then throw.
   - `is not <fn-test>` compiles to `!=` against a macro call.
   - The arithmetic precedence in the grammar is inverted, so the AST is wrong. The flat PHP that gets emitted happens to produce the right result.
   - Empty `if` crashes with a `TypeError`.
5. **The compiled template has no source map.** Runtime errors point at the compiled file and its line numbers (probe). Parser errors are thrown as `Mvc\View\Exception`, not as `Volt\Exception`.

---

## 1. Architecture

### 1.1 Pipeline

```
template file / string
  └─ Compiler::compile($path)                                C:304-521
       ├─ resolve compiled path (options, virtualPaths cache) C:404-454
       ├─ up to date? (exists / always / stat+mtime)         C:459-516
       └─ compileFile($path, $compiledPath, $extendsMode)    C:725-772
            └─ compileSource($code, $extendsMode)            C:2327-2471
                 ├─ reset per-template state                 C:2337-2343
                 ├─ phvolt_parse_view($code, $path)          C:2365  → B:191-209
                 │    ├─ re2c scanner phvolt_get_token       S:82-849
                 │    ├─ token pre-filter / structural checks B:301-802
                 │    └─ Lemon LALR parser                   G:176-825 (node builders H:*)
                 ├─ statementList($ast, $extendsMode)        C:2718-3012
                 │    └─ compileIf / compileForeach / … / expression() / functionCall() / resolveFilter()
                 └─ extends? merge parent blocks             C:2379-2453
            └─ file_put_contents(compiled)   (array → serialize())   C:757-769
Volt::render()  → require compiledPath                       V:264-308
```

- `Compiler::parse($code)` (`C:2203-2208`) returns the raw AST. The file name is fixed to `"eval code"`.
- `compileString()` (`C:1310-1315`) compiles a string without writing a file. It also sets `currentPath = "eval code"`.
- Parsing is done by C code that is called from Zephir through a custom optimizer (`optimizers/PhvoltParseViewOptimizer.php`). There is no PHP-level parser.

### 1.2 AST node shape (what `Compiler::parse()` returns)

The AST is a PHP list of statement arrays.

- Every node carries `file` and `line` (set from the scanner state in `H:*`). The exceptions are the `set` statement node (`H:186`) and the argument lists themselves.
- Type codes come from `SH:28-165`. Single-character operators use their ASCII code: `'+'`=43, `'-'`=45, `'*'`=42, `'/'`=47, `'%'`=37, `'.'`=46, `'!'`=33, `'<'`=60, `'>'`=62, `'|'`=124, `'~'`=126.

**Statements**

| Statement | `type` | Keys | Builder |
|---|---|---|---|
| raw text | 357 `RAW_FRAGMENT` | `value` | `H:37` |
| `{{ e }}` | 359 `ECHO` | `expr` | `H:212` |
| `if` | 300 | `expr`, `true_statements`?, `false_statements`? | `H:54` |
| `elseif` | 302 | `expr` (a **flat marker** inside `true_statements`, not a nested node) | `H:75` |
| `for` | 304 | `variable` (string), `key`?, `expr`, `if_expr`?, `block_statements` | `H:136` |
| `else`/`elsefor` in a for | 321 | — (flat marker inside `block_statements`) | `H:88` |
| `switch` | 411 | `expr`, `case_clauses`? | `H:100` |
| `case` / `default` | 412 / 413 | `expr` (case only); flat markers inside `case_clauses` | `H:118` |
| `set` | 306 | `assignments: [{variable: expr, op: 61\|281..284, expr, file, line}]` (no file/line on the statement) | `H:186-210` |
| `block` | 307 | `name` (string), `block_statements`? | `H:225` |
| `extends` | 310 | `path` (an **expression** node) | `H:292` |
| `include` | 313 | `path` (expr), `params`? (expr) | `H:306` |
| `do` | 316 | `expr` | `H:324` |
| `return` | 327 | `expr` | `H:338` |
| `autoescape` | 317 | `enable` (0/1), `block_statements` | `H:352` |
| `macro` | 322 | `name`, `parameters: [{variable, default?, file, line}]`?, `block_statements` | `H:247-290` |
| `call` | 325 | `name` (expr), `arguments`?, `caller`? | `H:514` |
| `cache` | 314 | `expr`, `lifetime`?, `block_statements` | `H:166` |
| `break` / `continue` | 320 / 319 | — | `H:380-402` |
| `{% %}` | 358 | — | `H:368` |

**Expressions** (built by `phvolt_ret_expr`, `H:450`)

- General keys: `type`, `left`?, `right`?, `ternary`?.
- Literals: `{type: 258|259|260|265, value}` for integer, double, string and identifier. `null`, `false` and `true` are 261, 262 and 263.
- Function call: `{type: 350 FCALL, name: expr, arguments?: [named_item…]}` (`H:496`).
- Named item: `{expr, name?, file, line}` (`H:432`). It is used for arguments and for array items, so an argument list is an **array of these items with no `type` key**.
- Array literal: `{type: 360, left?: [named_item…]}`. Array access: 361. Dot: 46. Pipe (filter): 124, with the filter in `right` as an identifier (265) or a call (350). Slice: `{type: 365, left, start?, end?}` (`H:475`). Ternary: `{type: 366, ternary: cond, left: then, right: else}`.
- Tests: `is` = 311; `is defined` = 363 / `is not defined` = 362; `in` = 309 / `not in` = 367; the `is empty|even|odd|numeric|scalar|iterable` family is 386-391, and the negated forms are 392-397.
- Compiler-internal: 364 `RESOLVED_EXPR` (`{value: <php code>}`), injected for filter arguments (`C:2569-2581`).

Sample from a probe:

```json
[{"type":310,"path":{"type":260,"value":"a.volt",…}},
 {"type":307,"name":"t","block_statements":[{"type":357,"value":"x",…},{"type":359,"expr":{"type":265,"value":"y",…},…}],…}]
```

### 1.3 Compiler dispatch

`statementList()` (`C:2718-3012`) loops over the statements:
- It first offers each one to the extensions (`compileStatement`, `C:2765-2781`).
- Then it switches on `type`. Each type maps to `compileIf`, `compileElseIf`, `compileSwitch`, `compileCase`, `compileForeach`, `compileSet`, `compileEcho`, the block/extends handling inline, `compileInclude`, `compileDo`, `compileReturn`, `compileAutoEscape`, `continue`/`break` inline, `compileForElse`, `compileMacro`, or `compileCall`.
- Anything else throws `UnknownVoltStatement` (`C:2988-2989`). Type 314 (`cache`) has no case, so it ends up here.

`expression()` (`C:1386-1782`) is `final`. In order, it:
1. offers the node to `resolveExpression` (`C:1402-1415`);
2. handles argument and array lists, which have no `type` (`C:1417-1451`);
3. sends dot nodes to `attributeReader()` (`C:1456`);
4. resolves `left` (`C:1465`);
5. handles `is` (`C:1472-1479`) and the pipe, type 124 (`C:1484-1491`);
6. resolves `right` (`C:1496`);
7. switches on the remaining types (`C:1502-1774`), and throws `UnknownVoltExpression` by default (`C:1773`).

Operators are emitted as **flat infix PHP without parentheses**, except for `ENCLOSED` (356).

### 1.4 Compile options

The options are read on every `compile()` call (`C:304-399`). They are set through `Volt::setOptions()` (`V:329`), which passes them to the compiler only when the compiler is first created (`V:110-114`), or through `Compiler::setOptions()` / `setOption()` (`C:2283-2310`).

| Key | Deprecated alias | Default | Validation | Effect | Ref |
|---|---|---|---|---|---|
| `always` | `compileAlways` (`E_USER_DEPRECATED`) | `false` | bool, else `InvalidOptionType` | recompile on every render | `C:317-330` |
| `prefix` | — | `""` | string | prepended to the compiled **file name**. Unrelated to `setUniquePrefix()`, which is the variable prefix (`C:2161-2190`, `C:2315`). | `C:335-341`, `433-435` |
| `path` | `compiledPath` | `""` | string, or `Closure(templatePath, options, extendsMode): string`; else `InvalidPathType` / `InvalidPathClosureReturn` | the compiled directory. If empty, the compiled file sits next to the template (`templatePath . extension`). | `C:347-356`, `404-454` |
| `separator` | `compiledSeparator` | `"%%"` | string | replaces `/`, `\` and `:` in `realpath()`, and **lowercases** the path (`ext/kernel/file.c:314-344`) | `C:361-374`, `414-423` |
| `extension` | `compiledExtension` | `".php"` | string | compiled file suffix | `C:379-392` |
| `stat` | — | `true` | **none** (only `=== true` is tested) | compare mtimes when the compiled file exists | `C:397-399`, `470-515` |
| `autoescape` | — | unset (false) | bool | sets the global echo escaping, read in `compileSource` | `C:2356-2362` |

- Extends mode (compiling a template as a parent) adds `separator . "e" . separator` before the extension, for example `layout.volt%%e%%.php` (`C:432-433`). That file holds `serialize()`d blocks (`C:757-758`), which are read back with `unserialize(…, ["allowed_classes" => false])` and recompiled when the result is not an array (`C:496-509`).
- `virtualPaths` (`C:158`, CP-17668) caches the separator-encoded path for each template path. `setOption()` and `setOptions()` clear it (`C:2290`, `2307`).
- Because the virtual path is lowercased, `Index.volt` and `index.volt` in the same directory share one compiled file on a case-sensitive filesystem.

### 1.5 Template path resolution (`extends` and static `include`)

`getFinalPath()` (`C:2478-2518`) works like this:
- An absolute path (Unix, UNC or `C:`) is used as is (`C:2486-2488`, `C:3064-3081`).
- `./` and `../` are relative to the directory of the template being compiled (`C:2494-2496`, #17269).
- Otherwise the path is joined to `View::getViewsDir()`:
  - **Multiple view dirs** (an array) are tried in order, and the first one where the file exists wins.
  - If none has the file, the **last** dir is used, which then fails with `TemplateFileNotFound` (`C:2503-2511`).

A static `include` needs the file **extension** (`{% include "p" %}` gives `TemplateFileNotFound`). A dynamic `include … with` goes through `View::partial()`, which accepts both `"p"` and `"p.volt"` (`View/Simple.zep:487-506`) (probe).

### 1.6 How a compiled template runs

`Volt::render($path, $params, $mustClean)` (`V:264-308`) does the following:
1. Fires `view:beforeCompile`, which can cancel by returning `false`.
2. Calls `compile($path)`. Both events fire **even when the compile step is a cache hit**.
3. Fires `view:afterCompile`.
4. Exports `$params` into the current symbol table with `let {key} = value` (`V:297-301`).
5. Runs `require $compiledTemplatePath` (`V:303`).

What this means for the template:
- **`$this` is the `Volt` engine.** `Volt` extends `AbstractEngine`, which `extends Injectable` (`AbstractEngine.zep:23`). DI services are reached through `Injectable::__get()` (`Di/Injectable.zep:60-110`). This is how the generated `$this->escaper`, `$this->url`, `$this->tag` and `$this->helper` work. The engine provides `$this->partial()`, `$this->getContent()` (`AbstractEngine.zep:49-83`), `$this->callMacro()`, `$this->slice()` and so on.
- **Variables are plain PHP locals.** `{{ x }}` compiles to `$x` (`C:1617-1619`), and a missing variable produces a PHP warning. Zephir locals of `render()` such as `$path` and `$compiledTemplatePath` are *not* visible (probe).
- **DI shadowing is decided at compile time.**
  - `x.y` compiles to `$this->x->y` when the compiler's container `has('x')` at compile time, and to `$x->y` otherwise (`C:258-262`). With `FactoryDefault`, a view variable named `request`, `url`, `tag`, `filter`, `assets`, `security`, … is therefore shadowed: `{{ request.name }}` becomes `<?= $this->request->name ?>` (probe).
  - The decision is frozen into the cache.
  - The same compile-time DI check picks `$this->helper->lower()` over `strtolower()` for the `lower` filter (`C:2677-2681`), and also decides TagFactory routing (`C:2007-2023`).
- **Function-style helpers are hard-coded**, for example `url()` → `$this->url->get(…)` (`C:2028-2030`). See section 3.9.
- **Scope is shared with partials.** `partial()` / `include … with` without a params array runs in the **caller's symbol table**: `View/Simple.zep:196-210` and `View.zep:586-596` call `create_symbol_table()` only when the params are an array. A `{% set %}` inside such a partial overwrites the caller's variables (probe: `name=overwritten`). A statically inlined `include` shares scope by design.
- **Macros are runtime closures.** They are stored in `Volt::$macros` (`V:44`) when the defining code runs, bound to `$this` (`C:1152`), and they persist across templates rendered by the same engine instance.

### 1.7 Runtime helpers on the engine (`Volt.zep`)

| Method | Used by | Behaviour |
|---|---|---|
| `callMacro(name, args)` `V:61-70` | every unknown function name (`C:2069`) | `MacroNotFound` if the name is not defined |
| `convertEncoding(text, from, to)` `V:77-84` | `convert_encoding` filter | `mb_convert_encoding(text, to, from)`; `MbstringRequired` without mbstring |
| `isIncluded(needle, haystack)` `V:150-169` | `in` / `not in` | `in_array` (loose) or `mb_strpos`/`strpos`; `InvalidHaystack` for any other type (for example a `Traversable`) |
| `length(item)` `V:180-195` | `length` filter | `count()` for an object or array, else `mb_strlen`; `null` → 0 |
| `preload(params)` `V:208-253` | `preload()` function | adds a `Link: <…>; rel=preload` header through the `response` service; strips `'` (legacy, `@todo`) |
| `slice(value, start, end)` `V:341-408` | `a[1:3]`, `slice` filter | **`end` is inclusive**. For an object it needs `Iterator` and `Countable` (calls `rewind()` and `count()`), else `array_slice` / `mb_substr` |
| `sort(array)` `V:416-421` | `sort` filter | `asort` (keeps keys, no flags) |
| `getCompiler()` `V:89-120` | — | lazy; passes DI and options **once**. A later `setOptions()` does not reach an existing compiler (probe). |

### 1.8 Events

- `view:beforeCompile` and `view:afterCompile` on the engine's events manager (`V:278-290`). Either can stop rendering.
- There are no compiler events. Compiler-level extensibility comes only from extension objects (section 4).

---

## 2. Template inheritance

### 2.1 How a child compiles (single level)

Example child: `{% extends "p.volt" %}{% block a %}…{% endblock %}`.

1. The **parser** sets `extends_mode` when it sees `extends`.
   - `extends` must be the first "positional" statement: `state->statement_position != 1` raises "Extends statement must be placed at the first line…" (`B:765-774`).
   - In extends mode, these are rejected at block level 0 with "Child templates only may contain blocks": `{{` (`B:439-446`), `if` (`B:480-485`), `for` (`B:519-524`), `switch` (`B:544-548`), non-blank raw text (`B:597-605`) and `set` (`B:617-622`).
   - Whitespace-only raw text at level 0 is dropped (`B:599-605`).
2. In `statementList(ast, extendsMode=false)`, the `EXTENDS` case (`C:2880-2916`):
   - computes `getFinalPath(path["value"])`;
   - runs `subCompiler = clone this` and then `subCompiler->compile(parentPath, true)`, which compiles the parent in **extends mode** into `parent%%e%%.php`;
   - if that call returns `null`, reads the e-file contents as a string (`C:2906-2910`);
   - stores the result in `this->extendedBlocks`, sets `this->extended = true`, and switches the local `blockMode = true`.
3. When the **parent is compiled in extends mode** (`blockMode = true`, `C:2734-2739`), its top-level text is collected in `compilation`. At each `BLOCK` (`C:2840-2878`):
   - `blocks[] = compilation` stores the text so far as an **unnamed chunk**, already compiled PHP;
   - `blocks[name] = block_statements` stores the block as **raw AST, not compiled**.
   - At the end of the level-1 list, the trailing text becomes another unnamed chunk (`C:2997-3007`).
   - `compileSource` returns `this->blocks` (`C:2455-2468`), and `compileFile` serializes it.
4. Back in the child, the child's own `BLOCK`s are recorded the same way into `this->blocks`, as AST.
5. **Merge** (`compileSource`, `C:2379-2453`). For each `name => block` of `extendedBlocks`, **in the parent's order**:
   - **String key, child defines it** (`array_key_exists`, `C:2408`): set `this->currentBlock = name` (`C:2413`) and run `statementList(child AST)`.
   - **String key, child does not define it:** compile the parent's AST **in the child's compiler context** with `statementList(block)` (`C:2424-2429`), or append the block as is when it is already a string (`C:2430-2432`).
   - **Integer key:** append the parent's compiled chunk (`C:2440-2448`).
   - The result is a single string. In extends mode (that is, a mid-level parent) it is an array with the same keys (`C:2385-2389`, `2435-2436`).
6. `#17294` (`C:2394-2401`): a child that defines no blocks has `blocks = null`, which used to crash `array_key_exists`. It is now coerced to `[]`.

### 2.2 State involved

| Property | Meaning | Lifetime |
|---|---|---|
| `extended` (`C:91`) | the current template has an `extends` | reset per `compileSource` (`C:2337`, CP-17668) |
| `extendedBlocks` (`C:100`) | the parent's blocks: AST arrays or compiled strings, **or the raw e-file string** (section 2.7) | reset per `compileSource` |
| `blocks` (`C:70`) | this template's named blocks (AST) plus unnamed chunks (compiled strings) | reset per `compileSource` |
| `blockLevel` (`C:61`) | nesting depth in block mode. In a child, the `EXTENDS` list enters with `blockMode=false` and leaves with `blockMode=true`, so it decrements without a matching increment and the level becomes -1 (`C:2737-2739`, `2914`, `2997-3006`). Fragile, but it is what keeps child top-level chunks from being re-added. | reset per `compileSource` |
| `currentBlock` (`C:82`) | the block that `super()` refers to. Set **only** for child-defined blocks (`C:2413`). **Never reset.** | per compiler instance |
| `exprLevel` (`C:89`) | depth of `expression()` recursion; decides how `super()` is emitted | reset per `compileSource` |

### 2.3 `super()`

`functionCall()` handles `super()` at `C:1925-1962`:
- It looks up `extendedBlocks[currentBlock]`.
- An AST block is compiled now with `statementListOrExtends` (`C:3020-3059`). A string block is used as is.
- At expression level 1 the code is emitted raw. `compileEcho` returns it without `<?= ?>` and without escaping (`C:663-668`).
- At deeper levels the code is passed through `addslashes()` and wrapped in single quotes (`C:1937-1957`).

| Case | Result |
|---|---|
| `{{ super() }}` in an overriding child block | ✔ parent content inlined (probe `[T-parent]-child`) |
| `{% if c %}{{ super() }}{% endif %}` | ✔ (probe) |
| `{{ super() ~ "x" }}`, `{{ super()\|upper }}` with **static** parent text | ✔ only because the parent block contains no PHP: `<?= 'T-parent' . '-child' ?>` (probe) |
| the same with a parent block containing `{{ name }}` | ✖ **silently wrong**: prints the PHP source `<?= $name ?>` as text (probe: `<?= '<?= $name ?>' . '!' ?>`) |
| `{% set p = super() %}` | ✖ emitted unquoted, `$p = T-parent;`, then a runtime `Error: Undefined constant "T"` (probe) |
| `super()` inside a **parent** block that the child does not override | ✖ **silently wrong**: the stale `currentBlock` from the previous child block is used, so it inlines a *different* block (probe: `<p>CA\|PB(PA)</p>`) |
| `{{ super() }}` in a template rendered without `extends` | ✖ prints the literal text `''`: `C:1961` returns `"''"` and `compileEcho` emits it raw (probe `PB('')`) |
| autoescape | `super()` output is never escaped (`C:666-668`) |
| test coverage | no compile or render test uses `super()`. The fixtures `A:extends/children2.volt` and `A:templates/c.volt` are unused (section 9). |

### 2.4 Multi-level inheritance (#17294, CP-17668)

The chain `leaf → mid → base` works (probe):
- base: `<b>{% block a %}A0…`
- mid: `{% block a %}A1({{ super() }})…`
- leaf: `{% block a %}A2({{ super() }})…`
- Result: `<b>A2(A1(A0))|B1(B0World)|C2(C0)</b>`. A chain that is empty in the middle (`deep → empty → mid → base`) also works.

How the chain is stored:
- A **root** parent's e-file stores named blocks as AST (`a:…{s:1:"a";a:1:{…type 357…}}`).
- A **mid-level** parent's e-file stores fully compiled strings (`s:1:"a";s:6:"A1(A0)"`).
- So `super()` from a leaf receives already-compiled code from mid-level parents and AST from the root.

Recent fixes:
- **#17294** (`c243b7560c`, `aaab3bb8ad`, 2026-07-07): null-blocks segfault (`C:2394-2401`). Test: `T:CompilerFilesTest.php:264`.
- **CP-17668** (2026-10-14):
  - `6ccb782539` moved the state reset from `compile()` into `compileSource()` (`C:2333-2343`), so `compileString()` and clones no longer leak blocks or extends state from an earlier template.
  - `f9877cd1f4` added the `virtualPaths` cache.
  - `8e1ac7d181` skips extension events when there are no extensions, and re-reads `extensions` for each statement.

### 2.5 Nested blocks: verdict from the code (all verified by probe)

The parser keeps a single counter, `state->block_level`. It is incremented by `block` (`B:654-663`), and **also by `if`, `for` and `switch`** (`B:486-487`, `527-528`, `554-555`). A `block` token is rejected whenever `block_level > 0`. `macro`, `autoescape`, `call` and `cache` do **not** touch the counter.

| Template | What happens |
|---|---|
| Parent: `{% block outer %}…{% block inner %}…{% endblock %}…{% endblock %}` | **Throws** `Phalcon\Mvc\View\Exception`: "Embedding blocks into other blocks is not supported in …/parent.volt on line 1". Also thrown when the file is rendered standalone, without any `extends`. |
| Child that overrides only `inner` (parent as above) | **Throws** the same error, naming the *parent* file, because the parent cannot be parsed. Overriding an inner block is impossible. |
| Child that itself contains nested blocks | **Throws** at parse time of the child. |
| `super()` inside a nested block | Unreachable, because nesting never parses. |
| `{% if %}{% block a %}…{% endblock %}{% endif %}`, or the same inside `for` or `switch` | **Throws** the same "Embedding blocks into other blocks" message, even though nothing is nested in a block. |
| `{% macro m() %}M[{% block a %}…{% endblock %}]{% endmacro %}` | Standalone: works, and the block is inlined (`C:2869-2876`). **As a parent:** it parses, but the output is **silently scrambled**. A block at `blockLevel` 2 splits the macro body into unnamed chunks out of order. Probe: the child gives `M[A-child<p>]</p>` instead of `<p>M[A-child]</p>`, and the macro body is lost. |
| `{% autoescape true %}X{% block a %}…{% endblock %}Y{% endautoescape %}` | Standalone: works. **As a parent:** order scrambled (`XA-child<i><p>Y</p>`), and the child's override is **not escaped**, because the parent's autoescape context is lost. Silent. |
| Block inside `call` / `cache` | Parses; the statement is then dropped (`call`) or throws (`cache`), see section 3. |
| Parser tests | No test covers any of these cases (section 9). |

On the compiler side, nothing prevents nesting (`C:2840-2878` recurses through `statementList`). The limitation lives in the parser, and the compiler's flat `blocks` map has no notion of parent and child blocks: names are global, chunks are positional, and `currentBlock` is a single scalar.

### 2.6 Other inheritance edge cases (probe)

| Case | Result |
|---|---|
| `hello {% extends … %}` | throws "Extends statement must be placed at the first line" |
| `{# c #}\n{% extends … %}` | OK. Comments are not positional. |
| `{% set x = 1 %}{% extends … %}` | **accepted**, because `set` does not increment `statement_position` (`S:347-357`). The assignment is then **silently dropped**: "Undefined variable $x" at runtime. |
| `{% extends layoutVar %}` | the grammar accepts any expression (`G:495-497`), but the compiler reads `path["value"]` (`C:2884-2888`), so the identifier is used as a **literal file name**, giving `TemplateFileNotFound …/layoutVar` |
| `{% extends "lay" ~ "out.volt" %}` | no `value` key: a PHP notice, the path becomes the views **directory**, reading it fails, the output is empty, and a junk `…%%e%%.php` file is written |
| a child block that the parent does not define | silently dropped. The merge iterates only the parent's keys (`C:2403`). |
| the same block name twice | the last one wins, silently (`C:2867`) |
| `{% do … %}` or `{% include … %}` at child top level | allowed by the parser, compiled into an unnamed chunk (`C:2858-2861`), **never emitted**. The included file is still compiled. |
| `{% macro %}` at child top level | throws "Child templates only may contain blocks", because the macro body contains `{{` or raw text at `block_level` 0 |
| a parent block compiled in the child | compiled with the **child's** compiler state: extensions, the autoescape flag and the stale `currentBlock` |

### 2.7 Caching and inheritance

- **`stat=false`:** a caching issue with `stat=false` and inheritance was reported to the maintainers privately on 2026-10-16; details are left out of this file.
- **No dependency tracking.** `compare_mtime(template, compiled)` (`C:475`, `ext/kernel/file.c:88-108`) checks only the template's own file. Editing a parent or a statically included file leaves children stale until they are touched or `always=true` (probe: `P1` stays `P1`, `INC1` stays `INC1`).
- Extends-mode caches are separate files (`%%e%%`) and are reused across children. Static includes are inlined into each includer.

---

## 3. Syntax inventory

### 3.1 Delimiters, comments, whitespace control

- **Delimiters:** `{{ … }}` for echo, `{% … %}` for statements, `{# … #}` for comments (`S:103-141`).
- **Comments** are removed in the scanner, and the raw text on either side is merged: `a {# c #} b` → raw `"a  b"`.
- **Whitespace control:**
  - `{%-` and `{{-` right-trim the **preceding** raw fragment. The scanner checks `double_next == '-'` before switching mode (`S:119-121`).
  - `-%}` and `-}}` set `whitespace_control = 1`, which left-trims the **next** raw fragment (`S:114-117`, `589-599`, `622-628`).
  - The `{%-` / `{{-` token rules themselves only reset the flag (`S:583-587`, `615-620`).
  - There is no "trim one newline" mode, and no `~` modifier.
- **`{% verbatim %}…{% endverbatim %}`** (#17085, 5.14.0): the body is literal (`S:157-260`, `G:487-493`). It replaced the never-compilable `{% raw %}`.

### 3.2 Statements

| Syntax | Grammar | Compiles to | Notes |
|---|---|---|---|
| `{{ expr }}` | `G:459` | `<?= expr ?>`, or `<?= $this->escaper->html(expr) ?>` under autoescape (`C:639-680`) | `tag.*()` calls are recompiled with double-quoted strings (`C:655-658`) |
| `{% if %}…{% elseif %}…{% else %}…{% endif %}` | `G:287-313` | `<?php if (…) { ?>…<?php } elseif (…) { ?>…<?php } else { ?>…<?php } ?>` (`C:965-995`, `689-704`) | `elseif` is a flat marker. ✖ `{% if x %}{% endif %}` throws a `TypeError`: the builder omits `true_statements` (`G:292`) and `C:980` reads it unconditionally (probe). ✖ `{% if x %}{% else %}y{% endif %}` is a **syntax error**: there is no grammar rule for an empty then-branch with a non-empty else (probe). A stray `elseif` reports "Unexpected ENDIF" (`B:504-511`). |
| `{% for v in e %}` / `{% for k, v in e %}` / `… if cond %}` … `{% else %}` / `{% elsefor %}` … `{% endfor %}` | `G:315-333` | `foreach` plus an optional `if` and an `$…iterated` flag for else (`C:784-952`) | `else` is turned into `ELSEFOR` when `if_level==0 && for_level>0` (`B:492-498`). ✖ An empty body is a syntax error. |
| `{% switch e %}{% case x %}…{% default %}…{% endswitch %}` | `G:336-353` | `<?php switch (…): ?><?php case …: ?>…<?php endswitch ?>` (`C:1324-1377`, `584-606`) | Horizontal whitespace inside the cases is stripped by a regex (`C:1364-1368`). Nested `switch` is rejected (`B:549-552`). `default` is a keyword only right after `{%` inside a switch (`B:574-582`, #16003). |
| `{% set a = e %}`, `+=`, `-=`, `*=`, `/=`, comma-separated; targets `a`, `a[e]`, `a.b` | `G:355-397` | `<?php $a = …; $b += …; ?>` (`C:1238-1299`) | `set` is not positional for the extends check (section 2.6) |
| `{% do e %}` | `G:507` | `<?php e; ?>` (`C:615-630`) | |
| `{% return e %}` | `G:511` | `<?php return e; ?>` (`C:1164-1179`) | used for macro return values. At top level it ends the `require`. |
| `{% include "file.volt" %}` | `G:499` | **static**: compile time, through `clone this`, with the compiled PHP inlined (`C:1023-1055`) | needs the extension. Bound by the stale-cache issue (section 2.7). |
| `{% include expr %}` / `{% include e with params %}` | `G:499-505` | `<?php $this->partial(path[, params]); ?>` (`C:1061-1070`) | runtime. Without `with`, it shares the symbol table (section 1.6). |
| `{% macro n(a, b = 1) %}…{% endmacro %}` | `G:399-445` | closure stored in `$this->macros['n']` and bound to `$this` (`C:1080-1155`) | see section 3.4 |
| `{% call m(args) %}…{% endcall %}` | `G:447-453` | **`""`**: `compileCall` is a stub, "Not implemented?" (`C:568-572`) | ✖ the whole block silently disappears (probe) |
| `{% cache key [ttl] %}…{% endcache %}` | `G:471-485` | ✖ **`UnknownVoltStatement` "Unknown statement 314"**: no case in `statementList` | parser-only feature (probe) |
| `{% autoescape true\|false %}…{% endautoescape %}` | `G:515-521` | compile-time toggle (`C:533-558`) | only literal `true`/`false` |
| `{% block n %}…{% endblock %}` | `G:463-469` | section 2 | |
| `{% extends expr %}` | `G:495-497` | section 2 | only a string literal really works |
| `{% break %}`, `{% continue %}` | `G:523-529` | `<?php break; ?>` / `<?php continue; ?>` (`C:2939-2951`) | not checked to be inside a loop. `break` inside a case breaks the switch. |
| `{% %}` | `G:455` | nothing (`C:2982-2986`) | |
| `{% verbatim %}` | `G:487-493` | literal text | |

**Not available:** `raw` (statement or filter), `with … endwith`, `apply` / `filter` blocks, `import` / `from`, `embed`, `use`, `spaceless`, `sandbox`, a `for` over a range with a step, a `for … else` loop variable outside the loop, or anything like `set … endset` to capture a block.

### 3.3 The `loop` variable

The loop context is generated **only if `loop` is referenced** inside the `for` body: `attributeReader` records `loopPointers[level]` (`C:249-252`), and `C:850-859` / `892-899` emit the setup code.

- **Fields:** `self` (a reference to the loop object), `length` (`count()` of the iterable, which therefore **requires `Countable`**), `index`, `index0`, `revindex`, `revindex0`, `first`, `last`.
- There is no `parent`, `depth`, `previtem` or `nextitem`.
- `loop` always refers to the **innermost** loop.
- `index0` is initialised to `1` before the first iteration (`C:857`). This is harmless because it is overwritten in the body.
- `loop` used outside any `for` compiles to an undefined `$<prefix>0loop`.
- `loopPointers` and `forElsePointers` are never reset between templates (the reset at `C:2337-2343` omits them).

### 3.4 Macros

- **Parameters:**
  - Defaults must be **literal** integer, string, double, `null`, `false` or `true` (`G:423-445`). Negative numbers, arrays and expressions are syntax errors (probe).
  - An empty macro body is a syntax error.
  - Nested macros are rejected (`B:670-683`).
- **Calls:** `{{ m(1, 2) }}` or named arguments with **quoted** keys, `{{ m("b": 2, "a": 1) }}`. The form `m(b: 2)` is a syntax error (probe).
  - The compiled closure takes `$__p` and tries the positional index first, then the name, then the default.
  - If a parameter is still missing, it throws a runtime `\Phalcon\Mvc\View\Exception`: "Macro 'm' was called without parameter: a" (`C:1115-1132`).
- **Resolution:** any function name the compiler does not recognise compiles to `$this->callMacro('name', [args])` (`C:2069`). An undefined name raises `MacroNotFound` at **runtime** (`V:65-67`), never at compile time. This also covers plain PHP functions: `{{ get_class(x) }}` raises MacroNotFound (probe, `T:CallMacroTest.php`).
- **Output:** the macro body echoes directly. `{{ m() }}` additionally echoes the return value (normally `null`). `{% set x = m() %}` captures only `{% return %}`.
- **Duplicates:** a duplicate name raises `MacroAlreadyDefined` at compile time (`C:1096-1098`). `Compiler::$macros` is **never reset**, so one compiler that compiles two templates defining the same macro name throws (probe). Static includes avoid this only because they compile in a clone.

### 3.5 Operators and precedence

Lemon precedence, lowest to highest (`G:22-36`):

`COMMA` < `? :` < `..` < `and` `or` (same level) < `in` < `is` `==` `!=` `<` `>` `>=` `<=` `===` `!==` < `/` `*` `%` < `+` `-` `~` < `[` < `|` < `not` `!` < `++` `--` < `(` < `.`

| Volt | PHP | Ref |
|---|---|---|
| `+ - * / %` | same | `C:1507-1525` |
| `a // b` | **`a % b`** (the grammar maps `DIVIDE DIVIDE` to `MOD`, `G:563-565`; not integer division) | probe |
| `a ** b` | `pow(a, b)` | `G:555`, `C:1543` |
| `~` | `.` | `C:1539` |
| `and` / `or` / `not` / `!` | `&&` / `\|\|` / `!` (there is no `&&` or `\|\|` token) | `C:1503`, `1621-1627` |
| `== != <> === !== < > <= >=` | same | `C:1527-1651` |
| `a .. b` | `range(a, b)` | `C:1653` |
| `a in b` / `a not in b` | `$this->isIncluded(a, b)` / `!…` | `C:1748-1754` |
| `c ? a : b` | `(c ? a : b)` | `C:1756` |
| unary `-` / `+` | `-x` / `+x` | `C:1760-1766` |
| `a.b` / `a.b()` / `a[e]` | `$a->b` / `$a->b()` / `$a[e]`. **Always property access**, with no array or getter fallback. | `C:234-286`, `1665` |
| `a[1:3]`, `a[:n]`, `a[n:]` | `$this->slice(a, s, e)`. Offsets may only be an integer literal or an identifier (`G:747-753`): no negatives, no expressions. | `C:1669-1690` |
| `x++`, `x--` | ✖ parse (`G:699-705`), then `UnknownVoltExpression` "Unknown expression 279" | probe |
| `??`, `?:` | ✖ **absent** (syntax error) | probe |
| string interpolation `"#{x}"` | ✖ absent | |

**The arithmetic precedence in the AST is wrong.** `+ - ~` are declared *after* `* / %`, so they bind tighter: `1 + 2 * 3` parses as `((1 + 2) * 3)`, and `a or b and c` as `((a or b) and c)` (probe). The compiler emits flat infix without parentheses (`1 + 2 * 3`), so PHP's own precedence produces the correct result. Extensions that walk the AST (`resolveExpression`, `$exprArgs`) still see the wrong tree.

### 3.6 Literals

- Integers, doubles (`[0-9]+.[0-9]+`), `'…'` / `"…"` strings, `null` / `true` / `false`, lists `[a, b]`, and hashes `{"k": v}` or `["k": v]`. Hash keys must be **string literals** (`G:763-765`).
- **Both quote styles compile to single-quoted PHP** (`C:1564-1581`), so escape sequences such as `"a\nb"` are not interpreted. The exception is TagFactory calls, which are compiled double-quoted (`C:1583-1602`, `2014-2021`).
- `{{ {"a": {"b": 1}} }}` is a syntax error, because the inner `}}` lexes as `CLOSE_EDELIMITER`. A space fixes it (probe).
- Identifiers may contain backslashes (`S:639`), so `\Foo\bar(1)` parses. It then goes to `callMacro('\Foo\bar')` (probe).

### 3.7 Tests (`is` / `is not`)

There are two mechanisms:

1. **Dedicated keyword tokens** (`G:595-649`, `C:1692-1746`):
   - `is [not] defined` → `[!]isset(x)`
   - `empty` → `empty()`
   - `even` / `odd` → `% 2`
   - `numeric` → `is_numeric`
   - `scalar` → `is_scalar`
   - `iterable` → `is_array || instanceof Traversable`
2. **Generic `x is expr`** → `resolveTest()` (`C:2217-2268`):
   - identifiers `empty|even|odd|numeric|scalar|iterable` (already caught by the tokens);
   - calls `divisibleby(n)` → `((x) % (n)) == 0`, `sameas(y)` → `(x) === (y)`, `type("string")` → `gettype(x) === …`;
   - **anything else** → `x == expr`. For example, `x is foo` becomes `$x == $foo`.

✖ **`is not` + test function:** the scanner turns `is not` into `NOTEQUALS` (`S:433-443`). As a result, `x is not divisibleby(3)` compiles to `$x != $this->callMacro('divisibleby', [3])`, and the same happens for `sameas` and `type`. That is a runtime `MacroNotFound` (probe). There are no user-defined tests.

### 3.8 Built-in filters (`resolveFilter`, `C:2640-2707`)

How arguments are passed: the filtered value becomes the **first argument**, through an injected `RESOLVED_EXPR` node (`C:2562-2582`). `default` is the exception.

| Filter | PHP | Notes |
|---|---|---|
| `abs` | `abs(x)` | |
| `capitalize` | `ucwords(x)` | words, not the first letter only |
| `convert_encoding(from, to)` | `$this->convertEncoding(x, from, to)` | |
| `default(d)` | `(empty(x) ? (d) : (x))` | `empty()` semantics: `0` and `"0"` count as empty. Without an argument: `(empty(x) ? (x) : (x))`. |
| `e`, `escape` | `$this->escaper->html(x)` | |
| `escape_attr` / `escape_css` / `escape_js` | `$this->escaper->attributes/css/js(x)` | |
| `format(…)` | `sprintf(x, …)` | |
| `join(sep)` | `join(sep, x)` | ✖ without an argument: `TypeError` (`C:2663`, probe) |
| `json_encode` / `json_decode` | same | |
| `keys` | `array_keys(x)` | |
| `left_trim` / `right_trim` / `trim` | `ltrim` / `rtrim` / `trim` | |
| `length` | `$this->length(x)` | |
| `lower`, `lowercase` / `upper`, `uppercase` | `$this->helper->lower/upper(x)` if DI has `helper` **at compile time**, else `strtolower` / `strtoupper` | |
| `nl2br`, `slashes` (`addslashes`), `stripslashes`, `striptags` (`strip_tags`) | same | |
| `slice(s, e)` | `$this->slice(x, s, e)` | `e` is inclusive |
| `sort` | `$this->sort(x)` | `asort` |
| `url_encode` | `urlencode(x)` | PHP, not the escaper |
| unknown | `UnknownVoltFilter` 'Unknown filter "n" in F on line L' | |
| a non-identifier and non-call filter, e.g. `a\|"x"` | `UnknownVoltFilterType` | |

**Missing compared with Twig/Jinja:** `raw` / `safe`, `date`, `number_format`, `round`, `replace`, `split`, `first`, `last`, `merge`, `batch`, `reverse`, `title`, `striptags(allowed)` via a named argument, and so on.

### 3.9 Built-in functions (`functionCall`, `C:1910-2069`)

These are checked in this order, **after** the extension hooks and user functions:

| Name | PHP | Ref |
|---|---|---|
| `content()`, `get_content()` | `$this->getContent()` | `C:1910-1912` |
| `partial(p[, params])` | `$this->partial(p, params)` (echoes; returns void) | `C:1918-1920` |
| `super()` | section 2.3 | `C:1925-1962` |
| `preload(href[, attrs])` | `$this->preload(…)` | `C:1968-1970` |
| any snake_case name whose camelCase is a **static method of legacy `Phalcon\Tag`** | `\Phalcon\Tag::method(args)`. For 16 hard-coded names (`link_to`, `image`, `form_legacy`, `submit_button`, `*_field`, `text_area`, `image_input`) the arguments are wrapped in `[…]`. | `C:1976-2002` |
| a name the DI `tag` service (TagFactory) `has()` **at compile time** | `$this->tag->name(args…)`, with arguments recompiled **double-quoted** | `C:2007-2023` |
| `url(…)` / `static_url(…)` | `$this->url->get(…)` / `$this->url->getStatic(…)` | `C:2028-2037` |
| `date(…)`, `time()`, `dump(x)` (→ `var_dump`), `constant(c)` | PHP equivalents | `C:2039-2064` |
| `version()`, `version_id()` | `(new Phalcon\Support\Version)->get()` / `getId()` | `C:2051-2057` |
| anything else | `$this->callMacro('name', [args])` | `C:2069` |
| a call on a non-identifier (`a.b()`, `a[1]()`, `(a)(1)`) | `expr(args)` | `C:2072` |

Because legacy `Tag` is checked first, a TagFactory helper whose camelCase name also exists on `Phalcon\Tag` (for example `form` or `image`) goes to the legacy class.

---

## 4. Extension API: the exact contract

### 4.1 Registration

- Engine: `$volt->getCompiler()->addFunction(...) / addFilter(...) / addExtension(...)`.
- `addFunction(string $name, string|Closure $def): static` (`C:218-223`) and `addFilter(string $name, string|Closure $def): static` (`C:203-208`) only store the definition. **Validation is lazy**: a definition that is neither a string nor a Closure (for example an array callable or an invokable object) throws `InvalidUserFunctionDefinition` / `InvalidUserFilterDefinition` when the name is first compiled (`C:1903`, `C:2637`).
- `addExtension(object $ext): static` (`C:177-193`):
  - throws `InvalidExtension` for a non-object;
  - calls `$ext->initialize($compiler)` if that method exists (untested);
  - appends the extension.
  - There is no interface. Hooks are found with `method_exists` (`C:1801`).

### 4.2 Resolution order

The **first string wins**.

- **Function call `name(...)`**, bare identifiers only (`C:1853`):
  1. the extensions' `compileFunction`, in registration order;
  2. a user function from `addFunction`;
  3. the built-ins in the order of section 3.9;
  4. `callMacro`.

  User definitions therefore **override built-ins**, including `content`, `partial`, `super`, `url` and `date` (probe: `addFunction('content', …)` replaced `content()`).
- **Filter:** `compileFilter` → user filter → built-in → `UnknownVoltFilter` (`C:2593-2709`).
- **Every expression node:** `resolveExpression` runs first (`C:1402-1415`), before any child is compiled, and can replace whole subtrees, function calls included.
- **Every statement:** `compileStatement` runs first (`C:2765-2781`).

### 4.3 Hook signatures and semantics

| Hook | Called with | Return |
|---|---|---|
| `initialize(Compiler $c)` | once, inside `addExtension` | ignored |
| `compileFunction(string $name, string $resolvedArgs, ?array $exprArgs)` | `C:1866-1869` | `string` = PHP **expression** source; anything else (`null`, `false`, …) = fall through to the next extension, then the built-in path |
| `compileFilter(string $name, string $resolvedArgs, ?array $exprArgs)` | `C:2599-2602` | same as above |
| `resolveExpression(array $expr)` | `C:1407-1410`, for **every** node, including argument and array lists, which have **no `type` key** | PHP expression source, or a non-string to continue |
| `compileStatement(array $statement)` | `C:2771-2774`, for every statement at every nesting level (raw, block, extends, …) | **template output** source (HTML or `<?php … ?>`) appended verbatim, or a non-string to continue |

- `fireExtensionEvent()` (`C:1791-1820`) returns the first string. A hook cannot "claim and emit nothing" except by returning `""`, and it cannot stop later extensions without returning a string.
- `$resolvedArgs` is the comma-joined, **already compiled PHP** of the arguments (`C:1844-1848`): `'$name'`, `'\'ab\', 3'`, and so on.
  - Arguments are compiled **before** the hook runs, so their side effects (for example nested hooks) have already happened.
  - For filters, `$resolvedArgs` starts with the filtered value (`'$name, 10, \'-\''`).
- `$exprArgs` is the **raw AST** argument list `[['expr' => node, 'name'? => 'k', 'file', 'line'], …]`, or `null` when there are no parentheses or no arguments.
  - For filters, a node `{type: 364, value: '<compiled left>'}` is prepended.
  - **Exception:** for `default`, the extension receives only the default value, without the left operand (`C:2562`; probe: `compileFilter(default, '\'x\'', [260])`).
- Observed call order for `{{ f(x)|g }}`: `compileStatement(echo)` → `resolveExpression(pipe)` → `resolveExpression(f-call)` → `resolveExpression(arg list)` → `resolveExpression(x)` → `compileFunction('f', '$x', …)` → `compileFilter('g', …)`.
- `tag.*()` echoes compile the expression **twice** (`C:653-658`), so hooks fire twice.
- An extension added during compilation (for example from inside a function closure) is picked up from the next statement onward (`C:2765`, CP-17668; `T:Compiler/FireExtensionEventTest.php:55`).

### 4.4 Closures

```php
$compiler->addFunction('shuffle', function (string $resolvedArgs, ?array $exprArgs): string {
    return 'str_shuffle(' . $resolvedArgs . ')';      // PHP source, run later from the cache
});
```

- The closure runs **at compile time, once per call site**, and its return value is pasted into the cached `.php` (`C:1894-1900`, `C:2625-2631`).
- A string definition compiles to `def(args)`, so `'str_repeat'` or `'App\Volt\H::slug'` (a static method) work (`C:1886-1888`).

Examples from the test suite:

```php
// T:Compiler/AddFunctionTest.php:86-91 → {{ shuffle("hello") }} ⇒ <?= str_shuffle('hello') ?>
$volt->addFunction($name, function ($arguments) use ($funcName) {
    return $funcName . '(' . $arguments . ')';
});

// T:Compiler/AddFilterTest.php:78-83 → {{ "1,2,3,4"|separate }} ⇒ <?= explode(",", '1,2,3,4') ?>
$volt->addFilter($name, function ($arguments) use ($filter) {
    return $filter . '(",", ' . $arguments . ')';
});

// T:Compiler/FireExtensionEventTest.php:111-152 — all four hooks; output
// "raw<?= 'function' ?><?= 'expression' ?><?= 'filter' ?><?= 'other' ?>"
public function compileFunction(string $name, string $arguments, mixed $funcArguments): ?string
{ return 'ext_function' === $name ? "'function'" : null; }
public function compileStatement(array $statement): ?string
{ return 'ext_raw' === ($statement['value'] ?? null) ? 'raw' : null; }
```

`T:CompilerTest.php:185` registers `addFunction('strtotime', 'strtotime')` for a macro fixture.

### 4.5 Writing a "runtime" function today

There is no API for registering a PHP callable that is invoked at render time with evaluated arguments. The workarounds are:

1. **A string definition naming a global function or static method:** `addFunction('slug', 'App\Volt\Helpers::slug')` → `App\Volt\Helpers::slug($title)`.
2. **A DI service:** register `formatter` and write `{{ formatter.money(x) }}`, which becomes `$this->formatter->money($x)`, but only if the service exists **when compiling** (`C:258-262`). Alternatively, a closure can emit `'$this->formatter->money(' . $a . ')'`.
3. **A closure object at runtime:** the closure cannot be serialized into the cache, so it has to live somewhere the generated code can reach, such as a DI service, a static registry or `$this->getDI()`. The generated code then calls it, for example `'$this->di->get("voltFns")["money"](' . $a . ')'`.
4. **Plain PHP functions are not callable** unless registered: `{{ str_replace(…) }}` goes to `callMacro`, which raises MacroNotFound (`T:CallMacroTest.php:26`, #15842).

### 4.6 Pitfalls

- **Compile time versus render time.** `addFunction('now', fn() => "'" . microtime(true) . "'")` freezes the timestamp into the cache (probe: `<?= '1792151937.5122' ?>`). Closures see neither runtime values nor the request.
- **Caching.** Registering or changing a function does not invalidate compiled files. Only `always=true` or deleting the cache does. With `stat=true`, only template mtimes are compared.
- **Escaping.** The returned code is wrapped in `$this->escaper->html()` when autoescape is on (`C:675-677`). There is no way to mark helper output as safe, so HTML-producing helpers are double-escaped. The only opt-out is `{% autoescape false %}`.
- **Code injection.** `$exprArgs` string values are **raw token values**. Interpolating them, instead of `$resolvedArgs`, into the returned PHP lets template literals inject code. The compiler's own escaping (`C:1427-1442`, `1564-1603`) applies only to `$resolvedArgs`.
- **Expression-only output.** A function or filter must return a PHP *expression*. Only `compileStatement` may emit statements.
- **DI access** in generated code goes through `$this->…` (the engine). The compiler's container (`getDI()`) may differ from the one used at render time, and any compile-time `has()` decision is frozen.
- **AST quirks:** the precedence inversion (section 3.5), the flat `elseif` / `case` / `elsefor` markers, argument lists without `type`, and `set` nodes without `file` / `line`.
- **Tests and contract drift.** `T:Compiler/FireExtensionEventTest.php:25` calls `compileFunction(array $expr, bool $extendsMode)`, which is not the real signature. `initialize()` has no test.

---

## 5. Escaping and autoescape

- **Global:** the option `autoescape => true` (`C:2356-2362`). **Local:** `{% autoescape true|false %}` (`C:533-558`). Both are **compile-time** flags and affect only `{{ }}` echoes (`C:675-677`).
- **Not escaped:** raw text, `{% do %}`, a macro's direct output, `partial()` output (it is echoed inside the partial), static include content (compiled with its own flag, through a clone), and `super()` (`C:666-668`).
- The **whole echoed expression** is wrapped: `<?= $this->escaper->html(EXPR) ?>`. So, under autoescape:
  - `{{ x|e }}` is escaped twice: `html(html($x))`;
  - `{{ x|escape_js }}` becomes `html(js($x))`;
  - `{{ content() }}`, `{{ link_to(…) }}`, `{{ tag.a(…) }}` and `{{ url(…) }}` are all HTML-escaped (probe).
  - There is **no `raw` / `safe` filter** (`{{ x|raw }}` → `UnknownVoltFilter`) and no "safe string" type.
- **Filters:**

  | Filter | Compiles to |
  |---|---|
  | `e`, `escape` | `escaper->html` |
  | `escape_attr` | `escaper->attributes` |
  | `escape_css` | `escaper->css` |
  | `escape_js` | `escaper->js` |
  | `url_encode` | `urlencode()` (not `escaper->url`) |

  The escaper is resolved at render time as the DI service `escaper`, through `Injectable::__get`.
- **Compiler-side literal escaping**, which protects the generated PHP (advisories in 5.13-5.20):
  - single-quoted emission escapes unescaped `'` (`C:1566-1581`);
  - double-quoted emission escapes `"` and `$` (`C:1583-1602`);
  - hash keys are escaped (`C:1427-1442`);
  - `join` arguments go through `expression()` (`C:2662-2664`).
- **Autoescape state across inheritance:** a parent's `{% autoescape %}` wrapper does not apply to child overrides (section 2.5). Parent blocks are compiled with the child's global flag.

---

## 6. Errors

### 6.1 Scanner and parser errors

These are thrown as `Phalcon\Mvc\View\Exception`, **not** `Volt\Exception` (`B:197-205`). The file and line are available only inside the message.

- `Syntax error, unexpected token X(value) in F on line N` (`G:54-101`)
- `Syntax error, unexpected EOF in F[, there is one 'if' block without close | there are N 'for' blocks without close | there is a 'switch' block without 'endswitch']` (`G:102-143`). The plural "for" message prints `if_level` instead of `for_level` (`G:132`).
- `Scanning error before '…' in F on line N` / `Scanning error near to EOF in F` (`B:154-186`)
- `Parsing failed, the template expression is nested too deeply` (`G:161-165`)
- Structural messages from `B:`:

  | Message | Ref |
  |---|---|
  | `Child templates only may contain blocks` | `441`, `482`, `521`, `546`, `601`, `619` |
  | `Embedding blocks into other blocks is not supported` | `656` |
  | `Embedding macros into other macros is not allowed` | `672` |
  | `Extends statement must be placed at the first line in the template` | `767` |
  | `A nested switch detected. There is no nested switch-case statements support` | `550` |
  | `Unexpected CASE` | `562` |
  | `Unexpected ENDSWITCH` | `586` |
  | `Unexpected ENDIF` (also used for a stray **elseif**) | `506` |
  | `Scanner: unknown opcode …` | `776-788` |

### 6.2 Compiler errors

`Phalcon\Mvc\View\Engine\Volt\Exception` (`E:Exception.zep`) extends `Mvc\View\Exception` and adds `getStatement(): array`. There are 24 subclasses in `Volt/Exceptions/` (#17019, 5.14.0):

| Class | Message |
|---|---|
| `UnknownVoltStatement` | "Unknown statement T in F on line L" |
| `UnknownVoltExpression` | "Unknown expression T in F on line L" |
| `UnknownVoltFilter` | 'Unknown filter "n" in F on line L' |
| `UnknownVoltFilterType` | "Unknown filter type in F on line L" |
| `InvalidUserFunctionDefinition` / `InvalidUserFilterDefinition` | "Invalid definition for user function/filter 'n' in F on line L" |
| `MacroAlreadyDefined` | "Macro 'm' is already defined" |
| `MacroNotFound` (runtime) | "Macro 'm' does not exist" |
| `TemplateFileNotFound` / `TemplateFileNotOpenable` | "Template file P does not exist / could not be opened" |
| `TemplatePathCollision` | "Template path and compilation template path cannot be the same" |
| `VoltDirectoryNotWritable` | "Volt directory can't be written" |
| `CannotOpenCompiledFile` | "Extends compilation file P could not be opened" |
| `InvalidOptionType` | "'opt' must be a T" |
| `InvalidPathType` / `InvalidPathClosureReturn` | `path` option errors |
| `InvalidCompilationPrefix` | bad unique prefix |
| `InvalidExtension` | non-object passed to `addExtension` |
| `InvalidHaystack` / `MbstringRequired` | runtime helpers |
| `CorruptedStatement` ("Corrupted statement") / `CorruptedStatementWithData` ("Corrupt statement", carries the node) / `InvalidStatement` ("Invalid statement in F on line L") / `InvalidIntermediateRepresentation` | malformed AST |

None of them exposes the template file and line as structured data.

Non-Volt errors also escape from the compiler:
- `TypeError` for an empty `if` or `|join` without arguments;
- PHP notices for a dynamic `extends`;
- `TypeError` from `getCompiledTemplatePath()` / `getTemplatePath()` before the first compile, since both are declared `-> string` (probe);
- `getOption()` is declared `string|null` but returns booleans (probe).

### 6.3 Runtime errors

- Errors come from the **compiled file**, with **compiled line numbers**. There is no mapping back to the `.volt` file. Probe: an error on line 3 of `c.volt` (which extends a 5-line parent) reports `cache/…c.volt.php:6`. Inlined includes and inheritance shift the lines.
- A missing macro argument raises a `\Phalcon\Mvc\View\Exception` from the generated code (`C:1128`).
- The only deprecation notices are the `E_USER_DEPRECATED` warnings for option aliases (`C:319-384`).

---

## 7. 7.0.x versus master

`upstream/7.0.x` has **no Volt work that master lacks**. It has 4 Volt-touching commits after the merge base (2026-04-25), and master already has all of them, for example the `convertEncoding()` change via `d3ea3aaa14`. Master has about 60 Volt commits since 2026-04-23, so **the RFC should target master**.

**Features on master only**
- `{% verbatim %}` (#17085, `c245a9e023`, `e3ade30071`, 2026-06-06). It replaced the `{% raw %}` that the merge base had: that one was parsed into type 400, could never compile, and fed an unused `forced_raw_state`. `T:Parser/RawStatementTest.php` was replaced by `T:VerbatimTest.php`.
- Absolute and `./` / `../` paths in `extends` / `include` (#17269, `bf4377ac88`, `1b00adb6a4`): `C:2478-2496`, `3064`.
- `compileCall()` typed `-> string` (#17055). It is still a stub.

**Fixes and hardening on master**
- String emission and escape sequences: #17002, #17046, `2430790982`, and advisory `baa391fc36` (`C:1564-1603`).
- Hash-key escaping: `5c8fe5dd62` (`C:1427-1442`).
- `join` injection: `e434061be3`.
- `default` inside a switch: #16003 (`B:574-582`).
- Lemon stack overflow fails closed: `b844e7e65b`.
- Syntax-error buffer leak: `be1c8fb98e`.
- Trailing-backslash out-of-bounds read and O(n²) list building: `ee20b98b06` (`S:630`, `H:403-428`).
- `unserialize(allowed_classes: false)` for e-files: `bc995c5ca1` (`C:496-509`).
- `open_basedir`-safe I/O through `FileTrait`: #17277.
- `statementList` returns a string: #16613.
- `preload()` without a container, and extends-mode `[]`: CP-17565.
- `super()` null-guard: `a9b63563b6` (`C:1931`).

**Refactors on master**
- 24 `Volt\Exceptions\*` classes (#17019).
- `FileTrait`, and `InfoTrait::phpFunctionExists` (#17279).
- `static` returns (#17035, #17055).
- Typed properties and phpstan `mvc_volt_node` shapes (`phalcon/Contracts/Mvc/MvcTypes.zep:149`; CP-17428, CP-17463).
- Tests moved to attribute data providers and the Talon base class.
- The option aliases (`always`/`compileAlways`, …) are identical on both branches; they predate the fork.

**Inheritance on master**
- `array_key_exists` for null overrides: `83262d049d` (`C:2408`).
- #17294 null-blocks segfault (`C:2394-2401`).
- CP-17668 (2026-10-14): `virtualPaths` cache (`f9877cd1f4`), extension-event short-circuit and per-statement re-read (`8e1ac7d181`), state reset moved into `compileSource` (`6ccb782539`).

**Changelog entries** (`CHANGELOG-5.0.md`):

| Line | Version | Entry |
|---|---|---|
| `:16`, `:37` | 5.23.0 | #17668 |
| `:123` | 5.21.0 | #17565 |
| `:169-178` | 5.20.3 | leak, out-of-bounds read, quadratic list building, unserialize |
| `:267` | 5.20.0 | string emission |
| `:453`, `:471` | 5.17.0 | #17269, #17294 |
| `:639` | 5.15.0 | `join` |
| `:689` | 5.14.1 | #16003 |
| `:719`, `:735`, `:1179-1203`, `:1286` | 5.14.0 | verbatim, raw removal, exceptions, #17046 |
| `:1414` | 5.13.0 | #17002 |
| `:1441` | 5.12.1 | #16613 |
| `:1468-1469` | 5.12.0 | — |

---

## 8. Rough edges seen in the code

**Grammar versus compiler mismatches**
1. `cache` parses (`G:471-485`) but has no compiler case, so it throws `UnknownVoltStatement` 314.
2. `call` parses (`G:447-453`) but `compileCall` returns `""` (`C:568-572`, "Not implemented?").
3. `++` / `--` parse (`G:699-705`) but there is no expression case, so they throw `UnknownVoltExpression` 279/280.
4. `extends expr` accepts any expression, but only `path["value"]` is used (`C:2884-2888`).
5. `is not` is lexed as `!=` (`S:433-443`), which breaks `is not divisibleby / sameas / type` (section 3.7).
6. `//` means modulo (`G:563-565`).
7. Arithmetic precedence is inverted (`G:29-30`); this is hidden by flat emission (section 3.5).
8. `{% if x %}{% endif %}` throws a `TypeError` (`G:292`, `C:980`). `{% if x %}{% else %}y{% endif %}` is a syntax error. Empty `for` and empty `macro` bodies are syntax errors.
9. The `block_level` counter is shared by `block`, `if`, `for` and `switch` (`B:486-487`, `527-528`, `554-555`, `654-663`), which gives the misleading "Embedding blocks into other blocks" message for a block inside `if` or `for`.

**Dead code**
10. `case 61` emits `" > "` for `'='` (`C:1531-1533`); no expression node has type 61.
11. `attributeReader` has two identical branches (`C:268-272`).
12. The identifier cases in `resolveTest` (`C:2229-2242`) can never be hit, because those words are tokens.
13. The `phvolt_tokens` table lists `WITH` twice (`B:91`, `B:96`).

**Magic numbers mixed with constants** in `C:`: `260` (`1023`), `124` (`1484`), `37`, `61`, `62`, `126`, `258`, `259`, `267`, `271-275`, `278`, `321` (`2953`), `325` (`2971`), `358` (`2982`), `364` (`2573`).

**Hard-coded lists and behaviours**
14. The 16-entry Tag `arrayHelpers` list (`C:1977-1994`).
15. Any static `Phalcon\Tag` method is reachable from templates through `method_exists` (`C:1996`), including side-effecting ones such as `set_default`. This is marked `@todo … will break a lot of applications if removed` (`C:1966`, `1974`).
16. `preload` is special-cased (`C:1968`), and `V:206` has a `@todo`.
17. Filters and functions sit in long `if` / `switch` chains (`C:1910-2069`, `2640-2707`); there is no registry.
18. Compile-time DI probing in several places: `attributeReader` (`C:258`), `lower`/`upper` (`C:2677`, `2700`), TagFactory (`C:2007`).

**State management**
19. Not reset per template (`C:2337-2343` omits them): `macros` (so `MacroAlreadyDefined` across templates), `currentBlock` (stale `super()`), `loopPointers`, `forElsePointers` and `autoescape` (only reassigned when the option exists).
20. `blocks` and `extendedBlocks` are typed loosely (`array|null`, `array|bool|string`), marked `TODO: Make array only?` and `TODO: Make it always array` (`C:63-70`, `93-100`). The string case is reachable (section 2.7).
21. `Volt::setOptions()` after `getCompiler()` is ignored (`V:89-120`, `329-332`).
22. `render(… var params)` and `partial(… var params)` have `// TODO: Make params array` (`V:264`, `AbstractEngine.zep:80`).

**Inheritance and caching**
23. No dependency tracking; the `stat=false` caching issue (section 2.7); parent blocks compiled in the child's context; child top-level `do` / `include` silently dropped; unknown child blocks dropped; `super()` quoting via `addslashes` (section 2).

**Inconsistencies**
24. The two meanings of "prefix": the `prefix` option for file names, and `setUniquePrefix` / `this->prefix` for variables (`C:146`, `335`).
25. `getOption()` is declared `string|null` but returns booleans.
26. Getters are declared `-> string` but return `null` before the first compile (`C:2078-2081`, `2150-2153`).
27. The `default` filter does not receive the left operand in hooks (`C:2560-2562`, with the comment "improve this!").
28. `join` swaps its arguments and crashes without them (`C:2662-2664`).
29. `capitalize` is implemented as `ucwords`.
30. `slice` treats `end` as inclusive.
31. Single-quoted emission means `"\n"` is not interpreted, except in TagFactory calls.
32. A static include needs the `.volt` extension, but a dynamic one does not.
33. Parser exceptions do not extend `Volt\Exception`.
34. The `for` EOF message uses `if_level` (`G:132`).
35. Compiled paths are lowercased, so `Index.volt` and `index.volt` collide.

**Runtime**
36. Engine and template scope are shared with partials when params are not an array.
37. `loop.length` needs `Countable`.
38. `Volt::slice()` on objects needs an `Iterator` (an `IteratorAggregate` fails).
39. `isIncluded()` throws on a `Traversable`.
40. Events fire on cache hits.

---

## 9. Test coverage map

Size: 92 files in `T:`. `Compiler/` has 40 files with about 65 methods, and large data providers: `CompileString` has about 131 cases, `Parse` about 120 and `FunctionCall` about 102. `Parser/` has 31 files with 146 methods. There is 1 file in `Extensions/` and 20 files at the top level.

| Area | Files (selected lines) | Covers |
|---|---|---|
| Parser AST | `Parser/*Test.php` (Access, Arithmetic, Array, Autoescape, Block, Cache, Call, Comment, Comparison, Concatenation, Do, Echo, Extends, Filter, For, FunctionCall, If, Include, In, Is, Logical, LoopControl, Macro, Range, RawFragment, Return, Set, Slice, StackOverflow, Switch, Ternary) | AST shape for each construct; `++`/`--` (Arithmetic :67/:131); `//` = MOD (:160); `cache` and `call` (AST only); the 300-paren stack overflow; switch error messages (Switch :33/:436). `Compiler/ParseTest.php` covers extends errors (:25-52) and syntax errors (:200-264). |
| Compiler statements | `Compiler/Compile{AutoEscape,Call,Case,Do,Echo,ElseIf,Foreach,ForElse,If,Include,Macro,Return,Set,Switch}Test.php`, `CompileStringTest.php` provider :38-620 | if, for (break/continue), set, autoescape, switch whitespace and `default` (#16003). Several tests are smoke-only: `CompileMacroTest` checks only that the output contains `function`, and `CompileCallTest` asserts the empty stub. |
| Expressions, filters, functions | `CompileStringTest.php` (:79-618), `FunctionCallTest.php` (:446, about 102 cases), `ResolveTest`, `AttributeReaderTest`, `ExpressionTest`, `CompileFileTest:65` (#13242) | operators, `is` tests, every built-in filter and function, TagFactory (:271-437), string-escaping advisories (:510-618), a 40k-item array (:876), trailing backslash (:915) |
| Inheritance and include | `CompilerFilesTest.php` | blocks (:85); children.extends (:149); absolute and relative extends (#17269, :182/:207); planted e-file (:233); **#17294 multi-level (:264)**; static include, recursive (:288/:311) |
| | `CompileStringTest.php` | state reset (:669, :704) |
| | `CompileSourceExtendsModeTest.php:42` | empty extends mode → `[]` |
| | `CompileTest.php:87` | `%%e%%` suffix |
| Macros | `CompilerTest.php` :170/:263, using the `A:macro/*` fixtures (hello, conditionaldate, my_input, error_messages, related_links, strtotime, list, form_row); `CallMacroTest` (#15842); `Extensions/PhpTest` (duplicates CallMacroTest) | |
| Extension API | `AddExtensionTest`, `GetExtensionsTest` (registry only); `AddFunctionTest` :58/:79; `AddFilterTest` :51/:71; `FireExtensionEventTest` :25 (wrong signature), :55 (extension added mid-compile), :109 (all four hooks) | |
| Options and paths | `CompileTest.php` (:29, :49 closure path, :87 separator / `_e_`, :126 symlink, :183 not found, :223 separator change); `Get/SetOption(s)`, `Get/SetUniquePrefix`, `GetCompiledTemplatePath`, `GetTemplatePath` | |
| Engine runtime | `LengthTest`, `SliceTest`, `SortTest`, `IsIncludedTest`, `ConvertEncodingTest`, `PreloadTest` (:30/:55), `PartialTest`, `RenderTest` (:30; :52 events via `tests/support/Listener/ViewCompileListener.php`); `GetCompiler`, `GetView`, `GetContent`, `GetSetDI`, `GetSetEventsManager`, `GetSetOptions`, `UnderscoreGet`, `Construct`; `tests/unit/Mvc/View/Simple/RenderTest.php:50` (subobject.volt); benchmark `tests/benchmarks/Mvc/VoltBench.php` | |

**Not covered by any test**
- `super()`: never compiled or rendered. The only mention is a parse-count case at `Compiler/ParseTest.php:176`.
- Nested blocks, blocks inside `if` / `for` / `macro` / `autoescape`, and the messages "Embedding blocks…" and "Embedding macros…".
- The non-`{{` branches of "Child templates only may contain blocks" (if, for, switch, set, raw).
- `stat=false` and `stat` effects in general; dependency staleness; `always`; the `prefix` and `extension` options; option validation errors.
- `cache`, `call`, `++`/`--` at compile time; `include … with`; `extends var`; compound `set`; slices; `**` / `//`; `is not <fn-test>`; `loop.first`, `last`, `length` and `revindex`.
- Macros: missing-parameter exception, `MacroAlreadyDefined`, `MacroNotFound` at runtime.
- `initialize()`; several extensions in sequence (first string wins); user functions overriding built-ins.
- Most exception classes: `TemplatePathCollision`, `TemplateFileNotOpenable`, `VoltDirectoryNotWritable`, `CannotOpenCompiledFile`, `InvalidExtension`, `InvalidUser*Definition`, `UnknownVoltStatement` / `Expression`, `Corrupted*`, `InvalidHaystack`, `MbstringRequired`.
- `render(mustClean)`; listeners returning `false`.
- `T:CompilerTest.php:62 shouldCreateContent` has neither a `test` prefix nor a `#[Test]` attribute, and is skipped, so it never runs.

**Fixtures used by no test:** `A:templates/{a,b,c}.volt` (a three-level `super()` chain), `A:compiler/*` except `partial.volt`, `A:extends/children.volt`, `children2.volt` (`super()`) and `partial.volt`, `A:builtinfunction/index.volt`, `A:switch-case/simple-usage.volt`, `A:macro/null-value.volt`.
