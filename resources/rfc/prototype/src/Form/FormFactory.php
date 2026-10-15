<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Type\Core\FormType;

class FormFactory implements FormFactoryInterface
{
    public function __construct(private readonly FormRegistryInterface $registry = new FormRegistry())
    {
    }

    public function create(string $type = FormType::class, mixed $data = null, array $options = []): FormInterface
    {
        return $this->createBuilder($type, $data, $options)->getForm();
    }

    public function createNamed(string $name, string $type = FormType::class, mixed $data = null, array $options = []): FormInterface
    {
        return $this->createNamedBuilder($name, $type, $data, $options)->getForm();
    }

    public function createBuilder(string $type = FormType::class, mixed $data = null, array $options = []): FormBuilderInterface
    {
        return $this->createNamedBuilder($this->registry->getType($type)->getBlockPrefix(), $type, $data, $options);
    }

    public function createNamedBuilder(string $name, string $type = FormType::class, mixed $data = null, array $options = []): FormBuilderInterface
    {
        if (null !== $data && !array_key_exists('data', $options)) {
            $options['data'] = $data;
        }

        $builder = $this->registry->getType($type)->createBuilder($this, $name, $options);

        return $builder;
    }

    public function getRegistry(): FormRegistryInterface
    {
        return $this->registry;
    }
}
