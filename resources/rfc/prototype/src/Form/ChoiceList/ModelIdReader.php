<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

use Phalcon\Form\Exception\RuntimeException;
use Phalcon\Mvc\ModelInterface;

/**
 * Reads the primary key of a Phalcon\Mvc\Model as the choice value: the attribute names come
 * from the models metadata service of the model's DI, so nothing has to be configured. A
 * composite key becomes "a|b" (the parts in metadata order).
 *
 * Invokable so it can be the "choice_value" callable of a ChoiceType/ModelType; the
 * ModelChoiceLoader recognises it to query by primary key.
 *
 * Counterpart of Symfony's Doctrine bridge IdReader.
 *
 * prototype: the metadata is resolved lazily on first use because it needs the DI (and a
 * connection, with the Introspection strategy) which may not exist when the form type is
 * configured. Composite keys: "|" as separator is a guess the RFC has to settle (see the
 * open decisions in the README).
 */
final class ModelIdReader
{
    public const SEPARATOR = '|';

    /** @var list<string>|null */
    private ?array $attributes = null;

    /** @param class-string<ModelInterface> $class */
    public function __construct(private readonly string $class)
    {
    }

    public function getClass(): string
    {
        return $this->class;
    }

    /**
     * The primary key attribute names (model side: translated through the column map when
     * the model has one).
     *
     * @return list<string>
     */
    public function getAttributes(): array
    {
        if (null !== $this->attributes) {
            return $this->attributes;
        }

        /** @var ModelInterface $model */
        $model    = new ($this->class)();
        $metaData = $model->getModelsMetaData();
        $columns  = $metaData->getPrimaryKeyAttributes($model);

        if ([] === $columns) {
            throw new RuntimeException(sprintf('The model "%s" has no primary key; set the "choice_value" option.', $this->class));
        }

        // prototype: getPrimaryKeyAttributes() returns column names; with a columnMap() the
        // attributes read on the model are the mapped ones (column => attribute).
        $map = $metaData->getColumnMap($model);

        return $this->attributes = array_values(array_map(
            static fn (string $column): string => is_array($map) ? ($map[$column] ?? $column) : $column,
            $columns,
        ));
    }

    public function isSingleId(): bool
    {
        return 1 === count($this->getAttributes());
    }

    /**
     * The choice value of a model: its (possibly composite) primary key as a string, null for
     * anything that is not a persisted model (a new, unsaved model has no key).
     */
    public function __invoke(mixed $model): ?string
    {
        if (!$model instanceof ModelInterface) {
            return null;
        }

        $parts = [];
        foreach ($this->getAttributes() as $attribute) {
            $value = $model->readAttribute($attribute);
            if (null === $value) {
                return null;
            }
            $parts[] = (string) $value;
        }

        return implode(self::SEPARATOR, $parts);
    }

    /**
     * Splits a choice value back into attribute => value, or null when it does not have the
     * shape of a key of this model.
     *
     * @return array<string, string>|null
     */
    public function parse(string $value): ?array
    {
        $attributes = $this->getAttributes();
        $parts      = 1 === count($attributes) ? [$value] : explode(self::SEPARATOR, $value);

        if (count($parts) !== count($attributes)) {
            return null;
        }

        return array_combine($attributes, $parts);
    }
}
