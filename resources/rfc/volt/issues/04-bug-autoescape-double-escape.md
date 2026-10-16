**Describe the bug**

With `autoescape` on, `Compiler::compileEcho()` wraps every `{{ … }}` in `$this->escaper->html()` (`Compiler.zep:639-679`; only `super()` is exempt). Output that is already HTML-safe is escaped a second time:

- `{{ content() }}` in a layout escapes the whole rendered action view;
- `{{ name|e }}` becomes `html(html($name))`, so `&` shows up as `&amp;amp;`.

**To Reproduce**

```php
use Phalcon\Di\FactoryDefault;
use Phalcon\Mvc\View;
use Phalcon\Mvc\View\Engine\Volt;

$dir = sys_get_temp_dir() . '/volt-autoescape/';
@mkdir($dir . 'index', 0777, true);
@mkdir($dir . 'cache', 0777, true);
file_put_contents($dir . 'index/index.volt', '<p>Hello</p>');
file_put_contents($dir . 'index.volt', '<main>{{ content() }}</main> {{ name|e }}');

$di   = new FactoryDefault();
$view = new View();
$view->setDI($di);
$view->setViewsDir($dir);
$view->registerEngines([
    '.volt' => function ($view) use ($di, $dir) {
        $volt = new Volt($view, $di);
        $volt->setOptions(['path' => $dir . 'cache/', 'always' => true, 'autoescape' => true]);

        return $volt;
    },
]);
$view->setVar('name', 'Tom & "Jerry"');
$view->start();
$view->render('index', 'index');
$view->finish();

echo $view->getContent();
// <main>&lt;p&gt;Hello&lt;/p&gt;</main> Tom &amp;amp; &amp;quot;Jerry&amp;quot;
```

Compiled:

```php
<main><?= $this->escaper->html($this->getContent()) ?></main> <?= $this->escaper->html($this->escaper->html($name)) ?>
```

**Expected behavior**

```html
<main><p>Hello</p></main> Tom &amp; &quot;Jerry&quot;
```

**Details**
 - Phalcon version: 5.23.0 (master `33f1076a88`)
 - PHP Version: 8.5.4
 - Operating System: Linux
 - Installation type: Compiling from source

**Additional context**

The fix is in `compileEcho()`: skip the outer `html()` when the outermost node is
- an escaping filter (`e`, `escape`, `escape_attr`, `escape_css`, `escape_js`, `url_encode`), or
- a call to `content()` / `get_content()` (`super()` already is).

`{{ x|escape_js }}` is also wrapped (`html(js($x))`). It does no visible damage, because `js()` output contains no HTML special characters, but the same rule fixes it.

There is no `raw` filter either, so users who hit this tend to turn autoescape off globally. A `raw` filter and a way to mark function output as safe are part of a separate NFR. A prototype of the `compileEcho()` change, with tests: https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/src/Compiler.php (`compileEcho`, `isSafeExpression`) and https://github.com/Izopi4a/cphalcon/blob/nfr-volt/resources/rfc/volt/prototype/tests/Prototype/OutputTest.php.
