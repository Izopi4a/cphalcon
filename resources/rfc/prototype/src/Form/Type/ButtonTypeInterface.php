<?php
declare(strict_types=1);

namespace Phalcon\Form\Type;

/**
 * Marker for types that produce a {@see \Phalcon\Form\Button}. ResolvedType hands them a
 * ButtonBuilder instead of a FormBuilder (same as Symfony's ButtonTypeInterface).
 */
interface ButtonTypeInterface extends TypeInterface
{
}
