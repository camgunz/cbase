#!/bin/sh

set -e

BUILD_TYPE=Debug

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. && make && ../gen_gcov.sh

