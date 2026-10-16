<?php

declare(strict_types=1);

namespace Phalcon\Tests\Unit\Mvc\View\Engine\Volt\Nfr\Fixtures;

final class Money
{
    public static function format(float $amount, string $currency = 'EUR'): string
    {
        return number_format($amount, 2) . ' ' . $currency;
    }
}
