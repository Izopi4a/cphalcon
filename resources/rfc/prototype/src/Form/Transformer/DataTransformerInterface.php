<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * Converts between two representations. Model transformers sit between model and norm
 * data, view transformers between norm and view data.
 *
 * @throws TransformationFailedException when the value cannot be converted; the form is then "not synchronized"
 */
interface DataTransformerInterface
{
    /** Model/norm -> norm/view (towards the user). */
    public function transform(mixed $value): mixed;

    /** View/norm -> norm/model (towards the model). */
    public function reverseTransform(mixed $value): mixed;
}
