<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures\Orm;

use Phalcon\Mvc\Model;

/** translations(locale, key_name, text) with a composite primary key (locale, key_name). */
final class Translation extends Model
{
    public ?string $locale = null;
    public ?string $key_name = null;
    public ?string $text = null;

    public function initialize(): void
    {
        $this->setSource('translations');
    }

    public function __toString(): string
    {
        return (string) $this->text;
    }
}
