#!/usr/bin/env bash
#
# Builds the extension once per parser feature, each feature alone on top of
# upstream, and runs a parse smoke test plus the upstream Volt unit suite
# against it. Catches C-level breakage that the lemon check in cook.py cannot.
#
#   ./tools/check-features.sh [feature ...]     default: every feature
#
# Needs ./build.sh stock first: the stock build is copied and only the Volt
# parser objects are rebuilt, so each feature takes seconds, not minutes.

set -uo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
REPO="$(git -C "$HERE" rev-parse --show-toplevel)"
STOCK="$HERE/.build/stock"
WORK="$HERE/.build/features"
FEATURES=("$@")
[ ${#FEATURES[@]} -gt 0 ] || FEATURES=(nested-blocks block-function is-not null-coalescing null-safe embed set-capture)

declare -A SMOKE=(
    [nested-blocks]='{% block a %}1{% block b %}2{% endblock %}{% endblock %}{% if x %}{% block c %}3{% endblock %}{% endif %}'
    [block-function]='{{ block("title") }}{{ article.block }}{%- block x -%}{%- endblock -%}'
    [is-not]='{{ a is not premium }}{{ a is not defined }}{{ a != b }}'
    [null-coalescing]='{{ a ?? b ?? "c" }}'
    [null-safe]='{{ a?.b?.c(1) }}{{ x ? 0.5 : 1 }}'
    [embed]='{% embed "card.volt" with ["t": 1] %}{% block body %}x{% endblock %}{% endembed %}'
    [set-capture]='{% set x %}captured{% endset %}{% set y = 1 %}'
)

[ -f "$STOCK/ext/modules/phalcon.so" ] || { echo "run ./build.sh stock first" >&2; exit 1; }

rm -rf "$WORK"
cp -a "$STOCK" "$WORK"
# phpize/configure wrote absolute paths into the build files: point them at the copy
grep -rIl --exclude-dir=.libs "$STOCK" "$WORK/ext" | xargs sed -i "s|$STOCK|$WORK|g"
"${CC:-gcc}" -std=gnu99 -w "$REPO/3rdparty/lemon/lemon.c" -o "$WORK/lemon"
VOLT="$WORK/ext/phalcon/mvc/view/engine/volt"
for f in scanner.h scanner.re base.c parser.php.lemon parser.php.inc.h scanner.c parser.c parser.php.c parser.php.h; do
    cp "$VOLT/$f" "$WORK/pristine-$f"
done

status=0
for feature in "${FEATURES[@]}"; do
    for f in scanner.h scanner.re base.c parser.php.lemon parser.php.inc.h scanner.c parser.c parser.php.c parser.php.h; do
        cp "$WORK/pristine-$f" "$VOLT/$f"
    done

    python3 -I "$HERE/tools/cook.py" "$feature" --out "$WORK/patch-$feature" > /dev/null || { echo "$feature: cook failed"; status=1; continue; }
    (cd "$WORK" && patch -p1 --quiet < "$WORK/patch-$feature/combined.patch") || { echo "$feature: patch failed"; status=1; continue; }

    (
        cd "$VOLT"
        re2c -W --no-debug-info --no-generation-date -o scanner.c scanner.re
        sed -i 's/YY/VV/g; s/yy/vv/g' scanner.c
        cp "$REPO/3rdparty/lemon/lempar.c" .
        "$WORK/lemon" -s parser.php.lemon > /dev/null
        { echo '#include "php_phalcon.h"'; cat parser.php.c base.c; } > parser.c
        sed -i 's|#line|//|g; s/define TOKEN/define VTOKEN/g; s/YY/VV/g; s/yy/vv/g' parser.c
        rm -f lempar.c parser.php.out
    )

    if ! (cd "$WORK/ext" && make -j"$(nproc)" > "$WORK/make-$feature.log" 2>&1); then
        echo "$feature: BUILD FAILED (see $WORK/make-$feature.log)"; status=1; continue
    fi

    SO="$WORK/ext/modules/phalcon.so"
    smoke=$(php -d extension="$SO" -r '$c = new Phalcon\Mvc\View\Engine\Volt\Compiler(); try { $c->parse($argv[1]); echo "parses"; } catch (Throwable $e) { echo "PARSE ERROR: ", $e->getMessage(); }' "${SMOKE[$feature]}")
    suite=$(cd "$REPO" && php -d extension="$SO" vendor/bin/phpunit -c resources/phpunit.xml.dist tests/unit/Mvc/View/Engine/Volt 2>&1 | grep -E '^(OK|Tests:)')
    printf "%-16s build ok   smoke: %-8s   upstream Volt suite: %s\n" "$feature" "$smoke" "$suite"
    [ "$smoke" = "parses" ] || status=1
done

exit $status
