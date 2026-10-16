<?php

declare(strict_types=1);

namespace Phalcon\Tests\Unit\Mvc\View\Engine\Volt\Nfr\Fixtures;

final class Html
{
    public static function bold(string $text): string
    {
        return '<b>' . $text . '</b>';
    }
}
