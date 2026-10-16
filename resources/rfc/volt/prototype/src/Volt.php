<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr;

use Closure;
use Phalcon\Di\DiInterface;
use Phalcon\Mvc\View\Engine\Volt as VoltEngine;
use Phalcon\Mvc\View\Engine\Volt\Compiler as VoltCompiler;
use Phalcon\Mvc\ViewBaseInterface;
use Phalcon\VoltNfr\Runtime\ExtensionInterface;
use Phalcon\VoltNfr\Runtime\Registry;
use Phalcon\VoltNfr\Runtime\VoltFilter;
use Phalcon\VoltNfr\Runtime\VoltFunction;
use Phalcon\VoltNfr\Runtime\VoltTest;

/**
 * The Volt engine with the runtime extension API. Compiled templates run
 * inside render(), so "$this" in generated code is this object: the
 * getRuntime*() methods are how compiled templates reach the callables.
 */
class Volt extends VoltEngine
{
    private Registry $registry;

    public function __construct(ViewBaseInterface $view, ?DiInterface $container = null)
    {
        parent::__construct($view, $container);

        $this->registry = new Registry();
    }

    public function getCompiler(): VoltCompiler
    {
        if (!$this->compiler instanceof Compiler) {
            $compiler = new Compiler($this->view, $this->registry);

            if (is_object($this->container)) {
                $compiler->setDI($this->container);
            }

            if (is_array($this->options)) {
                $compiler->setOptions($this->options);
            }

            $this->compiler = $compiler;
        }

        return $this->compiler;
    }

    // ------------------------------------------------- registration (public)

    public function addFunction(VoltFunction $function): static
    {
        $this->registry->add($function);

        return $this;
    }

    public function addFilter(VoltFilter $filter): static
    {
        $this->registry->add($filter);

        return $this;
    }

    public function addTest(VoltTest $test): static
    {
        $this->registry->add($test);

        return $this;
    }

    public function addExtension(ExtensionInterface $extension): static
    {
        $this->registry->addExtension($extension);

        return $this;
    }

    // ------------------------------------- called from compiled templates

    public function getRuntimeFunction(string $name): Closure
    {
        return $this->registry->resolve('function', $name, $this->container);
    }

    public function getRuntimeFilter(string $name): Closure
    {
        return $this->registry->resolve('filter', $name, $this->container);
    }

    public function getRuntimeTest(string $name): Closure
    {
        return $this->registry->resolve('test', $name, $this->container);
    }

    /**
     * {% extends layoutVar %}: compile the child against that parent (cached
     * per pair) and run it with the template's variables.
     */
    public function renderDynamicExtends(mixed $parent, string $child, array $variables): void
    {
        if (!is_string($parent) || $parent === '') {
            throw new Exception('extends: the parent template name must be a non-empty string');
        }

        $compiled = $this->getCompiler()->compileVariant($child, $parent);

        (function (): void {
            extract(func_get_arg(1));
            require func_get_arg(0);
        })($compiled, $variables);
    }
}
