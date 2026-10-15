<?php
declare(strict_types=1);

namespace Phalcon\Form\EventListener;

use Phalcon\Form\Event\EventSubscriberInterface;
use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;

/**
 * Trims submitted strings (unicode whitespace included) before anything else sees them.
 */
final class TrimListener implements EventSubscriberInterface
{
    public function preSubmit(FormEvent $event): void
    {
        $data = $event->getData();
        if (is_string($data)) {
            $event->setData(self::trim($data));
        }
    }

    public static function getSubscribedEvents(): array
    {
        return [FormEvents::PRE_SUBMIT => 'preSubmit'];
    }

    public static function trim(string $string): string
    {
        $result = preg_replace('/^[\pZ\pC]+|[\pZ\pC]+$/u', '', $string);

        return null === $result ? trim($string) : $result;
    }
}
