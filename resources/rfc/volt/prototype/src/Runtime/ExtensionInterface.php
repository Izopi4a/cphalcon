<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Runtime;

/**
 * A bundle of runtime functions, filters and tests, registered with
 * Volt::addExtension(). Only names and options are read at compile time; the
 * callables run at render time.
 */
interface ExtensionInterface
{
    /**
     * @return list<VoltFunction>
     */
    public function getFunctions(): array;

    /**
     * @return list<VoltFilter>
     */
    public function getFilters(): array;

    /**
     * @return list<VoltTest>
     */
    public function getTests(): array;
}
