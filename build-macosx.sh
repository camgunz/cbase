#!/bin/sh

set -e

BUILD_DIR='cbuild'
BUILD_TYPE='Debug'
# BUILD_TYPE='Release'

mkdir -p ${BUILD_DIR}

pushd ${BUILD_DIR} > /dev/null

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -DBIN_DIR=~/local/bin \
      -DLIB_DIR=~/local/lib \
      -DINCLUDE_DIR=~/local/include \
      -DSHARE_DIR=~/local/share \
      -DMPDECIMAL_INCLUDE_DIR=/Users/cgunyon/local/include \
      -DMPDECIMAL_LIBRARIES=/Users/cgunyon/local/lib/libmpdec.a \
      ..

make

popd > /dev/null

