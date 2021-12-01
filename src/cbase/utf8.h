#pragma once

#ifndef UTF8_H__
#define UTF8_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include <utf8proc.h>

#include "cbase/errors.h"
#include "cbase/alloc.h"
#include "cbase/rune.h"
#include "cbase/utf8_base.h"

bool utf8_byte_is_sequence_start(char b);

int utf8_validate_len_fast(const char *data, size_t byte_len, size_t *len);

int utf8_validate_len(const char *data, size_t byte_len, size_t *len);

int utf8_validate_fast(const char *data, size_t byte_len);

int utf8_validate(const char *data, size_t byte_len);

void utf8_len_fast(const char *data, size_t byte_len, size_t *len);

int utf8_len(const char *data, size_t byte_len, size_t *len);

bool utf8_equal_fast(const char *s1, const char *s2, size_t byte_len);

int utf8_equal(const char *s1, const char *s2, size_t byte_len, bool *equal);

void utf8_calc_rune_byte_len_fast(const char *data, size_t *rune_byte_len);

void utf8_decode_fast(const char *data, rune *r);

int utf8_decode(const char *data, size_t byte_len, rune *r);

void utf8_decode_len_fast(const char *data, rune *r, size_t *rune_byte_len);

int utf8_decode_len(const char *data,
                    size_t byte_len,
                    rune *r,
                    size_t *rune_byte_len);

void utf8_index_fast(const char *data,
                     size_t byte_len,
                     size_t index,
                     char **cursor);

int utf8_index(const char *data, size_t byte_len, size_t index, char **cursor);

void utf8_index_rune_len_fast(const char *data,
                              size_t byte_len,
                              size_t index,
                              rune *r,
                              size_t *rune_byte_len);

int utf8_index_rune_len(const char *data,
                        size_t byte_len,
                        size_t index,
                        rune *r,
                        size_t *rune_byte_len);

void utf8_index_rune_fast(const char *data,
                          size_t byte_len,
                          size_t index,
                          rune *r);

int utf8_index_rune(const char *data, size_t byte_len, size_t index, rune *r);

void utf8_index_reverse_fast(const char *data,
                             size_t byte_len,
                             size_t index,
                             char **cursor);

int utf8_index_reverse(const char *data,
                       size_t byte_len,
                       size_t index,
                       char **cursor);

void utf8_index_rune_len_reverse_fast(const char *data,
                                      size_t byte_len,
                                      size_t index,
                                      rune *r,
                                      size_t *rune_byte_len);

int utf8_index_rune_len_reverse(const char *data,
                                size_t byte_len,
                                size_t index,
                                rune *r,
                                size_t *rune_byte_len);

void utf8_index_rune_reverse_fast(const char *data,
                                  size_t byte_len,
                                  size_t index,
                                  rune *r);

int utf8_index_rune_reverse(const char *data,
                            size_t byte_len,
                            size_t index,
                            rune *r);

void utf8_find_data_fast(const char *haystack,
                         size_t hlen,
                         const char *needle,
                         size_t nlen,
                         bool *found,
                         size_t *location);

int utf8_find_data(const char *haystack,
                   size_t hlen,
                   const char *needle,
                   size_t nlen,
                   bool *found,
                   size_t *location);

void utf8_get_first_rune_len_fast(const char *data,
                                  rune *r,
                                  size_t *rune_byte_len);

int utf8_get_first_rune_len(const char *data,
                            size_t byte_len,
                            rune *r,
                            size_t *rune_byte_len);

void utf8_get_first_rune_fast(const char *data, rune *r);

int utf8_get_first_rune(const char *data, size_t byte_len, rune *r);

void utf8_get_last_rune_len_fast(const char *data,
                                 size_t byte_len,
                                 rune *r,
                                 size_t *rune_byte_len);

int utf8_get_last_rune_len(const char *data,
                           size_t byte_len,
                           rune *r,
                           size_t *rune_byte_len);

void utf8_get_last_rune_fast(const char *data, size_t byte_len, rune *r);

int utf8_get_last_rune(const char *data, size_t byte_len, rune *r);

void utf8_slice_fast(const char *data,
                     size_t byte_len,
                     size_t index,
                     size_t len,
                     char **start,
                     char **end);

int utf8_slice(const char *data,
               size_t byte_len,
               size_t index,
               size_t len,
               char **start,
               char **end);

bool utf8_starts_with_data_fast(const char *s1,
                                size_t byte_len1,
                                const char *s2,
                                size_t byte_len2);

int utf8_starts_with_data(const char *s1,
                          size_t byte_len1,
                          const char *s2,
                          size_t byte_len2,
                          bool *starts_with);

bool utf8_starts_with_rune_fast(const char *data, rune r);

int utf8_starts_with_rune(const char *data,
                          size_t byte_len,
                          rune r,
                          bool *starts_with);

bool utf8_ends_with_data_fast(const char *s1,
                              size_t byte_len1,
                              const char *s2,
                              size_t byte_len2);

int utf8_ends_with_data(const char *s1,
                        size_t byte_len1,
                        const char *s2,
                        size_t byte_len2,
                        bool *ends_with);

bool utf8_ends_with_rune_fast(const char *data, size_t byte_len, rune r);

int utf8_ends_with_rune(const char *data,
                        size_t byte_len,
                        rune r,
                        bool *ends_with);

void utf8_iterate_fast(char **data, size_t *byte_len);

int utf8_iterate(char **data, size_t *byte_len);

void utf8_iterate_rune_fast(char **data, size_t *byte_len, rune *r);

int utf8_iterate_rune(char **data, size_t *byte_len, rune *r);

void utf8_iterate_rune_len_fast(char **data,
                                size_t *byte_len,
                                rune *r,
                                size_t *rune_byte_len);

int utf8_iterate_rune_len(char **data,
                          size_t *byte_len,
                          rune *r,
                          size_t *rune_byte_len);

void utf8_iterate_reverse_fast(char **data, size_t *byte_len);

int utf8_iterate_reverse(char **data, size_t *byte_len);

void utf8_iterate_rune_reverse_fast(char **data, size_t *byte_len, rune *r);

int utf8_iterate_rune_reverse(char **data, size_t *byte_len, rune *r);

void utf8_iterate_rune_len_reverse_fast(char **data,
                                        size_t *byte_len,
                                        rune *r,
                                        size_t *rune_byte_len);

int utf8_iterate_rune_len_reverse(char **data,
                                  size_t *byte_len,
                                  rune *r,
                                  size_t *rune_byte_len);

void utf8_skip_runes_fast(char **data, size_t *len, size_t rune_count);

int utf8_skip_runes(char **data, size_t *len, size_t rune_count);

void utf8_skip_rune_fast(char **data, size_t *len);

int utf8_skip_rune(char **data, size_t *len);

void utf8_skip_runes_if_matching_fast(char **data,
                                      size_t *len,
                                      RuneMatchFunc *matches);

int utf8_skip_runes_if_matching(char **data,
                                size_t *len,
                                RuneMatchFunc *matches);

int utf8_skip_rune_if_matches(char **data,
                              size_t *len,
                              RuneMatchFunc *matches);

int utf8_skip_rune_if_equals(char **data, size_t *len, rune r);

int utf8_pop_rune_fast(char **data, size_t *len, rune *r);

int utf8_pop_rune(char **data, size_t *len, rune *r);

void utf8_pop_rune_if_matching_fast(char **data,
                                    size_t *len,
                                    RuneMatchFunc *matches,
                                    rune *r);

int utf8_pop_rune_if_matching(char **data,
                              size_t *len,
                              RuneMatchFunc *matches,
                              rune *r);

int utf8_pop_rune_if_equals(char **data,
                            size_t *len,
                            RuneMatchFunc *matches,
                            rune *r);

int utf8_seek_to_data(char **data,
                      size_t *len,
                      const char *data2,
                      size_t len2);

void utf8_seek_to_match_fast(char **data, size_t *len, RuneMatchFunc matches);

int utf8_seek_to_match(char **data, size_t *len, RuneMatchFunc matches);

int utf8_seek_to_rune(char **data, size_t *len, rune r);

void utf8_truncate_runes_fast(const char *data,
                              size_t *len,
                              size_t rune_count);

int utf8_truncate_runes(const char *data, size_t *len, size_t rune_count);

void utf8_truncate_rune_fast(const char *data, size_t *len);

int utf8_truncate_rune(const char *data, size_t *len);

void utf8_truncate_if_matching_fast(const char *data,
                                    size_t *len,
                                    RuneMatchFunc *matches);

int utf8_truncate_if_matching(const char *data,
                              size_t *len,
                              RuneMatchFunc *matches);

void utf8_truncate_if_equals_fast(const char *data, size_t *len, rune r);

int utf8_truncate_if_equals(const char *data, size_t *len, rune r);

void utf8_truncate_if_not_equals_fast(const char *data, size_t *len, rune r);

int utf8_truncate_if_not_equals(const char *data, size_t *len, rune r);

#endif

/* vi: set et ts=4 sw=4: */
