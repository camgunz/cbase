#!/bin/sh

BUILD_DIR="CMakeFiles/cbase_test.dir/src"
COVERAGE_DIR="coverage"

./cbase_test

lcov -q -c -i -d ${BUILD_DIR} -o base_coverage.info
lcov -q -c -d ${BUILD_DIR} -o test_coverage.info
lcov -q -a base_coverage.info -a test_coverage.info -o total_coverage.info
lcov -q --summary total_coverage.info
mkdir -p ${COVERAGE_DIR}
genhtml -q -o ${COVERAGE_DIR} total_coverage.info

