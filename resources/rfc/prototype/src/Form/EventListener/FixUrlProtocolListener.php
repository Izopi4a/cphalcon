<?php
declare(strict_types=1);

namespace Phalcon\Form\EventListener;

use Phalcon\Form\Event\EventSubscriberInterface;
use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;

/**
 * Prefixes a submitted URL with the default protocol when it has none ("example.com" -> "http://example.com").
 */
final class FixUrlProtocolListener implements EventSubscriberInterface
{
    public function __construct(private readonly ?string $defaultProtocol = 'http')
    {
    }

    public function onSubmit(FormEvent $event): void
    {
        $data = $event->getData();

        if ($this->defaultProtocol && $data && is_string($data) && !preg_match('~^(?:[/.]|[\w+.-]+://|[^:/?@]++:)~', $data)) {
            $event->setData($this->defaultProtocol . '://' . $data);
        }
    }

    public static function getSubscribedEvents(): array
    {
        return [FormEvents::SUBMIT => 'onSubmit'];
    }
}
