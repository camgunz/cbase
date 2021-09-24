#!/bin/bash

CC=clang

# echo '-Os'
# $CC -o checked_math -Os -DHAVE_CLOCK_MONOTONIC \
#   main.c \
#   rand.c \
#   timing.c \
#   checked_signed_add.c \
#   checked_unsigned_add.c \
#   checked_signed_sub.c \
#   checked_unsigned_sub.c \
#   checked_signed_mul.c \
#   checked_unsigned_mul.c \
#   signed_add_tests.c \
#   unsigned_add_tests.c \
#   signed_sub_tests.c \
#   unsigned_sub_tests.c \
#   signed_mul_tests.c \
#   unsigned_mul_tests.c \
#   signed_add_benchmarks.c \
#   unsigned_add_benchmarks.c \
#   && ./checked_math

echo '-O3'
$CC -o checked_math -O3 -DHAVE_CLOCK_MONOTONIC \
  main.c \
  rand.c \
  timing.c \
  checked_signed_add.c \
  checked_unsigned_add.c \
  checked_signed_sub.c \
  checked_unsigned_sub.c \
  checked_signed_mul.c \
  checked_unsigned_mul.c \
  signed_add_tests.c \
  unsigned_add_tests.c \
  signed_sub_tests.c \
  unsigned_sub_tests.c \
  signed_mul_tests.c \
  unsigned_mul_tests.c \
  signed_add_benchmarks.c \
  unsigned_add_benchmarks.c \
  && ./checked_math

