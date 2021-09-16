#!/bin/bash

CC=clang

echo '-Os'
$CC -o checked_math -Os \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  checked_signed_sub.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_sub_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-O0'
$CC -o checked_math -O0 \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  checked_signed_sub.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_sub_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-O2'
$CC -o checked_math -O2 \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  checked_signed_sub.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_sub_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math

echo '-O3'
$CC -o checked_math -O3 \
  main.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  checked_signed_sub.c \
  rand.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_sub_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  timing.c && ./checked_math
