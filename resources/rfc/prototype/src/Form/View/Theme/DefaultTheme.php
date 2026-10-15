<?php
declare(strict_types=1);

namespace Phalcon\Form\View\Theme;

use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\FormError;
use Phalcon\Form\View\FormRendererInterface;
use Phalcon\Form\View\FormView;
use Phalcon\Html\Escaper;
use Phalcon\Html\Escaper\EscaperInterface;
use Phalcon\Html\Helper\Input\Select;
use Phalcon\Html\TagFactory;

/**
 * The built-in theme: Symfony's form_div_layout as code, rendered through Phalcon\Html\TagFactory
 * helpers so the Zephir port is mechanical. One protected method per block; subclass and override
 * a method, or put an ArrayTheme/Volt theme in front of it, to change the markup.
 *
 * Markup conventions (identical to Symfony's div layout, so themes written for it port 1:1):
 *  - boolean attributes are rendered as required="required", disabled="disabled", checked="checked",
 *    selected="selected", multiple="multiple"; attr values `true` become name="name", `false` and
 *    `null` drop the attribute;
 *  - empty values do not get a value="" attribute (AbstractInput::setValue() does this anyway);
 *  - the helpers order type/for/id/name/value/class first, other attributes follow in array order.
 *
 * TagFactory statefulness: newInstance() caches one helper per name. AbstractInput helpers and
 * Label/Button/Element/Form/Close are safe to share: __invoke() rebuilds and __toString() clears
 * their attributes. Input\Input::setType() and Input\Select::selected() are NOT reset, and
 * Select::optGroup() is a toggle, so this theme never uses inputInput (it maps the "type" var to
 * the concrete helper instead, falling back to inputText with a type override) and constructs a
 * fresh Select per <select> with the escaper, bypassing the factory cache; selection is passed per
 * option as selected="selected" rather than through selected(). See RFC 7 / #17053 for reset().
 */
class DefaultTheme implements ThemeInterface
{
    /** block name => method */
    protected const BLOCKS = [
        'form_start'              => 'formStart',
        'form_end'                => 'formEnd',
        'form_rest'               => 'formRest',
        'form_row'                => 'formRow',
        'hidden_row'              => 'hiddenRow',
        'form_label'              => 'formLabel',
        'form_errors'             => 'formErrors',
        'form_help'               => 'formHelp',
        'form_widget'             => 'formWidget',
        'form_widget_compound'    => 'formWidgetCompound',
        'form_widget_simple'      => 'formWidgetSimple',
        'text_widget'             => 'textWidget',
        'textarea_widget'         => 'textareaWidget',
        'email_widget'            => 'emailWidget',
        'password_widget'         => 'passwordWidget',
        'hidden_widget'           => 'hiddenWidget',
        'url_widget'              => 'urlWidget',
        'tel_widget'              => 'telWidget',
        'search_widget'           => 'searchWidget',
        'color_widget'            => 'colorWidget',
        'range_widget'            => 'rangeWidget',
        'number_widget'           => 'numberWidget',
        'integer_widget'          => 'integerWidget',
        'date_widget'             => 'dateWidget',
        'datetime_widget'         => 'datetimeWidget',
        'time_widget'             => 'timeWidget',
        'checkbox_widget'         => 'checkboxWidget',
        'radio_widget'            => 'radioWidget',
        'choice_widget'           => 'choiceWidget',
        'choice_widget_collapsed' => 'choiceWidgetCollapsed',
        'choice_widget_expanded'  => 'choiceWidgetExpanded',
        'collection_widget'       => 'collectionWidget',
        'button_row'              => 'buttonRow',
        'button_label'            => 'buttonLabel',
        'button_widget'           => 'buttonWidget',
        'submit_widget'           => 'submitWidget',
        'reset_widget'            => 'resetWidget',
        'csrf_token'              => 'csrfToken',
    ];

    /** "type" var => TagFactory helper name */
    protected const INPUT_HELPERS = [
        'text'           => 'inputText',
        'email'          => 'inputEmail',
        'password'       => 'inputPassword',
        'hidden'         => 'inputHidden',
        'url'            => 'inputUrl',
        'tel'            => 'inputTel',
        'search'         => 'inputSearch',
        'color'          => 'inputColor',
        'range'          => 'inputRange',
        'number'         => 'inputNumeric',
        'date'           => 'inputDate',
        'datetime'       => 'inputDateTime',
        'datetime-local' => 'inputDateTimeLocal',
        'time'           => 'inputTime',
        'month'          => 'inputMonth',
        'week'           => 'inputWeek',
        'file'           => 'inputFile',
        'image'          => 'inputImage',
        'submit'         => 'inputSubmit',
    ];

    /** Class name as a string: the ChoiceList rewrite may or may not ship it when this runs. */
    protected const CHOICE_GROUP_VIEW = 'Phalcon\Form\ChoiceList\ChoiceGroupView';

    protected const PREFERRED_SEPARATOR = '-------------------';

    protected EscaperInterface $escaper;
    protected TagFactory $tagFactory;

    /**
     * @param TagFactory|null $tagFactory defaults to new TagFactory($escaper)
     * @param EscaperInterface|null $escaper the escaper the factory was built with (TagFactory
     *                                       has no getter); used for the per-call Select helpers
     */
    public function __construct(?TagFactory $tagFactory = null, ?EscaperInterface $escaper = null)
    {
        $this->escaper    = $escaper ?? new Escaper();
        $this->tagFactory = $tagFactory ?? new TagFactory($this->escaper);
    }

    public function hasBlock(string $blockName): bool
    {
        return isset(static::BLOCKS[$blockName]);
    }

    public function renderBlock(string $blockName, FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $method = static::BLOCKS[$blockName] ?? throw new LogicException(sprintf('%s has no block "%s".', static::class, $blockName));

        return $this->{$method}($renderer, $view, $vars);
    }

    // ---- form -------------------------------------------------------------------------------

    protected function formStart(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $view->setMethodRendered();

        $method     = strtoupper((string) ($vars['method'] ?? 'POST'));
        $formMethod = in_array($method, ['GET', 'POST'], true) ? $method : 'POST';

        $attrs = [];
        if ('' !== ($vars['name'] ?? '')) {
            $attrs['name'] = $vars['name'];
        }
        $attrs['method'] = strtolower($formMethod);
        if ('' !== ($vars['action'] ?? '')) {
            $attrs['action'] = $vars['action'];
        }
        // name/method/action win over attr (Symfony renders them first; browsers keep the first)
        $attrs = $this->attributes($attrs + ($vars['attr'] ?? []));
        // null overrides the helper's default enctype="multipart/form-data" (null attrs are skipped)
        $attrs['enctype'] = ($vars['multipart'] ?? false) ? 'multipart/form-data' : null;

        $html = $this->tagFactory->form($attrs);
        if ($formMethod !== $method) {
            $html .= $this->methodOverride($method);
        }

        return $html;
    }

    protected function formEnd(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $html = ($vars['render_rest'] ?? true) ? $renderer->renderRest($view) : '';

        return $html . $this->tagFactory->close('form');
    }

    protected function formRest(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $html = '';
        foreach ($view->children as $child) {
            if (!$child->isRendered()) {
                $html .= $renderer->renderRow($child);
            }
        }

        if (null === $view->parent && !$view->isMethodRendered()) {
            $view->setMethodRendered();
            $method = strtoupper((string) ($vars['method'] ?? 'POST'));
            if (!in_array($method, ['GET', 'POST'], true)) {
                $html .= $this->methodOverride($method);
            }
        }

        return $html;
    }

    // ---- row / label / errors / help --------------------------------------------------------

    protected function formRow(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $html = $renderer->renderLabel($view)
            . $renderer->renderWidget($view)
            . $renderer->renderHelp($view)
            . $renderer->renderErrors($view);

        return $this->tagFactory->element('div', $html, $this->attributes($vars['row_attr'] ?? []), true);
    }

    protected function hiddenRow(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $renderer->renderWidget($view);
    }

    protected function formLabel(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $label = $vars['label'] ?? null;
        if (false === $label) {
            return '';
        }

        $labelAttr = $vars['label_attr'] ?? [];
        if (!($vars['compound'] ?? false) && !isset($labelAttr['for'])) {
            $labelAttr = ['for' => $vars['id'] ?? null] + $labelAttr;
        }
        if ($vars['required'] ?? false) {
            $labelAttr['class'] = trim(($labelAttr['class'] ?? '') . ' required');
        }
        if (null === $label || true === $label || '' === $label) {
            $label = $renderer->humanize((string) ($vars['name'] ?? ''));
        }

        return $this->tagFactory->label((string) $label, $this->attributes($labelAttr));
    }

    protected function formErrors(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $errors = $vars['errors'] ?? [];
        if ([] === $errors) {
            return '';
        }

        $items = '';
        foreach ($errors as $error) {
            $message = $error instanceof FormError ? $error->getMessage() : (string) $error;
            $items .= $this->tagFactory->element('li', $message);
        }

        return $this->tagFactory->element('ul', $items, ['class' => 'form-errors'], true);
    }

    protected function formHelp(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $help = $vars['help'] ?? null;
        if (null === $help || '' === $help) {
            return '';
        }

        $attrs          = $vars['help_attr'] ?? [];
        $attrs['id']    = ($vars['id'] ?? '') . '_help';
        $attrs['class'] = trim('form-help ' . ($attrs['class'] ?? ''));

        return $this->tagFactory->element('p', (string) $help, $this->attributes($attrs));
    }

    // ---- widgets ----------------------------------------------------------------------------

    protected function formWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $renderer->renderBlock($view, ($vars['compound'] ?? false) ? 'form_widget_compound' : 'form_widget_simple', $vars);
    }

    protected function formWidgetCompound(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $html = '';
        if (null === $view->parent && [] !== ($vars['errors'] ?? [])) {
            $html .= $renderer->renderErrors($view);
        }
        foreach ($view->children as $child) {
            if (!$child->isRendered()) {
                $html .= $renderer->renderRow($child);
            }
        }
        $html .= $renderer->renderRest($view);

        return $this->tagFactory->element('div', $html, $this->containerAttributes($vars), true);
    }

    protected function formWidgetSimple(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->input((string) ($vars['type'] ?? 'text'), $vars);
    }

    protected function textWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'text');
    }

    protected function emailWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'email');
    }

    protected function passwordWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        // PasswordType already blanks "value" (always_empty)
        return $this->simpleWidget($renderer, $view, $vars, 'password');
    }

    protected function hiddenWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'hidden');
    }

    protected function urlWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'url');
    }

    protected function telWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'tel');
    }

    protected function searchWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'search');
    }

    protected function colorWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'color');
    }

    protected function rangeWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'range');
    }

    protected function numberWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        // NumberType sets type=number only with html5=true; otherwise a text input (like Symfony)
        return $this->simpleWidget($renderer, $view, $vars, 'text');
    }

    protected function integerWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'number');
    }

    protected function dateWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'date');
    }

    protected function datetimeWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'datetime-local');
    }

    protected function timeWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->simpleWidget($renderer, $view, $vars, 'time');
    }

    protected function textareaWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return (string) $this->tagFactory->inputTextarea(
            (string) $vars['full_name'],
            $this->stringValue($vars['value'] ?? null) ?? '',
            $this->widgetAttributes($vars)
        );
    }

    protected function checkboxWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->checkable('inputCheckbox', $vars);
    }

    protected function radioWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->checkable('inputRadio', $vars);
    }

    protected function choiceWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $renderer->renderBlock($view, ($vars['expanded'] ?? false) ? 'choice_widget_expanded' : 'choice_widget_collapsed', $vars);
    }

    protected function choiceWidgetExpanded(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $html = '';
        foreach ($view->children as $child) {
            $html .= $renderer->renderWidget($child) . $renderer->renderLabel($child);
        }

        return $this->tagFactory->element('div', $html, $this->containerAttributes($vars), true);
    }

    protected function choiceWidgetCollapsed(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $multiple    = (bool) ($vars['multiple'] ?? false);
        $required    = (bool) ($vars['required'] ?? false);
        $placeholder = $vars['placeholder'] ?? null;
        $value       = $vars['value'] ?? ($multiple ? [] : '');

        // a required list without a placeholder always has a selection: "required" means nothing
        if ($required && null === $placeholder && !($vars['placeholder_in_choices'] ?? false) && !$multiple
            && (($vars['attr']['size'] ?? 1) <= 1)) {
            $required = false;
        }

        $attrs = $this->attributes(array_replace(
            [
                'id'       => $vars['id'] ?? null,
                'name'     => $vars['full_name'] ?? null,
                'required' => $required,
                'disabled' => $vars['disabled'] ?? false,
                'multiple' => $multiple,
            ],
            $vars['attr'] ?? []
        ));

        $isSelected = $vars['is_selected'] ?? static fn (string $choice, mixed $value): bool => is_array($value)
            ? in_array($choice, $value, true)
            : $choice === $value;

        // fresh helper per <select>: Select keeps state across __invoke() calls (see class doc)
        $select = new Select($this->escaper);
        $select('    ', PHP_EOL, $attrs);

        if (null !== $placeholder) {
            $placeholderAttr = $this->attributes($vars['placeholder_attr'] ?? []);
            if ($required && ('' === $value || null === $value || [] === $value)) {
                $placeholderAttr['selected'] = 'selected';
            }
            $select->addPlaceholder((string) $placeholder, '', $placeholderAttr);
        }

        $preferred = $vars['preferred_choices'] ?? [];
        $choices   = $vars['choices'] ?? [];
        if ([] !== $preferred) {
            $this->addChoices($select, $preferred, $isSelected, $value);
            if ([] !== $choices) {
                $select->add((string) ($vars['separator'] ?? static::PREFERRED_SEPARATOR), null, ['disabled' => 'disabled']);
            }
        }
        $this->addChoices($select, $choices, $isSelected, $value);

        return (string) $select;
    }

    protected function collectionWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $prototype = $vars['prototype'] ?? null;
        if ($prototype instanceof FormView && !$prototype->isRendered()) {
            $vars['attr'] = array_replace($vars['attr'] ?? [], ['data-prototype' => $renderer->renderRow($prototype)]);
        }

        return $renderer->renderBlock($view, 'form_widget', $vars);
    }

    /** Buttons' prefixes start at "button", not "form": they need their own row (widget only) and label (none). */
    protected function buttonRow(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $this->tagFactory->element('div', $renderer->renderWidget($view), $this->attributes($vars['row_attr'] ?? []), true);
    }

    protected function buttonLabel(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return '';
    }

    protected function buttonWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $label = $vars['label'] ?? null;
        if (false === $label) {
            $label = '';
        } elseif (null === $label || true === $label || '' === $label) {
            $label = $renderer->humanize((string) ($vars['name'] ?? ''));
        }

        $attrs = $this->attributes(array_replace(
            [
                'type'     => $vars['type'] ?? 'button',
                'id'       => $vars['id'] ?? null,
                'name'     => $vars['full_name'] ?? null,
                'disabled' => $vars['disabled'] ?? false,
            ],
            $vars['attr'] ?? []
        ));

        return $this->tagFactory->button((string) $label, $attrs);
    }

    protected function submitWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $vars['type'] = $vars['type'] ?? 'submit';

        return $renderer->renderBlock($view, 'button_widget', $vars);
    }

    protected function resetWidget(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        $vars['type'] = $vars['type'] ?? 'reset';

        return $renderer->renderBlock($view, 'button_widget', $vars);
    }

    /** Placeholder for the CSRF extension: the token is a plain hidden input. */
    protected function csrfToken(FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return $renderer->renderBlock($view, 'hidden_widget', $vars);
    }

    // ---- helpers ----------------------------------------------------------------------------

    /** A "{type}_widget" block: fix the input type unless the type's buildView() chose one, then form_widget_simple. */
    protected function simpleWidget(FormRendererInterface $renderer, FormView $view, array $vars, string $defaultType): string
    {
        $vars['type'] = $vars['type'] ?? $defaultType;

        return $renderer->renderBlock($view, 'form_widget_simple', $vars);
    }

    /** <input> through the helper matching $type (inputText with a type override for unknown types). */
    protected function input(string $type, array $vars): string
    {
        $attrs  = $this->widgetAttributes($vars);
        $helper = static::INPUT_HELPERS[$type] ?? null;
        if (null === $helper) {
            $helper        = 'inputText';
            $attrs['type'] = $type;
        }

        return (string) $this->tagFactory->newInstance($helper)(
            (string) $vars['full_name'],
            $this->stringValue($vars['value'] ?? null),
            $attrs
        );
    }

    /** checkbox/radio: the helper sets checked="checked" only when attrs["checked"] === the value. */
    protected function checkable(string $helper, array $vars): string
    {
        $value = $this->stringValue($vars['value'] ?? '1') ?? '1';
        $attrs = $this->widgetAttributes($vars);
        if ($vars['checked'] ?? false) {
            $attrs['checked'] = $value;
        }

        return (string) $this->tagFactory->newInstance($helper)((string) $vars['full_name'], $value, $attrs);
    }

    /** @param iterable<object> $choices ChoiceView|ChoiceGroupView */
    protected function addChoices(Select $select, iterable $choices, callable $isSelected, mixed $value): void
    {
        foreach ($choices as $choice) {
            if (is_a($choice, static::CHOICE_GROUP_VIEW)) {
                $select->optGroup((string) $choice->label, $this->attributes($choice->attr ?? []));
                $this->addChoices($select, $choice->choices, $isSelected, $value);
                $select->optGroup();
                continue;
            }

            $attrs = $this->attributes($choice->attr ?? []);
            if ($isSelected($choice->value, $value)) {
                $attrs['selected'] = 'selected';
            }
            // add() drops an empty value attribute; addPlaceholder() keeps value=""
            if ('' === $choice->value) {
                $select->addPlaceholder((string) $choice->label, '', $attrs);
            } else {
                $select->add((string) $choice->label, (string) $choice->value, $attrs);
            }
        }
    }

    protected function methodOverride(string $method): string
    {
        return (string) $this->tagFactory->inputHidden('_method', $method, ['id' => null]);
    }

    /** id + required + disabled + attr, for inputs (name/value go through the helper's arguments). */
    protected function widgetAttributes(array $vars): array
    {
        return $this->attributes(array_replace(
            [
                'id'       => $vars['id'] ?? null,
                'required' => $vars['required'] ?? false,
                'disabled' => $vars['disabled'] ?? false,
            ],
            $vars['attr'] ?? []
        ));
    }

    /** id + attr, for the <div> around compound/expanded widgets. */
    protected function containerAttributes(array $vars): array
    {
        return $this->attributes(array_replace(['id' => $vars['id'] ?? null], $vars['attr'] ?? []));
    }

    /**
     * Symfony's "attributes" block: true => name="name", false/null => dropped, scalars as strings.
     * The helpers escape every value through the Escaper (null values are skipped there too).
     */
    protected function attributes(array $attrs): array
    {
        $result = [];
        foreach ($attrs as $name => $value) {
            if (true === $value) {
                $result[$name] = $name;
            } elseif (false === $value || null === $value) {
                continue;
            } elseif (is_scalar($value) || $value instanceof \Stringable) {
                $result[$name] = (string) $value;
            } else {
                throw new LogicException(sprintf('Attribute "%s" must be scalar, %s given.', $name, get_debug_type($value)));
            }
        }

        return $result;
    }

    protected function stringValue(mixed $value): ?string
    {
        return match (true) {
            null === $value                                     => null,
            is_scalar($value) || $value instanceof \Stringable  => (string) $value,
            default                                             => null, // arrays (multiple choice) have no single value
        };
    }
}
