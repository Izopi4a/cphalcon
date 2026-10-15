<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * Swaps the directions of another transformer, e.g. to use a view transformer as a model transformer.
 */
final class ReversedTransformer implements DataTransformerInterface
{
    public function __construct(private readonly DataTransformerInterface $reversedTransformer)
    {
    }

    public function transform(mixed $value): mixed
    {
        return $this->reversedTransformer->reverseTransform($value);
    }

    public function reverseTransform(mixed $value): mixed
    {
        return $this->reversedTransformer->transform($value);
    }
}
