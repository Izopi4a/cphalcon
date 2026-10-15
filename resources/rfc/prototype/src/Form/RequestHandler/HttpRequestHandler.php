<?php
declare(strict_types=1);

namespace Phalcon\Form\RequestHandler;

use Phalcon\Form\Exception\UnexpectedTypeException;
use Phalcon\Form\FormInterface;
use Phalcon\Http\Request\FileInterface;
use Phalcon\Http\RequestInterface;

/**
 * Same algorithm as NativeRequestHandler, read from a Phalcon\Http\RequestInterface. This is what
 * Form::handleRequest() should use when a "request" service exists, so a form can be tested with a
 * request object instead of superglobals.
 */
class HttpRequestHandler extends AbstractRequestHandler
{
    public function handleRequest(FormInterface $form, mixed $request = null): void
    {
        if (!$request instanceof RequestInterface) {
            throw new UnexpectedTypeException($request, RequestInterface::class);
        }

        $method = $form->getConfig()->getMethod();

        if ($method !== self::getRequestMethod($request)) {
            return;
        }

        if (in_array($method, self::HTTP_METHODS_WITHOUT_BODY, true)) {
            $query = $request->getQuery();
            $this->submitFromQuery($form, $method, is_array($query) ? $query : []);
        } else {
            $post = $request->getPost();
            $this->submitFromBody(
                $form,
                $method,
                is_array($post) ? $post : [],
                self::normalizeUploadedFiles($request->getUploadedFiles())
            );
        }
    }

    /**
     * Phalcon's Request::getMethod() already applies X-HTTP-Method-Override on POST; doing it here
     * too keeps the rule explicit and makes other RequestInterface implementations behave the same.
     */
    private static function getRequestMethod(RequestInterface $request): string
    {
        $method = strtoupper($request->getMethod());

        if ('POST' === $method) {
            $override = $request->getHeader('X-HTTP-Method-Override');
            if ('' !== $override) {
                $method = strtoupper($override);
            }
        }

        return $method;
    }

    /**
     * Rebuilds the nested $_FILES-like tree the form expects from Phalcon's flat file list.
     *
     * Phalcon\Http\Request::getUploadedFiles() flattens $_FILES into File objects whose getKey()
     * is the input path joined with dots: the input "ticket[attachments][0]" gives
     * "ticket.attachments.0" and a plain input "avatar" gives "avatar". Form names cannot contain
     * dots (FormConfigBuilder::validateName), so splitting on "." is unambiguous. Files with
     * UPLOAD_ERR_NO_FILE become null, like NativeRequestHandler::fixPhpFilesArray().
     *
     * @param iterable<FileInterface> $files
     *
     * @return array<string|int, mixed>
     */
    public static function normalizeUploadedFiles(iterable $files): array
    {
        $out = [];

        foreach ($files as $file) {
            if (!$file instanceof FileInterface || !method_exists($file, 'getKey')) {
                continue;
            }
            $key = (string) $file->getKey();
            if ('' === $key) {
                continue;
            }

            $error = $file->getError();
            $error = is_numeric($error) ? (int) $error : UPLOAD_ERR_NO_FILE;

            $value = UPLOAD_ERR_NO_FILE === $error ? null : [
                'name'     => (string) $file->getName(),
                'type'     => (string) $file->getType(),
                'tmp_name' => (string) $file->getTempName(),
                'error'    => $error,
                'size'     => (int) $file->getSize(),
            ];

            $node = &$out;
            foreach (explode('.', $key) as $segment) {
                if (!isset($node[$segment]) || !is_array($node[$segment])) {
                    $node[$segment] = [];
                }
                $node = &$node[$segment];
            }
            $node = $value;
            unset($node);
        }

        return $out;
    }
}
