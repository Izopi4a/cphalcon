<?php
declare(strict_types=1);

namespace Phalcon\Form\Util;

final class FormUtil
{
    /**
     * Only null and the empty string count as "empty" form data.
     * false, 0, "0" and [] are real values.
     */
    public static function isEmpty(mixed $data): bool
    {
        return null === $data || '' === $data;
    }

    /**
     * Merges request params and uploaded files (same shape as $_POST / $_FILES after normalisation).
     * Files win over params on key collision, matching Symfony's FormUtil::mergeParamsAndFiles.
     */
    public static function mergeParamsAndFiles(array $params, array $files): array
    {
        foreach ($files as $key => $value) {
            if (is_array($value) && isset($params[$key]) && is_array($params[$key])) {
                $params[$key] = self::mergeParamsAndFiles($params[$key], $value);
            } elseif (null !== $value) {
                $params[$key] = $value;
            }
        }

        return $params;
    }
}
