<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\FormInterface;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\Type\SubmitButtonTypeInterface;
use Phalcon\Form\View\FormView;

/** <button type="submit">; produces a SubmitButton so the root form can tell which one was pressed. */
class SubmitType extends AbstractType implements SubmitButtonTypeInterface
{
    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        $view->vars['clicked'] = $form instanceof \Phalcon\Form\ClickableInterface && $form->isClicked();
    }

    public function getParent(): ?string
    {
        return ButtonType::class;
    }

    public function getBlockPrefix(): string
    {
        return 'submit';
    }
}
