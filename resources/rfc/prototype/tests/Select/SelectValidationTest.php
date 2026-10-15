<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Form\EventListener\TransformationFailureListener;
use Phalcon\Form\FormFactory;
use Phalcon\Form\FormRegistry;
use Phalcon\Form\Options\UndefinedOptionsException;
use Phalcon\Form\Transformer\TransformationFailedException;
use Phalcon\Form\Type\Core\ChoiceType;
use Phalcon\Form\Type\PreloadedExtension;
use Phalcon\Form\Type\TransformationFailureExtension;
use PHPUnit\Framework\TestCase;

/**
 * Submitted values that are not in the list: single -> transformation failure (not synchronized),
 * multiple -> the known values are kept and the form gets one error.
 */
final class SelectValidationTest extends TestCase
{
    private const COLORS = ['Red' => 'r', 'Green' => 'g', 'Blue' => 'b'];

    private FormFactory $factory;
    /** With the extension that turns transformation failures into form errors (Symfony core extension). */
    private FormFactory $factoryWithErrors;

    protected function setUp(): void
    {
        $this->factory           = new FormFactory();
        $this->factoryWithErrors = new FormFactory(new FormRegistry([new PreloadedExtension([], [new TransformationFailureExtension()])]));
    }

    public function testUnknownSingleValueIsNotSynchronized(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'g', ['choices' => self::COLORS])->submit('x');

        self::assertFalse($form->isSynchronized());
        self::assertInstanceOf(TransformationFailedException::class, $form->getTransformationFailure());
        self::assertStringContainsString('"x"', $form->getTransformationFailure()->getMessage());
        self::assertNull($form->getData(), 'model data is reset, the old "g" is gone');
        self::assertNull($form->getNormData());
        self::assertSame('x', $form->getViewData(), 'the view keeps the raw submitted value');
        self::assertSame('x', $form->createView()->vars['value']);
        self::assertCount(0, $form->getErrors(), 'without the TransformationFailureExtension nobody adds an error...');
        self::assertTrue($form->isValid(), '...so isValid() is true although not synchronized (same as Symfony without the validator)');
    }

    public function testUnknownSingleValueWithTransformationFailureExtension(): void
    {
        $form = $this->factoryWithErrors->createNamed('color', ChoiceType::class, 'g', ['choices' => self::COLORS])->submit('x');

        self::assertFalse($form->isSynchronized());
        self::assertFalse($form->isValid());
        $errors = $form->getErrors();
        self::assertCount(1, $errors);
        self::assertSame(TransformationFailureListener::NOT_SYNCHRONIZED_ERROR, $errors[0]->getCode());
        self::assertSame('The selected choice is invalid.', $errors[0]->getMessage(), 'ChoiceType invalid_message');
        self::assertSame(['{{ value }}' => 'x'], $errors[0]->getMessageParameters());
        self::assertSame($form, $errors[0]->getOrigin());

        $view = $form->createView();
        self::assertFalse($view->vars['valid']);
        self::assertCount(1, $view->vars['errors']);
        self::assertSame('x', $view->vars['value']);
    }

    public function testCustomInvalidMessage(): void
    {
        $form = $this->factoryWithErrors->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'invalid_message' => 'Nope: {{ value }}'])->submit('x');
        self::assertSame('Nope: x', (string) $form->getErrors()[0]);

        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true, 'invalid_message' => 'Nope: {{ value }}'])->submit(['x', 'r']);
        self::assertSame('Nope: x', (string) $form->getErrors()[0]);
    }

    public function testUnknownInNestedFormBubblesNowhere(): void
    {
        $form = $this->factoryWithErrors->createNamedBuilder('f')
            ->add('color', ChoiceType::class, ['choices' => self::COLORS])
            ->getForm()
            ->submit(['color' => 'x']);

        self::assertTrue($form->isSynchronized(), 'the parent is fine');
        self::assertFalse($form->isValid(), 'but invalid because of the child');
        self::assertCount(0, $form->getErrors(), 'error_bubbling is false for choices');
        self::assertCount(1, $form->get('color')->getErrors());
        self::assertCount(1, $form->getErrors(true));
        self::assertSame([], $form->getData(), 'the unsynchronized child is not mapped back at all (no key)');
    }

    public function testUnknownAmongSeveralInMultipleKeepsTheKnownOnes(): void
    {
        $form = $this->factory->createNamed('colors', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true])->submit(['r', 'x', 'b']);

        self::assertTrue($form->isSynchronized(), 'multiple: unknown values do not fail the transformation');
        self::assertSame(['r', 'b'], $form->getData(), 'the known ones are kept');
        self::assertSame(['r', 'b'], $form->getViewData());
        self::assertFalse($form->isValid());

        $errors = $form->getErrors();
        self::assertCount(1, $errors);
        self::assertSame('The selected choice is invalid.', $errors[0]->getMessage());
        self::assertSame(['{{ value }}' => 'x'], $errors[0]->getMessageParameters());
        self::assertInstanceOf(TransformationFailedException::class, $errors[0]->getCause());
        self::assertNull($errors[0]->getCode(), 'Symfony attaches no code to this error');

        $form = $this->factory->createNamed('colors', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true])->submit(['x', 'y']);
        self::assertSame([], $form->getData());
        self::assertSame(['{{ value }}' => 'x", "y'], $form->getErrors()[0]->getMessageParameters(), 'all unknown values are listed');
    }

    public function testUnknownInMultipleDoesNotAlsoGetANotSynchronizedError(): void
    {
        $form = $this->factoryWithErrors->createNamed('colors', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true])->submit(['r', 'x']);

        self::assertCount(1, $form->getErrors(), 'the form is synchronized, so only the ChoiceType error');
        self::assertNull($form->getErrors()[0]->getCode());
    }

    public function testScalarSubmittedToMultipleIsNotSynchronized(): void
    {
        $form = $this->factoryWithErrors->createNamed('colors', ChoiceType::class, ['r'], ['choices' => self::COLORS, 'multiple' => true])->submit('r');

        self::assertFalse($form->isSynchronized());
        self::assertNull($form->getData());
        self::assertSame('r', $form->getViewData());
        self::assertCount(1, $form->getErrors());
        self::assertSame(TransformationFailureListener::NOT_SYNCHRONIZED_ERROR, $form->getErrors()[0]->getCode());
    }

    public function testNestedArraysInSubmittedValuesAreRejected(): void
    {
        $form = $this->factory->createNamed('colors', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true])->submit(['r', ['g']]);

        self::assertFalse($form->isSynchronized(), 'all submitted choices must be null, strings or ints');
        self::assertStringContainsString('NULL, strings or ints', $form->getTransformationFailure()->getMessage());
    }

    public function testIntegersMaySubmitAsInts(): void
    {
        // e.g. from a JSON body: ints are accepted and matched by their string form
        $form = $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => ['One' => 1, 'Two' => 2], 'multiple' => true])->submit([1, 2]);

        self::assertTrue($form->isSynchronized());
        self::assertSame([1, 2], $form->getData());
    }

    public function testExpandedUnknownValues(): void
    {
        $form = $this->factoryWithErrors->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'expanded' => true])->submit('x');
        self::assertFalse($form->isSynchronized(), 'radios: unknown value -> transformation failure');
        self::assertCount(1, $form->getErrors());
        self::assertSame(TransformationFailureListener::NOT_SYNCHRONIZED_ERROR, $form->getErrors()[0]->getCode());

        $form = $this->factoryWithErrors->createNamed('colors', ChoiceType::class, null, ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true])->submit(['x', 'r']);
        self::assertTrue($form->isSynchronized(), 'checkboxes: known values kept');
        self::assertSame(['r'], $form->getData());
        self::assertCount(1, $form->getErrors(), 'one error on the parent');
        self::assertSame($form, $form->getErrors()[0]->getOrigin());
        self::assertCount(0, $form->get('0')->getErrors(), 'children are fine');
    }

    public function testConstraintsOptionIsNotDefinedYet(): void
    {
        // TODO(M2 validation bridge): wire a "constraints" option (Phalcon\Filter\Validation
        // validators, e.g. InclusionIn) and register the TransformationFailureExtension only when
        // it is empty, like Symfony's ValidatorExtension does. Until then the option is unknown.
        $this->expectException(UndefinedOptionsException::class);
        $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'constraints' => ['not_blank']]);
    }
}
