<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr;

use Phalcon\Mvc\View\Engine\Volt\Compiler as VoltCompiler;
use Phalcon\Mvc\View\Engine\Volt\Exceptions\TemplateFileNotFound;
use Phalcon\Mvc\View\Exception as ViewException;
use Phalcon\Mvc\ViewBaseInterface;
use Phalcon\VoltNfr\Cache\Dependencies;
use Phalcon\VoltNfr\Inheritance\Resolver;
use Phalcon\VoltNfr\Runtime\Registry;

/**
 * The stock Volt compiler with the NFR changes layered on top:
 *
 * - compileSource(): inheritance is resolved on the AST (Inheritance\Resolver)
 *   before compiling, so the stock statementList() only sees a flat AST.
 *   That is what allows nested blocks, blocks inside if/for, block(), embed
 *   and dynamic extends, and it removes the serialized "%%e%%" block cache.
 * - compile()/compileFile(): a dependency sidecar per compiled file, so
 *   editing a parent or an include recompiles the templates that inline it.
 * - compileEcho(): output that is already safe (raw, escaping filters,
 *   safe runtime functions) is not escaped a second time by autoescape.
 * - compileInclude(): include "x" with [...] stays a compiled include with
 *   its own scope instead of switching to a runtime partial.
 * - NodeCompiler (a regular compiler extension) compiles the runtime
 *   functions/filters/tests and the new AST nodes (??, ?., is not, set capture).
 *
 * In a real implementation all of this goes into Compiler.zep itself.
 */
class Compiler extends VoltCompiler
{
    public const VERSION = 'volt-nfr-1';

    private Registry $registry;

    /** @var array<string, int> files inlined into the template being compiled */
    private array $dependencies = [];

    private ?string $extendsOverride = null;

    public function __construct(?ViewBaseInterface $view = null, ?Registry $registry = null)
    {
        parent::__construct($view);

        $this->registry = $registry ?? new Registry();
        $this->addExtension(new NodeCompiler($this, $this->registry));
    }

    public function getRegistry(): Registry
    {
        return $this->registry;
    }

    /**
     * Unknown "is" tests are a compile error instead of compiling to "==".
     */
    public function isStrictTests(): bool
    {
        return (bool) ($this->getOptions()['strictTests'] ?? true);
    }

    /**
     * What the compiled output depends on besides files.
     */
    public function getSignature(): string
    {
        $options = $this->getOptions();

        return self::VERSION . '|' . $this->registry->getSignature()
            . '|autoescape=' . var_export((bool) ($options['autoescape'] ?? false), true)
            . '|strictTests=' . var_export($this->isStrictTests(), true);
    }

    // ---------------------------------------------------------------- compile

    public function compile(string $templatePath, bool $extendsMode = false)
    {
        $compilation = parent::compile($templatePath, $extendsMode);

        // null: the stock compiler reused the compiled file. With stat on,
        // also check what was inlined into it.
        $options = $this->getOptions();
        if ($compilation === null && ($options['stat'] ?? true) !== false) {
            $compiled = $this->getCompiledTemplatePath();
            if (Dependencies::staleReason($compiled, $this->getSignature()) !== null) {
                $compilation = $this->compileFile($templatePath, $compiled, $extendsMode);
            }
        }

        return $compilation;
    }

    public function compileFile(string $path, string $compiledPath, bool $extendsMode = false)
    {
        $this->dependencies = [];
        $compilation = parent::compileFile($path, $compiledPath, $extendsMode);

        Dependencies::write($compiledPath, $this->dependencies, $this->getSignature());

        return $compilation;
    }

    protected function compileSource(string $viewCode, bool $extendsMode = false): array|string
    {
        // the state reset the stock compileSource() does
        $this->extended       = false;
        $this->extendedBlocks = false;
        $this->blocks         = null;
        $this->level          = 0;
        $this->foreachLevel   = 0;
        $this->blockLevel     = 0;
        $this->exprLevel      = 0;

        $options = $this->getOptions();
        if (isset($options['autoescape'])) {
            $this->autoescape = (bool) $options['autoescape'];
        }

        $path = is_string($this->currentPath) && $this->currentPath !== '' ? $this->currentPath : 'eval code';
        $ast  = $this->parseSource($viewCode, $path);
        $flat = (new Resolver($this))->resolve($ast, $path);

        return $this->statementList($flat);
    }

    /**
     * Compiles a child template against a parent chosen at render time
     * ({% extends layoutVar %}). One compiled file per (child, parent) pair.
     */
    public function compileVariant(string $childPath, string $parentName): string
    {
        $parentPath = $this->resolveTemplatePath($parentName, $childPath);
        $options    = $this->getOptions();
        $dir        = is_string($options['path'] ?? null) && $options['path'] !== ''
            ? $options['path']
            : sys_get_temp_dir() . DIRECTORY_SEPARATOR;
        $variant    = $dir . 'variant%%' . sha1($childPath . '|' . $parentPath) . '.php';

        clearstatcache();
        $stale = !is_file($variant)
            || ($options['always'] ?? false)
            || (($options['stat'] ?? true) !== false && (
                filemtime($childPath) >= filemtime($variant)
                || Dependencies::staleReason($variant, $this->getSignature()) !== null
            ));

        if ($stale) {
            $sub                  = clone $this;
            $sub->extendsOverride = $parentPath;
            $sub->compileFile($childPath, $variant);
        }

        return $variant;
    }

    // ------------------------------------------------------------ statements

    public function compileEcho(array $statement): string
    {
        if ($this->autoescape && isset($statement['expr']) && $this->isSafeExpression($statement['expr'])) {
            return '<?= ' . $this->expression($statement['expr']) . ' ?>';
        }

        return parent::compileEcho($statement);
    }

    public function compileInclude(array $statement): string
    {
        $pathExpr = $statement['path'] ?? null;
        $final    = ($pathExpr['type'] ?? null) === Node::STRING ? $this->findTemplate($pathExpr['value']) : null;

        // not a literal path to a Volt file: the runtime partial, as today
        if ($final === null) {
            return parent::compileInclude($statement);
        }

        $sub         = clone $this;
        $compilation = $sub->compile($final, false);
        if ($compilation === null) {
            $compilation = file_get_contents($sub->getCompiledTemplatePath());
        }

        $this->addDependency($final);
        foreach (Dependencies::read($sub->getCompiledTemplatePath())['files'] ?? [] as $file => $mtime) {
            $this->dependencies[$file] = $mtime;
        }

        if (!isset($statement['params'])) {
            return $compilation;
        }

        // include ... with [...]: the current variables plus the parameters,
        // in a scope of its own (Twig semantics), instead of $this->partial()
        return '<?php (function (array $__volt_scope) { extract($__volt_scope); ?>'
            . $compilation
            . '<?php })(array_merge(get_defined_vars(), ' . $this->expression($statement['params']) . ')); ?>';
    }

    // --------------------------------------------- services for the resolver

    /**
     * Compiles statements in the current state (for nodes that wrap a body).
     */
    public function compileStatements(array $statements): string
    {
        return $this->statementList($statements);
    }

    public function takeExtendsOverride(): ?string
    {
        $override              = $this->extendsOverride;
        $this->extendsOverride = null;

        return $override;
    }

    public function resolveTemplatePath(string $name, string $relativeTo): string
    {
        $saved             = $this->currentPath;
        $this->currentPath = $relativeTo;

        try {
            $final = $this->getFinalPath($name);
        } finally {
            $this->currentPath = $saved;
        }

        if (!is_file($final)) {
            throw new TemplateFileNotFound($final);
        }

        return $final;
    }

    public function parseFile(string $path): array
    {
        $this->addDependency($path);

        return $this->parseSource((string) file_get_contents($path), $path);
    }

    public function parseSource(string $code, string $path): array
    {
        try {
            $ast = $this->parse($code);
        } catch (ViewException $e) {
            throw new ViewException(str_replace('eval code', $path, $e->getMessage()), (int) $e->getCode(), $e);
        }

        return self::withFile($ast, $path);
    }

    /**
     * Puts the real file name into the AST. A plain recursive copy on
     * purpose: array_walk_recursive() by reference leaves IS_REFERENCE
     * elements behind, and the stock expression() does not dereference them
     * ("Cannot use a scalar value as an array", the same Zephir kernel gap as
     * referenced find() parameters on 7.0.x).
     */
    private static function withFile(array $node, string $path): array
    {
        foreach ($node as $key => $value) {
            if (is_array($value)) {
                $node[$key] = self::withFile($value, $path);
            } elseif ($key === 'file' && $value === 'eval code') {
                $node[$key] = $path;
            }
        }

        return $node;
    }

    public function addDependency(string $path): void
    {
        clearstatcache(true, $path);
        $this->dependencies[$path] = (int) filemtime($path);
    }

    // --------------------------------------------------------------- private

    private function findTemplate(string $name): ?string
    {
        $final = $this->getFinalPath($name);
        if (is_file($final)) {
            return $final;
        }

        return !str_ends_with($name, '.volt') && is_file($final . '.volt') ? $final . '.volt' : null;
    }

    /**
     * An expression whose result must not be HTML-escaped again.
     */
    private function isSafeExpression(array $expr): bool
    {
        if (($expr['type'] ?? null) === Node::PIPE) {
            $filter = $expr['right'];
            $name   = $filter['type'] === Node::FCALL ? ($filter['name']['value'] ?? null) : ($filter['value'] ?? null);

            return in_array($name, ['raw', 'e', 'escape', 'escape_js', 'escape_css', 'escape_attr', 'url_encode'], true)
                || ($this->registry->get('filter', (string) $name)?->isSafe() ?? false);
        }

        if (($expr['type'] ?? null) === Node::FCALL && ($expr['name']['type'] ?? null) === Node::IDENTIFIER) {
            $name = $expr['name']['value'];

            return in_array($name, ['content', 'get_content', 'partial'], true)
                || ($this->registry->get('function', $name)?->isSafe() ?? false);
        }

        return false;
    }
}
