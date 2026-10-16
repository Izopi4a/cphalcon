<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Fixtures;

final class Html
{
    public static function bold(string $text): string
    {
        return '<b>' . $text . '</b>';
    }
}
