#pragma once

#ifndef UTF8_CSTR_H__
#define UTF8_CSTR_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include <utf8proc.h>

#include "cbase/errors.h"
#include "cbase/alloc.h"
#include "cbase/rune.h"
#include "cbase/utf8.h"

/* [TODO] Bounds checking */

enum
{
    CBASE_UTF8_CSTR_EMPTY = 26000,
};

bool utf8_byte_is_sequence_start(char b);

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_validate_len_fast(const char *cstr, size_t *len) {
    return utf8_validate_len_fast(cstr, strlen(cstr), len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_validate_len(const char *cstr, size_t *len) {
    return utf8_validate_len(cstr, strlen(cstr), len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_validate_fast(const char *cstr) {
    return utf8_validate_fast(cstr, strlen(cstr));
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_validate(const char *cstr) {
    return utf8_validate(cstr, strlen(cstr));
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_len_fast(const char *cstr, size_t *len) {
    utf8_len_fast(cstr, strlen(cstr), len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int utf8_cstr_len(const char *cstr,
                                                              size_t *len) {
    return utf8_len(cstr, strlen(cstr), len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION bool
utf8_cstr_equal_fast(const char *cs1, const char *cs2) {
    return utf8_equal_fast(cs1, cs2, strlen(cs1));
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_equal(const char *cs1, const char *cs2, bool *equal) {
    return utf8_equal(cs1, cs2, strlen(cs1), equal);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_decode_fast(const char *cstr, rune *r) {
    utf8_decode_fast(cstr, r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_decode(const char *cstr, rune *r) {
    return utf8_decode(cstr, strlen(cstr), r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_decode_len_fast(const char *cstr, rune *r, size_t *rune_byte_len) {
    utf8_decode_len_fast(cstr, r, rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_decode_len(const char *cstr, rune *r, size_t *rune_byte_len) {
    return utf8_decode_len(cstr, strlen(cstr), r, rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_index_fast(const char *cstr, size_t index, char **cursor) {
    utf8_index_fast(cstr, strlen(cstr), index, cursor);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_index(const char *cstr, size_t index, char **cursor) {
    return utf8_index(cstr, strlen(cstr), index, cursor);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_index_rune_fast(const char *cstr, size_t index, rune *r) {
    utf8_index_rune_fast(cstr, strlen(cstr), index, r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_index_rune(const char *cstr, size_t index, rune *r) {
    return utf8_index_rune(cstr, strlen(cstr), index, r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_index_rune_len_fast(const char *cstr,
                              size_t index,
                              rune *r,
                              size_t *rune_byte_len) {
    utf8_index_rune_len_fast(cstr, strlen(cstr), index, r, rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_index_rune_len(const char *cstr,
                         size_t index,
                         rune *r,
                         size_t *rune_byte_len) {
    return utf8_index_rune_len(cstr, strlen(cstr), index, r, rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_index_reverse_fast(const char *cstr, size_t index, char **cursor) {
    utf8_index_reverse_fast(cstr, strlen(cstr), index, cursor);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_index_reverse(const char *cstr, size_t index, char **cursor) {
    return utf8_index_reverse(cstr, strlen(cstr), index, cursor);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_index_rune_reverse_fast(const char *cstr, size_t index, rune *r) {
    utf8_index_rune_reverse_fast(cstr, strlen(cstr), index, r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_index_rune_reverse(const char *cstr, size_t index, rune *r) {
    return utf8_index_rune_reverse(cstr, strlen(cstr), index, r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_index_rune_len_reverse_fast(const char *cstr,
                                      size_t index,
                                      rune *r,
                                      size_t *rune_byte_len) {
    utf8_index_rune_len_reverse_fast(cstr,
                                     strlen(cstr),
                                     index,
                                     r,
                                     rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_index_rune_len_reverse(const char *cstr,
                                 size_t index,
                                 rune *r,
                                 size_t *rune_byte_len) {
    return utf8_index_rune_len_reverse(cstr,
                                       strlen(cstr),
                                       index,
                                       r,
                                       rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_get_first_rune_fast(const char *cstr, rune *r) {
    utf8_get_first_rune_fast(cstr, r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_get_first_rune(const char *cstr, rune *r) {
    return utf8_get_first_rune(cstr, strlen(cstr), r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_get_first_rune_len_fast(const char *cstr,
                                  rune *r,
                                  size_t *rune_byte_len) {
    utf8_get_first_rune_len_fast(cstr, r, rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_get_first_rune_len(const char *cstr,
                             rune *r,
                             size_t *rune_byte_len) {
    return utf8_get_first_rune_len(cstr, strlen(cstr), r, rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_get_last_rune_fast(const char *cstr, rune *r) {
    utf8_get_last_rune_fast(cstr, strlen(cstr), r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_get_last_rune(const char *cstr, rune *r) {
    return utf8_get_last_rune(cstr, strlen(cstr), r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_get_last_rune_len_fast(const char *cstr,
                                 rune *r,
                                 size_t *rune_byte_len) {
    utf8_get_last_rune_len_fast(cstr, strlen(cstr), r, rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_get_last_rune_len(const char *cstr, rune *r, size_t *rune_byte_len) {
    return utf8_get_last_rune_len(cstr, strlen(cstr), r, rune_byte_len);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION void
utf8_cstr_slice_fast(const char *cstr,
                     size_t index,
                     size_t len,
                     char **start,
                     char **end) {
    utf8_slice_fast(cstr, strlen(cstr), index, len, start, end);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_slice(const char *cstr,
                size_t index,
                size_t len,
                char **start,
                char **end) {
    return utf8_slice(cstr, strlen(cstr), index, len, start, end);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION bool
utf8_cstr_starts_with_data_fast(const char *cs1, const char *cs2) {
    return utf8_starts_with_data_fast(cs1, strlen(cs1), cs2, strlen(cs2));
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_starts_with_data(const char *cs1,
                           const char *cs2,
                           bool *starts_with) {
    return utf8_starts_with_data(cs1,
                                 strlen(cs1),
                                 cs2,
                                 strlen(cs2),
                                 starts_with);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION bool
utf8_cstr_starts_with_rune_fast(const char *cstr, rune r) {
    return utf8_starts_with_rune_fast(cstr, r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_starts_with_rune(const char *cstr, rune r, bool *starts_with) {
    return utf8_starts_with_rune(cstr, strlen(cstr), r, starts_with);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION bool
utf8_cstr_ends_with_data_fast(const char *cs1, const char *cs2) {
    return utf8_ends_with_data_fast(cs1, strlen(cs1), cs2, strlen(cs2));
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_ends_with_data(const char *cs1, const char *cs2, bool *ends_with) {
    return utf8_ends_with_data(cs1, strlen(cs1), cs2, strlen(cs2), ends_with);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION bool
utf8_cstr_ends_with_rune_fast(const char *cstr, rune r) {
    return utf8_ends_with_rune_fast(cstr, strlen(cstr), r);
}

CBASE_STATIC_FUNCTION CBASE_INLINE_FUNCTION int
utf8_cstr_ends_with_rune(const char *cstr, rune r, bool *ends_with) {
    return utf8_ends_with_rune(cstr, strlen(cstr), r, ends_with);
}

#endif

/* vi: set et ts=4 sw=4: */
