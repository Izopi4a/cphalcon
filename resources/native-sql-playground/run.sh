#!/usr/bin/env bash
# Web UI on http://127.0.0.1:8085 (PORT=... to change)
DIR="$(cd "$(dirname "$0")" && pwd)"
exec "$DIR/spin" -S "127.0.0.1:${PORT:-8085}" -t "$DIR/public" "$DIR/public/index.php"
