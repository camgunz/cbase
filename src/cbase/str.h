#pragma once

#ifndef STR_H__
#define STR_H__

#include "cbase/internal.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "cbase/array_slice.h"
#include "cbase/rune.h"
#include "cbase/utf8.h"

enum
{
    CBASE_STRING_VSNPRINTF_FAILED = 26000,
    /* CBASE_STRING_CSTR_EMPTY, */
};

/*
 * [TODO] Could add some more transcoding methods, but the problem there is
 *        that errors corrupt the String's buffer. Maybe this is a job for
 *        "fast", or "in_place", or something?
 */

CBASE_SLICEABLE_ARRAY_STATIC_DEF(String, string, SSlice, sslice, char)

int string_assign_transcoded_data(String *string,
                                  const char *src,
                                  size_t byte_len,
                                  const char *src_encoding);

int string_index_rune(String *string, size_t index, rune *r);

int string_index_rune_reverse(String *string, size_t index, rune *r);

int string_get_first_rune(String *string, rune *r);

int string_get_last_rune(String *string, rune *r);

int string_starts_with_rune(String *string, rune r, bool *starts_with);

int string_ends_with_rune(String *string, rune r, bool *ends_with);

void string_slice_runes_fast(String *string,
                             size_t rune_index,
                             size_t rune_count,
                             SSlice *sslice);

int string_slice_runes(String *string,
                       size_t index,
                       size_t len,
                       SSlice *sslice);

void string_delete_runes_fast(String *string, size_t index, size_t rune_count);

int string_delete_runes(String *string, size_t index, size_t rune_count);

void string_delete_rune_fast(String *string, size_t index);

int string_delete_rune(String *string, size_t index);

int string_skip_rune(String *string);

int string_skip_runes(String *string, size_t rune_count);

int string_skip_rune_if_equals(String *string, rune r);

int string_pop_rune(String *string, rune *r);

int string_pop_rune_if_matches(String *string,
                               RuneMatchFunc *matches,
                               rune *r);

int string_skip_rune_if_matches(String *string, RuneMatchFunc *matches);

int string_seek_to_rune(String *string, rune r);

int string_truncate_runes(String *string, size_t rune_count);

int string_truncate_rune(String *string);

CBASE_VPRINTF(3)
int string_insert_vprintf(String *string,
                          size_t index,
                          const char *fmt,
                          va_list args);

CBASE_PRINTF(3, 4)
int string_insert_printf(String *string, size_t index, const char *fmt, ...);

CBASE_VPRINTF(2)
int string_vprintf(String *string, const char *fmt, va_list args);

CBASE_PRINTF(2, 3)
int string_printf(String *string, const char *fmt, ...);

CBASE_VPRINTF(2)
int string_init_vprintf(String *string, const char *fmt, va_list args);

CBASE_PRINTF(2, 3)
int string_init_printf(String *string, const char *fmt, ...);

CBASE_VPRINTF(2)
int string_new_vprintf(String **string, const char *fmt, va_list args);

CBASE_PRINTF(2, 3)
int string_new_printf(String **string, const char *fmt, ...);

CBASE_VPRINTF(2)
int string_prepend_vprintf(String *string, const char *fmt, va_list args);

CBASE_PRINTF(2, 3)
int string_prepend_printf(String *string, const char *fmt, ...);

CBASE_VPRINTF(2)
int string_append_vprintf(String *string, const char *fmt, va_list args);

CBASE_PRINTF(2, 3)
int string_append_printf(String *string, const char *fmt, ...);

#endif

/* vi: set et ts=4 sw=4: */
