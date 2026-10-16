<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Runtime;

abstract class AbstractExtension implements ExtensionInterface
{
    public function getFunctions(): array
    {
        return [];
    }

    public function getFilters(): array
    {
        return [];
    }

    public function getTests(): array
    {
        return [];
    }
}
