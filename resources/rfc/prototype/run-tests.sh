#!/usr/bin/env bash
# Runs the prototype tests against the locally built phalcon.so (needs ext/modules/phalcon.so).
cd "$(dirname "$0")" || exit 1
ROOT="$(cd ../../.. && pwd)"
exec php -d extension="$ROOT/ext/modules/phalcon.so" "$ROOT/vendor/bin/phpunit" -c phpunit.xml "$@"
