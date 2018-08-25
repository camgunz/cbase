#pragma once

#ifndef SLICE_H__
#define SLICE_H__

struct BufferStruct;

typedef struct SliceStruct {
    size_t len;
    char *data;
} Slice;

void slice_assign_data(Slice *slice, char *data, size_t len);

void slice_assign_slice(Slice *dst, Slice *src);

bool slice_equals_data_at_fast(Slice *slice, size_t index, size_t len,
                                                           const void *data);

bool slice_equals_data_at(Slice *slice, size_t index, size_t len,
                                                      const void *data,
                                                      bool *equal,
                                                      Status *status);

bool slice_equals_data(Slice *slice, const char *data);

bool slice_equals(Slice *s1, Slice *s2);

bool slice_starts_with_data_fast(Slice *slice, const void *data, size_t len);

bool slice_starts_with_data(Slice *slice, const void *data, size_t len,
                                                            bool *equal,
                                                            Status *status);

bool slice_ends_with_data_fast(Slice *slice, const void *data, size_t len);

bool slice_ends_with_data(Slice *slice, const void *data, size_t len,
                                                          bool *equal,
                                                          Status *status);

void slice_read_fast(Slice *slice, size_t index, size_t len, void *out);

bool slice_read(Slice *slice, size_t index, size_t len, void *out,
                                                        Status *status);

void slice_copy(Slice *dst, Slice *src);

bool slice_encode(Slice *src, const char *src_encoding,
                              const char *dst_encoding,
                              struct BufferStruct *dst,
                              Status *status);

void slice_clear(Slice *slice);

#endif

/* vi: set et ts=4 sw=4: */
