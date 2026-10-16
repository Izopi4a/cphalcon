**Describe the bug**

`//` in a Volt expression compiles to `%` (modulo). The grammar turns two `DIVIDE` tokens into a `PHVOLT_T_MOD` node (`ext/phalcon/mvc/view/engine/volt/parser.php.lemon:563-565`), so `{{ 7 // 2 }}` prints `1`.

**To Reproduce**

```php
$compiler = new \Phalcon\Mvc\View\Engine\Volt\Compiler();

echo $compiler->compileString('{{ 7 // 2 }}');
// <?= 7 % 2 ?>    → renders 1
```

**Expected behavior**

Either floor division, as in Twig (`{{ 7 // 2 }}` → `3`, compiled to something like `(int) floor(7 / 2)`), or a syntax error. Quietly computing the modulo is wrong in both readings.

**Details**
 - Phalcon version: 5.23.0 (master `33f1076a88`)
 - PHP Version: 8.5.4
 - Operating System: Linux
 - Installation type: Compiling from source

**Additional context**

The fix is in the one grammar rule: give it its own node and compile it to floor division, or drop the rule so `//` becomes a syntax error. phalcon/volt has the same rule.

Found while preparing a Volt NFR; the case is pinned in https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/tests/Today/OutputTodayTest.php (`testGrammarCompilerDrift`).
