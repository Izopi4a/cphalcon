<?php
declare(strict_types=1);

namespace Phalcon\Form\View\Theme;

use Phalcon\Form\View\FormRendererInterface;
use Phalcon\Form\View\FormView;

/**
 * Ad-hoc theme: block name => callable(FormRendererInterface $renderer, FormView $view, array $vars): string.
 * Handy for tests and for one-off overrides placed on a single view with FormRenderer::setTheme().
 */
final class ArrayTheme implements ThemeInterface
{
    /** @var array<string, callable> */
    private array $blocks = [];

    /** @param array<string, callable> $blocks */
    public function __construct(array $blocks = [])
    {
        foreach ($blocks as $name => $block) {
            $this->setBlock($name, $block);
        }
    }

    public function setBlock(string $blockName, callable $block): static
    {
        $this->blocks[$blockName] = $block;

        return $this;
    }

    public function hasBlock(string $blockName): bool
    {
        return isset($this->blocks[$blockName]);
    }

    public function renderBlock(string $blockName, FormRendererInterface $renderer, FormView $view, array $vars): string
    {
        return (string) ($this->blocks[$blockName])($renderer, $view, $vars);
    }
}
