<?php
declare(strict_types=1);

namespace Phalcon\Form\Type;

/**
 * Marker for types that produce a {@see \Phalcon\Form\SubmitButton}. ResolvedType hands them a
 * SubmitButtonBuilder (same as Symfony's SubmitButtonTypeInterface).
 */
interface SubmitButtonTypeInterface extends TypeInterface
{
}
