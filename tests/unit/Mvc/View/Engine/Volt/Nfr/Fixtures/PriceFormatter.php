<?php

declare(strict_types=1);

namespace Phalcon\Tests\Unit\Mvc\View\Engine\Volt\Nfr\Fixtures;

/**
 * A service with a dependency-free constructor that counts instances, to
 * show that runtime functions resolve services lazily (at render time).
 */
final class PriceFormatter
{
    public static int $instances = 0;

    public function __construct(private string $locale = 'en')
    {
        self::$instances++;
    }

    public function format(float $amount, string $currency = 'EUR'): string
    {
        return $this->locale . ':' . number_format($amount, 2) . ' ' . $currency;
    }

    public function badge(string $label): string
    {
        return '<span class="badge">' . htmlspecialchars($label) . '</span>';
    }

    public function isPremium(object $user): bool
    {
        return (bool) ($user->premium ?? false);
    }
}
