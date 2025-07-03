#!/bin/sh

set -o errexit
set -o nounset
set -o pipefail
if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

mkdir -p ./data/tests
cd ./build
ctest --output-on-failure
cd ..
rm -rf ./data/tests
