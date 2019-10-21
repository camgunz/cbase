#pragma once

#ifndef UTF8_H__
#define UTF8_H__

#include <stdbool.h>
#include <stdlib.h>

#include "cbase/rune.h"
#include "cbase/status.h"

enum {
    UTF8_TOO_LONG = 1,
    UTF8_INVALID_UTF8,
    UTF8_UNASSIGNED_CODEPOINT,
    UTF8_INVALID_OPTIONS,
    UTF8_EMPTY,
    UTF8_UNKNOWN_ERROR
};

/* [TODO] Bounds checking */

bool utf8_handle_error_code(ssize_t error_code, Status *status);

bool utf8_byte_is_sequence_start(char b);

bool utf8_process_fast(const char *data, size_t byte_len, size_t *len,
                                                          ssize_t *error);

bool utf8_process(const char *data, size_t byte_len, size_t *len,
                                                     Status *status);

bool utf8_process_cstr_fast(const char *data, size_t *len, size_t *byte_len,
                                                           ssize_t *error);

bool utf8_process_cstr(const char *data, size_t *len, size_t *byte_len,
                                                      Status *status);

bool utf8_validate_fast(const char *data, size_t byte_len, ssize_t *error);

bool utf8_validate(const char *data, size_t byte_len, Status *status);

bool utf8_validate_cstr_fast(const char *data, ssize_t *error);

bool utf8_validate_cstr(const char *data, Status *status);

bool utf8_validate_len_fast(const char *data, size_t byte_len,
                                              size_t *len,
                                              ssize_t *error);

bool utf8_validate_len(const char *data, size_t byte_len, size_t *len,
                                                          Status *status);

bool utf8_cstr_validate_len_fast(const char *data, size_t *len,
                                                   size_t *byte_len,
                                                   ssize_t *error);

bool utf8_cstr_validate_len(const char *data, size_t *len, size_t *byte_len,
                                                           Status *status);

void utf8_len(const char *data, size_t byte_len, size_t *len);

void utf8_cstr_len(const char *data, size_t *len);

bool utf8_equal_fast(const char *s1, const char *s2, size_t byte_len);

bool utf8_equal(const char *s1, const char *s2, size_t byte_len,
                                                bool *equal,
                                                Status *status);

bool utf8_cstr_equal_fast(const char *s1, const char *s2);

bool utf8_cstr_equal(const char *s1, const char *s2, bool *equal,
                                                     Status *status);

void utf8_decode_fast(const char *data, rune *r);

bool utf8_decode(const char *data, rune *r, Status *status);

void utf8_decode_len_fast(const char *data, rune *r, size_t *rune_byte_len);

bool utf8_decode_len(const char *data, rune *r, size_t *rune_byte_len,
                                                Status *status);

void utf8_index_fast(const char *data, size_t byte_len, size_t index,
                                                        char **cursor);

bool utf8_index(const char *data, size_t byte_len, size_t index,
                                                   char **cursor,
                                                   Status *status);

void utf8_index_rune_fast(const char *data, size_t byte_len, size_t index,
                                                             rune *r);

bool utf8_index_rune(const char *data, size_t byte_len, size_t index,
                                                        rune *r,
                                                        Status *status);

void utf8_index_rune_len_fast(const char *data, size_t byte_len,
                                                size_t index,
                                                rune *r,
                                                size_t *rune_byte_len);

bool utf8_index_rune_len(const char *data, size_t byte_len,
                                           size_t index,
                                           rune *r,
                                           size_t *rune_byte_len,
                                           Status *status);

void utf8_cstr_index_fast(const char *data, size_t index, char **cursor);

bool utf8_cstr_index(const char *data, size_t index, char **cursor,
                                                     Status *status);

void utf8_cstr_index_rune_fast(const char *data, size_t index, rune *r);

bool utf8_cstr_index_rune(const char *data, size_t index, rune *r,
                                                          Status *status);

void utf8_cstr_index_rune_len_fast(const char *data, size_t index,
                                                     rune *r,
                                                     size_t *rune_byte_len);

bool utf8_cstr_index_rune_len(const char *data, size_t index,
                                                rune *r,
                                                size_t *rune_byte_len,
                                                Status *status);

void utf8_index_reverse_fast(const char *data, size_t byte_len,
                                               size_t index,
                                               char **cursor);

bool utf8_index_reverse(const char *data, size_t byte_len, size_t index,
                                                           char **cursor,
                                                           Status *status);

void utf8_index_rune_reverse_fast(const char *data, size_t byte_len,
                                                    size_t index,
                                                    rune *r);

bool utf8_index_rune_reverse(const char *data, size_t byte_len,
                                               size_t index,
                                               rune *r,
                                               Status *status);

void utf8_index_rune_len_reverse_fast(const char *data, size_t byte_len,
                                                        size_t index,
                                                        rune *r,
                                                        size_t *rune_byte_len);

bool utf8_index_rune_len_reverse(const char *data, size_t byte_len,
                                                   size_t index,
                                                   rune *r,
                                                   size_t *rune_byte_len,
                                                   Status *status);

void utf8_cstr_index_reverse_fast(const char *data, size_t index,
                                                    char **cursor);

bool utf8_cstr_index_reverse(const char *data, size_t index,
                                               char **cursor,
                                               Status *status);

void utf8_cstr_index_rune_reverse_fast(const char *data, size_t index,
                                                         rune *r);

bool utf8_cstr_index_rune_reverse(const char *data, size_t index,
                                                    rune *r,
                                                    Status *status);

void utf8_cstr_index_rune_len_reverse_fast(const char *data,
                                           size_t index,
                                           rune *r,
                                           size_t *rune_byte_len);

bool utf8_cstr_index_rune_len_reverse(const char *data,
                                      size_t index,
                                      rune *r,
                                      size_t *rune_byte_len,
                                      Status *status);

void utf8_get_first_rune_fast(const char *data, rune *r);

bool utf8_get_first_rune(const char *data, rune *r, Status *status);

void utf8_get_first_rune_len_fast(const char *data, rune *r,
                                                    size_t *rune_byte_len);

bool utf8_get_first_rune_len(const char *data, rune *r, size_t *rune_byte_len,
                                                        Status *status);

void utf8_cstr_get_first_rune_fast(const char *data, rune *r);

bool utf8_cstr_get_first_rune(const char *data, rune *r, Status *status);

void utf8_cstr_get_first_rune_len_fast(const char *data,
                                       rune *r,
                                       size_t *rune_byte_len);

bool utf8_cstr_get_first_rune_len(const char *data, rune *r,
                                                    size_t *rune_byte_len,
                                                    Status *status);

void utf8_get_last_rune_fast(const char *data, size_t byte_len, rune *r);

bool utf8_get_last_rune(const char *data, size_t byte_len, rune *r,
                                                           Status *status);

void utf8_get_last_rune_len_fast(const char *data, size_t byte_len,
                                                   rune *r,
                                                   size_t *rune_byte_len);

bool utf8_get_last_rune_len(const char *data, size_t byte_len,
                                              rune *r,
                                              size_t *rune_byte_len,
                                              Status *status);

void utf8_cstr_get_last_rune_fast(const char *data, rune *r);

bool utf8_cstr_get_last_rune(const char *data, rune *r, Status *status);

void utf8_cstr_get_last_rune_len_fast(const char *data, rune *r,
                                                        size_t *rune_byte_len);

bool utf8_cstr_get_last_rune_len(const char *data, rune *r,
                                                   size_t *rune_byte_len,
                                                   Status *status);

void utf8_slice_fast(const char *data, size_t len, size_t byte_len,
                                                   size_t index,
                                                   char **start,
                                                   char **end);

bool utf8_slice(const char *data, size_t len, size_t byte_len,
                                              size_t index,
                                              char **start,
                                              char **end,
                                              Status *status);

bool utf8_starts_with_data_fast(const char *s1, size_t byte_len1,
                                const char *s2, size_t byte_len2);

bool utf8_starts_with_data(const char *s1, size_t byte_len1,
                           const char *s2, size_t byte_len2,
                                           bool *starts_with,
                                           Status *status);

bool utf8_starts_with_cstr_fast(const char *data, size_t byte_len,
                                                  const char *cs);

bool utf8_starts_with_cstr(const char *data, size_t byte_len,
                                             const char *cs,
                                             bool *starts_with,
                                             Status *status);

bool utf8_starts_with_rune_fast(const char *data, rune r);

bool utf8_starts_with_rune(const char *data, rune r, bool *starts_with,
                                                     Status *status);

bool utf8_cstr_starts_with_data_fast(const char *cs, const char *data,
                                                     size_t byte_len);

bool utf8_cstr_starts_with_data(const char *cs, const char *data,
                                                size_t byte_len,
                                                bool *starts_with,
                                                Status *status);

bool utf8_cstr_starts_with_cstr_fast(const char *cs1, const char *cs2);

bool utf8_cstr_starts_with_cstr(const char *cs1, const char *cs2,
                                                 bool *starts_with,
                                                 Status *status);

bool utf8_cstr_starts_with_rune_fast(const char *data, rune r);

bool utf8_cstr_starts_with_rune(const char *data, rune r, bool *starts_with,
                                                          Status *status);

bool utf8_ends_with_data_fast(const char *s1, size_t byte_len1,
                              const char *s2, size_t byte_len2);

bool utf8_ends_with_data(const char *s1, size_t byte_len1,
                         const char *s2, size_t byte_len2,
                                         bool *ends_with,
                                         Status *status);

bool utf8_ends_with_cstr_fast(const char *data, size_t byte_len,
                                                const char *cs);

bool utf8_ends_with_cstr(const char *data, size_t byte_len,
                                           const char *cs,
                                           bool *ends_with,
                                           Status *status);

bool utf8_ends_with_rune_fast(const char *data, size_t byte_len, rune r);

bool utf8_ends_with_rune(const char *data, size_t byte_len,
                                           rune r,
                                           bool *ends_with,
                                           Status *status);

bool utf8_cstr_ends_with_data_fast(const char *cs, const char *data,
                                                   size_t byte_len);

bool utf8_cstr_ends_with_data(const char *cs, const char *data,
                                              size_t byte_len,
                                              bool *ends_with,
                                              Status *status);

bool utf8_cstr_ends_with_cstr_fast(const char *cs1, const char *cs2);

bool utf8_cstr_ends_with_cstr(const char *cs1, const char *cs2,
                                               bool *ends_with,
                                               Status *status);

bool utf8_cstr_ends_with_rune_fast(const char *data, rune r);

bool utf8_cstr_ends_with_rune(const char *data, rune r, bool *ends_with,
                                                        Status *status);

void utf8_iterate_fast(char **data, size_t *byte_len, rune *r);

bool utf8_iterate(char **data, size_t *byte_len, rune *r, Status *status);

#endif

/* vi: set et ts=4 sw=4: */
