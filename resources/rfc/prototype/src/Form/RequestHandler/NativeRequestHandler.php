<?php
declare(strict_types=1);

namespace Phalcon\Form\RequestHandler;

use Phalcon\Form\Exception\UnexpectedTypeException;
use Phalcon\Form\FormError;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Util\FormUtil;

/**
 * Reads $_GET / $_POST / $_FILES. Mirrors Symfony's NativeRequestHandler:
 * method must match, named forms submit only when their key is present, PATCH keeps missing fields.
 */
class NativeRequestHandler implements RequestHandlerInterface
{
    private const HTTP_METHODS_WITHOUT_BODY = ['GET', 'HEAD', 'TRACE'];

    public function handleRequest(FormInterface $form, mixed $request = null): void
    {
        if (null !== $request) {
            throw new UnexpectedTypeException($request, 'null');
        }

        $name   = $form->getName();
        $method = $form->getConfig()->getMethod();

        if ($method !== self::getRequestMethod()) {
            return;
        }

        if (in_array($method, self::HTTP_METHODS_WITHOUT_BODY, true)) {
            if ('' === $name) {
                $data = $_GET;
            } else {
                if (!isset($_GET[$name])) {
                    return;
                }
                $data = $_GET[$name];
            }
        } else {
            $files = self::fixPhpFilesArray($_FILES);

            if ('' === $name) {
                $params = $_POST;
            } else {
                if (!isset($_POST[$name]) && !isset($files[$name])) {
                    return;
                }
                $default = $form->getConfig()->getCompound() ? [] : null;
                $params  = $_POST[$name] ?? $default;
                $files   = $files[$name] ?? $default;
            }

            $data = is_array($params) && is_array($files) ? FormUtil::mergeParamsAndFiles($params, $files) : ($params ?? $files);
        }

        // An unnamed root form must contain at least one known child key to count as submitted.
        if ('' === $name && is_array($data)) {
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

        if (is_array($data) && isset($data['_method']) && $method === $data['_method'] && !$form->has('_method')) {
            unset($data['_method']);
        }

        $form->submit($data, 'PATCH' !== $method);
    }

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

    protected static function getRequestMethod(): string
    {
        $method = strtoupper($_SERVER['REQUEST_METHOD'] ?? 'GET');
        if ('POST' === $method && isset($_SERVER['HTTP_X_HTTP_METHOD_OVERRIDE'])) {
            $method = strtoupper((string) $_SERVER['HTTP_X_HTTP_METHOD_OVERRIDE']);
        }

        return $method;
    }

    /**
     * Turns PHP's per-attribute $_FILES layout (name[a][b], tmp_name[a][b], ...) into per-file arrays,
     * and drops UPLOAD_ERR_NO_FILE entries so they read as null.
     */
    public static function fixPhpFilesArray(array $files): array
    {
        $out = [];
        foreach ($files as $key => $file) {
            $out[$key] = self::fixOne($file);
        }

        return $out;
    }

    private static function fixOne(mixed $file): mixed
    {
        if (!is_array($file)) {
            return $file;
        }
        $keys = ['error', 'name', 'size', 'tmp_name', 'type'];
        $has  = array_intersect($keys, array_keys($file));
        if (count($has) === count($keys) && !is_array($file['name'])) {
            return UPLOAD_ERR_NO_FILE === $file['error'] ? null : $file;
        }
        if (count($has) === count($keys) && is_array($file['name'])) {
            $result = [];
            foreach ($file['name'] as $k => $_) {
                $result[$k] = self::fixOne([
                    'error'    => $file['error'][$k],
                    'name'     => $file['name'][$k],
                    'size'     => $file['size'][$k],
                    'tmp_name' => $file['tmp_name'][$k],
                    'type'     => $file['type'][$k],
                ]);
            }

            return $result;
        }
        $result = [];
        foreach ($file as $k => $v) {
            $result[$k] = self::fixOne($v);
        }

        return $result;
    }
}
