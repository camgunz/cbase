#pragma once

#ifndef _CBASE_EQUAL_H__
#define _CBASE_EQUAL_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stdint.h>

CBASE_API_STATIC
void cb_cstr_equal(const char *a, const char *b) {
  return strcmp(a, b) == 0;
}

CBASE_API_STATIC
void cb_int_equal(intmax_t a, intmax_t b) {
  return a == b;
}

CBASE_API_STATIC
void cb_uint_equal(uintmax_t a, uintmax_t b) {
  return a == b;
}

#endif
