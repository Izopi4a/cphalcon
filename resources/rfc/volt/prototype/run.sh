#!/usr/bin/env bash
#
# Runs PHP against a built phalcon.so. Build the extensions first with ./build.sh.
#
#   ./run.sh test [phpunit args]        today's behaviour (stock .so) + the prototype (patched .so)
#   ./run.sh bench [calls]              per-call cost of runtime functions, clean PHP
#   ./run.sh tools/trace.php            any script, against the patched .so
#   STOCK=1 ./run.sh script.php         the same against the stock .so
#
# PHALCON_SO overrides the extension path.

cd "$(dirname "$0")" || exit 1
ROOT="$(cd ../../../.. && pwd)"
STOCK_SO=".build/stock/ext/modules/phalcon.so"
PATCHED_SO=".build/patched/ext/modules/phalcon.so"

if [ "$1" = "test" ]; then
    shift
    for so in "$STOCK_SO" "$PATCHED_SO"; do
        [ -f "$so" ] || { echo "missing $so: run ./build.sh stock && ./build.sh patched" >&2; exit 1; }
    done
    # tests/Today pins what users get today; tests/Prototype needs the patched parser
    php -d extension="$STOCK_SO" "$ROOT/vendor/bin/phpunit" -c phpunit.xml --testsuite today "$@" || exit $?
    exec php -d extension="$PATCHED_SO" "$ROOT/vendor/bin/phpunit" -c phpunit.xml --testsuite prototype "$@"
fi

# ./run.sh bench [calls]: timings need a clean PHP. The system CLI loads Xdebug and pcov, which
# slow every call and disable the JIT; -n skips all ini files and loads only what Phalcon needs.
if [ "$1" = "bench" ]; then
    shift
    exec php -n -d memory_limit=-1 -d extension=pdo -d extension=mbstring -d extension=ctype \
        -d extension="$PATCHED_SO" -d opcache.enable_cli=1 -d opcache.jit=tracing -d opcache.jit_buffer_size=64M \
        tools/bench.php "$@"
fi

if [ -n "$STOCK" ]; then
    SO="${PHALCON_SO:-$STOCK_SO}"
else
    SO="${PHALCON_SO:-$PATCHED_SO}"
fi
[ -f "$SO" ] || { echo "missing $SO: run ./build.sh" >&2; exit 1; }

exec php -d extension="$SO" "$@"
