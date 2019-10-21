#pragma once

#ifndef SSLICE_H__
#define SSLICE_H__

#include <stdbool.h>
#include <stdlib.h>

#include "cbase/buffer.h"
#include "cbase/rune.h"
#include "cbase/slice.h"

enum {
    SSLICE_EMPTY = 1,
    SSLICE_NOT_SUBSLICE,
};

typedef struct SSliceStruct {
    size_t len;
    size_t byte_len;
    char *data;
} SSlice;

bool sslice_assign_cstr(SSlice *sslice, char *cs, Status *status);

void sslice_assign_full(SSlice *sslice, char *data, size_t len,
                                                    size_t byte_len);

void sslice_assign_sslice(SSlice *dst, SSlice *src);

bool sslice_new_from_cstr(SSlice **sslice, char *cs, Status *status);

bool sslice_new_full(SSlice **sslice, char *data, size_t len,
                                                  size_t byte_len,
                                                  Status *status);

bool sslice_index_rune(SSlice *sslice, size_t index, rune *r, Status *status);

bool sslice_empty(SSlice *sslice);

bool sslice_get_first_rune(SSlice *sslice, rune *r, Status *status);

bool sslice_get_last_rune(SSlice *sslice, rune *r, Status *status);

bool sslice_equals_cstr(SSlice *sslice, const char *cs);

bool sslice_equals_utf8_data(SSlice *sslice, const char *data, size_t len);

bool sslice_equals_sslice(SSlice *s1, SSlice *s2);

bool sslice_equals_utf8_slice(SSlice *sslice, Slice *slice);

bool sslice_equals_utf8_buffer(SSlice *sslice, Buffer *buffer);

bool sslice_starts_with_rune(SSlice *sslice, rune r, bool *starts_with,
                                                     Status *status);

bool sslice_starts_with_cstr(SSlice *sslice, const char *cs, bool *starts_with,
                                                             Status *status);

bool sslice_starts_with_sslice(SSlice *sslice1, SSlice *sslice2,
                                                bool *starts_with,
                                                Status *status);

bool sslice_ends_with_rune(SSlice *sslice, rune r, bool *ends_with,
                                                   Status *status);

bool sslice_ends_with_cstr(SSlice *sslice, const char *cs, bool *ends_with,
                                                           Status *status);

bool sslice_ends_with_sslice(SSlice *sslice1, SSlice *sslice2,
                                              bool *ends_with,
                                              Status *status);

bool sslice_skip_runes(SSlice *sslice, size_t rune_count, Status *status);

bool sslice_skip_rune_if_equals(SSlice *sslice, rune r, Status *status);

bool sslice_pop_rune(SSlice *sslice, rune *r, Status *status);

bool sslice_pop_rune_if_matches(SSlice *sslice, RuneMatchFunc *matches,
                                                rune *r,
                                                Status *status);

bool sslice_pop_rune_if_alpha(SSlice *sslice, rune *r, Status *status);

bool sslice_pop_rune_if_hex_digit(SSlice *sslice, rune *r, Status *status);

bool sslice_pop_rune_if_digit(SSlice *sslice, rune *r, Status *status);

bool sslice_pop_rune_if_oct_digit(SSlice *sslice, rune *r, Status *status);

bool sslice_pop_rune_if_bin_digit(SSlice *sslice, rune *r, Status *status);

bool sslice_pop_rune_if_alnum(SSlice *sslice, rune *r, Status *status);

bool sslice_pop_rune_if_whitespace(SSlice *sslice, rune *r, Status *status);

bool sslice_seek_to_rune(SSlice *sslice, rune r, Status *status);

bool sslice_seek_to_cstr(SSlice *sslice, const char *cs, Status *status);

bool sslice_seek_to_whitespace(SSlice *sslice, Status *status);

bool sslice_seek_to_subslice(SSlice *sslice, SSlice *subslice,
                                             Status *status);

bool sslice_seek_past_subslice(SSlice *sslice, SSlice *subslice,
                                               Status *status);

bool sslice_seek_past_whitespace(SSlice *sslice, Status *status);

bool sslice_truncate_whitespace(SSlice *sslice, Status *status);

bool sslice_truncate_at_rune(SSlice *sslice, rune r, Status *status);

bool sslice_truncate_at_whitespace(SSlice *sslice, Status *status);

bool sslice_truncate_runes(SSlice *sslice, size_t rune_count, Status *status);

bool sslice_truncate_at_subslice(SSlice *sslice, SSlice *subslice,
                                                 Status *status);

void sslice_clear(SSlice *s);

bool sslice_skip_rune(SSlice *sslice, Status *status);

bool sslice_truncate_rune(SSlice *sslice, Status *status);

void sslice_seek_to_end(SSlice *sslice);

bool sslice_to_cstr(SSlice *sslice, char **cs, Status *status);

#endif

/* vi: set et ts=4 sw=4: */
