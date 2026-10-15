<?php
declare(strict_types=1);

namespace Phalcon\Form\Event;

/**
 * Event names fired through Phalcon\Events\Manager (component type "form").
 * Same life cycle as Symfony Forms so the documentation maps 1:1.
 */
final class FormEvents
{
    public const PRE_SET_DATA  = 'form:preSetData';
    public const POST_SET_DATA = 'form:postSetData';
    public const PRE_SUBMIT    = 'form:preSubmit';
    public const SUBMIT        = 'form:submit';
    public const POST_SUBMIT   = 'form:postSubmit';
    public const POST_VALIDATE = 'form:postValidate';

    private function __construct()
    {
    }
}
