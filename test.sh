#!/bin/sh

set -e

BUILD_DIR='cbuild'

pushd ${BUILD_DIR} > /dev/null
./cbase_test
popd > /dev/null
