<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

final class DateTimeType extends AbstractDateTimeType
{
    protected function defaultFormat(): string
    {
        return 'Y-m-d\TH:i';
    }

    protected function defaultInputFormat(): string
    {
        return 'Y-m-d H:i:s';
    }

    protected function html5Type(): string
    {
        return 'datetime-local';
    }

    public function getBlockPrefix(): string
    {
        return 'datetime';
    }
}
