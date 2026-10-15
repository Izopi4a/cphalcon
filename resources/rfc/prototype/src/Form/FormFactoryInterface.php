<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Type\Core\FormType;

interface FormFactoryInterface
{
    /** Creates a form named after the type's block prefix. */
    public function create(string $type = FormType::class, mixed $data = null, array $options = []): FormInterface;

    public function createNamed(string $name, string $type = FormType::class, mixed $data = null, array $options = []): FormInterface;

    public function createBuilder(string $type = FormType::class, mixed $data = null, array $options = []): FormBuilderInterface;

    public function createNamedBuilder(string $name, string $type = FormType::class, mixed $data = null, array $options = []): FormBuilderInterface;

    public function getRegistry(): FormRegistryInterface;
}
