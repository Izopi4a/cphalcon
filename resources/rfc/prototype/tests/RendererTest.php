<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\FormError;
use Phalcon\Form\FormFactory;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\InvalidOptionsException;
use Phalcon\Form\Type\Core\CheckboxType;
use Phalcon\Form\Type\Core\ChoiceType;
use Phalcon\Form\Type\Core\CollectionType;
use Phalcon\Form\Type\Core\DateType;
use Phalcon\Form\Type\Core\EmailType;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\Type\Core\HiddenType;
use Phalcon\Form\Type\Core\IntegerType;
use Phalcon\Form\Type\Core\NumberType;
use Phalcon\Form\Type\Core\PasswordType;
use Phalcon\Form\Type\Core\ResetType;
use Phalcon\Form\Type\Core\SubmitType;
use Phalcon\Form\Type\Core\TextareaType;
use Phalcon\Form\Type\Core\TextType;
use Phalcon\Form\View\FormRenderer;
use Phalcon\Form\View\FormRendererInterface;
use Phalcon\Form\View\FormView;
use Phalcon\Form\View\Theme\ArrayTheme;
use Phalcon\Form\View\Theme\DefaultTheme;
use PHPUnit\Framework\TestCase;

/**
 * FormRenderer + DefaultTheme through the real Phalcon\Html\TagFactory (phalcon.so). Expected
 * strings are exact except for whitespace between tags, which the Select helper indents.
 */
final class RendererTest extends TestCase
{
    private const CHOICE_GROUP_VIEW = 'Phalcon\Form\ChoiceList\ChoiceGroupView';

    private FormFactory $factory;
    private FormRenderer $renderer;

    protected function setUp(): void
    {
        $this->factory  = new FormFactory();
        $this->renderer = new FormRenderer(new DefaultTheme());
    }

    public function testCompoundFormRendersExactHtml(): void
    {
        $groups  = class_exists(self::CHOICE_GROUP_VIEW);
        $choices = $groups
            ? ['Low' => 'low', 'Severe' => ['High & up' => 'high']]
            : ['Low' => 'low', 'High & up' => 'high'];

        $form = $this->factory->createNamedBuilder('ticket', FormType::class, null, ['action' => '/tickets'])
            ->add('title', TextType::class, ['attr' => ['placeholder' => 'Short "summary"']])
            ->add('email', EmailType::class, ['label' => 'Your e-mail', 'required' => false])
            ->add('body', TextareaType::class, ['help' => 'Markdown ok', 'attr' => ['rows' => 4]])
            ->add('urgent', CheckboxType::class, ['required' => false])
            ->add('priority', ChoiceType::class, ['choices' => $choices, 'placeholder' => 'Pick one', 'required' => false])
            ->add('save', SubmitType::class)
            ->getForm();
        $form->submit([
            'title'    => 'Hi <there>',
            'email'    => 'a@b.c',
            'body'     => 'Some <text>',
            'urgent'   => '1',
            'priority' => 'high',
            'save'     => '',
        ]);
        $view = $form->createView();

        $html = $this->renderer->renderStart($view) . $this->renderer->renderWidget($view) . $this->renderer->renderEnd($view);

        $select = $groups
            ? '<select id="ticket_priority" name="ticket[priority]">'
                . '<option value="">Pick one</option>'
                . '<option value="low">Low</option>'
                . '<optgroup label="Severe"><option value="high" selected="selected">High &amp; up</option></optgroup>'
                . '</select>'
            : '<select id="ticket_priority" name="ticket[priority]">'
                . '<option value="">Pick one</option>'
                . '<option value="low">Low</option>'
                . '<option value="high" selected="selected">High &amp; up</option>'
                . '</select>';

        self::assertSame(
            '<form action="/tickets" name="ticket" method="post">'
            . '<div id="ticket">'
            . '<div><label for="ticket_title" class="required">Title</label>'
            . '<input type="text" id="ticket_title" name="ticket[title]" value="Hi &lt;there&gt;" required="required" placeholder="Short &quot;summary&quot;"></div>'
            . '<div><label for="ticket_email">Your e-mail</label>'
            . '<input type="email" id="ticket_email" name="ticket[email]" value="a@b.c"></div>'
            . '<div><label for="ticket_body" class="required">Body</label>'
            . '<textarea id="ticket_body" name="ticket[body]" required="required" rows="4">Some &lt;text&gt;</textarea>'
            . '<p id="ticket_body_help" class="form-help">Markdown ok</p></div>'
            . '<div><label for="ticket_urgent">Urgent</label>'
            . '<input type="checkbox" id="ticket_urgent" name="ticket[urgent]" value="1" checked="checked"></div>'
            . '<div><label for="ticket_priority">Priority</label>' . $select . '</div>'
            . '<div><button type="submit" id="ticket_save" name="ticket[save]">Save</button></div>'
            . '</div>'
            . '</form>',
            $this->normalize($html)
        );
        self::assertTrue($view->isRendered());
    }

    public function testNestedNamesAndIds(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('address', FormType::class, ['label' => false])
            ->getForm();
        $form->get('address')
            ->add('zip', TextType::class)
            ->add('street', TextType::class, ['required' => false, 'disabled' => true]);
        $form->submit(['address' => ['zip' => '1000', 'street' => '']]);
        $view = $form->createView();

        self::assertSame('ticket[address][zip]', $view['address']['zip']->vars['full_name']);
        self::assertSame(
            '<div><div id="ticket_address">'
            . '<div><label for="ticket_address_zip" class="required">Zip</label>'
            . '<input type="text" id="ticket_address_zip" name="ticket[address][zip]" value="1000" required="required"></div>'
            . '<div><label for="ticket_address_street">Street</label>'
            . '<input type="text" id="ticket_address_street" name="ticket[address][street]" disabled="disabled"></div>'
            . '</div></div>',
            $this->normalize($this->renderer->renderRow($view['address'])),
            'label false suppresses the compound label; empty value has no value attribute'
        );
    }

    public function testErrorsAfterSubmit(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')->add('title', TextType::class)->getForm();
        $form->submit(['title' => 'x']);
        $form->get('title')->addError(new FormError('Too <short>'));
        $form->get('title')->addError(new FormError('Second'));
        $form->addError(new FormError('Form-level problem'));
        $view = $form->createView();

        self::assertSame(
            '<ul class="form-errors"><li>Too &lt;short&gt;</li><li>Second</li></ul>',
            $this->renderer->renderErrors($view['title'])
        );
        self::assertSame(
            '<div><label for="ticket_title" class="required">Title</label>'
            . '<input type="text" id="ticket_title" name="ticket[title]" value="x" required="required">'
            . '<ul class="form-errors"><li>Too &lt;short&gt;</li><li>Second</li></ul></div>',
            $this->renderer->renderRow($view['title']),
            'row = label + widget + help + errors'
        );

        // root errors are rendered by the compound widget (there is no row for the root)
        $view = $form->createView();
        self::assertStringStartsWith(
            '<div id="ticket"><ul class="form-errors"><li>Form-level problem</li></ul><div>',
            $this->renderer->renderWidget($view)
        );

        $clean = $this->factory->createNamedBuilder('f')->add('a', TextType::class)->getForm()->createView();
        self::assertSame('', $this->renderer->renderErrors($clean['a']));
        self::assertSame('', $this->renderer->renderHelp($clean['a']));
    }

    public function testLabelHumanizeFalseAndOverride(): void
    {
        $view = $this->factory->createNamedBuilder('f')
            ->add('firstName', TextType::class, ['required' => false])
            ->add('last_name', TextType::class, ['label' => false])
            ->add('age', TextType::class, ['label_attr' => ['class' => 'big', 'data-x' => true]])
            ->getForm()->createView();

        self::assertSame('<label for="f_firstName">First name</label>', $this->renderer->renderLabel($view['firstName']));
        self::assertSame('', $this->renderer->renderLabel($view['last_name']));
        self::assertSame(
            '<label for="f_age" class="big required" data-x="data-x">Age</label>',
            $this->renderer->renderLabel($view['age']),
            'label_attr merged, required class appended, boolean attr as name="name"'
        );
        self::assertSame('<label for="f_firstName">Given name</label>', $this->renderer->renderLabel($view['firstName'], 'Given name'));
        self::assertSame(
            '<label for="f_firstName" class="x">Given name</label>',
            $this->renderer->renderLabel($view['firstName'], null, ['label' => 'Given name', 'label_attr' => ['class' => 'x']])
        );

        // vars passed to the row reach the blocks it renders (label), like Symfony's variable stack
        self::assertSame(
            '<div class="r"><label for="f_firstName">Row label</label><input type="text" id="f_firstName" name="f[firstName]"></div>',
            $this->renderer->renderRow($view['firstName'], ['label' => 'Row label', 'row_attr' => ['class' => 'r']])
        );

        self::assertSame('First name', $this->renderer->humanize('firstName'));
        self::assertSame('First name', $this->renderer->humanize('first_name'));
        self::assertSame('Zip', $this->renderer->humanize('zip'));
    }

    public function testRequiredDisabledAndAttrMerging(): void
    {
        $view = $this->factory->createNamedBuilder('f')
            ->add('a', TextType::class, ['attr' => ['readonly' => true, 'data-off' => false, 'data-null' => null, 'class' => 'in']])
            ->add('b', TextType::class, ['required' => false, 'disabled' => true])
            ->getForm()->createView();

        self::assertSame(
            '<input type="text" id="f_a" name="f[a]" class="in" required="required" readonly="readonly">',
            $this->renderer->renderWidget($view['a']),
            'true => name="name"; false and null attrs are dropped'
        );
        self::assertSame(
            '<input type="text" id="f_b" name="f[b]" disabled="disabled">',
            $this->renderer->renderWidget($view['b'])
        );

        // attr passed at render time is merged key by key with the view's attr
        $view = $this->factory->createNamedBuilder('f')->add('a', TextType::class, ['attr' => ['class' => 'in', 'placeholder' => 'p']])->getForm()->createView();
        self::assertSame(
            '<input type="text" id="f_a" name="f[a]" class="out" required="required" placeholder="p" data-x="1">',
            $this->renderer->renderWidget($view['a'], ['attr' => ['class' => 'out', 'data-x' => 1]])
        );
    }

    public function testSimpleWidgetTypes(): void
    {
        $form = $this->factory->createNamedBuilder('f')
            ->add('pw', PasswordType::class)
            ->add('tok', HiddenType::class)
            ->add('due', DateType::class, ['required' => false])
            ->add('n', IntegerType::class)
            ->add('x', NumberType::class, ['html5' => true])
            ->add('y', NumberType::class)
            ->getForm();
        $form->submit(['pw' => 'secret', 'tok' => 't', 'due' => '2026-10-15', 'n' => '3', 'x' => '1.5', 'y' => '2.5']);
        $view = $form->createView();

        self::assertSame('<input type="password" id="f_pw" name="f[pw]" required="required">', $this->renderer->renderWidget($view['pw']), 'always_empty');
        self::assertSame('<input type="hidden" id="f_tok" name="f[tok]" value="t">', $this->renderer->renderRow($view['tok']), 'hidden_row = widget only');
        self::assertSame('<input type="date" id="f_due" name="f[due]" value="2026-10-15">', $this->renderer->renderWidget($view['due']));
        self::assertSame('<input type="number" id="f_n" name="f[n]" value="3" required="required">', $this->renderer->renderWidget($view['n']));
        self::assertSame('<input type="number" id="f_x" name="f[x]" value="1.5" required="required" step="any">', $this->renderer->renderWidget($view['x']));
        self::assertSame('<input type="text" id="f_y" name="f[y]" value="2.5" required="required">', $this->renderer->renderWidget($view['y']));
    }

    public function testSelectMultipleRequiredAndDisabled(): void
    {
        $form = $this->factory->createNamedBuilder('f')
            ->add('tags', ChoiceType::class, ['choices' => ['A' => 'a', 'B & C' => 'b'], 'multiple' => true, 'required' => false, 'attr' => ['disabled' => true]])
            ->add('one', ChoiceType::class, ['choices' => ['A' => 'a', 'B' => 'b']])
            ->add('two', ChoiceType::class, ['choices' => ['A' => 'a', 'B' => 'b'], 'placeholder' => 'Choose'])
            ->getForm();
        $form->submit(['tags' => ['b'], 'one' => 'a', 'two' => '']);
        $view = $form->createView();

        self::assertSame(
            '<select id="f_tags" name="f[tags][]" disabled="disabled" multiple="multiple">'
            . '<option value="a">A</option><option value="b" selected="selected">B &amp; C</option></select>',
            $this->normalize($this->renderer->renderWidget($view['tags']))
        );
        self::assertSame(
            '<select id="f_one" name="f[one]"><option value="a" selected="selected">A</option><option value="b">B</option></select>',
            $this->normalize($this->renderer->renderWidget($view['one'])),
            'a required select without placeholder always has a selection: no required attribute'
        );
        self::assertSame(
            '<select id="f_two" name="f[two]" required="required">'
            . '<option value="" selected="selected">Choose</option><option value="a">A</option><option value="b">B</option></select>',
            $this->normalize($this->renderer->renderWidget($view['two'])),
            'required + placeholder: the placeholder is selected while the value is empty'
        );
    }

    public function testFormStartWithPatchMethodAndMultipart(): void
    {
        $view       = new FormView();
        $view->vars = array_replace($view->vars, [
            'name'           => 'upload',
            'method'         => 'PATCH',
            'action'         => '/uploads/1?a=1&b=2',
            'multipart'      => true,
            'attr'           => ['class' => 'f', 'novalidate' => true],
            'block_prefixes' => ['form', '_upload'],
        ]);

        self::assertSame(
            // attribute order is the Form helper's: action/name/class first, then its method/enctype defaults, then the rest
            '<form action="/uploads/1?a=1&amp;b=2" name="upload" class="f" method="post" enctype="multipart/form-data" novalidate="novalidate">'
            . '<input type="hidden" name="_method" value="PATCH">',
            $this->renderer->renderStart($view)
        );
        self::assertTrue($view->isMethodRendered());
        self::assertSame('</form>', $this->renderer->renderEnd($view), 'the hidden _method is not repeated by form_rest');

        $get       = new FormView();
        $get->vars = array_replace($get->vars, ['name' => 'search', 'method' => 'GET', 'action' => '', 'multipart' => false, 'block_prefixes' => ['form', '_search']]);
        self::assertSame('<form name="search" method="get">', $this->renderer->renderStart($get), 'no enctype, no empty action, no _method');

        // form_end without form_start still emits the method override (Symfony parity)
        $late       = new FormView();
        $late->vars = array_replace($late->vars, ['name' => 'x', 'method' => 'DELETE', 'block_prefixes' => ['form', '_x']]);
        self::assertSame('<input type="hidden" name="_method" value="DELETE"></form>', $this->renderer->renderEnd($late));
        self::assertSame('</form>', $this->renderer->renderEnd($late, ['render_rest' => false]));
    }

    public function testRowAndWidgetRenderOnlyOnce(): void
    {
        $view = $this->factory->createNamedBuilder('f')->add('a', TextType::class)->getForm()->createView();

        $this->renderer->renderLabel($view['a']);
        $this->renderer->renderLabel($view['a']);
        $this->renderer->renderWidget($view['a']);
        self::assertTrue($view['a']->isRendered());
        self::assertTrue($view->isRendered(), 'all children rendered => parent rendered');

        $this->expectException(BadMethodCallException::class);
        $this->expectExceptionMessage('Field "a" has already been rendered');
        $this->renderer->renderWidget($view['a']);
    }

    public function testRowAfterWidgetThrows(): void
    {
        $view = $this->factory->createNamedBuilder('f')->add('a', TextType::class)->getForm()->createView();
        $this->renderer->renderWidget($view['a']);

        $this->expectException(BadMethodCallException::class);
        $this->renderer->renderRow($view['a']);
    }

    public function testFormRestRendersOnlyUnrenderedChildren(): void
    {
        $view = $this->factory->createNamedBuilder('f')
            ->add('a', TextType::class)
            ->add('b', TextType::class)
            ->add('c', TextType::class)
            ->getForm()->createView();

        $this->renderer->renderRow($view['b']);
        $rest = $this->renderer->renderRest($view);

        self::assertStringContainsString('id="f_a"', $rest);
        self::assertStringNotContainsString('id="f_b"', $rest);
        self::assertStringContainsString('id="f_c"', $rest);
        self::assertSame(
            '<div><label for="f_a" class="required">A</label><input type="text" id="f_a" name="f[a]" required="required"></div>'
            . '<div><label for="f_c" class="required">C</label><input type="text" id="f_c" name="f[c]" required="required"></div>',
            $rest
        );
        self::assertSame('</form>', $this->renderer->renderEnd($view), 'nothing left for form_end');
    }

    public function testArrayThemeOnNestedViewOnlyAffectsThatSubtreeAndFallsBackToParentBlock(): void
    {
        $form = $this->factory->createNamedBuilder('t')
            ->add('a', TextType::class)
            ->add('address', FormType::class)
            ->getForm();
        $form->get('address')->add('zip', TextType::class)->add('city', TextType::class, ['label' => 'Town']);
        $view = $form->createView();

        $theme = new ArrayTheme([
            // generic override for every text widget below "address": wrap the default rendering
            'text_widget'              => static fn (FormRendererInterface $r, FormView $v, array $vars): string => '<span class="wrap">' . $r->renderParentBlock($v, 'widget', ['attr' => ['class' => 'c']]) . '</span>',
            // unique override for one field only; the same helper called again also falls back
            '_t_address_zip_widget'    => static fn (FormRendererInterface $r, FormView $v, array $vars): string => '<b>' . $r->searchAndRenderBlock($v, 'widget') . '</b>',
            '_t_address_city_label'    => static fn (FormRendererInterface $r, FormView $v, array $vars): string => '<em>' . $vars['label'] . '</em>',
        ]);
        $this->renderer->setTheme($view['address'], $theme);

        self::assertSame(
            '<div id="t">'
            . '<div><label for="t_a" class="required">A</label><input type="text" id="t_a" name="t[a]" required="required"></div>'
            . '<div><label class="required">Address</label><div id="t_address">'
            . '<div><label for="t_address_zip" class="required">Zip</label>'
            . '<b><span class="wrap"><input type="text" id="t_address_zip" name="t[address][zip]" class="c" required="required"></span></b></div>'
            . '<div><em>Town</em>'
            . '<span class="wrap"><input type="text" id="t_address_city" name="t[address][city]" class="c" required="required"></span></div>'
            . '</div></div>'
            . '</div>',
            $this->renderer->renderWidget($view),
            'a: untouched; zip: unique block -> text_widget -> form_widget_simple; city: text_widget only, label override sees row vars'
        );
    }

    public function testThemeOverrideOnNestedViewUsesRowVars(): void
    {
        // companion to the test above: the city label override received "Town" from form_row's vars
        $form = $this->factory->createNamedBuilder('t')->add('address', FormType::class)->getForm();
        $form->get('address')->add('city', TextType::class, ['label' => 'Town']);
        $view = $form->createView();
        $this->renderer->setTheme($view['address'], new ArrayTheme([
            '_t_address_city_label' => static fn (FormRendererInterface $r, FormView $v, array $vars): string => '<em>' . $vars['label'] . '</em>',
        ]));

        self::assertSame('<em>Town</em>', $this->renderer->renderLabel($view['address']['city']));
        self::assertSame('<em>Other</em>', $this->renderer->renderLabel($view['address']['city'], 'Other'));
    }

    public function testRenderParentBlockOutsideOfRenderingThrows(): void
    {
        $view = $this->factory->createNamedBuilder('f')->add('a', TextType::class)->getForm()->createView();

        $this->expectException(LogicException::class);
        $this->renderer->renderParentBlock($view['a'], 'widget');
    }

    public function testThemeWithoutDefaultsThrowsForMissingBlock(): void
    {
        $view = $this->factory->createNamedBuilder('f')->add('a', TextType::class)->getForm()->createView();
        $this->renderer->setTheme($view, new ArrayTheme(['form_label' => static fn (): string => 'L']), false);

        self::assertSame('L', $this->renderer->renderLabel($view['a']), 'blocks of the view\'s theme still resolve');

        $this->expectException(LogicException::class);
        $this->expectExceptionMessage('none of the blocks "_f_a_widget", "text_widget", "form_widget" exist');
        $this->renderer->renderWidget($view['a']);
    }

    public function testLaterThemesWin(): void
    {
        $view = $this->factory->createNamedBuilder('f')->add('a', TextType::class)->getForm()->createView();
        $this->renderer->setTheme($view, [
            new ArrayTheme(['text_widget' => static fn (): string => 'first']),
            new ArrayTheme(['text_widget' => static fn (): string => 'second']),
        ]);
        $this->renderer->setTheme($view['a'], new ArrayTheme(['form_label' => static fn (): string => 'own']));

        self::assertSame('second', $this->renderer->renderWidget($view['a']));
        self::assertSame('own', $this->renderer->renderLabel($view['a']));
    }

    public function testCollectionWidgetEmitsPrototype(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('notes', CollectionType::class, ['entry_type' => TextType::class, 'allow_add' => true, 'required' => false])
            ->add('tags', CollectionType::class, ['entry_type' => TextType::class, 'required' => false, 'data' => ['x']])
            ->getForm();
        $form->submit(['notes' => ['one', 'two'], 'tags' => ['x']]);
        $view = $form->createView();

        $html = $this->renderer->renderWidget($view['notes']);
        self::assertSame(
            '<div id="ticket_notes" data-prototype="'
            . '&lt;div&gt;&lt;label for=&quot;ticket_notes___name__&quot;&gt;__name__label__&lt;/label&gt;'
            . '&lt;input type=&quot;text&quot; id=&quot;ticket_notes___name__&quot; name=&quot;ticket[notes][__name__]&quot;&gt;&lt;/div&gt;">'
            . '<div><label for="ticket_notes_0">0</label><input type="text" id="ticket_notes_0" name="ticket[notes][0]" value="one"></div>'
            . '<div><label for="ticket_notes_1">1</label><input type="text" id="ticket_notes_1" name="ticket[notes][1]" value="two"></div>'
            . '</div>',
            $html
        );
        self::assertStringContainsString('__name__', $html);
        self::assertTrue($view['notes']->vars['prototype']->isRendered());

        self::assertSame(
            '<div id="ticket_tags"><div><label for="ticket_tags_0">0</label><input type="text" id="ticket_tags_0" name="ticket[tags][0]" value="x"></div></div>',
            $this->renderer->renderWidget($view['tags']),
            'no allow_add => no prototype'
        );
    }

    public function testButtons(): void
    {
        $view = $this->factory->createNamedBuilder('f')
            ->add('save', SubmitType::class, ['attr' => ['class' => 'btn']])
            ->add('clear', ResetType::class, ['label' => 'Start <over>', 'disabled' => true])
            ->getForm()->createView();

        self::assertSame('<div><button type="submit" id="f_save" name="f[save]" class="btn">Save</button></div>', $this->renderer->renderRow($view['save']));
        self::assertSame('<button type="reset" id="f_clear" name="f[clear]" disabled="disabled">Start &lt;over&gt;</button>', $this->renderer->renderWidget($view['clear']));
        self::assertSame('', $this->renderer->renderLabel($view['clear']));
    }

    public function testExpandedChoiceRendersRadiosAndCheckboxes(): void
    {
        try {
            $form = $this->factory->createNamedBuilder('t')
                ->add('color', ChoiceType::class, ['choices' => ['Red' => 'r', 'Green' => 'g'], 'expanded' => true])
                ->add('flags', ChoiceType::class, ['choices' => ['A' => 'a', 'B' => 'b'], 'expanded' => true, 'multiple' => true, 'required' => false])
                ->getForm();
        } catch (InvalidOptionsException $e) {
            self::markTestSkipped('ChoiceType does not support "expanded" yet: ' . $e->getMessage());
        }
        $form->submit(['color' => 'g', 'flags' => ['a', 'b']]);
        $view = $form->createView();

        self::assertSame(
            '<div id="t_color">'
            . '<input type="radio" id="t_color_0" name="t[color]" value="r" required="required"><label for="t_color_0" class="required">Red</label>'
            . '<input type="radio" id="t_color_1" name="t[color]" value="g" required="required" checked="checked"><label for="t_color_1" class="required">Green</label>'
            . '</div>',
            $this->renderer->renderWidget($view['color'])
        );
        self::assertSame(
            '<div id="t_flags">'
            . '<input type="checkbox" id="t_flags_0" name="t[flags][]" value="a" checked="checked"><label for="t_flags_0">A</label>'
            . '<input type="checkbox" id="t_flags_1" name="t[flags][]" value="b" checked="checked"><label for="t_flags_1">B</label>'
            . '</div>',
            $this->renderer->renderWidget($view['flags'])
        );
    }

    public function testOptgroupsAndPreferredChoices(): void
    {
        if (!class_exists(self::CHOICE_GROUP_VIEW)) {
            self::markTestSkipped('ChoiceGroupView (optgroups) is not available in this prototype yet.');
        }

        $form = $this->factory->createNamedBuilder('t')
            ->add('prio', ChoiceType::class, [
                'choices'           => ['Low' => 'low', 'Severe' => ['High & up' => 'high', 'Blocker' => 'block']],
                'preferred_choices' => ['block'],
                'required'          => false,
                'placeholder'       => 'Pick one',
            ])
            ->getForm();
        $form->submit(['prio' => 'high']);
        $view = $form->createView();

        self::assertSame(
            '<select id="t_prio" name="t[prio]">'
            . '<option value="">Pick one</option>'
            . '<optgroup label="Severe"><option value="block">Blocker</option></optgroup>'
            . '<option disabled="disabled">-------------------</option>'
            . '<option value="low">Low</option>'
            . '<optgroup label="Severe"><option value="high" selected="selected">High &amp; up</option><option value="block">Blocker</option></optgroup>'
            . '</select>',
            $this->normalize($this->renderer->renderWidget($view['prio']))
        );
    }

    public function testDefaultThemeIsReusableAcrossRenders(): void
    {
        // the Select helper keeps state between calls; the theme must not leak selections/groups
        $make = function (string $value): FormInterface {
            $form = $this->factory->createNamedBuilder('f')->add('c', ChoiceType::class, ['choices' => ['A' => 'a', 'B' => 'b'], 'required' => false])->getForm();

            return $form->submit(['c' => $value]);
        };
        $first  = $this->normalize($this->renderer->renderWidget($make('a')->createView()['c']));
        $second = $this->normalize($this->renderer->renderWidget($make('')->createView()['c']));

        self::assertSame('<select id="f_c" name="f[c]"><option value=""></option><option value="a" selected="selected">A</option><option value="b">B</option></select>', $first);
        self::assertSame('<select id="f_c" name="f[c]"><option value=""></option><option value="a">A</option><option value="b">B</option></select>', $second);
    }

    /** Collapses whitespace between tags (the Select helper indents its options). */
    private function normalize(string $html): string
    {
        return preg_replace('/>\s+</', '><', trim($html));
    }
}
