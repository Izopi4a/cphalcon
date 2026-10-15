<?php
declare(strict_types=1);

namespace Phalcon\Form\View\Theme;

use Phalcon\Form\View\FormRendererInterface;
use Phalcon\Form\View\FormView;

/**
 * A set of named blocks ("form_row", "email_widget", "_ticket_title_label", ...). The default
 * theme is code (one method per block); a Volt theme would map blocks to compiled macros.
 */
interface ThemeInterface
{
    public function hasBlock(string $blockName): bool;

    /**
     * Renders a block this theme has. $vars are the fully merged variables of the current
     * scope; nested blocks are rendered through $renderer (so other themes can override them).
     */
    public function renderBlock(string $blockName, FormRendererInterface $renderer, FormView $view, array $vars): string;
}
