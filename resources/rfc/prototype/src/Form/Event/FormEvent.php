<?php
declare(strict_types=1);

namespace Phalcon\Form\Event;

use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\FormInterface;

/**
 * Payload passed as the "data" argument of the Phalcon event. Listeners replace
 * the data with setData() on the pre/submit events; post events are read-only.
 */
class FormEvent
{
    public function __construct(
        private readonly FormInterface $form,
        private mixed $data,
        private readonly bool $mutable = true,
    ) {
    }

    public function getForm(): FormInterface
    {
        return $this->form;
    }

    public function getData(): mixed
    {
        return $this->data;
    }

    public function setData(mixed $data): void
    {
        if (!$this->mutable) {
            throw new BadMethodCallException('The data of this event is read-only.');
        }
        $this->data = $data;
    }
}
