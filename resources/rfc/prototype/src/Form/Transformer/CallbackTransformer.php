<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * Transformer built from two closures: transform(value) and reverseTransform(value).
 */
final class CallbackTransformer implements DataTransformerInterface
{
    public function __construct(
        private readonly \Closure $transform,
        private readonly \Closure $reverseTransform,
    ) {
    }

    public function transform(mixed $value): mixed
    {
        return ($this->transform)($value);
    }

    public function reverseTransform(mixed $value): mixed
    {
        return ($this->reverseTransform)($value);
    }
}
