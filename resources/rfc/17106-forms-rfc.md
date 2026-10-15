# [NFR] Forms overhaul for v7: compound forms, collections and a type system

Status: DRAFT for discussion on #17106. Target: `7.0.x`.
Related: #17106 (Embedded Forms, 2013), #17338 (`""` -> `null`), #17053 (Tag deprecation), #17054 (HTTP rework), #16898 / #17131 (Container instead of `Di::getDefault()`), #16896 (new Container).

## Problem

`Phalcon\Forms` is a flat list of elements wrapped around `Phalcon\Tag`-era rendering. The
embedded-forms request has been open since 2013 with the same answer every time: the current
design cannot express it. Concretely, on `7.0.x` today:

- **No tree.** `Form` holds `elements` keyed by a flat name. There is no parent/child relation,
  no `parent[child]` naming, no way to distribute a submitted array to sub-forms, and no
  collection of repeated sub-forms. The only awareness of `[` in a name is a guard in
  `Select::render()` that skips setting `id`; `Input\AbstractInput` sets `id = name` and emits
  invalid ids for `a[b]`.
- **Data binding is name-equals-property.** `Form::bind()` writes `set<Camelize(key)>()` or a
  public property; `Form::getValue()` walks an 8-step lookup that ends in `$_POST[name]`, i.e.
  the form reads superglobals directly. There is no notion of a model value vs. a view value, so
  `""` vs `null` (#17338), dates, booleans and choices are all left to the application.
- **No events.** `Form` fires nothing through `Phalcon\Events\Manager`; the only hooks are
  `beforeValidation` / `afterValidation` / `getCustomValue` found by `method_exists`.
  `tests/unit/Forms/Form/SetEventsManagerTest.php` has been skipped with "Need implementation".
- **Validation is bolted on per call.** `isValid()` appends every element's validators to the
  validation object on every call (duplicating them when a `Validation` was injected), never
  clears element messages, and `get(msg->getField())` throws for combined-field messages.
- **Rendering couples the domain to the widget.** Elements render themselves by calling a
  `TagFactory` helper named in a `method` property, with values typed as `string`. There is no
  view object, no theming, no way to render a nested structure. `TagFactory` helpers are cached
  stateful singletons (`Input\Select::selected` is never reset), which bites as soon as the same
  helper renders twice in one request, exactly what a collection does.
- **Small defects accumulate** because nothing in the design pushes back: `remove()` resets the
  index only when the element was *not* found; the forbidden-name check for `tagFactory` can
  never match because names are lowercased first.

Symfony Forms solved every one of these with a handful of ideas that are not Symfony-specific:
a form is a tree; a type is reusable configuration with inheritance; data has three
representations joined by transformers; mapping between the tree and the model is a separate
object; rendering works on a view snapshot through a theme. Phalcon already owns the building
blocks for all of it (Validation, Events, TagFactory, Volt, the new Container, Security).

## Why rewrite vs fix

- **The missing feature is structural.** Embedded forms need a tree, a name scheme, a data
  mapper and a view. None of those exist as seams in `Phalcon\Forms\Form`; adding them means
  changing what `add()`, `bind()`, `getValue()`, `isValid()` and `render()` mean. That is a new
  class with the old name, which is worse than a new class.
- **Encapsulation cannot be retrofitted.** Reading `$_POST` inside `getValue()` and writing the
  entity inside `bind()` are the design; making the form testable means capturing input through a
  request handler and writing the model through a mapper, both new concepts.
- **The current rendering path is slated for change anyway.** #17053 deprecates `Phalcon\Tag`
  and routes Volt through `TagFactory`. A Forms component built now on `Element::render()` would
  be built on the deprecated path.
- **Everything else on the v7 board benefits from the same primitives.** A property-path
  accessor (needed by the data mapper) is also what `Validation` lacks for nested fields and what
  `Model::assign()` reimplements inline. Per-form events are a straight use of
  `Phalcon\Events\Manager`. Delivering these as reusable pieces is cheaper than three local fixes.

## Non-goals

- Not a 1:1 port of Symfony Forms. We copy the architecture and the proven option names where
  they fit, and leave out what depends on Symfony-only infrastructure: Intl/localized number and
  date transformers, OptionsResolver's deprecations/nested options/info, PropertyInfo-based
  guessing, Twig-specific renderer internals, DataCollector, Flow types, polymorphic collections.
- Not a replacement for `Phalcon\Filter\Validation` or `Phalcon\Html\TagFactory`. Both are
  consumed as they are, with small additive changes called out below.
- No HTTP changes. The request handler is an interface precisely so #17054 can land before or
  after this without touching forms.

## Proposed approach

### 0. Namespace and coexistence

New component under `Phalcon\Form` (singular). `Phalcon\Forms` stays in 7.0 untouched and marked
`@deprecated` (removed in 8.0). No adapter between the two: the models differ too much for a
façade to be honest. A migration guide covers the mapping (`Element\Text` -> `TextType`,
`addValidator` -> `constraints`, `bind/isValid` -> `handleRequest/isValid`, `render` -> `form_row`).

### 1. The form tree (`Phalcon\Form`)

- `FormInterface` / `Form`: a node with `name`, optional `parent`, ordered `children`, three data
  representations (`modelData`, `normData`, `viewData`), `errors`, `submitted`, `extraData`,
  `transformationFailure`. Implements `Countable`, `IteratorAggregate`, `ArrayAccess` over
  children.
- Life cycle copied as-is from Symfony because every step exists for a reason:
  - `setData(model)`: `preSetData` event -> model transformers (`transform`) -> view transformers
    (`transform`) -> `dataMapper->mapDataToForms(viewData, children)` -> `postSetData`.
  - `submit(data, clearMissing = true)`: normalise scalars -> `preSubmit` -> compound: submit each
    child with `data[name] ?? null` (skip absent when `!clearMissing`), leftover keys ->
    `extraData` -> `empty_data` if empty -> `dataMapper->mapFormsToData(children, viewData)` ->
    view transformers `reverseTransform` (no transformers: `"" -> null`, which closes #17338) ->
    `submit` event -> model transformers `reverseTransform` -> `postSubmit`.
    A `TransformationFailedException` anywhere marks the form not synchronized and keeps the raw
    view data so the input re-renders.
  - `isValid()` = submitted and `count(getErrors(deep: true)) === 0`.
- Child names must match `/^[a-zA-Z0-9_][a-zA-Z0-9_\-:]*$/`. The HTML `full_name` (`parent[child]`)
  and `id` (`parent_child`) are computed only at view time.
- `addError(FormError)` forwards to the parent while `error_bubbling` is on (default
  `compound && !inherit_data`), so leaf fields keep their errors and anonymous sub-forms bubble.
- `inherit_data` and `InheritDataAwareIterator` are kept: they are what lets a sub-form group
  fields of the parent object without a nested object.
- Options that reach `Form` through its config, same names as Symfony: `data`, `data_class`,
  `empty_data`, `mapped`, `property_path`, `getter`, `setter`, `inherit_data`, `compound`,
  `by_reference`, `error_bubbling`, `trim`, `required`, `disabled`, `label`, `label_attr`, `attr`,
  `row_attr`, `help`, `method`, `action`, `block_name`, `block_prefix`, `priority`,
  `invalid_message`, `invalid_message_parameters`, `is_empty_callback`.

### 2. Config, builder, factory, registry

- `Config\FormConfigBuilder` (mutable, build time) -> `Config\FormConfigInterface` (frozen,
  `locked = true` on `getFormConfig()`, setters throw afterwards). Holds the option values above
  plus `type`, `viewTransformers`, `modelTransformers`, `dataMapper`, `requestHandler`,
  `eventsManager`, `attributes`, `autoInitialize`.
- `FormBuilder`: `add(name, typeClass, options)` stored lazily, `create()`, `get()`, `remove()`,
  `getForm()`; `addEventListener(event, callable, priority)`, `addViewTransformer`,
  `addModelTransformer`, `setDataMapper`, `setRequestHandler`, `setAttribute`.
- `FormFactory`: `create(type, data, options)`, `createNamed(name, type, data, options)`,
  `createBuilder(...)`, `createNamedBuilder(...)`. Registered in the Container as `formFactory`
  (and in `Di\FactoryDefault` while both exist).
- `FormRegistry` + `ResolvedType`: resolves `getParent()` chains and type extensions once, caches
  per type class, owns the `OptionsResolver` (cloned from the parent, then the type's and its
  extensions' `configureOptions`).
- Order of `buildForm` / `buildView` / `finishView`: parent type (recursively), the type, then the
  type's extensions. An extension on `FormType` therefore applies to every field; that is how
  validation and CSRF plug in without touching the core.

### 3. Type system (`Phalcon\Form\Type`)

- `TypeInterface`: `buildForm(FormBuilderInterface, array options)`, `buildView(FormView, FormInterface, array options)`,
  `finishView(...)`, `configureOptions(OptionsResolver)`, `getParent(): string|null`,
  `getBlockPrefix(): string`. `AbstractType` defaults `getParent()` to `FormType`.
- `TypeExtensionInterface` / `AbstractTypeExtension`: same hooks plus static `getExtendedTypes()`.
- `ExtensionInterface` (type loader) / `PreloadedExtension` for registration through the Container.
- `Options\OptionsResolver`, reduced to what forms use: `setDefaults`, lazy defaults (a `Closure`
  receiving `Options`), `setRequired`, `setDefined`, `setAllowedTypes`, `setAllowedValues`,
  `setNormalizer`, `resolve`, undefined-option rejection, `clone`. Dropped: nested options,
  deprecations, `define()`, info, prototype, ignore-undefined.
- Core types, milestone-tagged below. Each is small: options + transformers + view vars.

### 4. Data mapping (`Phalcon\Form\Data` and `Phalcon\Support\PropertyAccess`)

- `DataMapperInterface` { `mapDataToForms(viewData, iterable forms)`, `mapFormsToData(iterable forms, viewData)` }.
  `DataMapper` reads a child only when the data is non-empty, the child is `mapped` and the path is
  readable; writes only when `mapped && isSubmitted() && isSynchronized() && !isDisabled()` and the
  path is writable; skips the write when the value is `===` the current one on a by-reference
  object. Accessors: `PropertyPathAccessor` (default), `CallbackAccessor` (`getter`/`setter`
  options), `ChainAccessor`.
- `Phalcon\Support\PropertyAccess\PropertyPath` (`a.b[c]`, dot = property, bracket = index) and
  `PropertyAccessor` (`getValue`, `setValue(&target)`, `isReadable`, `isWritable`; getters
  `get|is|has`, setters, public properties, array indices, adder/remover pairs for iterables,
  nested array write-back by reference). Shipped as a general Support component because
  `Validation` (nested fields) and `Mvc\Model::assign()` can use it too. No wildcards, magic
  `__call` or null-safe paths.
- `Transformer\DataTransformerInterface` { `transform`, `reverseTransform` } and
  `TransformationFailedException` (carries `invalidMessage`, `invalidMessageParameters`).
  Core set: `CallbackTransformer`, `ReversedTransformer`, `BooleanToStringTransformer`,
  `ChoiceToValueTransformer`, `ChoicesToValuesTransformer`, `NumberToStringTransformer`
  (non-Intl), `IntegerToStringTransformer`, `DateTimeToStringTransformer` (format option, also
  used reversed for `input: string`), `DateTimeToTimestampTransformer`,
  `ValueToDuplicatesTransformer`.

### 5. Events

Use `Phalcon\Events\Manager`, one instance per form config, created by the builder with
`enablePriorities(true)`. Component type is `form`; names follow the Symfony life cycle so the
documentation maps 1:1:

`form:preSetData`, `form:postSetData`, `form:preSubmit`, `form:submit`, `form:postSubmit`,
`form:postValidate`.

The `data` argument is a `Form\Event\FormEvent` (`getForm()`, `getData()`, `setData()`;
`setData()` throws on the two post-events). Listeners attach through
`FormBuilder::addEventListener()` or `addEventSubscriber(EventSubscriberInterface)`.
Core listeners: `TrimListener` (`preSubmit`), `ResizeFormListener` (collections, see below),
`MergeCollectionListener` (multiple choice with `by_reference`), `TransformationFailureListener`
(`postSubmit`, priority -1024, only when no `constraints` option is set).

### 6. Collections (the #17106 feature)

`Type\Core\CollectionType` with `entry_type`, `entry_options`, `allow_add`, `allow_delete`,
`prototype`, `prototype_name` (`__name__`), `prototype_data`, `prototype_options`,
`delete_empty`, `keep_as_list`. `ResizeFormListener`:

- `postSetData` (priority 255): drop existing children, add one child per `key => value` with
  `property_path => "[key]"`.
- `preSubmit`: non-array -> `[]`; with `allow_delete` remove children missing from the payload;
  with `allow_add` add a child per new key from the prototype options.
- `submit` (priority 50): apply `delete_empty`, drop data keys without a child when
  `allow_delete`, re-index when `keep_as_list`, `setData`.

Embedding a single sub-form is the degenerate case: `add('address', AddressType::class)` on a
compound parent; the mapper reads/writes `address` on the parent object (or `[address]` on an
array). The example from #17106 becomes:

```php
$builder->add('title', TextType::class)
        ->add('messages', CollectionType::class, [
            'entry_type' => MessageType::class, 'allow_add' => true,
        ]);
```

rendering `name="ticket[title]"`, `name="ticket[messages][0][message]"`,
`name="ticket[messages][0][notes][0][note]"`, and mapping back onto `Ticket`, `Message`, `Note`
objects or nested arrays with no application glue.

### 7. View and rendering (`Phalcon\Form\View`)

- `FormView`: `vars`, `children`, `parent`, `rendered` flag (`isRendered()` is true when all
  children are rendered). Built by `Form::createView()` after submit: `buildView` top-down, child
  views, sort by `priority`, `finishView` bottom-up (`multipart` bubbles up).
- Standard vars: `id`, `name`, `full_name`, `value`, `data`, `attr`, `label`, `label_attr`,
  `errors`, `required`, `disabled`, `compound`, `submitted`, `valid`, `help`, `block_prefixes`,
  `unique_block_prefix`, `cache_key`; root also `method`, `action`, `multipart`. Type-specific:
  `checked`, `choices`, `multiple`, `expanded`, `prototype`, `allow_add`, `allow_delete`, `type`.
- `block_prefixes` = type chain (`getBlockPrefix()`) + `block_prefix` option + `unique_block_prefix`,
  e.g. `['form', 'text', 'email', '_ticket_email']`. Block lookup walks it backwards:
  `_ticket_email_widget` -> `email_widget` -> `text_widget` -> `form_widget`.
- `FormRenderer` / `ThemeInterface`. Blocks: `form_start`, `form_end`, `form_rest`, `form_row`,
  `form_label`, `form_errors`, `form_help`, `form_widget` (dispatching to `form_widget_compound`
  or `form_widget_simple`), `hidden_row`, `hidden_widget`, `textarea_widget`, `checkbox_widget`,
  `radio_widget`, `choice_widget` (+ `_collapsed`/`_expanded`), `collection_widget`,
  `button_widget`, `submit_widget`, `csrf_token`. `row` and `widget` are render-once.
- Two theme sources, searched in order:
  1. **Volt themes**: a `.volt` file whose `{% block text_widget %}` blocks are compiled as macros.
     Users override exactly the way they do in Symfony/Twig.
  2. **`Theme\DefaultTheme`** in Zephir: one method per block, rendering through `TagFactory`
     helpers. A C extension cannot ship template files, so the default must be code. It is also
     the fallback for any block a Volt theme does not define.
- Volt integration via a `Compiler` extension registering `form_start`, `form_end`, `form_row`,
  `form_widget`, `form_label`, `form_errors`, `form_help`, `form_rest`. Compiles to
  `$this->formRenderer->renderRow($view, $vars)` etc. The renderer is a Container/DI service
  `formRenderer`. This aligns with #17053: forms never call `Phalcon\Tag`.
- Additive change to `Phalcon\Html`: `TagFactory::newInstance()` is kept, but the input helpers
  gain a `reset()` or the renderer calls `new` helpers per widget, so stateful helpers cannot leak
  across collection entries. Decide with #17053.

### 8. Validation bridge (`Phalcon\Form\Validation`)

- `ValidationExtension` (type extension on `FormType`) adds options `constraints` (array of
  `Phalcon\Filter\Validation\ValidatorInterface`), `error_mapping`, `allow_extra_fields`,
  `extra_fields_message`, `validation_groups`.
- `ValidationListener` on `form:postSubmit`, root only. For each synchronized form in the tree
  with `constraints`, run them through a `Phalcon\Filter\Validation` instance over that form's
  norm data under its own name; each `Phalcon\Messages\Message` becomes a `FormError` on that
  form (bubbling applies). Then, if the root `data_class` object exposes `validation()` /
  `getMessages()` (a `Phalcon\Mvc\Model` or anything implementing a small
  `ValidatableInterface`), run it and map each message's `field` onto the tree via
  `ViolationMapper`: match by `property_path` through `inherit_data` children, honour
  `error_mapping`, fall back to the root. Then `form:postValidate`, children first.
- Not synchronized forms get `invalid_message` (`{{ value }}` substituted) unless a child already
  carries it. Extra submitted keys add `extra_fields_message` unless `allow_extra_fields`.
- Follow-up NFR (separate): teach `Phalcon\Filter\Validation::getValue()` dotted/bracket paths
  via `PropertyAccessor`, so a single validation set can address `address.zip`.

### 9. CSRF (`Phalcon\Form\Csrf`)

`CsrfExtension` on `FormType`: options `csrf_protection` (true), `csrf_field_name` (`_token`),
`csrf_token_id`, `csrf_message`. Uses `Phalcon\Encryption\Security` (`getTokenKey()`,
`getToken()`, `checkToken()`), injected as `security`. The hidden field is added to the root
view only (`finishView`), not as a real child; validated on `form:preSubmit` and removed from
the payload so it never counts as extra data.

### 10. Request handling (`Phalcon\Form\RequestHandler`)

`RequestHandlerInterface` { `handleRequest(FormInterface, request = null)`, `isFileUpload(data)` }.
`NativeRequestHandler` reads `$_GET`/`$_POST`/`$_FILES` (Symfony's algorithm: method check,
named vs unnamed root, `post_max_size` guard, `$_FILES` normalisation, PATCH =>
`clearMissing = false`). `HttpRequestHandler` does the same over
`Phalcon\Http\RequestInterface` (`getMethod`, `getPost`, `getQuery`, `getUploadedFiles`), and is
what `Form::handleRequest()` uses when a `request` service exists. #17054 only has to keep those
four methods, or ship an adapter.

### 11. Container wiring

A `Container\Provider\Form` registers `formFactory`, `formRegistry`, `formRenderer`,
`propertyAccessor`, the core `ExtensionInterface`, and tags `form.type` / `form.type_extension`
so user types are autowired by class name (`FormRegistry::getType()` falls back to `new $class`
when a type is not registered, as Symfony does). No `Di::getDefault()` anywhere, in line with
#17131.

## Milestones

| | Scope | Closes |
|---|---|---|
| **M1 Core** | Form tree, config/builder/factory/registry, reduced OptionsResolver, events, `PropertyAccess`, `DataMapper`, core transformers, `NativeRequestHandler` + `HttpRequestHandler`, `FormView` + `DefaultTheme` + Volt functions. Types: `FormType`, `TextType`, `TextareaType`, `HiddenType`, `PasswordType`, `EmailType`, `UrlType`, `TelType`, `SearchType`, `CheckboxType`, `RadioType`, `ChoiceType` (collapsed), `IntegerType`, `NumberType`, `DateType` (`single_text`), `CollectionType`, `SubmitType`, `ButtonType`. | #17106, #17338 |
| **M2 Validation and CSRF** | `ValidationExtension`, `ValidationListener`, `ViolationMapper`, `error_mapping`, `CsrfExtension`, `TransformationFailureListener`; `ChoiceType` expanded (+ `CheckboxListMapper`/`RadioListMapper`), `RepeatedType`, `FileType` (uploads), `ColorType`, `RangeType`, `DateTimeType`/`TimeType` (`single_text`). | #17332 (events in validation) |
| **M3 Theming, guessing, migration** | Volt theme files with block override and parent-block fallback, `form_theme` tag; type guessing from `Mvc\Model\MetaData` (`TypeGuesserInterface`); `Phalcon\Forms` deprecation notices + migration guide; `Forms\Manager` replacement in `FormFactory`; docs. | |

Rough size: M1 ≈ 6k lines of Zephir plus tests, M2 ≈ 3k, M3 ≈ 2k. Each milestone is one PR
series against `7.0.x`; M1 alone is useful and shippable.

## Backward compatibility

- `Phalcon\Forms\*` unchanged in 7.0, `@deprecated` in docblocks and stubs, emits
  `E_USER_DEPRECATED` behind the `phalcon.forms.deprecation_notices` ini flag (default Off).
  Removed in 8.0.
- No existing class, interface or service name is changed. New services: `formFactory`,
  `formRegistry`, `formRenderer`, `propertyAccessor`.
- `Phalcon\Html` gets additive changes only (helper state reset).
- Volt gains new function names (`form_*`); applications that defined their own `form_row`
  through `addFunction()` win, since user functions are resolved first.

## Implementation plan

1. Agree on this document (namespace, coexistence, theme delivery, validation bridge scope).
2. Prototype M1 core in plain PHP with tests in a scratch package to validate the API and the
   life cycle ordering, since iteration is seconds and Zephir is near-mechanical to port to.
3. Port to Zephir under `phalcon/Form` and `phalcon/Support/PropertyAccess`, tests under
   `tests/unit/Form`, in PR-sized slices: PropertyAccess -> tree + config + builder -> types +
   options -> mapper + transformers -> events + collection -> request handlers -> view + theme +
   Volt.
4. M2, M3 as above.

## Open questions for the maintainers

1. **Namespace:** new `Phalcon\Form` next to deprecated `Phalcon\Forms`, or replace `Phalcon\Forms`
   in place and accept the hard break in 7.0?
2. **Theme delivery:** is a Zephir `DefaultTheme` acceptable as the built-in theme, with Volt
   themes as overrides? Alternative: ship default Volt themes in a Composer package
   (`phalcon/form-themes`) and have no built-in HTML in the extension.
3. **Validation:** should the bridge stay at "constraints per form + model messages mapped onto
   the tree", or should `Phalcon\Filter\Validation` grow nested-path support first (separate NFR)?
4. **PropertyAccess as `Phalcon\Support`:** agree to ship it as a general component so
   `Validation` and `Model::assign()` can adopt it later?
5. **Sequencing with #17053 and #17054:** forms will depend on `TagFactory` helpers being safely
   re-renderable and on four `Request` methods. Does either rework change those?
6. **Prototype location:** PHP prototype in a scratch repo, or directly in `phalcon/phalcon`?

## Appendix: concept map

| Symfony | Phalcon v7 proposal |
|---|---|
| `FormInterface`, `Form` | `Phalcon\Form\FormInterface`, `Form` |
| `FormConfigBuilder`/`FormConfigInterface` | `Form\Config\FormConfigBuilder`, `FormConfigInterface` |
| `FormBuilder`, `FormFactory`, `FormRegistry`, `ResolvedFormType` | same names under `Phalcon\Form` |
| `FormTypeInterface`, `AbstractType`, type extensions | `Form\Type\TypeInterface`, `AbstractType`, `TypeExtensionInterface` |
| `OptionsResolver` | `Form\Options\OptionsResolver` (reduced) |
| `DataMapperInterface`, `DataMapper`, accessors | `Form\Data\*` |
| `PropertyAccess` | `Phalcon\Support\PropertyAccess\{PropertyPath, PropertyAccessor}` |
| `DataTransformerInterface`, core transformers | `Form\Transformer\*` |
| `EventDispatcher` + `FormEvents` | `Phalcon\Events\Manager` + `form:*` events, `Form\Event\FormEvent` |
| `CollectionType` + `ResizeFormListener` | `Form\Type\Core\CollectionType` + `Form\EventListener\ResizeFormListener` |
| `FormView`, `FormRenderer`, Twig themes | `Form\View\FormView`, `FormRenderer`, `Theme\DefaultTheme` + Volt themes |
| Validator extension, `ViolationMapper` | `Form\Validation\*` over `Phalcon\Filter\Validation` + model messages |
| CSRF extension | `Form\Csrf\CsrfExtension` over `Phalcon\Encryption\Security` |
| `NativeRequestHandler`, `HttpFoundationRequestHandler` | `Form\RequestHandler\NativeRequestHandler`, `HttpRequestHandler` |
| DI extension | `Phalcon\Container\Provider\Form` |

Research notes behind this document: `survey-symfony-core.md`, `survey-symfony-types.md`,
`survey-symfony-data.md`, `survey-symfony-view.md`, `survey-phalcon-current.md` in this directory.
