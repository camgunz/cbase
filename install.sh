#!/bin/sh

set -e

BUILD_DIR='cbuild'

pushd ${BUILD_DIR} > /dev/null
make install
popd > /dev/null
