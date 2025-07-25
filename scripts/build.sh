#!/bin/sh

set -o errexit
set -o nounset
set -o pipefail
if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

cd build 
/sbin/cmake -G Ninja .. 
/sbin/ninja 
cd ..
