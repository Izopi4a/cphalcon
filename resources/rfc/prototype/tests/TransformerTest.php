<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\ChoiceList\ArrayChoiceList;
use Phalcon\Form\Transformer\BooleanToStringTransformer;
use Phalcon\Form\Transformer\CallbackTransformer;
use Phalcon\Form\Transformer\ChoicesToValuesTransformer;
use Phalcon\Form\Transformer\ChoiceToValueTransformer;
use Phalcon\Form\Transformer\DateTimeImmutableToDateTimeTransformer;
use Phalcon\Form\Transformer\DateTimeToStringTransformer;
use Phalcon\Form\Transformer\DateTimeToTimestampTransformer;
use Phalcon\Form\Transformer\IntegerToStringTransformer;
use Phalcon\Form\Transformer\NumberToStringTransformer;
use Phalcon\Form\Transformer\ReversedTransformer;
use Phalcon\Form\Transformer\StringToFloatTransformer;
use Phalcon\Form\Transformer\TransformationFailedException;
use PHPUnit\Framework\TestCase;

final class TransformerTest extends TestCase
{
    public function testCallbackAndReversed(): void
    {
        $upper = new CallbackTransformer(strtoupper(...), strtolower(...));
        self::assertSame('AB', $upper->transform('ab'));
        self::assertSame('ab', $upper->reverseTransform('AB'));

        $reversed = new ReversedTransformer($upper);
        self::assertSame('ab', $reversed->transform('AB'));
        self::assertSame('AB', $reversed->reverseTransform('ab'));
    }

    public function testBooleanToString(): void
    {
        $t = new BooleanToStringTransformer('yes', [null, 'no']);
        self::assertSame('yes', $t->transform(true));
        self::assertNull($t->transform(false));
        self::assertNull($t->transform(null));
        self::assertTrue($t->reverseTransform('yes'));
        self::assertTrue($t->reverseTransform('anything'));
        self::assertFalse($t->reverseTransform(null), 'missing checkbox');
        self::assertFalse($t->reverseTransform('no'), 'configured false value');

        $this->expectException(TransformationFailedException::class);
        $t->reverseTransform(1);
    }

    public function testBooleanToStringTransformRejectsNonBool(): void
    {
        $this->expectException(TransformationFailedException::class);
        (new BooleanToStringTransformer('1'))->transform('1');
    }

    public function testChoiceToValue(): void
    {
        $list = new ArrayChoiceList(['Yes' => true, 'No' => false, 'Maybe' => null]);
        $t    = new ChoiceToValueTransformer($list);

        self::assertSame('1', $t->transform(true));
        self::assertSame('0', $t->transform(false));
        self::assertTrue($t->reverseTransform('1'));
        self::assertFalse($t->reverseTransform('0'));
        self::assertNull($t->reverseTransform(''), '"" with no matching choice is null');
        self::assertNull($t->reverseTransform(null));

        $this->expectException(TransformationFailedException::class);
        $t->reverseTransform('2');
    }

    public function testChoicesToValuesWithObjectChoicesUseIndices(): void
    {
        $a    = new \stdClass();
        $b    = new \stdClass();
        $list = new ArrayChoiceList(['A' => $a, 'B' => $b]);
        $t    = new ChoicesToValuesTransformer($list);

        self::assertSame(['0', '1'], $list->getValues());
        self::assertSame(['1'], $t->transform([$b]));
        self::assertSame([], $t->transform(null));
        self::assertSame([$a, $b], $t->reverseTransform(['0', '1']));
        self::assertSame([], $t->reverseTransform(null));

        $this->expectException(TransformationFailedException::class);
        $t->reverseTransform(['0', '9']);
    }

    public function testChoicesToValuesRejectsNonArray(): void
    {
        $this->expectException(TransformationFailedException::class);
        (new ChoicesToValuesTransformer(new ArrayChoiceList(['a' => 'a'])))->reverseTransform('a');
    }

    public function testNumberToString(): void
    {
        $t = new NumberToStringTransformer();
        self::assertSame('1.5', $t->transform(1.5));
        self::assertSame('42', $t->transform(42));
        self::assertSame('0.3', $t->transform(0.1 + 0.2), 'float noise trimmed');
        self::assertSame('', $t->transform(null));
        self::assertSame(1.5, $t->reverseTransform('1.5'));
        self::assertSame(1.5, $t->reverseTransform('1,5'), 'decimal comma accepted');
        self::assertSame(42.0, $t->reverseTransform('42'));
        self::assertNull($t->reverseTransform(''));
        self::assertNull($t->reverseTransform(null));

        $scaled = new NumberToStringTransformer(2, true);
        self::assertSame('1,234.57', $scaled->transform(1234.567));
        self::assertSame(1234.57, $scaled->reverseTransform('1,234.57'), 'grouping separator stripped');
        self::assertSame(1.23, $scaled->reverseTransform('1.234'), 'rounded to scale');

        $this->expectException(TransformationFailedException::class);
        $t->reverseTransform('abc');
    }

    public function testIntegerToString(): void
    {
        $t = new IntegerToStringTransformer();
        self::assertSame('7', $t->transform(7));
        self::assertSame(7, $t->reverseTransform('7'));
        self::assertSame(-3, $t->reverseTransform('-3'));
        self::assertNull($t->reverseTransform(''));

        $this->expectException(TransformationFailedException::class);
        $t->reverseTransform('1.5');
    }

    public function testStringToFloat(): void
    {
        $t = new StringToFloatTransformer(2);
        self::assertSame(1.5, $t->transform('1.5'));
        self::assertNull($t->transform(null));
        self::assertSame('1.50', $t->reverseTransform(1.5));

        $this->expectException(TransformationFailedException::class);
        $t->transform('x');
    }

    public function testDateTimeToString(): void
    {
        $t  = new DateTimeToStringTransformer('UTC', 'Europe/Berlin', 'Y-m-d H:i');
        $dt = new \DateTimeImmutable('2024-03-10 12:00', new \DateTimeZone('UTC'));

        self::assertSame('2024-03-10 13:00', $t->transform($dt), 'shown in the view timezone');
        self::assertSame('', $t->transform(null));

        $back = $t->reverseTransform('2024-03-10 13:00');
        self::assertInstanceOf(\DateTime::class, $back);
        self::assertSame('UTC', $back->getTimezone()->getName(), 'stored in the model timezone');
        self::assertSame('2024-03-10 12:00:00', $back->format('Y-m-d H:i:s'), 'unspecified seconds reset to 0');
        self::assertNull($t->reverseTransform(''));

        try {
            $t->reverseTransform('2024-02-31 10:00');
            self::fail('invalid day must throw');
        } catch (TransformationFailedException $e) {
            self::assertSame('Please enter a valid date.', $e->getInvalidMessage());
        }

        $this->expectException(TransformationFailedException::class);
        $t->transform('2024-03-10');
    }

    public function testDateTimeToTimestamp(): void
    {
        $t  = new DateTimeToTimestampTransformer('UTC', 'UTC');
        $dt = new \DateTime('@86400');

        self::assertSame(86400, $t->transform($dt));
        self::assertNull($t->transform(null));
        self::assertSame('1970-01-02', $t->reverseTransform(86400)->format('Y-m-d'));
        self::assertSame('1970-01-02', $t->reverseTransform('86400')->format('Y-m-d'));
        self::assertNull($t->reverseTransform(null));

        $this->expectException(TransformationFailedException::class);
        $t->reverseTransform('yesterday');
    }

    public function testDateTimeImmutableToDateTime(): void
    {
        $t         = new DateTimeImmutableToDateTimeTransformer();
        $immutable = new \DateTimeImmutable('2024-01-01 00:00:00');
        $mutable   = $t->transform($immutable);

        self::assertInstanceOf(\DateTime::class, $mutable);
        self::assertEquals($immutable, $t->reverseTransform($mutable));
        self::assertNull($t->transform(null));

        $this->expectException(TransformationFailedException::class);
        $t->transform($mutable);
    }
}
