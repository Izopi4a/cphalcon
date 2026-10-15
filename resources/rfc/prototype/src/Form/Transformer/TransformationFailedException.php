<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

use Phalcon\Form\Exception\RuntimeException;

class TransformationFailedException extends RuntimeException
{
    public function __construct(
        string $message = '',
        int $code = 0,
        ?\Throwable $previous = null,
        private readonly ?string $invalidMessage = null,
        private readonly array $invalidMessageParameters = [],
    ) {
        parent::__construct($message, $code, $previous);
    }

    /** Message meant for the end user, overrides the form's "invalid_message" option. */
    public function getInvalidMessage(): ?string
    {
        return $this->invalidMessage;
    }

    public function getInvalidMessageParameters(): array
    {
        return $this->invalidMessageParameters;
    }
}
