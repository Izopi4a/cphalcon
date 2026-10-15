<?php
declare(strict_types=1);

namespace Phalcon\Form\View;

use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\View\Theme\ThemeInterface;

/**
 * Renders FormView trees through themes (Symfony's FormRenderer + FormRendererEngine folded
 * into one service; the Volt engine of the RFC would be a second ThemeInterface implementation).
 */
interface FormRendererInterface
{
    /**
     * Attach themes to a view. They are searched (last added first) for that view and all of
     * its descendants, before the parents' themes and the renderer's default themes.
     *
     * @param ThemeInterface|list<ThemeInterface> $themes
     * @param bool $useDefaultThemes false: the default themes are not used for this view and its
     *                               subtree (the nearest view with an explicit flag decides)
     */
    public function setTheme(FormView $view, ThemeInterface|array $themes, bool $useDefaultThemes = true): void;

    /**
     * Renders one block by its exact name ("form_start"). Vars are the view's vars with $vars
     * on top ("attr" and "label_attr" merged key by key).
     *
     * @throws LogicException when no theme defines the block
     */
    public function renderBlock(FormView $view, string $blockName, array $vars = []): string;

    /**
     * Renders the most specific block for a suffix: block_prefixes are tried from last to
     * first as "{prefix}_{suffix}" ("_ticket_email_widget", "email_widget", "text_widget",
     * "form_widget"). Calling it again for the same view and suffix while that block renders
     * resumes one level up, so a block can delegate to its parent type's block.
     *
     * "row" and "widget" are render-once: the view is marked rendered afterwards and a second
     * call throws.
     *
     * @throws BadMethodCallException when a "row"/"widget" of an already rendered view is asked
     * @throws LogicException when no block exists in the hierarchy
     */
    public function searchAndRenderBlock(FormView $view, string $blockNameSuffix, array $vars = []): string;

    /**
     * Explicit form of the recursive searchAndRenderBlock() call: render the next block up the
     * hierarchy for a suffix that is currently being rendered for this view.
     *
     * @throws LogicException when no block for $blockNameSuffix is being rendered for the view
     */
    public function renderParentBlock(FormView $view, string $blockNameSuffix, array $vars = []): string;

    /** "first_name" / "firstName" -> "First name" */
    public function humanize(string $text): string;

    public function renderStart(FormView $view, array $vars = []): string;

    public function renderEnd(FormView $view, array $vars = []): string;

    public function renderRow(FormView $view, array $vars = []): string;

    public function renderWidget(FormView $view, array $vars = []): string;

    public function renderLabel(FormView $view, ?string $label = null, array $vars = []): string;

    public function renderErrors(FormView $view, array $vars = []): string;

    public function renderHelp(FormView $view, array $vars = []): string;

    public function renderRest(FormView $view, array $vars = []): string;
}
