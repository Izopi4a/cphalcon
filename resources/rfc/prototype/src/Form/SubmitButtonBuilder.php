<?php
declare(strict_types=1);

namespace Phalcon\Form;

/** Builder for {@see SubmitButton}; picked by ResolvedType for SubmitButtonTypeInterface types. */
class SubmitButtonBuilder extends ButtonBuilder
{
    public function getForm(): FormInterface
    {
        return new SubmitButton($this->getFormConfig());
    }
}
