#!/bin/bash

CC=clang

echo '-O0'
$CC -o checked_math -O0 \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-O0 Overflowing'
$CC -o checked_math -O0 -D_MAKE_OVERFLOW \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-O2'
$CC -o checked_math -O2 \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-O2 Overflowing'
$CC -o checked_math -O2 -D_MAKE_OVERFLOW \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-O3'
$CC -o checked_math -O3 \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-O3 Overflowing'
$CC -o checked_math -O3 -D_MAKE_OVERFLOW \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-Os'
$CC -o checked_math -Os \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-Os Overflowing'
$CC -o checked_math -Os -D_MAKE_OVERFLOW \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math
