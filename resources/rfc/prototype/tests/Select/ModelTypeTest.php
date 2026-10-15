<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Form\ChoiceList\ChoiceGroupView;
use Phalcon\Form\ChoiceList\ChoiceView;
use Phalcon\Form\ChoiceList\LazyChoiceList;
use Phalcon\Form\ChoiceList\ModelIdReader;
use Phalcon\Form\Options\InvalidOptionsException;
use Phalcon\Form\Options\MissingOptionsException;
use Phalcon\Form\Tests\Fixtures\Orm\City;
use Phalcon\Form\Tests\Fixtures\Orm\Country;
use Phalcon\Form\Tests\Fixtures\Orm\Translation;
use Phalcon\Form\Tests\Fixtures\Orm\Trip;
use Phalcon\Form\Transformer\TransformationFailedException;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\Type\Core\ModelType;
use Phalcon\Form\View\FormView;
use Phalcon\Mvc\Model\Resultset\Simple;

/**
 * ModelType: a <select> over Phalcon\Mvc\Model rows (the old Select element + ResultsetData +
 * `using` [value, label]).
 */
final class ModelTypeTest extends OrmTestCase
{
    /** @return list<string> "label:value" of a flat list of ChoiceView */
    private static function flat(array $views): array
    {
        return array_values(array_map(static fn (ChoiceView $v): string => $v->label . ':' . $v->value, $views));
    }

    // --- loading the list

    public function testFindAllInInsertionOrderByDefault(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class])->createView();

        self::assertSame(['France:1', 'Sweden:2', 'Japan:3', 'Brazil:4'], self::flat($view->vars['choices']), 'labels from __toString, values are the string primary keys');
        self::assertContainsOnlyInstancesOf(Country::class, array_map(static fn (ChoiceView $v) => $v->data, $view->vars['choices']), 'the view keeps the model behind each option');
        self::assertSame('Japan', $view->vars['choices'][2]->data->name);
        self::assertCount(1, $this->selectQueries(), 'one find()');
        self::assertStringNotContainsString('WHERE', $this->selectQueries()[0]);
    }

    public function testParametersWithConditionsBindAndOrder(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, [
            'class'      => Country::class,
            'parameters' => ['conditions' => 'continent = :c:', 'bind' => ['c' => 'Europe'], 'order' => 'name DESC'],
        ])->createView();

        self::assertSame(['Sweden:2', 'France:1'], self::flat($view->vars['choices']));
        self::assertStringContainsString('WHERE "countries"."continent" = :c ORDER BY "countries"."name" DESC', $this->selectQueries()[0]);
    }

    public function testParametersAsConditionsString(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'parameters' => "continent = 'Asia'"])->createView();

        self::assertSame(['Japan:3'], self::flat($view->vars['choices']));
    }

    public function testCallableParametersAreEvaluatedOnFirstLoad(): void
    {
        $calls = 0;
        $form  = $this->factory->createNamed('country', ModelType::class, null, [
            'class'      => Country::class,
            'parameters' => static function () use (&$calls): array {
                ++$calls;

                return ['conditions' => 'continent = :c:', 'bind' => ['c' => 'Europe'], 'order' => 'name'];
            },
        ]);

        self::assertSame(0, $calls, 'not evaluated at build time');
        self::assertSame(['France:1', 'Sweden:2'], self::flat($form->createView()->vars['choices']));
        self::assertSame(1, $calls);
    }

    public function testChoicesAreLoadedLazily(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'required' => false]);

        $list = $form->getConfig()->getAttribute('choice_list');
        self::assertInstanceOf(LazyChoiceList::class, $list);
        self::assertFalse($list->isLoaded());
        self::assertSame([], $this->selectQueries(), 'building the form runs no query');

        self::assertSame('', $form->getViewData(), 'null data: nothing to look up');
        self::assertNull($form->submit('')->getData());
        self::assertSame([], $this->selectQueries(), 'neither does an empty value in or out');

        $form->createView();
        self::assertTrue($list->isLoaded());
        self::assertCount(1, $this->selectQueries(), 'the option list needs the rows');
    }

    public function testEmptyResultsetLeavesOnlyThePlaceholder(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, [
            'class'       => Country::class,
            'parameters'  => ['conditions' => 'continent = :c:', 'bind' => ['c' => 'Antarctica']],
            'placeholder' => 'No country',
        ])->createView();

        self::assertSame([], $view->vars['choices']);
        self::assertSame([], $view->vars['preferred_choices']);
        self::assertSame('No country', $view->vars['placeholder']);
        self::assertSame('', $view->vars['value']);
    }

    // --- choice_label / choice_value

    public function testChoiceLabelFallsBackToToString(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class])->createView();

        self::assertSame(['France', 'Sweden', 'Japan', 'Brazil'], array_map(static fn (ChoiceView $v) => $v->label, $view->vars['choices']));
    }

    public function testChoiceLabelIsRequiredWithoutToString(): void
    {
        $this->expectException(InvalidOptionsException::class);
        $this->expectExceptionMessage('"choice_label" option is required');

        $this->factory->createNamed('city', ModelType::class, null, ['class' => City::class]);
    }

    public function testChoiceLabelAsAttributeName(): void
    {
        $view = $this->factory->createNamed('city', ModelType::class, null, ['class' => City::class, 'choice_label' => 'name'])->createView();

        self::assertSame(['Paris:1', 'Tokyo:2', 'Stockholm:3'], self::flat($view->vars['choices']), 'public typed property read by the PropertyAccessor (like using[1])');
    }

    public function testChoiceLabelAsGetter(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'choice_label' => 'label'])->createView();

        self::assertSame(['France (Europe)', 'Sweden (Europe)', 'Japan (Asia)', 'Brazil (South America)'], array_map(static fn (ChoiceView $v) => $v->label, $view->vars['choices']), 'getLabel()');
    }

    public function testChoiceLabelCallableReceivesTheModel(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, [
            'class'        => Country::class,
            'choice_label' => static fn (Country $c, int $key, string $value): string => sprintf('%s#%s@%d', $c->name, $value, $key),
        ])->createView();

        self::assertSame(['France#1@0', 'Sweden#2@1', 'Japan#3@2', 'Brazil#4@3'], array_map(static fn (ChoiceView $v) => $v->label, $view->vars['choices']), 'the key is the 0-based resultset position');
    }

    public function testChoiceValueDefaultsToThePrimaryKeyFromMetadata(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class]);

        $reader = $form->getConfig()->getOption('choice_value');
        self::assertInstanceOf(ModelIdReader::class, $reader);
        self::assertSame(['id'], $reader->getAttributes(), 'from modelsMetadata->getPrimaryKeyAttributes()');
        self::assertSame('3', $reader(Country::findFirst(3)));
        self::assertNull($reader(new Country()), 'an unsaved model has no value');
        self::assertNull($reader('3'), 'not a model');
    }

    public function testChoiceValueAsCustomAttribute(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'choice_value' => 'name']);
        $view = $form->createView();

        self::assertSame(['France:France', 'Sweden:Sweden', 'Japan:Japan', 'Brazil:Brazil'], self::flat($view->vars['choices']));

        $form->submit('Japan');
        self::assertInstanceOf(Country::class, $form->getData());
        self::assertSame(3, $form->getData()->id);
    }

    public function testChoiceValueCallable(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'choice_value' => static fn (?Country $c): ?string => $c ? 'c' . $c->id : null]);

        self::assertSame(['1' => 'c1', '2' => 'c2', '3' => 'c3', '4' => 'c4'], array_combine(array_map(static fn (ChoiceView $v) => (string) $v->data->id, $form->createView()->vars['choices']), array_map(static fn (ChoiceView $v) => $v->value, $form->createView()->vars['choices'])));
        self::assertSame(2, $form->submit('c2')->getData()->id);
    }

    // --- single: in and out

    public function testSubmitIdGivesTheModelInstance(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class]);
        $form->submit('2');

        $country = $form->getData();
        self::assertInstanceOf(Country::class, $country);
        self::assertSame(2, $country->id);
        self::assertSame('Sweden', $country->name);
        self::assertSame('Europe', $country->continent);
        self::assertSame('2', $form->getViewData());
        self::assertTrue($form->isSynchronized());
        self::assertTrue($form->isValid());
    }

    public function testSubmittingAKeyLoadsOnlyThatRow(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class]);
        $form->submit('2');

        self::assertSame(2, $form->getData()->id);
        $queries = $this->selectQueries();
        self::assertCount(1, $queries, 'exactly one query for the submission');
        self::assertStringContainsString('WHERE ("countries"."id" = :mt_0_0)', $queries[0], 'by primary key, not the whole table');
        self::assertFalse($form->getConfig()->getAttribute('choice_list')->isLoaded(), 'the list itself is still unloaded');

        $form->createView();
        self::assertCount(2, $this->selectQueries(), 'rendering the options loads the list (second query)');
        self::assertStringNotContainsString('WHERE', $this->selectQueries()[1]);
    }

    public function testTheSingleRowQueryKeepsTheParameterConditions(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, [
            'class'      => Country::class,
            'parameters' => ['conditions' => 'continent = :c:', 'bind' => ['c' => 'Europe'], 'order' => 'name'],
        ]);
        $form->submit('3');

        self::assertFalse($form->isSynchronized(), 'Japan exists but is outside the configured subset');
        self::assertNull($form->getData());
        $queries = $this->selectQueries();
        self::assertCount(1, $queries);
        self::assertStringContainsString('WHERE ("countries"."continent" = :c) AND (("countries"."id" = :mt_0_0))', $queries[0]);
    }

    public function testNoSingleRowQueryWithACustomValueCallableOrALimit(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'choice_value' => static fn (?Country $c): ?string => $c?->name]);
        $form->submit('Japan');
        self::assertSame(3, $form->getData()->id);
        self::assertCount(1, $this->selectQueries());
        self::assertStringNotContainsString('WHERE', $this->selectQueries()[0], 'an opaque callable: the whole list is loaded and matched');

        $this->resetQueryLog();
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'parameters' => ['order' => 'name', 'limit' => 2]]);
        $form->submit('4');
        self::assertSame(4, $form->getData()->id, 'Brazil, France are the first two by name');
        self::assertStringContainsString('LIMIT', $this->selectQueries()[0], 'limit: cannot restrict by key without changing the subset, the whole (limited) list is loaded');
        self::assertFalse($this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'parameters' => ['order' => 'name', 'limit' => 2]])->submit('3')->isSynchronized(), 'Japan is the third by name');
    }

    public function testPreselectedInstanceIsMatchedByPrimaryKeyNotIdentity(): void
    {
        $sweden = Country::findFirst(2);
        $this->resetQueryLog();

        $form = $this->factory->createNamed('country', ModelType::class, $sweden, ['class' => Country::class]);

        self::assertSame('2', $form->getViewData());
        self::assertSame([], $this->selectQueries(), 'the value is computed from the instance: no list query');

        $view = $form->createView();
        self::assertSame('2', $view->vars['value']);
        self::assertTrue($view->vars['is_selected']('2', $view->vars['value']));
        self::assertNotSame($sweden, $view->vars['choices'][1]->data, 'the option holds a different instance of the same row');
        self::assertSame($sweden, $form->getData(), 'the original instance stays the form data');
    }

    public function testPreselectedFromAParentFormBoundToACityRelation(): void
    {
        $paris = City::findFirst(1);
        $form  = $this->factory->createNamedBuilder('city', FormType::class, $paris, ['data_class' => City::class])
            ->add('country', ModelType::class, ['class' => Country::class])
            ->getForm();

        self::assertSame('1', $form->get('country')->getViewData(), 'read through Model::__get("country") (no getCountry() method exists)');
        self::assertInstanceOf(Country::class, $form->get('country')->getData());
        self::assertSame('France', $form->get('country')->getData()->name);

        $form->submit(['country' => '3']);

        self::assertTrue($form->isValid());
        self::assertInstanceOf(Country::class, $paris->country, 'written through Model::__set("country"): the dirty related record');
        self::assertSame(3, $paris->country->id);
        self::assertSame(1, $paris->country_id, 'Phalcon updates the foreign key when the city is saved, not before');
    }

    public function testNewCityWithoutCountryShowsThePlaceholder(): void
    {
        $city = new City();
        $form = $this->factory->createNamedBuilder('city', FormType::class, $city, ['data_class' => City::class])
            ->add('country', ModelType::class, ['class' => Country::class, 'required' => false, 'placeholder' => 'Pick one'])
            ->getForm();

        self::assertSame('', $form->get('country')->getViewData(), 'the belongsTo on a new model resolves to null');
        $view = $form->createView();
        self::assertSame('Pick one', $view['country']->vars['placeholder']);
        self::assertSame('', $view['country']->vars['value']);

        $form->submit(['country' => '']);
        self::assertNull($form->get('country')->getData());
        self::assertNull($city->country);
    }

    public function testPlaceholder(): void
    {
        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class]);
        self::assertNull($form->createView()->vars['placeholder'], 'required (default): no placeholder');

        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'required' => false]);
        self::assertSame('', $form->createView()->vars['placeholder'], 'not required: an empty placeholder option');

        $form = $this->factory->createNamed('country', ModelType::class, Country::findFirst(1), ['class' => Country::class, 'placeholder' => 'Choose a country']);
        $view = $form->createView();
        self::assertSame('Choose a country', $view->vars['placeholder']);
        self::assertFalse($view->vars['placeholder_in_choices']);
        self::assertSame(['France:1', 'Sweden:2', 'Japan:3', 'Brazil:4'], self::flat($view->vars['choices']));

        self::assertNull($form->submit('')->getData(), 'submitting the placeholder clears the relation');
    }

    public function testInvalidIdIsNotSynchronized(): void
    {
        $france = Country::findFirst(1);
        $this->resetQueryLog();
        $form = $this->factory->createNamed('country', ModelType::class, $france, ['class' => Country::class]);
        $form->submit('99');

        self::assertFalse($form->isSynchronized());
        self::assertInstanceOf(TransformationFailedException::class, $form->getTransformationFailure());
        self::assertStringContainsString('"99"', $form->getTransformationFailure()->getMessage());
        self::assertNull($form->getData(), 'the preselected France is gone');
        self::assertSame('99', $form->getViewData(), 'the view keeps the raw value');
        self::assertStringContainsString('"countries"."id" = :mt_0_0', $this->selectQueries()[0], 'one lookup by key found nothing');

        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class]);
        $form->submit('abc');
        self::assertFalse($form->isSynchronized(), 'not even key-shaped');
    }

    // --- groups and preferred

    public function testGroupByContinentMakesOptgroups(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'group_by' => 'continent'])->createView();

        self::assertSame(['Europe', 'Asia', 'South America'], array_keys($view->vars['choices']), 'groups in first-seen order');
        self::assertContainsOnlyInstancesOf(ChoiceGroupView::class, $view->vars['choices']);
        self::assertSame(['France:1', 'Sweden:2'], self::flat($view->vars['choices']['Europe']->choices));
        self::assertSame(['Japan:3'], self::flat($view->vars['choices']['Asia']->choices));

        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'group_by' => static fn (Country $c): ?string => 'Europe' === $c->continent ? 'EU' : null])->createView();
        self::assertSame(['EU', 2, 3], array_keys($view->vars['choices']), 'callable: null leaves a choice ungrouped');
    }

    public function testPreferredChoices(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'preferred_choices' => static fn (Country $c): bool => 'Asia' === $c->continent])->createView();

        self::assertSame(['Japan:3'], self::flat($view->vars['preferred_choices']));
        self::assertSame(['France:1', 'Sweden:2', 'Japan:3', 'Brazil:4'], self::flat($view->vars['choices']), 'duplicated in the main list by default');

        // prototype: an array of models as preferred_choices compares by identity (===), so
        // separately loaded instances never match. RFC: compare by choice value instead?
        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'preferred_choices' => [Country::findFirst(3)]])->createView();
        self::assertSame([], $view->vars['preferred_choices'], 'documented limitation: identity comparison');
    }

    // --- choices given directly

    public function testResultsetPassedAsChoices(): void
    {
        $resultset = Country::find(['order' => 'name']);
        self::assertInstanceOf(Simple::class, $resultset);
        $this->resetQueryLog();

        $form = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'choices' => $resultset]);
        $view = $form->createView();

        self::assertSame(['Brazil:4', 'France:1', 'Japan:3', 'Sweden:2'], self::flat($view->vars['choices']), 'the resultset order; keys still primary keys');
        self::assertNull($form->getConfig()->getOption('choice_loader'), 'no loader of our own');
        self::assertSame([], $this->selectQueries(), 'no query: the rows were already fetched');

        $form->submit('3');
        self::assertSame('Japan', $form->getData()->name);
        self::assertSame([], $this->selectQueries());
    }

    public function testArrayOfModelsPassedAsChoices(): void
    {
        $models = [Country::findFirst(2), Country::findFirst(4)];
        $this->resetQueryLog();

        $form = $this->factory->createNamed('country', ModelType::class, $models[1], ['class' => Country::class, 'choices' => $models, 'choice_label' => 'label']);

        self::assertSame('4', $form->getViewData());
        self::assertSame(['Sweden (Europe):2', 'Brazil (South America):4'], self::flat($form->createView()->vars['choices']));
        $form->submit('2');
        self::assertSame($models[0], $form->getData(), 'the very instance from the array');
        self::assertFalse($this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class, 'choices' => $models])->submit('1')->isSynchronized(), 'France is not among the given models');
        self::assertSame([], $this->selectQueries());
    }

    // --- multiple

    public function testMultipleGivesAnArrayOfInstances(): void
    {
        $form = $this->factory->createNamed('countries', ModelType::class, null, ['class' => Country::class, 'multiple' => true]);

        self::assertSame([], $form->getViewData());
        $form->submit(['3', '1']);

        $data = $form->getData();
        self::assertCount(2, $data);
        self::assertContainsOnlyInstancesOf(Country::class, $data);
        self::assertSame(['Japan', 'France'], array_map(static fn (Country $c) => $c->name, $data), 'submitted order');
        self::assertSame(['3', '1'], $form->getViewData());
        self::assertTrue($form->isValid());

        // prototype: ChoiceType's PRE_SUBMIT listener looks every value up on its own (one query
        // each), then the transformer fetches them all at once with an OR: 3 queries for 2
        // values, none of them the whole table. Symfony's loader does a single IN query.
        $queries = $this->selectQueries();
        self::assertCount(3, $queries);
        foreach ($queries as $sql) {
            self::assertStringContainsString('"countries"."id" = :mt_0_0', $sql, 'every lookup before the view was by key, never the whole table');
        }
        self::assertStringContainsString('OR ("countries"."id" = :mt_1_0)', $queries[2]);

        self::assertStringEndsWith('[]', $form->createView()->vars['full_name']);
        self::assertCount(4, $this->selectQueries(), 'the view loads the list');
    }

    public function testMultiplePreselectedFromInstancesAndRoundTrip(): void
    {
        $form = $this->factory->createNamed('countries', ModelType::class, [Country::findFirst(2), Country::findFirst(3)], ['class' => Country::class, 'multiple' => true]);

        self::assertSame(['2', '3'], $form->getViewData());
        $view = $form->createView();
        self::assertTrue($view->vars['is_selected']('3', $view->vars['value']));
        self::assertFalse($view->vars['is_selected']('1', $view->vars['value']));

        $form->submit([]);
        self::assertSame([], $form->getData(), 'nothing selected');
    }

    public function testMultipleUnknownIdIsAnError(): void
    {
        $form = $this->factory->createNamed('countries', ModelType::class, null, ['class' => Country::class, 'multiple' => true]);
        $form->submit(['1', '99']);

        self::assertTrue($form->isSynchronized(), 'the known one is kept');
        self::assertSame([1], array_map(static fn (Country $c) => $c->id, $form->getData()));
        self::assertFalse($form->isValid());
        self::assertCount(1, $form->getErrors());
        self::assertSame('The selected choice is invalid.', (string) $form->getErrors()[0], 'ChoiceType invalid_message');
        self::assertSame(['{{ value }}' => '99'], $form->getErrors()[0]->getMessageParameters());
    }

    public function testMultipleByReferenceFalseUsesAdderAndRemover(): void
    {
        $trip = new Trip([Country::findFirst(1), Country::findFirst(2)]);
        $form = $this->factory->createNamedBuilder('trip', FormType::class, $trip)
            ->add('countries', ModelType::class, ['class' => Country::class, 'multiple' => true, 'by_reference' => false])
            ->getForm();

        self::assertSame(['1', '2'], $form->get('countries')->getViewData(), 'preselected from getCountries()');

        $form->submit(['countries' => ['2', '3']]);

        self::assertSame([2, 3], array_map(static fn (Country $c) => $c->id, $trip->getCountries()));
        // prototype: the PropertyAccessor diffs by identity. The submitted Sweden is a freshly
        // loaded instance, so Sweden is removed and added again instead of being kept. RFC: a
        // value-based diff (compare by choice_value) would give ['removeCountry(1)', 'addCountry(3)'].
        self::assertSame(['removeCountry(1)', 'removeCountry(2)', 'addCountry(2)', 'addCountry(3)'], $trip->calls);
    }

    // --- composite key, option validation

    public function testCompositePrimaryKeyValues(): void
    {
        $form = $this->factory->createNamed('t', ModelType::class, null, ['class' => Translation::class, 'parameters' => ['order' => 'locale, key_name']]);

        self::assertSame(['locale', 'key_name'], $form->getConfig()->getOption('choice_value')->getAttributes());
        $view = $form->createView();
        self::assertSame(['Bye:en|farewell', 'Hello:en|greeting', 'Bonjour:fr|greeting'], self::flat($view->vars['choices']), 'parts joined with "|" in metadata order');

        $this->resetQueryLog();
        $form = $this->factory->createNamed('t', ModelType::class, null, ['class' => Translation::class]);
        $form->submit('fr|greeting');
        self::assertInstanceOf(Translation::class, $form->getData());
        self::assertSame('Bonjour', $form->getData()->text);
        self::assertStringContainsString('WHERE ("translations"."locale" = :mt_0_0 AND "translations"."key_name" = :mt_0_1)', $this->selectQueries()[0]);

        self::assertFalse($this->factory->createNamed('t', ModelType::class, null, ['class' => Translation::class])->submit('fr')->isSynchronized(), 'not key-shaped: no query, not synchronized');
    }

    public function testClassIsRequiredAndMustBeAModel(): void
    {
        try {
            $this->factory->createNamed('c', ModelType::class);
            self::fail('expected MissingOptionsException');
        } catch (MissingOptionsException $e) {
            self::assertStringContainsString('class', $e->getMessage());
        }

        $this->expectException(InvalidOptionsException::class);
        $this->expectExceptionMessage('must be a Phalcon\Mvc\ModelInterface');
        $this->factory->createNamed('c', ModelType::class, null, ['class' => Trip::class]);
    }

    public function testViewVarsAndBlockPrefix(): void
    {
        $view = $this->factory->createNamed('country', ModelType::class, null, ['class' => Country::class])->createView();

        self::assertInstanceOf(FormView::class, $view);
        self::assertSame(['form', 'choice', 'model', '_country'], $view->vars['block_prefixes'], 'a model select renders with the choice theme blocks');
        self::assertFalse($view->vars['multiple']);
        self::assertFalse($view->vars['expanded']);
    }
}
