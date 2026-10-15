<?php
declare(strict_types=1);

namespace Phalcon\Form\View;

use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\View\Theme\DefaultTheme;
use Phalcon\Form\View\Theme\ThemeInterface;

/**
 * Symfony's FormRenderer and AbstractRendererEngine in one class (there is a single "engine":
 * ThemeInterface objects). Block lookup for a view:
 *
 *   1. the view's own themes (last set wins),
 *   2. the themes of each ancestor view, nearest first,
 *   3. the renderer's default themes (last added wins), unless setTheme(..., false).
 *
 * Per-view state is keyed by spl_object_id(): a view only lives for one request, and unlike
 * Symfony's cache_key two different forms with the same name never share themes.
 */
class FormRenderer implements FormRendererInterface
{
    /** @var list<ThemeInterface> */
    private array $defaultThemes;

    /** @var array<int, list<ThemeInterface>> view id => themes */
    private array $themes = [];

    /** @var array<int, bool> view id => use default themes */
    private array $useDefaultThemes = [];

    /** @var array<string, list<string>> "{view id}_{suffix}" => block names, most generic first */
    private array $blockNameHierarchyMap = [];

    /** @var array<string, int> "{view id}_{suffix}" => level currently rendering */
    private array $hierarchyLevelMap = [];

    /** @var array<int, list<array>> view id => stack of variable scopes */
    private array $variableStack = [];

    /** @param ThemeInterface|list<ThemeInterface>|null $defaultThemes null: a DefaultTheme */
    public function __construct(ThemeInterface|array|null $defaultThemes = null)
    {
        $defaultThemes ??= new DefaultTheme();
        $this->defaultThemes = is_array($defaultThemes) ? array_values($defaultThemes) : [$defaultThemes];
    }

    public function addDefaultTheme(ThemeInterface $theme): static
    {
        $this->defaultThemes[] = $theme;

        return $this;
    }

    public function setTheme(FormView $view, ThemeInterface|array $themes, bool $useDefaultThemes = true): void
    {
        $id = spl_object_id($view);

        foreach (is_array($themes) ? $themes : [$themes] as $theme) {
            if (!$theme instanceof ThemeInterface) {
                throw new LogicException(sprintf('Themes must implement %s, got %s.', ThemeInterface::class, get_debug_type($theme)));
            }
            $this->themes[$id][] = $theme;
        }
        $this->useDefaultThemes[$id] = $useDefaultThemes;
    }

    public function renderBlock(FormView $view, string $blockName, array $vars = []): string
    {
        $theme = $this->findTheme($view, $blockName);
        if (null === $theme) {
            throw new LogicException(sprintf('No block "%s" found while rendering the form "%s".', $blockName, $view->vars['name'] ?? ''));
        }

        $viewId = spl_object_id($view);
        $scope  = $this->mergeVars($this->currentScope($view), $vars);

        $this->variableStack[$viewId][] = $scope;
        try {
            return $theme->renderBlock($blockName, $this, $view, $scope);
        } finally {
            $this->popScope($viewId);
        }
    }

    public function searchAndRenderBlock(FormView $view, string $blockNameSuffix, array $vars = []): string
    {
        $renderOnlyOnce = 'row' === $blockNameSuffix || 'widget' === $blockNameSuffix;

        if ($renderOnlyOnce && $view->isRendered()) {
            throw new BadMethodCallException(sprintf(
                'Field "%s" has already been rendered, save the result of renderWidget()/renderRow() and reuse it instead.',
                $view->vars['name'] ?? ''
            ));
        }

        $viewId = spl_object_id($view);
        $key    = $viewId . '_' . $blockNameSuffix;
        // The scope is per view, not per suffix: form_row(view, {label: 'X'}) calls form_label(view)
        // from inside the row block, and that label block must see "label" = 'X'.
        $scope = $this->mergeVars($this->currentScope($view), $vars);

        if (!isset($this->blockNameHierarchyMap[$key])) {
            // INITIAL CALL: ['form_widget', 'text_widget', 'email_widget', '_ticket_email_widget']
            $hierarchy = [];
            foreach ($view->vars['block_prefixes'] ?? ['form'] as $prefix) {
                $hierarchy[] = $prefix . '_' . $blockNameSuffix;
            }
            $level      = count($hierarchy) - 1;
            $init       = true;
            $outerLevel = -1;
        } else {
            // RECURSIVE CALL from inside a block: resume one level up (= parent type's block).
            $hierarchy  = $this->blockNameHierarchyMap[$key];
            $outerLevel = $this->hierarchyLevelMap[$key];
            $level      = $outerLevel - 1;
            $init       = false;
        }

        [$theme, $level] = $this->findThemeInHierarchy($view, $hierarchy, $level);
        if (null === $theme) {
            throw new LogicException(sprintf(
                'Unable to render the form "%s": none of the blocks "%s" exist.',
                $view->vars['name'] ?? '',
                implode('", "', array_reverse($hierarchy))
            ));
        }

        $this->blockNameHierarchyMap[$key] = $hierarchy;
        $this->hierarchyLevelMap[$key]     = $level;
        $this->variableStack[$viewId][]    = $scope;

        try {
            $html = $theme->renderBlock($hierarchy[$level], $this, $view, $scope);
        } finally {
            $this->popScope($viewId);
            if ($init) {
                unset($this->blockNameHierarchyMap[$key], $this->hierarchyLevelMap[$key]);
            } else {
                // The outer block may call us again: it must resume from its own level.
                $this->hierarchyLevelMap[$key] = $outerLevel;
            }
        }

        if ($renderOnlyOnce) {
            $view->setRendered();
        }

        return $html;
    }

    public function renderParentBlock(FormView $view, string $blockNameSuffix, array $vars = []): string
    {
        if (!isset($this->blockNameHierarchyMap[spl_object_id($view) . '_' . $blockNameSuffix])) {
            throw new LogicException(sprintf(
                'renderParentBlock() can only be called while a "%s" block of the view "%s" is being rendered.',
                $blockNameSuffix,
                $view->vars['name'] ?? ''
            ));
        }

        return $this->searchAndRenderBlock($view, $blockNameSuffix, $vars);
    }

    public function humanize(string $text): string
    {
        return ucfirst(strtolower(trim(preg_replace(['/([A-Z])/', '/[_\s]+/'], ['_$1', ' '], $text))));
    }

    public function renderStart(FormView $view, array $vars = []): string
    {
        return $this->renderBlock($view, 'form_start', $vars);
    }

    public function renderEnd(FormView $view, array $vars = []): string
    {
        return $this->renderBlock($view, 'form_end', $vars);
    }

    public function renderRow(FormView $view, array $vars = []): string
    {
        return $this->searchAndRenderBlock($view, 'row', $vars);
    }

    public function renderWidget(FormView $view, array $vars = []): string
    {
        return $this->searchAndRenderBlock($view, 'widget', $vars);
    }

    public function renderLabel(FormView $view, ?string $label = null, array $vars = []): string
    {
        if (null !== $label) {
            $vars['label'] = $label;
        }

        return $this->searchAndRenderBlock($view, 'label', $vars);
    }

    public function renderErrors(FormView $view, array $vars = []): string
    {
        return $this->searchAndRenderBlock($view, 'errors', $vars);
    }

    public function renderHelp(FormView $view, array $vars = []): string
    {
        return $this->searchAndRenderBlock($view, 'help', $vars);
    }

    public function renderRest(FormView $view, array $vars = []): string
    {
        return $this->searchAndRenderBlock($view, 'rest', $vars);
    }

    /** The variables of the block currently rendering for this view, or the view's own vars. */
    private function currentScope(FormView $view): array
    {
        $stack = $this->variableStack[spl_object_id($view)] ?? [];

        return [] === $stack ? $view->vars : $stack[count($stack) - 1];
    }

    private function popScope(int $viewId): void
    {
        array_pop($this->variableStack[$viewId]);
        if ([] === $this->variableStack[$viewId]) {
            unset($this->variableStack[$viewId]);
        }
    }

    /** View vars with $vars on top; "attr" and "label_attr" are merged key by key instead of replaced. */
    private function mergeVars(array $base, array $vars): array
    {
        foreach (['attr', 'label_attr', 'row_attr'] as $name) {
            if (isset($vars[$name], $base[$name]) && is_array($vars[$name]) && is_array($base[$name])) {
                $vars[$name] = array_replace($base[$name], $vars[$name]);
            }
        }

        return array_replace($base, $vars);
    }

    /** @return array{0: ?ThemeInterface, 1: int} the theme and the level (index into $hierarchy) it has */
    private function findThemeInHierarchy(FormView $view, array $hierarchy, int $level): array
    {
        for (; $level >= 0; --$level) {
            $theme = $this->findTheme($view, $hierarchy[$level]);
            if (null !== $theme) {
                return [$theme, $level];
            }
        }

        return [null, -1];
    }

    private function findTheme(FormView $view, string $blockName): ?ThemeInterface
    {
        // The nearest view (self or ancestor) with an explicit useDefaultThemes flag decides.
        // Symfony only honours the flag of the root view; this is a superset of that behaviour.
        $useDefaults = null;

        for ($current = $view; null !== $current; $current = $current->parent) {
            $useDefaults ??= $this->useDefaultThemes[spl_object_id($current)] ?? null;
            $themes = $this->themes[spl_object_id($current)] ?? [];
            for ($i = count($themes) - 1; $i >= 0; --$i) {
                if ($themes[$i]->hasBlock($blockName)) {
                    return $themes[$i];
                }
            }
        }

        if ($useDefaults ?? true) {
            for ($i = count($this->defaultThemes) - 1; $i >= 0; --$i) {
                if ($this->defaultThemes[$i]->hasBlock($blockName)) {
                    return $this->defaultThemes[$i];
                }
            }
        }

        return null;
    }
}
