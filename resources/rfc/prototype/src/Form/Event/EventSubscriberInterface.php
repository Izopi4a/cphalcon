<?php
declare(strict_types=1);

namespace Phalcon\Form\Event;

interface EventSubscriberInterface
{
    /**
     * @return array<string, string|array{0: string, 1: int}> event name => method, or [method, priority]
     */
    public static function getSubscribedEvents(): array;
}
