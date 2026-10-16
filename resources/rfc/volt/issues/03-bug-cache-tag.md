**Describe the bug**

`{% cache %}` was removed from the compiler in 4.0, but the scanner and grammar still accept it (`CACHE`/`ENDCACHE` tokens, `cache_statement` in `parser.php.lemon:471-485`). A template using it parses, then fails in the compiler with a message that names an internal number:

**To Reproduce**

```php
$compiler = new \Phalcon\Mvc\View\Engine\Volt\Compiler();

$compiler->compileString('{% cache "sidebar" 3600 %}x{% endcache %}');
// Phalcon\Mvc\View\Engine\Volt\Exceptions\UnknownVoltStatement:
// Unknown statement 314 in eval code on line 1
```

**Expected behavior**

Either a syntax error from the parser, like any other unknown tag, or a message that says what happened: "`{% cache %}` was removed in Phalcon 4; use the view cache or a partial".

**Details**
 - Phalcon version: 5.23.0 (master `33f1076a88`)
 - PHP Version: 8.5.4
 - Operating System: Linux
 - Installation type: Compiling from source

**Additional context**

Removing the two grammar rules, the tokens and the `cache_lifetime` rule makes it a plain syntax error. The docs' Compiler API section still lists `compileCache` "(DEPRECATED)"; that line can go with it. phalcon/volt has the same grammar.

Pinned in https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/tests/Today/OutputTodayTest.php (`testGrammarCompilerDrift`).
