<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Runtime;

use Closure;
use Phalcon\Di\DiInterface;
use Phalcon\VoltNfr\Exception;

/**
 * Runtime functions, filters and tests. The compiler reads names and options;
 * the engine resolves callables lazily at render time (once per name).
 */
final class Registry
{
    /** @var array<string, array<string, VoltCallable>> */
    private array $items = ['function' => [], 'filter' => [], 'test' => []];

    /** @var array<string, Closure> */
    private array $resolved = [];

    public function add(VoltCallable $callable): void
    {
        $kind = match (true) {
            $callable instanceof VoltFunction => 'function',
            $callable instanceof VoltFilter   => 'filter',
            $callable instanceof VoltTest     => 'test',
        };

        $this->items[$kind][$callable->getName()] = $callable;
        unset($this->resolved[$kind . ':' . $callable->getName()]);
    }

    public function addExtension(ExtensionInterface $extension): void
    {
        foreach ([...$extension->getFunctions(), ...$extension->getFilters(), ...$extension->getTests()] as $item) {
            $this->add($item);
        }
    }

    public function get(string $kind, string $name): ?VoltCallable
    {
        return $this->items[$kind][$name] ?? null;
    }

    /**
     * The callable as a Closure (named arguments keep working), resolving
     * [Service::class, 'method'] through the container on first use.
     */
    public function resolve(string $kind, string $name, ?DiInterface $container): Closure
    {
        $key = $kind . ':' . $name;
        if (isset($this->resolved[$key])) {
            return $this->resolved[$key];
        }

        $item = $this->get($kind, $name) ?? throw new Exception("Unknown runtime $kind '$name'");
        $callable = $item->getCallable();

        if (is_array($callable) && is_string($callable[0] ?? null) && !$this->isStatic($callable)) {
            $callable[0] = $this->instance($callable[0], $container);
        }

        return $this->resolved[$key] = Closure::fromCallable($callable);
    }

    /**
     * Everything the compiled output depends on; stored next to each compiled
     * template so a changed registry recompiles it.
     */
    public function getSignature(): string
    {
        $parts = [];
        foreach ($this->items as $items) {
            foreach ($items as $item) {
                $parts[] = $item->getSignature();
            }
        }
        sort($parts);

        return sha1(implode("\n", $parts));
    }

    private function isStatic(array $callable): bool
    {
        return class_exists($callable[0])
            && method_exists($callable[0], $callable[1])
            && (new \ReflectionMethod($callable[0], $callable[1]))->isStatic();
    }

    private function instance(string $name, ?DiInterface $container): object
    {
        if ($container !== null && $container->has($name)) {
            return $container->getShared($name);
        }

        if ($container !== null && class_exists($name)) {
            return $container->get($name);
        }

        if (class_exists($name)) {
            return new $name();
        }

        throw new Exception("Cannot resolve '$name': not a service in the container and not a class");
    }
}
