#!/usr/bin/env bash
# Runs PHP against a built phalcon.so. Usage:
#   ./run.sh tools/trace.php          # any script
#   ./run.sh test [phpunit args]      # the prototype test suite
# PHALCON_SO overrides the extension path (default: this checkout's ext/modules/phalcon.so, else
# the sibling clone ~/projects/github.com/phalcon/cphalcon where the 7.0.x build lives).
cd "$(dirname "$0")" || exit 1
ROOT="$(cd ../../../.. && pwd)"
SO="${PHALCON_SO:-$ROOT/ext/modules/phalcon.so}"
[ -f "$SO" ] || SO="$HOME/projects/github.com/phalcon/cphalcon/ext/modules/phalcon.so"
if [ "$1" = "test" ]; then
    shift
    exec php -d extension="$SO" "$ROOT/vendor/bin/phpunit" -c phpunit.xml "$@"
fi
exec php -d extension="$SO" "$@"
