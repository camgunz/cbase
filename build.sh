#!/bin/sh

set -e

BUILD_DIR='cbuild'
BUILD_TYPE='Debug'
# BUILD_TYPE='Release'

# if [ -d ${BUILD_DIR} ]
# then
#     rm -rf ${BUILD_DIR}
# fi

mkdir -p ${BUILD_DIR}

pushd ${BUILD_DIR} > /dev/null

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -DBIN_DIR=~/local/bin \
      -DLIB_DIR=~/local/lib \
      -DINCLUDE_DIR=~/local/include \
      -DSHARE_DIR=~/local/share \
      -DMPDECIMAL_INCLUDE_DIR=${HOME}/local/include \
      -DMPDECIMAL_LIBRARIES=${HOME}/local/lib/libmpdec.so.2.4.2 \
      ..

make

popd > /dev/null

