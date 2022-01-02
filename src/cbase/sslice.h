#pragma once

#ifndef SSLICE_H__
#define SSLICE_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "cbase/errors.h"
#include "cbase/alloc.h"
#include "cbase/buffer.h"
#include "cbase/utf8.h"
#include "cbase/strbase.h"

enum
{
    CBASE_SSLICE_EMPTY = 25000,
    CBASE_SSLICE_NOT_SUBSLICE,
};

typedef struct SSliceStruct {
    size_t len;
    size_t byte_len;
    char *data;
} SSlice;

static inline void
sslice_assign_full(SSlice *sslice, char *data, size_t len, size_t byte_len) {
    strbase_assign_full(&sslice->data,
                        &sslice->len,
                        &sslice->byte_len,
                        data,
                        len,
                        byte_len);
}

static inline int sslice_assign_cstr(SSlice *sslice, char *cs) {
    return strbase_assign_cstr(&sslice->data,
                               &sslice->len,
                               &sslice->byte_len,
                               cs);
}

static inline void sslice_assign_sslice(SSlice *dst, SSlice *src) {
    strbase_assign_full(&dst->data,
                        &dst->len,
                        &dst->byte_len,
                        src->data,
                        src->len,
                        src->byte_len);
}

static inline int sslice_new_from_cstr(SSlice **sslice, char *cs) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(SSlice), sslice));

    int error = sslice_assign_cstr(*sslice, cs);

    if (error) {
        cbfree(*sslice);
        return error;
    }

    return 0;
}

static inline int
sslice_new_full(SSlice **sslice, char *data, size_t len, size_t byte_len) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(SSlice), sslice));

    sslice_assign_full(*sslice, data, len, byte_len);

    return 0;
}

static inline void sslice_clear(SSlice *s) {
    strbase_clear(&s->len, &s->byte_len);
}

static inline int sslice_index_rune(SSlice *sslice, size_t index, rune *r) {
    return strbase_index_rune(sslice->data, sslice->byte_len, index, r);
}

static inline bool sslice_empty(SSlice *sslice) {
    return strbase_empty(sslice->data, sslice->len, sslice->byte_len);
}

static inline int sslice_get_first_rune(SSlice *sslice, rune *r) {
    return sslice_index_rune(sslice, 0, r);
}

static inline int sslice_get_last_rune(SSlice *sslice, rune *r) {
    return sslice_index_rune(sslice, sslice->len - 1, r);
}

static inline bool sslice_equals_cstr(SSlice *sslice, const char *cs) {
    return strbase_equals_cstr(sslice->data, sslice->byte_len, cs);
}

static inline bool sslice_equals_utf8_data(SSlice *sslice,
                                           const char *data,
                                           size_t byte_len) {
    return strbase_equals_utf8_data(sslice->data,
                                    sslice->byte_len,
                                    data,
                                    byte_len);
}

static inline bool sslice_equals_sslice(SSlice *s1, SSlice *s2) {
    return strbase_equals(s1->data,
                          s1->len,
                          s1->byte_len,
                          s2->data,
                          s2->len,
                          s2->byte_len);
}

static inline bool sslice_equals_utf8_slice(SSlice *sslice, Slice *slice) {
    return sslice_equals_utf8_data(sslice, slice->data, slice->len);
}

static inline bool sslice_equals_utf8_buffer(SSlice *sslice, Buffer *buffer) {
    return sslice_equals_utf8_data(sslice, buffer->elements, buffer->len);
}

static inline int sslice_starts_with_rune(SSlice *sslice,
                                          rune r,
                                          bool *starts_with) {
    return strbase_starts_with_rune(sslice->data, r, starts_with);
}

static inline int sslice_starts_with_cstr(SSlice *sslice,
                                          const char *cs,
                                          bool *starts_with) {
    return strbase_starts_with_cstr(sslice->data,
                                    sslice->byte_len,
                                    cs,
                                    starts_with);
}

static inline int sslice_starts_with_sslice(SSlice *sslice1,
                                            SSlice *sslice2,
                                            bool *starts_with) {
    return strbase_starts_with_data(sslice1->data,
                                    sslice1->byte_len,
                                    sslice2->data,
                                    sslice2->byte_len,
                                    starts_with);
}

static inline int sslice_ends_with_rune(SSlice *sslice,
                                        rune r,
                                        bool *ends_with) {
    return strbase_ends_with_rune(sslice->data,
                                  sslice->byte_len,
                                  r,
                                  ends_with);
}

static inline int sslice_ends_with_cstr(SSlice *sslice,
                                        const char *cs,
                                        bool *ends_with) {
    return strbase_ends_with_cstr(sslice->data,
                                  sslice->byte_len,
                                  cs,
                                  ends_with);
}

static inline int sslice_ends_with_sslice(SSlice *sslice1,
                                          SSlice *sslice2,
                                          bool *ends_with) {
    return strbase_ends_with_data(sslice1->data,
                                  sslice1->byte_len,
                                  sslice2->data,
                                  sslice2->byte_len,
                                  ends_with);
}

static inline int sslice_skip_runes(SSlice *sslice, size_t rune_count) {
    return strbase_skip_runes(&sslice->data,
                              &sslice->len,
                              &sslice->byte_len,
                              rune_count);
}

static inline int sslice_skip_rune_if_equals(SSlice *sslice, rune r) {
    return strbase_skip_rune_if_equals(&sslice->data,
                                       &sslice->len,
                                       &sslice->byte_len,
                                       r);
}

static inline int sslice_pop_rune(SSlice *sslice, rune *r) {
    return strbase_pop_rune(&sslice->data, &sslice->len, &sslice->byte_len, r);
}

static inline int sslice_pop_rune_if_matches(SSlice *sslice,
                                             RuneMatchFunc *matches,
                                             rune *r) {
    return strbase_pop_rune_if_matches(&sslice->data,
                                       &sslice->len,
                                       &sslice->byte_len,
                                       matches,
                                       r);
}

static inline int sslice_pop_rune_if_alpha(SSlice *sslice, rune *r) {
    return sslice_pop_rune_if_matches(sslice, rune_is_alpha, r);
}

static inline int sslice_pop_rune_if_hex_digit(SSlice *sslice, rune *r) {
    return sslice_pop_rune_if_matches(sslice, rune_is_hex_digit, r);
}

static inline int sslice_pop_rune_if_digit(SSlice *sslice, rune *r) {
    return sslice_pop_rune_if_matches(sslice, rune_is_digit, r);
}

static inline int sslice_pop_rune_if_oct_digit(SSlice *sslice, rune *r) {
    return sslice_pop_rune_if_matches(sslice, rune_is_oct_digit, r);
}

static inline int sslice_pop_rune_if_bin_digit(SSlice *sslice, rune *r) {
    return sslice_pop_rune_if_matches(sslice, rune_is_bin_digit, r);
}

static inline int sslice_pop_rune_if_alnum(SSlice *sslice, rune *r) {
    return sslice_pop_rune_if_matches(sslice, rune_is_alnum, r);
}

static inline int sslice_pop_rune_if_whitespace(SSlice *sslice, rune *r) {
    return sslice_pop_rune_if_matches(sslice, rune_is_whitespace, r);
}

static inline int sslice_seek_to_rune(SSlice *sslice, rune r) {
    return strbase_seek_to_rune(&sslice->data,
                                &sslice->len,
                                &sslice->byte_len,
                                r);
}

static inline int sslice_seek_to_cstr(SSlice *sslice, const char *cs) {
    return strbase_seek_to_cstr(&sslice->data,
                                &sslice->len,
                                &sslice->byte_len,
                                cs);
}

static inline int sslice_seek_to_whitespace(SSlice *sslice) {
    return strbase_seek_to_whitespace(&sslice->data,
                                      &sslice->len,
                                      &sslice->byte_len);
}

static inline int sslice_seek_to_subslice(SSlice *sslice, SSlice *subslice) {
    if (subslice->data < sslice->data) {
        return CBASE_SSLICE_NOT_SUBSLICE;
    }

    if (subslice->data >= (sslice->data + sslice->byte_len)) {
        return CBASE_ERROR_OUT_OF_BOUNDS;
    }

    if (sslice->data == subslice->data) {
        return 0;
    }

    size_t start_byte_len = subslice->data - sslice->data;
    size_t start_len;

    utf8_len(sslice->data, sslice->byte_len, &start_len);

    sslice->len -= start_len;
    sslice->byte_len -= start_byte_len;
    sslice->data = subslice->data;

    return 0;
}

static inline int sslice_seek_past_subslice(SSlice *sslice, SSlice *subslice) {
    size_t start_len = 0;
    char *start = subslice->data + subslice->byte_len;
    char *current_end = sslice->data + sslice->byte_len;

    if (start < sslice->data) {
        return CBASE_SSLICE_NOT_SUBSLICE;
    }

    if (start >= current_end) {
        sslice_clear(sslice);
        return 0;
    }

    size_t start_byte_len = subslice->data - sslice->data;

    if (start_byte_len) {
        utf8_len(sslice->data, start_byte_len, &start_len);
    }

    sslice->len -= (start_len + subslice->len);
    sslice->byte_len -= (start_byte_len + subslice->len);
    sslice->data = start;

    return 0;
}

static inline int sslice_seek_past_whitespace(SSlice *sslice) {
    return strbase_seek_past_whitespace(&sslice->data,
                                        &sslice->len,
                                        &sslice->byte_len);
}

static inline int sslice_truncate_whitespace(SSlice *sslice) {
    return strbase_truncate_whitespace(sslice->data,
                                       &sslice->len,
                                       &sslice->byte_len);
}

static inline int sslice_truncate_at_rune(SSlice *sslice, rune r) {
    return strbase_truncate_at_rune(sslice->data,
                                    &sslice->len,
                                    &sslice->byte_len,
                                    r);
}

static inline int sslice_truncate_at_whitespace(SSlice *sslice) {
    return strbase_truncate_at_whitespace(sslice->data,
                                          &sslice->len,
                                          &sslice->byte_len);
}

static inline int sslice_truncate_runes(SSlice *sslice, size_t rune_count) {
    return strbase_truncate_runes(sslice->data,
                                  &sslice->len,
                                  &sslice->byte_len,
                                  rune_count);
}

static inline int sslice_truncate_at_subslice(SSlice *sslice,
                                              SSlice *subslice) {
    if (subslice->data < sslice->data) {
        return CBASE_SSLICE_NOT_SUBSLICE;
    }

    if (((size_t)(subslice->data - sslice->data)) >= sslice->len) {
        return CBASE_SSLICE_NOT_SUBSLICE;
    }

    sslice->byte_len = subslice->data - sslice->data;
    utf8_len(sslice->data, sslice->byte_len, &sslice->len);

    return 0;
}

static inline int sslice_skip_rune(SSlice *sslice) {
    return sslice_skip_runes(sslice, 1);
}

static inline int sslice_truncate_rune(SSlice *sslice) {
    return sslice_truncate_runes(sslice, 1);
}

static inline void sslice_seek_to_end(SSlice *sslice) {
    sslice->data += sslice->byte_len;
    sslice->len = 0;
    sslice->byte_len = 0;
}

static inline int sslice_to_cstr(SSlice *sslice, char **cs) {
    return cbstrndup(sslice->data, sslice->byte_len, cs);
}

#endif
