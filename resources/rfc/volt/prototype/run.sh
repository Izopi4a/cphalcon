#!/usr/bin/env bash
#
# Runs PHP against a built phalcon.so. Build the extensions first with ./build.sh.
#
#   ./run.sh test [phpunit args]        today's behaviour (stock .so) + the prototype (patched .so)
#   ./run.sh tools/probe.php            any script, against the patched .so
#   STOCK=1 ./run.sh tools/probe.php    the same script against the stock .so
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

if [ -n "$STOCK" ]; then
    SO="${PHALCON_SO:-$STOCK_SO}"
else
    SO="${PHALCON_SO:-$PATCHED_SO}"
fi
[ -f "$SO" ] || { echo "missing $SO: run ./build.sh" >&2; exit 1; }

exec php -d extension="$SO" "$@"
