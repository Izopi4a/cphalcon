<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\EventListener\MergeCollectionListener;
use Phalcon\Form\FormFactory;
use Phalcon\Form\Tests\Fixtures\Country;
use Phalcon\Form\Tests\Fixtures\Post;
use Phalcon\Form\Tests\Fixtures\Profile;
use Phalcon\Form\Type\Core\ChoiceType;
use Phalcon\Form\Type\Core\FormType;
use PHPUnit\Framework\TestCase;

/**
 * <select multiple name="...[]">: arrays in and out, by_reference and the MergeCollectionListener.
 */
final class SelectMultipleTest extends TestCase
{
    private const COLORS = ['Red' => 'r', 'Green' => 'g', 'Blue' => 'b'];

    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    public function testArrayInAndOut(): void
    {
        $form = $this->factory->createNamed('colors', ChoiceType::class, ['g', 'b'], ['choices' => self::COLORS, 'multiple' => true]);

        self::assertSame(['g', 'b'], $form->getViewData());
        $view = $form->createView();
        self::assertSame(['g', 'b'], $view->vars['value']);
        self::assertTrue($view->vars['multiple']);
        self::assertTrue($view->vars['is_selected']('g', $view->vars['value']));
        self::assertFalse($view->vars['is_selected']('r', $view->vars['value']));

        $form->submit(['r']);
        self::assertSame(['r'], $form->getData());
        self::assertTrue($form->isValid());
    }

    public function testEmptySubmitIsAnEmptyArray(): void
    {
        self::assertSame([], $this->factory->createNamed('c', ChoiceType::class, ['g'], ['choices' => self::COLORS, 'multiple' => true])->submit(null)->getData(), 'nothing posted (browsers send nothing for an empty multi-select)');
        self::assertSame([], $this->factory->createNamed('c', ChoiceType::class, ['g'], ['choices' => self::COLORS, 'multiple' => true])->submit([])->getData());

        $form = $this->factory->createNamed('c', ChoiceType::class, ['g'], ['choices' => self::COLORS, 'multiple' => true])->submit(null);
        self::assertTrue($form->isEmpty());
        self::assertSame([], $form->createView()->vars['value']);
    }

    public function testNullDataIsAnEmptyArrayInTheView(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true]);

        self::assertSame([], $form->getViewData());
        self::assertNull($form->getData(), 'but the model stays null until submitted');
    }

    public function testFullNameEndsWithBrackets(): void
    {
        $view = $this->factory->createNamedBuilder('f')
            ->add('colors', ChoiceType::class, ['choices' => self::COLORS, 'multiple' => true])
            ->getForm()->createView();

        self::assertSame('f[colors][]', $view['colors']->vars['full_name']);
        self::assertSame('f_colors', $view['colors']->vars['id'], 'the id has no brackets');
        self::assertSame('f[]', $this->factory->createNamed('f', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true])->createView()->vars['full_name']);
    }

    public function testIntValuesKeepTheirType(): void
    {
        $form = $this->factory->createNamed('n', ChoiceType::class, [2], ['choices' => ['One' => 1, 'Two' => 2, 'Three' => 3], 'multiple' => true]);
        self::assertSame(['2'], $form->getViewData());

        $form->submit(['1', '3']);
        self::assertSame([1, 3], $form->getData());
    }

    public function testObjectChoices(): void
    {
        $fr   = new Country(1, 'France');
        $se   = new Country(2, 'Sweden');
        $form = $this->factory->createNamed('c', ChoiceType::class, [$se], ['choices' => [$fr, $se], 'choice_label' => 'name', 'choice_value' => 'id', 'multiple' => true]);

        self::assertSame(['2'], $form->getViewData());
        $form->submit(['1', '2']);
        self::assertSame([$se, $fr], $form->getData(), 'the same instances come back; by_reference merges: kept $se first, new $fr appended');

        $form = $this->factory->createNamed('c', ChoiceType::class, [$se], ['choices' => [$fr, $se], 'choice_label' => 'name', 'choice_value' => 'id', 'multiple' => true, 'by_reference' => false]);
        $form->submit(['1', '2']);
        self::assertSame([$fr, $se], $form->getData(), 'without merge the submitted order is kept');
    }

    public function testDuplicateSubmittedValuesAreKept(): void
    {
        // Symfony does not deduplicate; documented as current behaviour
        $form = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true])->submit(['r', 'r']);

        self::assertSame(['r', 'r'], $form->getData());
    }

    public function testWrittenBackToAnArrayProperty(): void
    {
        $profile         = new Profile();
        $profile->colors = ['g'];

        $form = $this->factory->createNamedBuilder('profile', FormType::class, $profile)
            ->add('colors', ChoiceType::class, ['choices' => self::COLORS, 'multiple' => true])
            ->getForm();

        self::assertSame(['g'], $form->get('colors')->getViewData(), 'preselected from the entity');
        $form->submit(['colors' => ['r', 'b']]);
        self::assertSame(['r', 'b'], $profile->colors);
    }

    public function testByReferenceFalseUsesAdderAndRemover(): void
    {
        $post = new Post(['php', 'forms']);
        $form = $this->factory->createNamedBuilder('post', FormType::class, $post)
            ->add('tags', ChoiceType::class, ['choices' => ['php', 'forms', 'phalcon'], 'multiple' => true, 'by_reference' => false])
            ->getForm();

        $form->submit(['tags' => ['forms', 'phalcon']]);

        self::assertSame(['removeTag(php)', 'addTag(phalcon)'], $post->calls, 'PropertyAccessor diffs against getTags() and calls the adder/remover');
        self::assertSame(['forms', 'phalcon'], array_values($post->getTags()));
    }

    public function testByReferenceTrueMergesIntoTheOriginalCollection(): void
    {
        // The original array has custom keys: the MergeCollectionListener keeps them and the
        // identity of kept items instead of replacing the whole array.
        $post = new Post([10 => 'php', 20 => 'forms']);
        $form = $this->factory->createNamedBuilder('post', FormType::class, $post)
            ->add('tags', ChoiceType::class, ['choices' => ['php', 'forms', 'phalcon'], 'multiple' => true])
            ->getForm();

        $form->submit(['tags' => ['forms', 'phalcon']]);

        self::assertSame([20 => 'forms', 1 => 'phalcon'], $form->get('tags')->getData(), 'merged: key 20 kept, "php" removed, "phalcon" added');
        self::assertSame(['removeTag(php)', 'addTag(phalcon)'], $post->calls);
        self::assertSame([20 => 'forms', 21 => 'phalcon'], $post->getTags(), 'the adder appends');
    }

    public function testMergeCollectionListenerKeepsIdentityAndKeys(): void
    {
        $a = new \stdClass();
        $b = new \stdClass();
        $c = new \stdClass();
        $form = $this->factory->createNamed('c', ChoiceType::class, ['x' => $a, 'y' => $b], ['choices' => [$a, $b, $c], 'multiple' => true]);
        $form->submit(['1', '2']);

        $data = $form->getData();
        self::assertSame(['y', 1], array_keys($data), 'kept item keeps its key "y" (identity ===), "x" is removed, the new item gets its key from the submitted list');
        self::assertSame($b, $data['y']);
        self::assertSame($c, $data[1]);

        // The listener alone: nothing to merge into -> the submitted data as is
        $listener = new MergeCollectionListener(true, true);
        $event    = new FormEvent($this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true]), ['r']);
        $listener->onSubmit($event);
        self::assertSame(['r'], $event->getData());

        // Not allowed to add or delete -> the original wins
        $listener = new MergeCollectionListener(false, false);
        $form     = $this->factory->createNamed('c', ChoiceType::class, ['r'], ['choices' => self::COLORS, 'multiple' => true]);
        $event    = new FormEvent($form, ['g']);
        $listener->onSubmit($event);
        self::assertSame(['r'], $event->getData());
    }

    public function testByReferenceFalseReplacesTheArray(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, [10 => 'r', 20 => 'g'], ['choices' => self::COLORS, 'multiple' => true, 'by_reference' => false]);
        $form->submit(['g', 'b']);

        self::assertSame(['g', 'b'], $form->getData(), 'no merge: a fresh 0-indexed array');
    }

    public function testDisabledMultipleIgnoresSubmission(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, ['r'], ['choices' => self::COLORS, 'multiple' => true, 'disabled' => true])->submit(['g']);

        self::assertSame(['r'], $form->getData());
        self::assertTrue($form->isValid());
    }

    public function testEmptyDataForMultiple(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::COLORS, 'multiple' => true, 'empty_data' => ['g']])->submit(null);

        self::assertSame(['g'], $form->getData(), 'empty_data (view values) when nothing is posted');
    }
}
