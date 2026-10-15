# Survey: Symfony Form — core tree and data flow
(Read-only survey by a research agent, 2026-10-15. Source: symfony/form, Tests/ ignored. "(outside list)" = file outside the assigned scope that decides the behaviour.)

## 1. Lifecycle

**Construction**
- `FormFactory::createNamedBuilder($name, $type, $data, $options)`: `$data` becomes `$options['data']`. `FormRegistry::getType()` returns a cached `ResolvedFormType`, built through `resolveType()` (parent chain plus type extensions, cycle check). `ResolvedFormType::createBuilder()` resolves options with `getOptionsResolver()` (parent's resolver cloned, then inner type's and extensions' `configureOptions`) and calls `newBuilder()` -> `FormBuilder` with its own `EventDispatcher`. Buttons get `ButtonBuilder` / `SubmitButtonBuilder`. `$type->buildForm()` runs parent first, then inner type, then extensions. `FormType::buildForm` (outside list) copies options into config setters and calls `setDataLocked(true)` if the `data` option was given.
- `FormBuilder::getForm()`: `resolveChildren()` turns lazy children into builders; `new Form($this->getFormConfig())` (clone with `locked = true`); each child added with `$form->add($child->setAutoInitialize(false)->getForm())`; if `getAutoInitialize()`, `$form->initialize()` (root only) -> `setData($config->getData())`.
- `Form::__construct` throws if compound but no `DataMapper`. An `inherit_data` form starts with `defaultDataSet = true`.
- Data is initialised lazily: `getData()`, `getNormData()`, `getViewData()` and `submit()` call `setData($config->getData())` if not run yet.

**`Form::setData($modelData)`, in order**
1. Guards: throws if already submitted (and `defaultDataSet`), throws if `inheritData`, returns silently if `getDataLocked()` and `$modelData !== $config->getData()`. Objects cloned when `!getByReference()`.
2. Re-entrancy guard `lockSetData` ("cycle detected").
3. `FormEvents::PRE_SET_DATA` (`PreSetDataEvent`), listener may `$event->setData()`.
4. Scalar cast to string if no transformers.
5. `modelToNorm()` (model transformers, forward), then `normToView()` (view transformers, forward). Exceptions not caught here.
6. Non-empty view data must be `instanceof data_class`.
7. Store `modelData`, `normData`, `viewData`; `defaultDataSet = true`; release lock.
8. If children: `getDataMapper()->mapDataToForms($viewData, new \RecursiveIteratorIterator(new InheritDataAwareIterator($this->children)))`.
9. `FormEvents::POST_SET_DATA` (`PostSetDataEvent`, `setData` throws).

**`Form::submit($submittedData, $clearMissing = true)`, in order**
1. Throws if already submitted. `errors = []`.
2. If `isDisabled()`: `submitted = true`, return.
3. Lazy `setData()` if needed.
4. Normalise input: `false` -> `null`; scalars -> strings. File upload (`RequestHandlerInterface::isFileUpload`) without `allow_file_upload` -> `TransformationFailedException`. Array to non-compound, non-`multiple` field -> failure (deferred until after PRE_SUBMIT if `allow_array_submission`).
5. Inside `try`:
   1. `FormEvents::PRE_SUBMIT` (`PreSubmitEvent`, can replace data).
   2. If compound: payload must be array (`null` -> `[]`). For each child `$child->submit($submittedData[$name] ?? null, $clearMissing)`, skipping absent keys when `!$clearMissing`. Each submitted key `unset` from payload. Clicked button tracked (`ClickableInterface::isClicked()` or nested `getClickedButton()`). Leftover keys -> `$this->extraData`.
   3. If not `inheritData`: `$viewData` = `$this->viewData` for compound, submitted value for simple. If `FormUtil::isEmpty()`, use `getEmptyData()` (a `\Closure` called as `($form, $viewData)`). If children: `mapFormsToData(RecursiveIteratorIterator(InheritDataAwareIterator(children)), $viewData)`. `viewToNorm()` (view transformers reverse; `''` -> `null` when none). `FormEvents::SUBMIT` (`SubmitEvent`, can replace norm data). `normToModel()` (model transformers reverse), then `normToView()` again.
6. `catch (TransformationFailedException)`: stored in `transformationFailure` -> `isSynchronized()` false. View data falls back to raw submitted data.
7. `submitted = true`; store all three representations.
8. `FormEvents::POST_SUBMIT` (`PostSubmitEvent`, read-only).

Children submit first, so their POST_SUBMIT fires before the parent's SUBMIT.

**Validation is not in `Form`.** `ValidationListener::validateForm` (outside list) listens to POST_SUBMIT and acts only on the root (`isRoot()`): validates the whole tree and maps violations onto forms with `addError`. `FormValidator` (outside list) adds the extra-fields error when `!allow_extra_fields && getExtraData()`. Then `FormEvents::POST_VALIDATE` (`PostValidateEvent`) is dispatched depth-first, children before parent, on each form's own dispatcher.

Event names: `form.pre_set_data`, `form.post_set_data`, `form.pre_submit`, `form.submit`, `form.post_submit`, `form.post_validate`. `FormEvent` holds `getForm()`, `getData()`, `setData()`.

**Request handling:** `Form::handleRequest($req)` -> `config->getRequestHandler()->handleRequest($this, $req)`. `NativeRequestHandler`: nothing if method mismatch with `getMethod()`. GET/HEAD/TRACE read `$_GET[$name]`; others read `$_POST[$name]` merged with fixed-up `$_FILES` via `FormUtil::mergeParamsAndFiles`. Form name absent -> no submit. `post_max_size` exceeded -> `submit(null, false)` + `addError`. `MissingDataHandler` (outside list) folds in `false_values` defaults, except for PATCH. Unnamed root submits only if at least one child key present. `_method` stripped. Finally `submit($data, 'PATCH' !== $method)` (PATCH => `clearMissing = false`).

## 2. Compound tree
- **Adding children.** Builder: `FormBuilder::add()` stores `[type, options]` lazily in `unresolvedChildren`, order kept in `children`. Form: `Form::add()` accepts a `FormInterface`, or name/type (forces `auto_initialize = false`, goes through `getFormFactory()->createNamed` / `createForProperty`); throws if submitted or not compound. Stores child in an `OrderedHashMap` keyed by `getName()`, calls `$child->setParent($this)`. Empty-named child cannot have a parent. If data already set (not locked, not `inheritData`) -> `mapDataToForms` for just that child. Also `remove()`, `has()`, `get()`, ArrayAccess.
- **Names.** `parent[child]` is built only at view time, in `BaseType::buildView` (outside list): `full_name = sprintf('%s[%s]', $parentFullName, $name)`, `id = parent_id.'_'.$name`. Empty root name gives bare child names. `FormConfigBuilder::isValidName`: `/^[a-zA-Z0-9_][a-zA-Z0-9_\-:]*$/`.
- **Property path.** `Form::getPropertyPath()` uses configured `property_path`; otherwise walks up past `inherit_data` ancestors: `[name]` if that ancestor has no `data_class`, else `name`.
- **Distribution.** Parent indexes submitted array by child name. Missing keys submit `null` when `clearMissing`, skipped otherwise. Unknown keys -> `getExtraData()`, rejected later by validator.
- **`DataMapper` (outside list).** Reads only if child `getMapped()` and path readable. Writes only if mapped, `isSubmitted()`, `isSynchronized()`, `!isDisabled()` and path writable.
- **`inherit_data`.** Form holds no data: `getData()`/`getNormData()`/`getViewData()` delegate to parent; `setData()` throws; `submit()` skips its own map/transform phase; `InheritDataAwareIterator::hasChildren()` returns `getConfig()->getInheritData()` so the parent's mapper reaches grandchildren directly.
- **Errors.** `addError()` sets origin, then forwards to `$this->parent->addError()` if `getErrorBubbling()`, else stores locally. Default `error_bubbling` (FormType) is `compound && !inherit_data`. `getErrors($deep, $flatten)` returns `FormErrorIterator` (recursive when not flattened, `findByCodes()`). `isValid()` requires submitted, true if disabled, else `0 === count(getErrors(true))`. `required`/`disabled` inherited: `isRequired()` false if parent not required; `isDisabled()` true if parent disabled.

## 3. Data representations (private fields of `Form`)
- `modelData`: domain value. `getData()`; `setData()` takes this.
- `normData`: model through `modelTransformers`; what `SubmitEvent` sees. `getNormData()`.
- `viewData`: norm through `viewTransformers`; what the `DataMapper` reads/writes for compound forms, string or array for simple ones. `getViewData()`.
- Transformers live in config: `addModelTransformer` prepends by default (`array_unshift`), `addViewTransformer` appends.
- Also: `extraData`, `transformationFailure`, `submitted`, `defaultDataSet`, `clickedButton`.

## 4. FormConfig (`FormConfigBuilder` implements `FormConfigInterface`)
Fields: `name`, `propertyPath`, `mapped`, `byReference`, `inheritData`, `compound`, `type` (`ResolvedFormTypeInterface`), `viewTransformers`, `modelTransformers`, `dataMapper`, `required`, `disabled`, `errorBubbling`, `emptyData`, `attributes`, `data`, `dataClass`, `dataLocked`, `formFactory`, `action`, `method`, `requestHandler` (default static `NativeRequestHandler`), `autoInitialize`, `isEmptyCallback`, event `dispatcher`, resolved `options` (`getOption()`).
Immutability: `getFormConfig()` returns a clone with `locked = true`; every setter/adder throws `BadMethodCallException` once locked (covers listeners: dispatcher is per-form, only reachable via locked config). Gap: `setIsEmptyCallback()` has no lock check. After build only the tree (`add`/`remove`, until submit) and data/state fields change.

## 5. Minimal interface set for a reduced reimplementation
- `FormInterface`: tree node (parent/children, set/submit, three data getters, errors).
- `FormConfigInterface` + `FormConfigBuilderInterface`: mutable build-time vs frozen runtime state.
- `FormBuilderInterface`: lazy children, `getForm()`.
- `FormTypeInterface`: `buildForm`, `configureOptions`, `getParent`; add `buildView`/`finishView` if rendering.
- `ResolvedFormTypeInterface`: flattens parent chain + extensions, owns options resolver.
- `FormRegistryInterface` / `FormFactoryInterface`: type names -> resolved types -> builders.
- `DataMapperInterface`: `mapDataToForms`, `mapFormsToData`; the only bridge between compound view data and children.
- `DataTransformerInterface`: `transform` / `reverseTransform`, `TransformationFailedException` for "not synchronized".
- `RequestHandlerInterface`: `handleRequest`, `isFileUpload`; decouples form from the HTTP Request.
- `ClickableInterface`: `isClicked()` (`SubmitButton` sets `clicked = null !== $submittedData`; `Button` is an inert `FormInterface` leaf).
- `ClearableErrorsInterface`: `clearErrors($deep)`; optional.
- Value types: `FormError` (message, template, params, cause, origin), `FormErrorIterator`, `FormEvent` + six event names. Per-form event dispatcher.
- Helpers worth porting: `OrderedHashMap` (stable child order, mutation during iteration), `InheritDataAwareIterator`, `FormUtil::isEmpty` (only `null` and `''` are empty).
