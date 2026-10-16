<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Prototype;

use Phalcon\Mvc\View\Engine\Volt\Compiler;
use Phalcon\VoltNfr\Node;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

/**
 * AST from the patched parser (the patches/ series), through the stock
 * Compiler::parse(). Shows the node shapes a Compiler.zep implementation
 * would handle.
 */
final class ParserTest extends TestCase
{
    private function parse(string $source): array
    {
        return self::strip((new Compiler())->parse($source));
    }

    private static function strip(array $node): array
    {
        unset($node['file'], $node['line']);
        foreach ($node as $key => $value) {
            if (is_array($value)) {
                $node[$key] = self::strip($value);
            }
        }

        return $node;
    }

    public function testNestedBlocks(): void
    {
        $this->assertSame([[
            'type'             => Node::BLOCK,
            'name'             => 'outer',
            'block_statements' => [
                ['type' => Node::RAW_FRAGMENT, 'value' => 'a'],
                ['type' => Node::BLOCK, 'name' => 'inner', 'block_statements' => [['type' => Node::RAW_FRAGMENT, 'value' => 'b']]],
            ],
        ]], $this->parse('{% block outer %}a{% block inner %}b{% endblock %}{% endblock %}'));
    }

    public function testBlockInsideIf(): void
    {
        $ast = $this->parse('{% if x %}{% block b %}y{% endblock %}{% endif %}');

        $this->assertSame(Node::BLOCK, $ast[0]['true_statements'][0]['type']);
    }

    /**
     * "block" is a function name everywhere except right after "{%".
     */
    public function testBlockAsAFunctionName(): void
    {
        $ast = $this->parse('{{ block("title") }}{%- block x -%}{%- endblock -%}');

        $this->assertSame(['type' => Node::IDENTIFIER, 'value' => 'block'], $ast[0]['expr']['name']);
        $this->assertSame(Node::BLOCK, $ast[1]['type']);
    }

    /**
     * #12846: a property named "block" (after ".") is an identifier too.
     */
    public function testBlockAsAPropertyName(): void
    {
        $this->assertSame('<?= $article->block ?>', (new Compiler())->compileString('{{ article.block }}'));
    }

    /**
     * @return array<string, array{string, int}>
     */
    public static function expressions(): array
    {
        return [
            '??'     => ['{{ a ?? b }}', Node::COALESCE],
            '?.'     => ['{{ a?.b }}', Node::NULLSAFE],
            'is not' => ['{{ a is not premium }}', Node::ISNOT],
            '!='     => ['{{ a != b }}', Node::NOTEQUALS],
            'is'     => ['{{ a is premium }}', Node::IS],
        ];
    }

    #[DataProvider('expressions')]
    public function testExpressionNodes(string $source, int $type): void
    {
        $this->assertSame($type, $this->parse($source)[0]['expr']['type']);
    }

    public function testCoalesceBindsLooserThanComparisonAndIsRightAssociative(): void
    {
        $expr = $this->parse('{{ a ?? b ?? c == d }}')[0]['expr'];

        $this->assertSame(Node::COALESCE, $expr['type']);
        $this->assertSame(Node::COALESCE, $expr['right']['type']);
        $this->assertSame(272, $expr['right']['right']['type']); // EQUALS
    }

    public function testNullSafeMethodCallIsACallOnANullSafeNode(): void
    {
        $expr = $this->parse('{{ a?.b?.c(1) }}')[0]['expr'];

        $this->assertSame(Node::FCALL, $expr['type']);
        $this->assertSame(Node::NULLSAFE, $expr['name']['type']);
        $this->assertSame(Node::NULLSAFE, $expr['name']['left']['type']);
    }

    public function testDoubleLiteralIsNotANullSafeToken(): void
    {
        $this->assertSame(366, $this->parse('{{ a ? 0.5 : 1 }}')[0]['expr']['type']); // TERNARY
    }

    public function testEmbed(): void
    {
        $ast = $this->parse('{% embed "card.volt" with ["t": 1] %}{% block body %}x{% endblock %}{% endembed %}');

        $this->assertSame(Node::EMBED, $ast[0]['type']);
        $this->assertSame('card.volt', $ast[0]['path']['value']);
        $this->assertSame(Node::ARRAY, $ast[0]['params']['type']);
        $this->assertSame('body', $ast[0]['block_statements'][0]['name']);
    }

    public function testSetCaptureNextToAssignment(): void
    {
        $ast = $this->parse('{% set x %}hi{% endset %}{% set y = 1 %}');

        $this->assertSame(['type' => Node::SET_CAPTURE, 'name' => 'x', 'block_statements' => [['type' => Node::RAW_FRAGMENT, 'value' => 'hi']]], $ast[0]);
        $this->assertSame(306, $ast[1]['type']); // SET
    }

    public function testChildTemplatesStillOnlyContainBlocks(): void
    {
        $this->expectExceptionMessage('Child templates only may contain blocks');

        (new Compiler())->parse('{% extends "a.volt" %}text outside{% block a %}{% endblock %}');
    }
}
