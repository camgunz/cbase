#pragma once

#ifndef STR_H__
#define STR_H__

#include "cbase/internal.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cbase/buffer.h"
#include "cbase/sslice.h"

enum {
    CBASE_STRING_VSNPRINTF_FAILED = 26000,
};

/* [TODO] Make internal string encoding configurable (currently UTF-8 only). */

typedef struct StringStruct {
    size_t len;
    Buffer buffer;
} String;

void string_assign_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len);

int string_assign_cstr_full(String *string, const char *cs, size_t len,
                                                            size_t byte_len);

int string_assign_cstr(String *string, const char *cs);

void string_assign_utf8_data_full_fast(String *string, const char *data,
                                                       size_t len,
                                                       size_t byte_len);

int string_assign_utf8_data_full(String *string, const char *data,
                                                 size_t len,
                                                 size_t byte_len);

void string_assign_utf8_data_fast(String *string, const char *data,
                                                  size_t byte_len);

int string_assign_utf8_data(String *string, const char *data,
                                            size_t byte_len);

void string_assign_sslice_fast(String *string, SSlice *sslice);

int string_assign_sslice(String *string, SSlice *sslice);

/* here */

int string_assign_data_fast(String *string, const char *data,
                                            size_t byte_len,
                                            const char *encoding);

int string_assign_data(String *string, const char *data, size_t byte_len,
                                                         const char *encoding);

int string_assign_slice_fast(String *string, BSlice *slice,
                                             const char *encoding);

int string_assign_slice(String *string, BSlice *slice, const char *encoding);

void string_assign_utf8_slice_fast(String *string, BSlice *slice);

int string_assign_utf8_slice(String *string, BSlice *slice);

int string_assign_local_slice_fast(String *string, BSlice *slice);

int string_assign_local_slice(String *string, BSlice *slice);

int string_assign_buffer_fast(String *string, Buffer *buffer,
                                              const char *encoding);

int string_assign_buffer(String *string, Buffer *buffer, const char *encoding);

void string_assign_utf8_buffer_full_fast(String *string, Buffer *buffer,
                                                         size_t len);

int string_assign_utf8_buffer_full(String *string, Buffer *buffer,
                                                   size_t len);

void string_assign_utf8_buffer_fast(String *string, Buffer *buffer);

int string_assign_utf8_buffer(String *string, Buffer *buffer);

int string_assign_local_buffer_fast(String *string, Buffer *buffer);

int string_assign_local_buffer(String *string, Buffer *buffer);

void string_assign_string_fast(String *dst, String *src);

int string_assign_string(String *dst, String *src);

int string_ensure_capacity(String *string, size_t byte_len);

void string_init(String *string);

int string_init_alloc(String *string, size_t alloc);

int string_init_from_cstr(String *string, const char *cs);

int string_init_from_cstr_full(String *string, const char *cs,
                                               size_t len,
                                               size_t byte_len);

int string_init_from_utf8_data(String *string, const char *data,
                                               size_t byte_len);

int string_init_from_utf8_data_full(String *string, const char *data,
                                                    size_t len,
                                                    size_t byte_len);

int string_init_from_sslice(String *string, SSlice *sslice);

int string_init_from_string(String *string, String *input);

int string_init_from_slice(String *string, BSlice *slice, const char *encoding);

int string_init_from_utf8_slice(String *string, BSlice *slice);

int string_init_from_local_slice(String *string, BSlice *slice);

int string_init_from_buffer(String *string, Buffer *buffer,
                                            const char *encoding);

int string_init_from_utf8_buffer(String *string, Buffer *buffer);

int string_init_from_local_buffer(String *string, Buffer *buffer);

int string_new(String **string);

int string_new_alloc(String **string, size_t alloc);

int string_new_from_cstr(String **string, const char *cs);

int string_new_from_cstr_full(String **string, const char *cs,
                                               size_t len,
                                               size_t byte_len);

int string_new_from_utf8_data_full(String **string, const char *data,
                                                    size_t len,
                                                    size_t byte_len);

int string_new_from_sslice(String **string, SSlice *sslice);

int string_new_from_string(String **string, String *input);

int string_new_from_slice(String **string, BSlice *slice, const char *encoding);

int string_new_from_utf8_slice(String **string, BSlice *slice);

int string_new_from_local_slice(String **string, BSlice *slice);

int string_new_from_buffer(String **string, Buffer *buffer,
                                            const char *encoding);

int string_new_from_utf8_buffer(String **string, Buffer *buffer);

int string_new_from_local_buffer(String **string, Buffer *buffer);

int string_compact(String *string);

int string_index_rune(String *string, size_t index, rune *r);

int string_index_rune_reverse(String *string, size_t index, rune *r);

int string_get_first_rune(String *string, rune *r);

int string_get_last_rune(String *string, rune *r);

bool string_equals_cstr(String *string, const char *cs);

bool string_equals_utf8_data(String *string, const char *data,
                                             size_t byte_len);

bool string_equals_sslice(String *string, SSlice *sslice);

bool string_equals_string(String *s1, String *s2);

bool string_equals_utf8_slice(String *string, BSlice *slice);

bool string_equals_utf8_buffer(String *string, Buffer *buffer);

int string_starts_with_rune(String *string, rune r, bool *starts_with);

int string_starts_with_cstr_len(String *string, const char *cs,
                                                size_t byte_len,
                                                bool *starts_with);

int string_starts_with_cstr(String *string, const char *cs, bool *starts_with);

int string_ends_with_rune(String *string, rune r, bool *ends_with);

int string_ends_with_utf8_data(String *string, const char *cs,
                                               size_t byte_len,
                                               bool *ends_with);

int string_ends_with_cstr(String *string, const char *cs, bool *ends_with);

void string_slice_fast(String *string, size_t index, size_t len,
                                                     SSlice *sslice);

int string_slice(String *string, size_t index, size_t len, SSlice *sslice);

void string_slice_full(String *string, SSlice *sslice);

void string_delete_fast(String *string, size_t index, size_t rune_count);

int string_delete(String *string, size_t index, size_t rune_count);

int string_skip_rune(String *string);

int string_skip_runes(String *string, size_t rune_count);

int string_skip_rune_if_equals(String *string, rune r);

int string_pop_rune(String *string, rune *r);

int string_pop_rune_if_matches(String *string, RuneMatchFunc *matches,
                                               rune *r);

int string_skip_rune_if_matches(String *string, RuneMatchFunc *matches);

int string_seek_to_rune(String *string, rune r);

int string_seek_to_cstr(String *string, const char *cs);

int string_truncate_runes(String *string, size_t rune_count);

int string_truncate_rune(String *string);

char* string_to_cstr(String *string);

void string_insert_cstr_full_fast(String *string, size_t index,
                                                  const char *cs,
                                                  size_t len,
                                                  size_t byte_len);

int string_insert_cstr_full(String *string, size_t index, const char *cs,
                                                          size_t len,
                                                          size_t byte_len);

int string_insert_cstr(String *string, size_t index, const char *cs);

void string_insert_utf8_data_full_fast(String *string, size_t index,
                                                       const char *data,
                                                       size_t len,
                                                       size_t byte_len);

int string_insert_utf8_data_full(String *string, size_t index,
                                                 const char *data,
                                                 size_t len,
                                                 size_t byte_len);

void string_insert_utf8_data_fast(String *string, size_t index,
                                                  const char *data,
                                                  size_t byte_len);

int string_insert_utf8_data(String *string, size_t index, const char *data,
                                                          size_t byte_len);

void string_insert_sslice_fast(String *string, size_t index, SSlice *sslice);

int string_insert_sslice(String *string, size_t index, SSlice *sslice);

void string_insert_string_fast(String *dst, size_t index, String *src);

int string_insert_string(String *dst, size_t index, String *src);

int string_insert_slice_fast(String *string, size_t index,
                                             BSlice *slice,
                                             const char *encoding);

int string_insert_slice(String *string, size_t index, BSlice *slice,
                                                      const char *encoding);

void string_insert_utf8_slice_fast(String *string, size_t index,
                                                   BSlice *slice);

int string_insert_utf8_slice(String *string, size_t index, BSlice *slice);

int string_insert_local_slice_fast(String *string, size_t index, BSlice *slice);

int string_insert_local_slice(String *string, size_t index, BSlice *slice);

int string_insert_buffer_fast(String *string, size_t index,
                                              Buffer *buffer,
                                              const char *encoding);

int string_insert_buffer(String *string, size_t index, Buffer *buffer,
                                                       const char *encoding);

int string_insert_utf8_buffer_fast(String *string, size_t index,
                                                   Buffer *buffer);

int string_insert_utf8_buffer(String *string, size_t index, Buffer *buffer);

int string_insert_local_buffer_fast(String *string, size_t index,
                                                    Buffer *buffer);

int string_insert_local_buffer(String *string, size_t index, Buffer *buffer);

int string_insert_data_fast(String *string, size_t index,
                                            const char *data,
                                            size_t byte_len,
                                            const char *encoding);

int string_insert_data(String *string, size_t index, const char *data,
                                                     size_t byte_len,
                                                     const char *encoding);

int string_insert_local_data_fast(String *string, size_t index,
                                                  const char *data,
                                                  size_t byte_len);

int string_insert_local_data(String *string, size_t index, const char *data,
                                                           size_t byte_len);

void string_prepend_cstr_full_fast(String *string, const char *cs,
                                                   size_t len,
                                                   size_t byte_len);

int string_prepend_cstr_full(String *string, const char *cs, size_t len,
                                                             size_t byte_len);

int string_prepend_cstr(String *string, const char *cs);

void string_prepend_utf8_data_full_fast(String *string, const char *data,
                                                        size_t len,
                                                        size_t byte_len);

int string_prepend_utf8_data_full(String *string, const char *data,
                                                  size_t len,
                                                  size_t byte_len);

int string_prepend_utf8_data(String *string, const char *data,
                                             size_t byte_len);

void string_prepend_sslice_fast(String *string, SSlice *sslice);

int string_prepend_sslice(String *string, SSlice *sslice);

void string_prepend_string_fast(String *dst, String *src);

int string_prepend_string(String *dst, String *src);

int string_prepend_slice_fast(String *string, BSlice *slice,
                                              const char *encoding);

int string_prepend_slice(String *string, BSlice *slice, const char *encoding);

void string_prepend_utf8_slice_fast(String *string, BSlice *slice);

int string_prepend_utf8_slice(String *string, BSlice *slice);

int string_prepend_local_slice_fast(String *string, BSlice *slice);

int string_prepend_local_slice(String *string, BSlice *slice);

int string_prepend_buffer_fast(String *string, Buffer *buffer,
                                               const char *encoding);

int string_prepend_buffer(String *string, Buffer *buffer,
                                          const char *encoding);

int string_prepend_utf8_buffer_fast(String *string, Buffer *buffer);

int string_prepend_utf8_buffer(String *string, Buffer *buffer);

int string_prepend_local_buffer_fast(String *string, Buffer *buffer);

int string_prepend_local_buffer(String *string, Buffer *buffer);

int string_prepend_data_fast(String *string, const char *data,
                                             size_t byte_len,
                                             const char *encoding);

int string_prepend_data(String *string, const char *data,
                                        size_t byte_len,
                                        const char *encoding);

int string_prepend_local_data_fast(String *string, const char *data,
                                                   size_t byte_len);

int string_prepend_local_data(String *string, const char *data,
                                              size_t byte_len);

void string_append_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len);

int string_append_cstr_full(String *string, const char *cs, size_t len,
                                                            size_t byte_len);

int string_append_cstr(String *string, const char *cs);

void string_append_utf8_data_full_fast(String *string, const char *data,
                                                       size_t len,
                                                       size_t byte_len);

int string_append_utf8_data_full(String *string, const char *data,
                                                 size_t len,
                                                 size_t byte_len);

int string_append_utf8_data(String *string, const char *data, size_t byte_len);

void string_append_sslice_fast(String *string, SSlice *sslice);

int string_append_sslice(String *string, SSlice *sslice);

void string_append_string_fast(String *dst, String *src);

int string_append_string(String *dst, String *src);

int string_append_slice_fast(String *string, BSlice *slice,
                                             const char *encoding);

int string_append_slice(String *string, BSlice *slice, const char *encoding);

void string_append_utf8_slice_fast(String *string, BSlice *slice);

int string_append_utf8_slice(String *string, BSlice *slice);

int string_append_local_slice_fast(String *string, BSlice *slice);

int string_append_local_slice(String *string, BSlice *slice);

int string_append_buffer_fast(String *string, Buffer *buffer,
                                              const char *encoding);

int string_append_buffer(String *string, Buffer *buffer, const char *encoding);

int string_append_utf8_buffer_fast(String *string, Buffer *buffer);

int string_append_utf8_buffer(String *string, Buffer *buffer);

int string_append_local_buffer_fast(String *string, Buffer *buffer);

int string_append_local_buffer(String *string, Buffer *buffer);

int string_append_data_fast(String *string, const char *data,
                                            size_t byte_len,
                                            const char *encoding);

int string_append_data(String *string, const char *data,
                                       size_t byte_len,
                                       const char *encoding);

int string_append_local_data_fast(String *string, const char *data,
                                                  size_t byte_len);

int string_append_local_data(String *string, const char *data,
                                             size_t byte_len);

int string_encode(String *string, const char *encoding, Buffer *out);

int string_localize(String *string, Buffer *out);

void string_clear(String *string);

void string_free(String *string);

int string_insert_printf(String *string, size_t index, const char *fmt, ...);

int string_vprintf(String *string, const char *fmt, va_list args);

int string_printf(String *string, const char *fmt, ...);

int string_init_vprintf(String *string, const char *fmt, va_list args);

int string_init_printf(String *string, const char *fmt, ...);

int string_new_vprintf(String **string, const char *fmt, va_list args);

int string_new_printf(String **string, const char *fmt, ...);

int string_prepend_vprintf(String *string, const char *fmt, va_list args);

int string_prepend_printf(String *string, const char *fmt, ...);

int string_append_vprintf(String *string, const char *fmt, va_list args);

int string_append_printf(String *string, const char *fmt, ...);

int string_insert_vprintf(String *string, size_t index, const char *fmt,
                                                        va_list args);

int string_replace_cstr(String *string, const char *cs,
                                        const char *replacement);

#endif

/* vi: set et ts=4 sw=4: */
