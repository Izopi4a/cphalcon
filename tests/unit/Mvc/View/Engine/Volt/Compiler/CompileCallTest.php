<?php

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

declare(strict_types=1);

namespace Phalcon\Tests\Unit\Mvc\View\Engine\Volt\Compiler;

use Phalcon\Mvc\View\Engine\Volt\Compiler;
use Phalcon\Talon\PHPUnit\AbstractUnitTestCase;

class CompileCallTest extends AbstractUnitTestCase
{
    /**
     * @author Phalcon Team <team@phalcon.io>
     * @since  2018-11-13
     */
    public function testMvcViewEngineVoltCompilerCompileCall(): void
    {
        $compiler = new Compiler();

        /**
         * {% call %} compiles the macro call with its body as caller()
         */
        $result = $compiler->compileString('{% call m(1) %}BODY{% endcall %}');

        $this->assertStringContainsString('$this->pushMacroCaller(', $result);
        $this->assertStringContainsString('?>BODY<?php', $result);
        $this->assertStringContainsString("\$this->callMacro('m', [1]);", $result);
        $this->assertStringContainsString('$this->popMacroCaller();', $result);

        $this->expectException(\Phalcon\Mvc\View\Engine\Volt\Exceptions\CorruptedStatement::class);
        $compiler->compileCall([], false);
    }
}
