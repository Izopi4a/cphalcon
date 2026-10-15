<?php
declare(strict_types=1);

namespace Phalcon\Form\EventListener;

use Phalcon\Form\Event\EventSubscriberInterface;
use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;
use Phalcon\Form\FormError;

/**
 * Fallback that turns a transformation failure into a FormError when no validator does so.
 * Runs last on POST_SUBMIT; skipped when the form already has errors or a child is not synchronized
 * (then the child carries the error).
 */
final class TransformationFailureListener implements EventSubscriberInterface
{
    // prototype: Symfony keeps this constant on Form; it moves there with the validation bridge
    public const NOT_SYNCHRONIZED_ERROR = 'NOT_SYNCHRONIZED_ERROR';

    public function convertTransformationFailureToFormError(FormEvent $event): void
    {
        $form    = $event->getForm();
        $failure = $form->getTransformationFailure();

        if (null === $failure || !$form->isValid()) {
            return;
        }

        foreach ($form as $child) {
            if (!$child->isSynchronized()) {
                return;
            }
        }

        $viewData          = $form->getViewData();
        $viewDataAsString  = is_scalar($viewData) ? (string) $viewData : get_debug_type($viewData);
        $config            = $form->getConfig();
        $messageTemplate   = $failure->getInvalidMessage() ?? $config->getOption('invalid_message') ?? 'The value {{ value }} is not valid.';
        $messageParameters = array_replace(
            ['{{ value }}' => $viewDataAsString],
            $config->getOption('invalid_message_parameters') ?? [],
            $failure->getInvalidMessageParameters()
        );

        $form->addError(new FormError(
            strtr($messageTemplate, $messageParameters),
            $messageTemplate,
            $messageParameters,
            $failure,
            self::NOT_SYNCHRONIZED_ERROR
        ));
    }

    public static function getSubscribedEvents(): array
    {
        return [FormEvents::POST_SUBMIT => ['convertTransformationFailureToFormError', -1024]];
    }
}
