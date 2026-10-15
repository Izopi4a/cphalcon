<?php
declare(strict_types=1);

namespace Phalcon\Form\RequestHandler;

use Phalcon\Form\FormInterface;
use Phalcon\Form\Util\FormUtil;

/**
 * The request-source-independent half of Symfony's request handling algorithm. Subclasses only
 * decide where the method, query params, body params and (normalised) uploaded files come from.
 */
abstract class AbstractRequestHandler implements RequestHandlerInterface
{
    protected const HTTP_METHODS_WITHOUT_BODY = ['GET', 'HEAD', 'TRACE'];

    public function isFileUpload(mixed $data): bool
    {
        return is_array($data) && isset($data['error']) && is_int($data['error']);
    }

    public function getUploadFileError(mixed $data): ?int
    {
        if (!is_array($data) || !isset($data['error']) || !is_int($data['error'])) {
            return null;
        }

        return UPLOAD_ERR_OK === $data['error'] ? null : $data['error'];
    }

    /** GET/HEAD/TRACE: the form's slice of the query string. A named form needs its key present. */
    protected function submitFromQuery(FormInterface $form, string $method, array $query): void
    {
        $name = $form->getName();

        if ('' === $name) {
            $data = $query;
        } else {
            if (!isset($query[$name])) {
                return;
            }
            $data = $query[$name];
        }

        $this->submitIfPresent($form, $method, $data);
    }

    /**
     * Other methods: body params merged with uploaded files. $files must already be in per-file
     * shape (['name', 'type', 'tmp_name', 'error', 'size'] leaves, null for "no file") nested by
     * the same keys as $params.
     */
    protected function submitFromBody(FormInterface $form, string $method, array $params, array $files): void
    {
        $name = $form->getName();

        if ('' !== $name) {
            if (!isset($params[$name]) && !isset($files[$name])) {
                return;
            }
            $default = $form->getConfig()->getCompound() ? [] : null;
            $params  = $params[$name] ?? $default;
            $files   = $files[$name] ?? $default;
        }

        $data = is_array($params) && is_array($files) ? FormUtil::mergeParamsAndFiles($params, $files) : ($params ?? $files);

        $this->submitIfPresent($form, $method, $data);
    }

    /** Unnamed-root guard, "_method" stripping and the PATCH => clearMissing=false rule. */
    private function submitIfPresent(FormInterface $form, string $method, mixed $data): void
    {
        // An unnamed root form must contain at least one known child key to count as submitted.
        if ('' === $form->getName() && is_array($data)) {
            $known = false;
            foreach ($form->all() as $child) {
                if (array_key_exists($child->getName(), $data)) {
                    $known = true;
                    break;
                }
            }
            if (!$known) {
                return;
            }
        }

        // Method-spoofing field added by the form renderer, not a real child.
        if (is_array($data) && isset($data['_method']) && $method === $data['_method'] && !$form->has('_method')) {
            unset($data['_method']);
        }

        $form->submit($data, 'PATCH' !== $method);
    }
}
