<?php
declare(strict_types=1);

namespace Phalcon\Form\EventListener;

use Phalcon\Form\Event\EventSubscriberInterface;
use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;
use Phalcon\Form\Exception\UnexpectedTypeException;
use Phalcon\Form\FormInterface;

/**
 * Resizes a collection form to match the data it is given.
 *
 *   postSetData (priority 255): drop all children, add one per key => value of the model data.
 *   preSubmit:                  non-array -> []; allow_delete removes children missing from the
 *                               payload; allow_add adds a child per new key (prototype options).
 *   submit (priority 50):       delete_empty, drop data keys without a child (allow_delete),
 *                               re-index when keep_as_list, then replace the event data.
 *
 * Same algorithm as Symfony's ResizeFormListener; the only difference is that the events travel
 * through Phalcon\Events\Manager (see FormConfigBuilder::addEventSubscriber for the wrapping).
 */
class ResizeFormListener implements EventSubscriberInterface
{
    /** @var array<string, mixed> options used for children added on submit */
    protected array $prototypeOptions;
    private \Closure|bool $deleteEmpty;

    /**
     * @param string               $type             entry type FQCN
     * @param array<string, mixed> $options          entry options
     * @param bool|callable        $deleteEmpty      true, or callable(mixed $childData): bool
     * @param array<string, mixed> $prototypeOptions options for entries added on submit (defaults to $options)
     */
    public function __construct(
        private readonly string $type,
        private readonly array $options = [],
        private readonly bool $allowAdd = false,
        private readonly bool $allowDelete = false,
        bool|callable $deleteEmpty = false,
        ?array $prototypeOptions = null,
        private readonly bool $keepAsList = false,
    ) {
        $this->deleteEmpty      = is_bool($deleteEmpty) ? $deleteEmpty : $deleteEmpty(...);
        $this->prototypeOptions = $prototypeOptions ?? $options;
    }

    public static function getSubscribedEvents(): array
    {
        return [
            FormEvents::PRE_SET_DATA  => 'preSetData',
            FormEvents::POST_SET_DATA => ['postSetData', 255], // as early as possible
            FormEvents::PRE_SUBMIT    => 'preSubmit',
            // MergeCollectionListener uses priority 10, this one has to run before it.
            FormEvents::SUBMIT        => ['onSubmit', 50],
        ];
    }

    /**
     * Only validates the data type early; the children are (re)built in postSetData so that
     * other PRE_SET_DATA listeners may still replace the data.
     */
    public function preSetData(FormEvent $event): void
    {
        self::assertCollection($event->getData() ?? []);
    }

    public function postSetData(FormEvent $event): void
    {
        $form = $event->getForm();
        $data = $event->getData() ?? [];

        self::assertCollection($data);

        // First remove all rows
        foreach ($form as $name => $child) {
            $form->remove((string) $name);
        }

        // Then add all rows again in the correct order
        foreach ($data as $name => $value) {
            $form->add((string) $name, $this->type, array_replace([
                'property_path' => '[' . $name . ']',
            ], $this->options));
        }
    }

    public function preSubmit(FormEvent $event): void
    {
        $form = $event->getForm();
        $data = $event->getData();

        if (!is_array($data)) {
            $data = [];
        }

        // Remove all rows that are missing from the submitted data
        if ($this->allowDelete) {
            foreach ($form as $name => $child) {
                if (!isset($data[$name])) {
                    $form->remove((string) $name);
                }
            }
        }

        // Add all additional rows
        if ($this->allowAdd) {
            foreach ($data as $name => $value) {
                if (!$form->has((string) $name)) {
                    $form->add((string) $name, $this->type, array_replace([
                        'property_path' => '[' . $name . ']',
                    ], $this->prototypeOptions));
                }
            }
        }

        // Like Symfony, the event data is left untouched: Form::submit() turns null into [] itself
        // and reports any other non-array as a transformation failure. Extra keys without
        // allow_add have no child to be submitted to and end up in the collection's extraData.
    }

    public function onSubmit(FormEvent $event): void
    {
        $form = $event->getForm();
        $data = $event->getData() ?? [];

        // At this point, $data is an array or an array-like object that already contains the
        // new entries, which were added by the data mapper. The data mapper ignores existing
        // entries, so we need to manually unset removed entries in the collection.
        self::assertCollection($data);

        if (false !== $this->deleteEmpty) {
            $previousData = $form->getData();
            /** @var FormInterface $child */
            foreach ($form as $name => $child) {
                if (!$child->isValid() || !$child->isSynchronized()) {
                    continue;
                }

                $isNew   = !isset($previousData[$name]);
                $isEmpty = $this->deleteEmpty instanceof \Closure ? ($this->deleteEmpty)($child->getData()) : $child->isEmpty();

                // $isNew can only be true if allowAdd is true, so we don't
                // need to check allowAdd again
                if ($isEmpty && ($isNew || $this->allowDelete)) {
                    unset($data[$name]);
                    $form->remove((string) $name);
                }
            }
        }

        // The data mapper only adds, but does not remove items, so do this here
        if ($this->allowDelete) {
            $toDelete = [];

            foreach ($data as $name => $child) {
                if (!$form->has((string) $name)) {
                    $toDelete[] = $name;
                }
            }

            foreach ($toDelete as $name) {
                unset($data[$name]);
            }
        }

        if ($this->keepAsList) {
            $formReindex = [];
            foreach ($form as $name => $child) {
                $formReindex[] = $child;
                $form->remove((string) $name);
            }
            foreach ($formReindex as $index => $child) {
                $form->add((string) $index, $this->type, array_replace([
                    'property_path' => '[' . $index . ']',
                ], $this->options));
            }
            $data = array_values(is_array($data) ? $data : iterator_to_array($data));
        }

        $event->setData($data);
    }

    private static function assertCollection(mixed $data): void
    {
        if (!is_array($data) && !($data instanceof \Traversable && $data instanceof \ArrayAccess)) {
            throw new UnexpectedTypeException($data, 'array or (\Traversable and \ArrayAccess)');
        }
    }
}
