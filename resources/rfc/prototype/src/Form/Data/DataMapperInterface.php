<?php
declare(strict_types=1);

namespace Phalcon\Form\Data;

use Phalcon\Form\FormInterface;

/**
 * The only bridge between a compound form's view data and its children.
 */
interface DataMapperInterface
{
    /** @param iterable<FormInterface> $forms */
    public function mapDataToForms(mixed $viewData, iterable $forms): void;

    /** @param iterable<FormInterface> $forms */
    public function mapFormsToData(iterable $forms, mixed &$viewData): void;
}
