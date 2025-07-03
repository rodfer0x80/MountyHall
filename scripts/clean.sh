#!/bin/sh

set -o errexit
set -o nounset
set -o pipefail
if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

rm -rf ./build/* ./build/.ninja_log ./build/.ninja_deps \
  ./data/* \
  ./tests/Testing \
