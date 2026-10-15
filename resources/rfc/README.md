# Phalcon v7 Forms overhaul — working notes (branch T17106-forms-overhaul)

Handoff file. If you are a new session/model picking this up, read this first, then
`17106-forms-rfc.md` in this directory (if it exists yet).

## Goal
Design (then build) a Symfony-*shaped* forms component for Phalcon v7, built from Phalcon's
own parts, NOT a 1:1 port of Symfony Forms. Closes GitHub issue phalcon/cphalcon#17106
(Embedded Forms, open since 2013) and #17338 ("" -> null). Maintainer niden commented
2026-06-10: "Planning this for v7 with a Forms overhaul" — no spec exists. We write the RFC.

## Decisions already made (2026-10-15)
- Target branch: upstream `7.0.x` (PHP >= 8.3). v7 has no docs; project board
  https://github.com/orgs/phalcon/projects/13 has 0 items in progress.
- Architecture to borrow from Symfony: FormType-as-config with getParent() inheritance,
  compound form tree (`parent[child]` names), data mapper + data transformers,
  form events, validation attached to the tree with error bubbling, FormView separated
  from Form, themed rendering. First milestone = compound forms + CollectionType.
- Phalcon pieces to build on: Phalcon\Filter\Validation, Phalcon\Events\Manager,
  Phalcon\Html\TagFactory + Volt (aligns with #17053 Tag deprecation), the new
  Phalcon\Container (#16896), Phalcon\Encryption\Security for CSRF.
  Beware overlap with niden's planned rewrites: #17054 (HTTP Request/Response),
  #17053 (Phalcon\Tag deprecation), #16898/#17131 (Container instead of Di::getDefault()).
- Process: RFC first, in niden's NFR shape (Problem / Why rewrite vs fix / Proposed
  approach / Milestones / BC / Open questions). Post it as a comment on #17106 and ask
  whether his Forms overhaul has a shape. Only then code.
- Code plan after a yes: prototype core in plain PHP (fast iteration) -> port to Zephir
  (phalcon/Forms/...), fan out implementation with firstmate/workflows per subsystem.
- Everything must be Zephir in `phalcon/`; never hand-edit `ext/*.zep.c`. Add tests under
  tests/unit/Forms. Commit trailer convention: `Assisted-by: Claude Code`.
- Repo hygiene: user has write access upstream. Push ONLY to remote `fork`
  (git@github.com:Izopi4a/cphalcon.git), never to `origin`. Open PRs from the fork.

## Toolchain (set up 2026-10-15, system PHP 8.5.4 from apt)
- Zephir CLI: `vendor/bin/zephir` (0.19.0, from composer). Parser ext built from source
  (zephir-lang/php-zephir-parser v1.8.0; needs `./configure CC='gcc -std=gnu99 -w'` on gcc 15)
  installed at ~/.local/lib/php/zephir_parser.so, enabled by ~/.config/php/conf.d/zephir_parser.ini.
  Shell must have: `export PHP_INI_SCAN_DIR=":$HOME/.config/php/conf.d"` (leading colon = append).
- Regenerate ext/: `vendor/bin/zephir generate` (~7s). Build: `cd ext && phpize && ./configure
  --enable-phalcon CFLAGS='-g -O0' && make -j32`. Tests: `php -d extension=ext/modules/phalcon.so
  vendor/bin/phpunit -c phpunit.xml.dist tests/unit/Forms`.
- NEVER commit ext/ changes (CONTRIBUTING); `git checkout -- ext && git clean -f ext/phalcon/*__closure*`
  before committing. The committed ext/ on 7.0.x is stale (297 files differ after generate).
- PHP prototype of the M1 core lives in resources/rfc/prototype/ (plain PHP 8.3+, PHPUnit from
  cphalcon's vendor). It is design validation only; delete before any upstream PR.

## Research inputs
Symfony sources shallow-cloned (scratch, may be gone):
/tmp/claude-1000/-home-izopi4a/326b8842-b11d-4ad8-bc9d-f685b0a6d968/scratchpad/symfony/{form,options-resolver,property-access}
Re-clone with: git clone --depth 1 https://github.com/symfony/form (etc.)
Survey notes from the reading agents are saved as `survey-*.md` in this directory.

## Status
- [x] branch created, handoff written
- [x] surveys saved: symfony-core, symfony-types, symfony-data, symfony-view
- [x] survey saved: phalcon-current
- [x] 17106-forms-rfc.md drafted (2026-10-15, awaiting user review)
- [x] Zephir toolchain working (generate + build)
- [ ] user review of RFC
- [~] PHP prototype of M1 core: tree, config/builder, factory/registry, options, events, PropertyAccess, DataMapper, FormType, TextType done + 12 lifecycle tests green (2026-10-15). Remaining: transformers, core types, CollectionType, buttons, HttpRequestHandler, view renderer.
- [ ] posted on #17106

## Next step after prototype M1 core: the <select> test matrix (user priority, 2026-10-15)
User (long-time Phalcon user) says select is where people always got stuck: default value, empty
value, validation, optgroups. Goal: exhaustive ChoiceType / ModelType tests in
prototype/tests/Select*. Matrix to cover (each = at least one test):

ChoiceType, collapsed single:
- choices as label=>value with string values, int values, "0" and 0 and "" as legitimate values
  (must not be confused with "no selection"), null/bool values
- default/preselected value from setData, from entity property, from `data` option, from
  `empty_data`; preselected value not in choices -> what happens (Symfony: no option selected,
  submit of unknown value -> transformation failure -> not synchronized + error)
- placeholder: string, false (none), with required true/false; placeholder selected when value null;
  empty string submit with placeholder -> null model data; required + placeholder + "" -> invalid
- validation: submitted value not in list -> error, synchronized false, view keeps raw value;
  InclusionIn from Phalcon\Filter\Validation as `constraints` once the validation bridge exists
- optgroups: nested choices array (group label => [label => value]), `group_by` callable,
  preferred_choices (rendered first + separator), choice_attr (disabled options), choice_label /
  choice_value callables, choice_translation off
- disabled option submitted -> rejected?; disabled select submitted -> ignored
- view vars: choices/preferred_choices structure, is_selected, placeholder_in_choices, value
ChoiceType, multiple:
- array data in/out, empty submit -> [], unknown value among several -> error on the form,
  full_name ends with [], by_reference false + adder/remover on entity (MergeCollectionListener)
ModelType (Phalcon\Mvc\Model backed, like old Select element with ResultsetData + `using`):
- `class` + `parameters` (find() args: conditions, bind, order, columns?) -> options, lazy
- choice_value defaults to primary key via metadata; choice_label as property/getter/closure
- submitted id -> model instance as form data; multiple -> array of models; relation setter
- empty resultset; placeholder; preselected from related model (belongsTo); invalid id -> error
- optgroups via group_by property on the model
- tests use in-memory SQLite (Phalcon\Db\Adapter\Pdo\Sqlite ':memory:') + DI with modelsManager
  and modelsMetadata, a fixture model created with CREATE TABLE in setUp.
Also mirror each case as a Volt rendering expectation later (M1 view/renderer): <select>,
<option value selected disabled>, <optgroup label>.
ChoiceType, expanded (user: `<input type=checkbox name="color[]">` must be a normal case):
- expanded+multiple -> one CheckboxType child per choice, child full_name = parent full_name + "[]",
  CheckboxListMapper (array of values <-> per-child bools), submit of ['red','blue'] -> ['red','blue']
  model data, unknown value -> error on the parent, none checked -> []
- expanded single -> RadioType children, RadioListMapper, placeholder radio -> null, required
- preselected from data/entity, disabled option, choice_attr per checkbox, optgroups rendered as
  fieldsets/labels, by_reference false with adder/remover on entity
- also assert FileType multiple and <select multiple> get "[]" and that CollectionType(allow_add)
  accepts PHP-auto-indexed `tags[]` submissions (0..n keys)
