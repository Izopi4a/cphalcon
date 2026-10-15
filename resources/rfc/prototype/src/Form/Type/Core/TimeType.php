<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

final class TimeType extends AbstractDateTimeType
{
    protected function defaultFormat(): string
    {
        return 'H:i';
    }

    protected function defaultInputFormat(): string
    {
        return 'H:i:s';
    }

    protected function html5Type(): string
    {
        return 'time';
    }

    public function getBlockPrefix(): string
    {
        return 'time';
    }
}
