#!/bin/sh

set -o errexit
set -o nounset
set -o pipefail
if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

PROJECT_NAME="MountyHall"

./build/$PROJECT_NAME -n 2000000 -o ./data/output.csv
