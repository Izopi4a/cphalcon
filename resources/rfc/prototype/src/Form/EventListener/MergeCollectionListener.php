<?php
declare(strict_types=1);

namespace Phalcon\Form\EventListener;

use Phalcon\Form\Event\EventSubscriberInterface;
use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;
use Phalcon\Form\Exception\UnexpectedTypeException;

/**
 * Merges the collection produced by the view->norm transformation back into the original norm
 * collection (SUBMIT event), so that the original array/collection keeps its identity and keys
 * and the model receives adder/remover calls for the delta only. Items are compared with ===.
 *
 * Used by ChoiceType when multiple && by_reference. Same algorithm as Symfony.
 */
final class MergeCollectionListener implements EventSubscriberInterface
{
    public function __construct(
        private readonly bool $allowAdd = false,
        private readonly bool $allowDelete = false,
    ) {
    }

    public static function getSubscribedEvents(): array
    {
        return [FormEvents::SUBMIT => 'onSubmit'];
    }

    public function onSubmit(FormEvent $event): void
    {
        $dataToMergeInto = $event->getForm()->getNormData();
        $data            = $event->getData() ?? [];

        if (!is_array($data) && !($data instanceof \Traversable && $data instanceof \ArrayAccess)) {
            throw new UnexpectedTypeException($data, 'array or (\Traversable and \ArrayAccess)');
        }
        if (null !== $dataToMergeInto && !is_array($dataToMergeInto) && !($dataToMergeInto instanceof \Traversable && $dataToMergeInto instanceof \ArrayAccess)) {
            throw new UnexpectedTypeException($dataToMergeInto, 'array or (\Traversable and \ArrayAccess)');
        }

        // If we are not allowed to change anything, return immediately
        if ($data === $dataToMergeInto || (!$this->allowAdd && !$this->allowDelete)) {
            $event->setData($dataToMergeInto);

            return;
        }

        if (null === $dataToMergeInto) {
            // No original data was set. Set it if allowed
            if ($this->allowAdd) {
                $dataToMergeInto = $data;
            }
        } else {
            // Calculate delta
            $itemsToAdd    = is_object($data) ? clone $data : $data;
            $itemsToDelete = [];

            foreach ($dataToMergeInto as $beforeKey => $beforeItem) {
                foreach ($data as $afterKey => $afterItem) {
                    if ($afterItem === $beforeItem) {
                        // Item found, next original item
                        unset($itemsToAdd[$afterKey]);
                        continue 2;
                    }
                }

                // Item not found, remember for deletion
                $itemsToDelete[] = $beforeKey;
            }

            // Remove deleted items before adding to free keys that are to be replaced
            if ($this->allowDelete) {
                foreach ($itemsToDelete as $key) {
                    unset($dataToMergeInto[$key]);
                }
            }

            // Add remaining items
            if ($this->allowAdd) {
                foreach ($itemsToAdd as $key => $item) {
                    if (!isset($dataToMergeInto[$key])) {
                        $dataToMergeInto[$key] = $item;
                    } else {
                        $dataToMergeInto[] = $item;
                    }
                }
            }
        }

        $event->setData($dataToMergeInto);
    }
}
