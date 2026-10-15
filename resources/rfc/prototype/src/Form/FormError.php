<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Exception\BadMethodCallException;

class FormError
{
    private ?FormInterface $origin = null;

    /**
     * @param string      $message           Already translated/interpolated message
     * @param string|null $messageTemplate   Template with {{ placeholders }}
     * @param array       $messageParameters Placeholder values
     * @param mixed       $cause             Whatever produced the error (exception, Message, token...)
     * @param string|null $code              Machine readable code, e.g. "NOT_SYNCHRONIZED_ERROR"
     */
    public function __construct(
        private readonly string $message,
        private readonly ?string $messageTemplate = null,
        private readonly array $messageParameters = [],
        private readonly mixed $cause = null,
        private readonly ?string $code = null,
    ) {
    }

    public function __toString(): string
    {
        return $this->message;
    }

    public function getMessage(): string
    {
        return $this->message;
    }

    public function getMessageTemplate(): string
    {
        return $this->messageTemplate ?? $this->message;
    }

    public function getMessageParameters(): array
    {
        return $this->messageParameters;
    }

    public function getCause(): mixed
    {
        return $this->cause;
    }

    public function getCode(): ?string
    {
        return $this->code;
    }

    public function setOrigin(FormInterface $origin): void
    {
        if (null !== $this->origin) {
            throw new BadMethodCallException('setOrigin() must only be called once.');
        }
        $this->origin = $origin;
    }

    public function getOrigin(): ?FormInterface
    {
        return $this->origin;
    }
}
