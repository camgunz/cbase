#pragma once

#ifndef BUFFER_H__
#define BUFFER_H__

#include <stdbool.h>
#include <stdlib.h>

#include "cbase/array.h"
#include "cbase/slice.h"
#include "cbase/status.h"

typedef struct BufferStruct {
    Array array;
} Buffer;

void buffer_assign_data_fast(Buffer *buffer, const char *bytes, size_t len);

bool buffer_assign_data(Buffer *buffer, const char *bytes, size_t len,
                                                           Status *status);

void buffer_assign_buffer_fast(Buffer *dst, Buffer *src);

bool buffer_assign_buffer(Buffer *dst, Buffer *src, Status *status);

void buffer_assign_slice_fast(Buffer *buffer, Slice *slice);

bool buffer_assign_slice(Buffer *buffer, Slice *slice, Status *status);

bool buffer_ensure_capacity(Buffer *buffer, size_t len, Status *status);

bool buffer_set_size(Buffer *buffer, size_t len, Status *status);

void buffer_init(Buffer *buffer);

bool buffer_init_alloc(Buffer *buffer, size_t alloc, Status *status);

bool buffer_init_from_data(Buffer *buffer, const char *data, size_t len,
                                                             Status *status);

bool buffer_new(Buffer **buffer, Status *status);

bool buffer_new_alloc(Buffer **buffer, size_t alloc, Status *status);

bool buffer_new_from_data(Buffer **buffer, const char *data, size_t len,
                                                             Status *status);

bool buffer_compact(Buffer *buffer, Status *status);

bool buffer_equals_data_at_fast(Buffer *buffer, size_t index,
                                                const void *data,
                                                size_t len);

bool buffer_equals_data_at(Buffer *buffer, size_t index, const void *data,
                                                         size_t len,
                                                         bool *equal,
                                                         Status *status);

bool buffer_equals_data(Buffer *buffer, const char *data, size_t len);

bool buffer_equals_buffer(Buffer *b1, Buffer *b2);

bool buffer_starts_with_data_fast(Buffer *buffer, const void *data,
                                                  size_t len);

bool buffer_starts_with_data(Buffer *buffer, const void *data,
                                             size_t len,
                                             bool *equal,
                                             Status *status);

bool buffer_ends_with_data_fast(Buffer *buffer, const void *data, size_t len);

bool buffer_ends_with_data(Buffer *buffer, const void *data, size_t len,
                                                             bool *equal,
                                                             Status *status);

void buffer_read_fast(Buffer *buffer, size_t index, size_t len, void *out);

bool buffer_read(Buffer *buffer, size_t index, size_t len, void *out,
                                                              Status *status);

void buffer_slice_fast(Buffer *buffer, size_t index, size_t len,
                                                     Slice *slice);

bool buffer_slice(Buffer *buffer, size_t index, size_t len,
                                                Slice *slice,
                                                Status *status);

void buffer_slice_full(Buffer *buffer, Slice *slice);

void buffer_delete_fast(Buffer *buffer, size_t index, size_t len);

bool buffer_delete(Buffer *buffer, size_t index, size_t len,
                                                 Status *status);

void buffer_clear_no_zero(Buffer *buffer);

void buffer_clear(Buffer *buffer);

void buffer_free(Buffer *buffer);

void buffer_insert_data_fast(Buffer *buffer, size_t index, const char *bytes,
                                                           size_t count);

bool buffer_insert_data(Buffer *buffer, size_t index, const char *bytes,
                                                      size_t count,
                                                      Status *status);

void buffer_insert_blank_data_fast_no_zero(Buffer *buffer, size_t index,
                                                           size_t count);

void buffer_insert_blank_data_fast(Buffer *buffer, size_t index,
                                                   size_t count);

bool buffer_insert_blank_data_no_zero(Buffer *buffer, size_t index,
                                                      size_t count,
                                                      Status *status);

bool buffer_insert_blank_data(Buffer *buffer, size_t index, size_t count,
                                                            Status *status);

void buffer_insert_slice_fast(Buffer *buffer, size_t index, Slice *slice);

bool buffer_insert_slice(Buffer *buffer, size_t index, Slice *slice,
                                                       Status *status);

void buffer_prepend_data_fast(Buffer *buffer, const char *bytes, size_t count);

bool buffer_prepend_data(Buffer *buffer, const char *bytes, size_t count,
                                                      Status *status);

void buffer_prepend_slice_fast(Buffer *buffer, Slice *slice);

bool buffer_prepend_slice(Buffer *buffer, Slice *slice, Status *status);

void buffer_append_data_fast(Buffer *buffer, const char *bytes, size_t count);

bool buffer_append_data(Buffer *buffer, const char *bytes, size_t count,
                                                           Status *status);

void buffer_append_slice_fast(Buffer *buffer, Slice *slice);

bool buffer_append_slice(Buffer *buffer, Slice *slice, Status *status);

void buffer_overwrite_data_fast(Buffer *buffer, size_t index, const char *bytes,
                                                              size_t count);

bool buffer_overwrite_data(Buffer *buffer, size_t index, const char *bytes,
                                                         size_t count,
                                                         Status *status);

void buffer_overwrite_slice_fast(Buffer *buffer, size_t index, Slice *slice);

bool buffer_overwrite_slice(Buffer *buffer, size_t index, Slice *slice,
                                                          Status *status);

void buffer_zero_section_fast(Buffer *buffer, size_t index, size_t len);

bool buffer_zero_section(Buffer *buffer, size_t index, size_t len,
                                                       Status *status);

void buffer_zero_fast(Buffer *buffer);

bool buffer_zero(Buffer *buffer, Status *status);

bool buffer_encode(Buffer *src, const char *src_encoding,
                                const char *dst_encoding,
                                Buffer *dst,
                                Status *status);
#endif

/* vi: set et ts=4 sw=4: */
