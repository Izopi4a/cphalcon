#!/usr/bin/env bash
#
# Builds the Phalcon extension from this checkout's ext/ into prototype/.build/<flavor>/.
#
#   ./build.sh stock     HEAD's ext/ unchanged: what users run today
#   ./build.sh patched   HEAD's ext/ + the patches/NN-*.patch series (one per
#                        feature, applied in order), with the Volt scanner and
#                        parser regenerated (bin/genparsers.sh steps)
#
# Needs phpize, a C compiler and re2c. Takes about 3 minutes with -j$(nproc).
# Nothing in the repository is modified; the build happens in .build/.

set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO="$(git -C "$HERE" rev-parse --show-toplevel)"
FLAVOR="${1:-patched}"
OUT="$HERE/.build/$FLAVOR"
JOBS="${JOBS:-$(nproc)}"

case "$FLAVOR" in
    stock|patched) ;;
    *) echo "usage: $0 [stock|patched]" >&2; exit 2 ;;
esac

rm -rf "$OUT"
mkdir -p "$OUT"
git -C "$REPO" archive HEAD ext | tar -x -C "$OUT"

if [ "$FLAVOR" = "patched" ]; then
    for series in "$HERE"/patches/[0-9][0-9]-*.patch; do
        (cd "$OUT" && patch -p1 --quiet < "$series") || { echo "failed: $series" >&2; exit 1; }
    done

    # lemon.c predates C23 prototypes; gnu99 builds it with current compilers
    "${CC:-gcc}" -std=gnu99 -w "$REPO/3rdparty/lemon/lemon.c" -o "$OUT/lemon"

    (
        cd "$OUT/ext/phalcon/mvc/view/engine/volt"

        if [ "$(re2c --vernum)" -gt 9999 ]; then
            re2c -W --no-debug-info --no-generation-date -o scanner.c scanner.re
        else
            re2c --no-debug-info --no-generation-date -o scanner.c scanner.re
        fi
        sed -i 's/YY/VV/g; s/yy/vv/g' scanner.c

        cp "$REPO/3rdparty/lemon/lempar.c" .
        "$OUT/lemon" -s parser.php.lemon
        { echo '#include "php_phalcon.h"'; cat parser.php.c base.c; } > parser.c
        sed -i 's|#line|//|g; s/define TOKEN/define VTOKEN/g; s/YY/VV/g; s/yy/vv/g' parser.c
        rm -f lempar.c parser.php.out
    )
fi

cd "$OUT/ext"
phpize > /dev/null
CFLAGS="${CFLAGS:--O1 -g0}" ./configure --enable-phalcon > /dev/null
make -j"$JOBS" > make.log 2>&1 || { tail -40 make.log; exit 1; }

echo "$OUT/ext/modules/phalcon.so"
