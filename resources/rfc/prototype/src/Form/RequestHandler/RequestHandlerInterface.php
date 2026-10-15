<?php
declare(strict_types=1);

namespace Phalcon\Form\RequestHandler;

use Phalcon\Form\FormInterface;

interface RequestHandlerInterface
{
    /** Reads the request and calls $form->submit() if the form was submitted. */
    public function handleRequest(FormInterface $form, mixed $request = null): void;

    /** Whether submitted data looks like an uploaded file. */
    public function isFileUpload(mixed $data): bool;

    /** PHP upload error code (UPLOAD_ERR_*) when it is a failed upload, else null. */
    public function getUploadFileError(mixed $data): ?int;
}
