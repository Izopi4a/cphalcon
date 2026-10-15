<?php
declare(strict_types=1);

namespace Phalcon\Form\Options;

/**
 * Reduced OptionsResolver: defaults, lazy defaults (Closure(Options $options[, $previous])),
 * required, defined, allowed types/values, normalizers, undefined-option rejection.
 * Dropped from Symfony: nested options, deprecations, define()/info, prototypes, ignore-undefined.
 */
final class OptionsResolver implements Options
{
    /** @var array<string, true> */
    private array $defined = [];
    /** @var array<string, mixed> non-lazy defaults */
    private array $defaults = [];
    /** @var array<string, list<\Closure>> lazy default closures, applied in order */
    private array $lazy = [];
    /** @var array<string, true> */
    private array $required = [];
    /** @var array<string, list<string>> */
    private array $allowedTypes = [];
    /** @var array<string, list<mixed>> */
    private array $allowedValues = [];
    /** @var array<string, list<\Closure>> */
    private array $normalizers = [];

    // --- state used only while resolve() runs
    /** @var array<string, mixed> user supplied options */
    private array $given = [];
    /** @var array<string, mixed> */
    private array $resolved = [];
    /** @var array<string, true> */
    private array $calling = [];
    private bool $locked = false;

    public function setDefault(string $option, mixed $value): static
    {
        $this->assertNotLocked();

        if ($value instanceof \Closure) {
            $reflection = new \ReflectionFunction($value);
            $params     = $reflection->getParameters();
            $firstType  = isset($params[0]) ? $params[0]->getType() : null;

            if ($firstType instanceof \ReflectionNamedType && Options::class === $firstType->getName()) {
                // Lazy default. A second parameter means "chain onto the previous default",
                // otherwise this closure replaces whatever was set before.
                if (count($params) < 2 || !isset($this->lazy[$option])) {
                    $this->lazy[$option] = [];
                }
                $this->lazy[$option][] = $value;
                unset($this->defaults[$option]);
                $this->defined[$option] = true;

                return $this;
            }
        }

        unset($this->lazy[$option]);
        $this->defaults[$option] = $value;
        $this->defined[$option]  = true;

        return $this;
    }

    public function setDefaults(array $defaults): static
    {
        foreach ($defaults as $option => $value) {
            $this->setDefault((string) $option, $value);
        }

        return $this;
    }

    public function hasDefault(string $option): bool
    {
        return array_key_exists($option, $this->defaults) || isset($this->lazy[$option]);
    }

    public function setRequired(string|array $options): static
    {
        $this->assertNotLocked();
        foreach ((array) $options as $option) {
            $this->defined[$option]  = true;
            $this->required[$option] = true;
        }

        return $this;
    }

    public function isRequired(string $option): bool
    {
        return isset($this->required[$option]);
    }

    public function setDefined(string|array $options): static
    {
        $this->assertNotLocked();
        foreach ((array) $options as $option) {
            $this->defined[$option] = true;
        }

        return $this;
    }

    public function isDefined(string $option): bool
    {
        return isset($this->defined[$option]);
    }

    /** @return list<string> */
    public function getDefinedOptions(): array
    {
        return array_keys($this->defined);
    }

    public function setAllowedTypes(string $option, string|array $types): static
    {
        $this->assertNotLocked();
        $this->assertDefined($option);
        $this->allowedTypes[$option] = array_values((array) $types);

        return $this;
    }

    public function addAllowedTypes(string $option, string|array $types): static
    {
        $this->assertNotLocked();
        $this->assertDefined($option);
        $this->allowedTypes[$option] = array_values(array_merge($this->allowedTypes[$option] ?? [], (array) $types));

        return $this;
    }

    public function setAllowedValues(string $option, mixed $values): static
    {
        $this->assertNotLocked();
        $this->assertDefined($option);
        $this->allowedValues[$option] = is_array($values) ? array_values($values) : [$values];

        return $this;
    }

    public function setNormalizer(string $option, \Closure $normalizer): static
    {
        $this->assertNotLocked();
        $this->assertDefined($option);
        $this->normalizers[$option] = [$normalizer];

        return $this;
    }

    public function addNormalizer(string $option, \Closure $normalizer): static
    {
        $this->assertNotLocked();
        $this->assertDefined($option);
        $this->normalizers[$option][] = $normalizer;

        return $this;
    }

    public function remove(string|array $options): static
    {
        $this->assertNotLocked();
        foreach ((array) $options as $option) {
            unset(
                $this->defined[$option], $this->defaults[$option], $this->lazy[$option], $this->required[$option],
                $this->allowedTypes[$option], $this->allowedValues[$option], $this->normalizers[$option]
            );
        }

        return $this;
    }

    /**
     * @return array<string, mixed> every defined option with its final value
     */
    public function resolve(array $options = []): array
    {
        $this->assertNotLocked();

        $unknown = array_diff_key($options, $this->defined);
        if ([] !== $unknown) {
            ksort($unknown);
            throw new UndefinedOptionsException(sprintf(
                'The option%s "%s" do%s not exist. Defined options are: "%s".',
                count($unknown) > 1 ? 's' : '',
                implode('", "', array_keys($unknown)),
                count($unknown) > 1 ? '' : 'es',
                implode('", "', array_keys($this->defined))
            ));
        }

        $missing = array_diff_key($this->required, $options, $this->defaults, $this->lazy);
        if ([] !== $missing) {
            throw new MissingOptionsException(sprintf(
                'The required option%s "%s" %s missing.',
                count($missing) > 1 ? 's' : '',
                implode('", "', array_keys($missing)),
                count($missing) > 1 ? 'are' : 'is'
            ));
        }

        $clone           = clone $this;
        $clone->given    = $options;
        $clone->resolved = [];
        $clone->calling  = [];
        $clone->locked   = true;

        $result = [];
        foreach (array_keys($clone->defined) as $option) {
            if ($clone->hasValue($option)) {
                $result[$option] = $clone[$option];
            }
        }

        return $result;
    }

    // --- Options (ArrayAccess) implementation, valid only during resolve()

    public function offsetExists(mixed $offset): bool
    {
        return $this->locked && $this->hasValue((string) $offset);
    }

    public function offsetGet(mixed $offset): mixed
    {
        if (!$this->locked) {
            throw new \LogicException('Options can only be read inside resolve().');
        }
        $option = (string) $offset;

        if (array_key_exists($option, $this->resolved)) {
            return $this->resolved[$option];
        }
        if (!$this->hasValue($option)) {
            if (!isset($this->defined[$option])) {
                throw new UndefinedOptionsException(sprintf('The option "%s" does not exist.', $option));
            }
            throw new OptionDefinitionException(sprintf('The optional option "%s" has no value set. Check with isset() first.', $option));
        }
        if (isset($this->calling[$option])) {
            throw new OptionDefinitionException(sprintf(
                'The options "%s" have a cyclic dependency.',
                implode('", "', array_keys($this->calling))
            ));
        }

        $this->calling[$option] = true;
        try {
            if (array_key_exists($option, $this->given)) {
                $value = $this->given[$option];
            } elseif (isset($this->lazy[$option])) {
                $value = null;
                foreach ($this->lazy[$option] as $closure) {
                    $value = $closure($this, $value);
                }
            } else {
                $value = $this->defaults[$option];
            }

            if (isset($this->allowedTypes[$option])) {
                $this->verifyTypes($option, $value);
            }
            if (isset($this->allowedValues[$option])) {
                $this->verifyValues($option, $value);
            }
            foreach ($this->normalizers[$option] ?? [] as $normalizer) {
                $value = $normalizer($this, $value);
            }
        } finally {
            unset($this->calling[$option]);
        }

        return $this->resolved[$option] = $value;
    }

    public function offsetSet(mixed $offset, mixed $value): void
    {
        throw new \LogicException('Options are read-only during resolution. Use setDefault() before resolve().');
    }

    public function offsetUnset(mixed $offset): void
    {
        throw new \LogicException('Options are read-only during resolution. Use remove() before resolve().');
    }

    public function count(): int
    {
        return count($this->defined);
    }

    // --- internals

    private function hasValue(string $option): bool
    {
        return array_key_exists($option, $this->given)
            || array_key_exists($option, $this->defaults)
            || isset($this->lazy[$option]);
    }

    private function verifyTypes(string $option, mixed $value): void
    {
        foreach ($this->allowedTypes[$option] as $type) {
            if (self::isOfType($value, $type)) {
                return;
            }
        }
        throw new InvalidOptionsException(sprintf(
            'The option "%s" with value %s is expected to be of type "%s", but is of type "%s".',
            $option,
            self::formatValue($value),
            implode('" or "', $this->allowedTypes[$option]),
            get_debug_type($value)
        ));
    }

    private function verifyValues(string $option, mixed $value): void
    {
        foreach ($this->allowedValues[$option] as $allowed) {
            if ($allowed instanceof \Closure ? $allowed($value) : $allowed === $value) {
                return;
            }
        }
        throw new InvalidOptionsException(sprintf(
            'The option "%s" with value %s is invalid.',
            $option,
            self::formatValue($value)
        ));
    }

    private static function isOfType(mixed $value, string $type): bool
    {
        if (str_ends_with($type, '[]')) {
            if (!is_iterable($value)) {
                return false;
            }
            $inner = substr($type, 0, -2);
            foreach ($value as $item) {
                if (!self::isOfType($item, $inner)) {
                    return false;
                }
            }

            return true;
        }

        return match ($type) {
            'mixed'            => true,
            'null'             => null === $value,
            'bool', 'boolean'  => is_bool($value),
            'int', 'integer'   => is_int($value),
            'float', 'double'  => is_float($value),
            'string'           => is_string($value),
            'array'            => is_array($value),
            'iterable'         => is_iterable($value),
            'callable'         => is_callable($value),
            'object'           => is_object($value),
            'scalar'           => is_scalar($value),
            'numeric'          => is_numeric($value),
            'resource'         => is_resource($value),
            default            => $value instanceof $type,
        };
    }

    private static function formatValue(mixed $value): string
    {
        return match (true) {
            is_object($value) => get_class($value),
            is_array($value)  => 'array',
            is_string($value) => '"' . $value . '"',
            null === $value   => 'null',
            is_bool($value)   => $value ? 'true' : 'false',
            default           => (string) $value,
        };
    }

    private function assertNotLocked(): void
    {
        if ($this->locked) {
            throw new \LogicException('Options cannot be changed while they are being resolved.');
        }
    }

    private function assertDefined(string $option): void
    {
        if (!isset($this->defined[$option])) {
            throw new UndefinedOptionsException(sprintf('The option "%s" does not exist. Defined options are: "%s".', $option, implode('", "', array_keys($this->defined))));
        }
    }
}
