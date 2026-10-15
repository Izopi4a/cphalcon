<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

final class DateType extends AbstractDateTimeType
{
    protected function defaultFormat(): string
    {
        return 'Y-m-d';
    }

    protected function defaultInputFormat(): string
    {
        return 'Y-m-d';
    }

    protected function html5Type(): string
    {
        return 'date';
    }

    public function getBlockPrefix(): string
    {
        return 'date';
    }
}
