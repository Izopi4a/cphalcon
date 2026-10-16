**Describe the bug**

`{% call %}…{% endcall %}` parses, but compiles to an empty string, so everything between the tags disappears from the output without an error. `Compiler::compileCall()` is a stub:

```zephir
// phalcon/Mvc/View/Engine/Volt/Compiler.zep:568
public function compileCall(array statement, bool extendsMode) -> string
{
    // Not implemented?
    return "";
}
```

The grammar still has the statement (`macro_call_statement`, `parser.php.lemon:447-453`). #3180 asked for `call`/`caller` and was closed in 2017 as implemented.

**To Reproduce**

```php
$compiler = new \Phalcon\Mvc\View\Engine\Volt\Compiler();

var_export($compiler->compileString('{% call m(1) %}BODY{% endcall %}'));
// ''
```

**Expected behavior**

Either the call is compiled (the macro called with the body available as `caller()`), or compilation fails with a clear "`{% call %}` is not supported" message. Dropping template content without a word is the worst of the three.

**Details**
 - Phalcon version: 5.23.0 (master `33f1076a88`)
 - PHP Version: 8.5.4
 - Operating System: Linux
 - Installation type: Compiling from source

**Additional context**

The smallest fix is to throw from `compileCall()` until it is implemented. The docs list `compileCall` as "Compiles calls to macros".

Pinned in https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/tests/Today/OutputTodayTest.php (`testGrammarCompilerDrift`).
