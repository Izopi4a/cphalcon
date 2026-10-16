<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr;

/**
 * AST node types produced by the Volt parser (ext/.../volt/scanner.h).
 * 420+ are added by patches/volt-parser.patch.
 */
final class Node
{
    public const STRING       = 260;
    public const NULL         = 261;
    public const IDENTIFIER   = 265;
    public const NOTEQUALS    = 273;
    public const DOT          = 46;
    public const PIPE         = 124;
    public const IF           = 300;
    public const FOR          = 304;
    public const BLOCK        = 307;
    public const EXTENDS      = 310;
    public const IS           = 311;
    public const INCLUDE      = 313;
    public const AUTOESCAPE   = 317;
    public const MACRO        = 322;
    public const CALL         = 325;
    public const FCALL        = 350;
    public const RAW_FRAGMENT = 357;
    public const ECHO         = 359;
    public const ARRAY        = 360;
    public const SWITCH       = 411;

    // patches/volt-parser.patch
    public const COALESCE    = 420;
    public const NULLSAFE    = 421;
    public const ISNOT       = 422;
    public const EMBED       = 423;
    public const SET_CAPTURE = 426;

    /**
     * Not produced by the parser: raw PHP that the inheritance resolver
     * emits (scope wrappers, dynamic extends). Compiled by NodeCompiler.
     */
    public const PHP = 'nfr:php';

    /**
     * Keys under which a statement holds nested statement lists.
     */
    public const CONTAINERS = [
        'block_statements',
        'true_statements',
        'false_statements',
        'case_clauses',
        'caller',
    ];

    public static function php(string $code): array
    {
        return ['type' => self::PHP, 'code' => $code, 'file' => '', 'line' => 0];
    }

    public static function isCall(array $expr, string $name): bool
    {
        return ($expr['type'] ?? null) === self::FCALL
            && ($expr['name']['type'] ?? null) === self::IDENTIFIER
            && ($expr['name']['value'] ?? null) === $name;
    }
}
