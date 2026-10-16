<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Fixtures;

use Phalcon\VoltNfr\Runtime\AbstractExtension;
use Phalcon\VoltNfr\Runtime\VoltFilter;
use Phalcon\VoltNfr\Runtime\VoltFunction;
use Phalcon\VoltNfr\Runtime\VoltTest;

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
