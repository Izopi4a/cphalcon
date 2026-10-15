<?php
declare(strict_types=1);

namespace Phalcon\Form;

/**
 * A button that submits the form. Form::submit() records the first clicked submit button so
 * the controller can branch on $form->getClickedButton() (e.g. "save" vs "save and add another").
 */
class SubmitButton extends Button
{
}
