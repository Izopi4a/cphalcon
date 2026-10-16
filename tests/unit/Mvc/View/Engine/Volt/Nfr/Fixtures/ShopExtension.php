<?php

declare(strict_types=1);

namespace Phalcon\Tests\Unit\Mvc\View\Engine\Volt\Nfr\Fixtures;

use Phalcon\Mvc\View\Engine\Volt\Runtime\AbstractExtension;
use Phalcon\Mvc\View\Engine\Volt\Runtime\VoltFilter;
use Phalcon\Mvc\View\Engine\Volt\Runtime\VoltFunction;
use Phalcon\Mvc\View\Engine\Volt\Runtime\VoltTest;

/**
 * The shape of an application extension: names and options, callables that
 * point at a DI service ("prices").
 */
final class ShopExtension extends AbstractExtension
{
    public function getFunctions(): array
    {
        return [
            new VoltFunction('price', ['prices', 'format']),
            new VoltFunction('badge', ['prices', 'badge'], ['safe' => true]),
        ];
    }

    public function getFilters(): array
    {
        return [new VoltFilter('price', ['prices', 'format'])];
    }

    public function getTests(): array
    {
        return [new VoltTest('premium', ['prices', 'isPremium'])];
    }
}
