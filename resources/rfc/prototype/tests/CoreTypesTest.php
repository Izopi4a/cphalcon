<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\EventListener\TransformationFailureListener;
use Phalcon\Form\FormFactory;
use Phalcon\Form\FormRegistry;
use Phalcon\Form\Options\InvalidOptionsException;
use Phalcon\Form\Type\Core\CheckboxType;
use Phalcon\Form\Type\Core\ColorType;
use Phalcon\Form\Type\Core\DateTimeType;
use Phalcon\Form\Type\Core\DateType;
use Phalcon\Form\Type\Core\EmailType;
use Phalcon\Form\Type\Core\HiddenType;
use Phalcon\Form\Type\Core\IntegerType;
use Phalcon\Form\Type\Core\NumberType;
use Phalcon\Form\Type\Core\PasswordType;
use Phalcon\Form\Type\Core\RadioType;
use Phalcon\Form\Type\Core\RangeType;
use Phalcon\Form\Type\Core\SearchType;
use Phalcon\Form\Type\Core\TelType;
use Phalcon\Form\Type\Core\TextareaType;
use Phalcon\Form\Type\Core\TimeType;
use Phalcon\Form\Type\Core\UrlType;
use Phalcon\Form\Type\PreloadedExtension;
use Phalcon\Form\Type\TransformationFailureExtension;
use PHPUnit\Framework\TestCase;

final class CoreTypesTest extends TestCase
{
    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    public function testTextFamilyBlockPrefixes(): void
    {
        foreach ([EmailType::class => 'email', SearchType::class => 'search', TelType::class => 'tel', RangeType::class => 'range', UrlType::class => 'url'] as $type => $prefix) {
            $form = $this->factory->createNamed('f', $type);
            $form->submit('v');
            self::assertSame(['form', 'text', $prefix, '_f'], $form->createView()->vars['block_prefixes'], $type);
        }
    }

    public function testTextareaNormalisesLineEndings(): void
    {
        $form = $this->factory->createNamed('f', TextareaType::class);
        $form->submit("a\r\nb\rc");

        self::assertSame("a\nb\nc", $form->getData());
        self::assertSame("a\nb\nc", $form->createView()->vars['value']);
        self::assertNull($this->factory->createNamed('f', TextareaType::class)->submit('')->getData(), '"" still becomes null');
    }

    public function testPasswordIsNeverRenderedAndNotTrimmed(): void
    {
        $form = $this->factory->createNamed('f', PasswordType::class)->submit(' secret ');

        self::assertSame(' secret ', $form->getData());
        self::assertSame('', $form->createView()->vars['value']);

        $form = $this->factory->createNamed('f', PasswordType::class, null, ['always_empty' => false])->submit('secret');
        self::assertSame('secret', $form->createView()->vars['value']);
    }

    public function testUrlGetsDefaultProtocol(): void
    {
        self::assertSame('http://example.com', $this->factory->createNamed('f', UrlType::class)->submit('example.com')->getData());
        self::assertSame('ftp://example.com', $this->factory->createNamed('f', UrlType::class)->submit('ftp://example.com')->getData(), 'existing protocol kept');
        self::assertSame('mailto:a@b.c', $this->factory->createNamed('f', UrlType::class)->submit('mailto:a@b.c')->getData());
        self::assertSame('example.com', $this->factory->createNamed('f', UrlType::class, null, ['default_protocol' => null])->submit('example.com')->getData());
        self::assertSame('text', $this->factory->createNamed('f', UrlType::class)->submit('x')->createView()->vars['type']);
    }

    public function testColorHtml5Validation(): void
    {
        $form = $this->factory->createNamed('f', ColorType::class, null, ['html5' => true])->submit('#00ff00');
        self::assertTrue($form->isValid());
        self::assertSame('#00ff00', $form->getData());

        $form = $this->factory->createNamed('f', ColorType::class, null, ['html5' => true])->submit('green');
        self::assertFalse($form->isValid());
        self::assertSame('INVALID_COLOR_ERROR', $form->getErrors()[0]->getCode());
        self::assertTrue($this->factory->createNamed('f', ColorType::class)->submit('green')->isValid(), 'no check without html5');
    }

    public function testHiddenDefaults(): void
    {
        $form = $this->factory->createNamedBuilder('f')->add('id', HiddenType::class)->getForm();
        $form->submit(['id' => '5']);
        $view = $form->createView();

        self::assertFalse($view['id']->vars['required']);
        self::assertTrue($form->get('id')->getConfig()->getErrorBubbling());
        self::assertSame('5', $form->getData()['id']);
    }

    public function testIntegerType(): void
    {
        $form = $this->factory->createNamed('f', IntegerType::class)->submit(' 42 ');
        self::assertSame(42, $form->getData());
        self::assertSame('42', $form->createView()->vars['value']);

        $form = $this->factory->createNamed('f', IntegerType::class, 7);
        self::assertSame('7', $form->getViewData(), 'int model data rendered as string');

        $form = $this->factory->createNamed('f', IntegerType::class)->submit('1.5');
        self::assertFalse($form->isSynchronized());
        self::assertNull($form->getData());
        self::assertSame('1.5', $form->getViewData(), 'raw input kept for re-rendering');

        self::assertNull($this->factory->createNamed('f', IntegerType::class)->submit('')->getData());
    }

    public function testNumberType(): void
    {
        $form = $this->factory->createNamed('f', NumberType::class, null, ['scale' => 2])->submit('3,14159');
        self::assertSame(3.14, $form->getData());
        self::assertSame('3.14', $form->createView()->vars['value']);

        $form = $this->factory->createNamed('f', NumberType::class, null, ['input' => 'string', 'scale' => 1], )->submit('2.5');
        self::assertSame('2.5', $form->getData(), 'input=string gives a string model');

        $form = $this->factory->createNamed('f', NumberType::class, 1.5, ['html5' => true]);
        $view = $form->createView();
        self::assertSame('number', $view->vars['type']);
        self::assertSame('any', $view->vars['attr']['step']);

        self::assertFalse($this->factory->createNamed('f', NumberType::class)->submit('x')->isSynchronized());

        $this->expectException(InvalidOptionsException::class);
        $this->factory->createNamed('f', NumberType::class, null, ['input' => 'float']);
    }

    public function testDateTypeInputs(): void
    {
        $form = $this->factory->createNamed('f', DateType::class, new \DateTime('2024-05-06 10:00'));
        self::assertSame('2024-05-06', $form->getViewData());
        $form->submit('2024-12-24');
        self::assertInstanceOf(\DateTime::class, $form->getData());
        self::assertSame('2024-12-24 00:00:00', $form->getData()->format('Y-m-d H:i:s'));
        self::assertSame('date', $form->createView()->vars['type']);

        $form = $this->factory->createNamed('f', DateType::class, '2024-01-02', ['input' => 'string']);
        self::assertSame('2024-01-02', $form->getViewData());
        self::assertSame('2024-02-03', $form->submit('2024-02-03')->getData());

        $form = $this->factory->createNamed('f', DateType::class, null, ['input' => 'datetime_immutable'])->submit('2024-02-03');
        self::assertInstanceOf(\DateTimeImmutable::class, $form->getData());

        $form = $this->factory->createNamed('f', DateType::class, null, ['input' => 'timestamp', 'model_timezone' => 'UTC', 'view_timezone' => 'UTC'])->submit('1970-01-02');
        self::assertSame(86400, $form->getData());

        $form = $this->factory->createNamed('f', DateType::class)->submit('not-a-date');
        self::assertFalse($form->isSynchronized());
        self::assertSame('not-a-date', $form->getViewData());

        $this->expectException(InvalidOptionsException::class);
        $this->factory->createNamed('f', DateType::class, null, ['widget' => 'choice']);
    }

    public function testDateTimeAndTimeTypes(): void
    {
        $form = $this->factory->createNamed('f', DateTimeType::class, null, ['model_timezone' => 'UTC', 'view_timezone' => 'Europe/Berlin']);
        $form->submit('2024-07-01T12:30');
        self::assertSame('2024-07-01 10:30:00 UTC', $form->getData()->format('Y-m-d H:i:s T'), 'view timezone converted to model timezone');
        self::assertSame('2024-07-01T12:30', $form->createView()->vars['value']);

        $form = $this->factory->createNamed('f', TimeType::class, null, ['input' => 'string'])->submit('08:15');
        self::assertSame('08:15:00', $form->getData());
        self::assertSame('time', $form->createView()->vars['type']);
    }

    public function testCheckboxAndRadio(): void
    {
        $form = $this->factory->createNamedBuilder('f')
            ->add('agree', CheckboxType::class)
            ->add('news', CheckboxType::class, ['value' => 'yes'])
            ->add('pick', RadioType::class)
            ->getForm();
        self::assertFalse($form->get('agree')->getData(), 'default data is false, not null');

        $form->submit(['news' => 'yes', 'pick' => '1']);
        self::assertSame(['agree' => false, 'news' => true, 'pick' => true], $form->getData());
        self::assertTrue($form->get('agree')->isEmpty());

        $view = $form->createView();
        self::assertFalse($view['agree']->vars['checked']);
        self::assertTrue($view['news']->vars['checked']);
        self::assertSame('yes', $view['news']->vars['value']);
        self::assertSame('1', $view['agree']->vars['value']);
        self::assertSame(['form', 'checkbox', 'radio', '_f_pick'], $view['pick']->vars['block_prefixes']);

        $form = $this->factory->createNamed('f', CheckboxType::class, true);
        self::assertTrue($form->createView()->vars['checked']);
    }

    public function testTransformationFailureExtensionAddsOneError(): void
    {
        $factory = new FormFactory(new FormRegistry([new PreloadedExtension([], [new TransformationFailureExtension()])]));
        $form    = $factory->createNamedBuilder('f')->add('age', IntegerType::class)->getForm();

        $form->submit(['age' => 'abc']);

        self::assertFalse($form->isValid());
        self::assertCount(0, $form->getErrors(), 'root is synchronized: the child carries the error');
        $errors = $form->get('age')->getErrors();
        self::assertCount(1, $errors);
        self::assertSame(TransformationFailureListener::NOT_SYNCHRONIZED_ERROR, $errors[0]->getCode());
        self::assertSame('Please enter an integer.', $errors[0]->getMessage());
        self::assertSame(['{{ value }}' => 'abc'], $errors[0]->getMessageParameters());
        self::assertSame('abc', $form->get('age')->getViewData());
        self::assertSame('abc', $form->createView()['age']->vars['value']);
        self::assertCount(1, $form->getErrors(true));
    }
}
