<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Runtime;

/**
 * A template function, filter or test backed by a PHP callable that runs at
 * RENDER time, with the evaluated argument values. The counterpart of today's
 * Compiler::addFunction(), whose closure runs at COMPILE time and returns PHP
 * source.
 *
 * Accepted callables:
 * - any Closure (including first-class callables: Money::format(...))
 * - 'strlen', 'App\Money::format', [Money::class, 'format'] (static)
 * - [$object, 'method'], invokable objects
 * - [ServiceOrClass::class, 'method'] with a non-static method: the instance
 *   comes from the DI container the first time the template calls it (lazy)
 */
abstract class VoltCallable
{
    /**
     * @param array{safe?: bool, needsContext?: bool} $options
     *        safe:          the result is HTML and is not escaped by autoescape
     *        needsContext:  the template variables are passed as first argument
     */
    public function __construct(
        private string $name,
        private mixed $callable,
        private array $options = []
    ) {
    }

    public function getName(): string
    {
        return $this->name;
    }

    public function getCallable(): mixed
    {
        return $this->callable;
    }

    public function isSafe(): bool
    {
        return (bool) ($this->options['safe'] ?? false);
    }

    public function needsContext(): bool
    {
        return (bool) ($this->options['needsContext'] ?? false);
    }

    /**
     * PHP expression that calls the callable directly, when it can be written
     * into the compiled template as is: a function name or a static method.
     * Null means "look it up at render time" (closures, objects, DI services).
     */
    public function getStaticCallCode(): ?string
    {
        $callable = $this->callable;

        if (is_string($callable) && !str_contains($callable, '::')) {
            return function_exists($callable) ? '\\' . ltrim($callable, '\\') : null;
        }

        if (is_string($callable)) {
            $callable = explode('::', $callable, 2);
        }

        if (is_array($callable) && is_string($callable[0] ?? null) && class_exists($callable[0])) {
            $method = new \ReflectionMethod($callable[0], $callable[1]);

            return $method->isStatic() && $method->isPublic()
                ? '\\' . ltrim($callable[0], '\\') . '::' . $callable[1]
                : null;
        }

        return null;
    }

    /**
     * Part of the cache signature: what the compiled code depends on.
     */
    public function getSignature(): string
    {
        $callable = $this->getStaticCallCode() ?? 'runtime';

        return static::class . ':' . $this->name . ':' . $callable . ':' . json_encode($this->options);
    }
}
