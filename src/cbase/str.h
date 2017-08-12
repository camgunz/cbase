#ifndef STR_H__
#define STR_H__

enum {
    STRING_EMPTY = 1,
};

typedef struct StringStruct {
    Buffer buffer;
    size_t len;
    size_t byte_len;
} String;

/*
 * cstr (NULL-terminated UTF-8 data)
 * UTF-8 data (not NULL-terminated)
 * SSlice
 * String
 * data
 * Slice
 *   - UTF-8
 *   - Local
 * Buffer
 *   - UTF-8
 *   - Local
 */

static inline
void string_assign_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    buffer_assign_fast(&string->buffer, cs, byte_len + 1);
    string->len = len;
    string->byte_len = byte_len;
}

static inline
bool string_assign_cstr_full(String *string, const char *cs, size_t len,
                                                             size_t byte_len,
                                                             Status *status) {
    if (!buffer_assign(&string->buffer, cs, byte_len + 1, status)) {
        return false;
    }

    string->len = len;
    string->byte_len = byte_len;
}

static inline
bool string_assign_cstr(String *string, const char *cs, Status *status) {
    size_t len = 0;
    size_t byte_len = 0;

    if (cs) {
        if (!utf8_len_and_byte_len(cs, &len, &byte_len, status)) {
            return false;
        }
    }

    return string_assign_cstr_full(string, cs, len, byte_len, status);
}

static inline
void string_assign_utf8_data_full_fast(String *string, const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    char terminating_null = '\0';

    buffer_assign_fast(&string->buffer, data, byte_len);
    buffer_append_fast(&string->buffer, &terminating_null, 1);

    string->len = len;
    string->byte_len = byte_len;
}

static inline
bool string_assign_utf8_data_full(String *string, const char *data,
                                                  size_t len,
                                                  size_t byte_len,
                                                  Status *status) {
    char terminating_null = '\0';

    if ((!buffer_ensure_capacity(&string->buffer, byte_len + 1, status)) ||
        (!buffer_assign(&string->buffer, data, byte_len)) ||
        (!buffer_append_fast(&string->buffer, &terminating_null, 1))) {
        return false;
    }

    string->len = len;
    string->byte_len = byte_len;

    return status_ok(status);
}

static inline
bool string_assign_utf8_data(String *string, const char *data,
                                             size_t byte_len,
                                             Status *status) {
    size_t len = 0;

    if (data) {
        if (!utf8ncmp(data, byte_len, &len, status)) {
            return false;
        }
    }

    return string_assign_full(string, data, len, byte_len, status);
}

static inline
void string_assign_sslice_fast(String *string, SSlice *sslice) {
    string_assign_utf8_data_full_fast(string, sslice->data, sslice->len,
                                                            sslice->byte_len);
}

static inline
bool string_assign_sslice(String *string, SSlice *sslice, Status *status) {
    return string_assign_utf8_data_full_fast(string, sslice->data,
                                                     sslice->len,
                                                     sslice->byte_len,
                                                     status);
}

static inline
void string_assign_string_fast(String *dst, String *src) {
    string_assign_utf8_data_full_fast(dst, src->data, src->len, src->byte_len);
}

static inline
bool string_assign_string(String *dst, String *src, Status *status) {
    return string_assign_utf8_data_full(dst, src->data, src->len,
                                                        src->byte_len,
                                                        status);
}

bool string_assign_data_fast(String *string, const char *data,
                                             size_t byte_len,
                                             const char *encoding) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return false;
    }

    if ((!buffer_encode(buffer, encoding, "utf-8", &output, status)) ||
        (!string_assign_utf8_data_fast(string, output.array.data,
                                               output.array.len,
                                               status))) {
        buffer_free(&output);
        return false;
    }

    buffer_free(&output);
    return status_ok(status);
}

bool string_assign_data(String *string, const char *data,
                                        size_t byte_len,
                                        const char *encoding) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return false;
    }

    if ((!buffer_encode(buffer, encoding, "utf-8", &output, status)) ||
        (!string_assign_utf8_data(string, output.array.data, output.array.len,
                                                             status))) {
        buffer_free(&output);
        return false;
    }

    buffer_free(&output);
    return status_ok(status);
}

static inline
bool string_assign_slice_fast(String *string, Slice *slice,
                                              const char *encoding,
                                              Status *status) {
    return string_assign_data_fast(string, slice->data, slice->len, encoding,
                                                                    status);
}

static inline
bool string_assign_slice(String *string, Slice *slice, const char *encoding,
                                                       Status *status) {
    return string_assign_data(string, slice->data, slice->len, encoding,
                                                               status);
}

static inline
bool string_assign_utf8_slice_fast(String *string, Slice *slice,
                                                   Status *status) {
    return string_assign_utf8_data_fast(string, slice->data, slice->len,
                                                             status);
}

static inline
bool string_assign_utf8_slice(String *string, Slice *slice, Status *status) {
    return string_assign_utf8_data(string, slice->data, slice->len, status);
}

static inline
bool string_assign_local_slice_fast(String *string, Slice *slice,
                                                    Status *status) {
    return string_assign_data_fast(string, slice->data, slice->len, "wchar_t",
                                                                    status);
}

static inline
bool string_assign_local_slice(String *string, Slice *slice, Status *status) {
    return string_assign_data(string, slice->data, slice->len, "wchar_t",
                                                               status);
}

bool string_assign_buffer_fast(String *string, Buffer *buffer,
                                               const char *encoding,
                                               Status *status) {
    return string_assign_data_fast(string, buffer->array.data,
                                           buffer->array.len,
                                           encoding,
                                           status);
}

bool string_assign_buffer(String *string, Buffer *buffer, const char *encoding,
                                                          Status *status) {
    return string_assign_data(string, buffer->array.data, buffer->array.len,
                                                          encoding,
                                                          status);
}

static inline
bool string_assign_utf8_buffer_fast(String *string, Buffer *buffer
                                                    Status *status) {
    return string_assign_utf8_data_fast(string, buffer->array.data,
                                                buffer->array.len,
                                                status);
}

static inline
bool string_assign_utf8_buffer(String *string, Buffer *buffer,
                                               Status *status) {
    return string_assign_utf8_data(string, buffer->array.data,
                                           buffer->array.len,
                                           status);
}

static inline
bool string_assign_local_buffer_fast(String *string, Buffer *buffer,
                                                     Status *status) {
    return string_assign_buffer_fast(string, buffer, "wchar_t", status);
}

static inline
bool string_assign_local_buffer(String *string, Buffer *buffer,
                                                Status *status) {
    return string_assign_buffer(string, buffer, "wchar_t", status);
}

static inline
bool string_ensure_capacity(String *string, size_t byte_len, Status *status) {
    return buffer_ensure_capacity(&s->buffer, byte_len + 1, status);
}

static inline
void string_init(String *string) {
    buffer_init(&string->buffer, sizeof(char));
    string->len = 0;
    string->byte_len = 0;
}

static inline
bool string_init_alloc(String *string, size_t alloc, Status *status) {
    if (!buffer_init_alloc(&string->buffer, alloc, status)) {
        return false;
    }

    string->len = 0;
    string->byte_len = 0;

    return status_ok(status);
}

static inline
bool string_init_from_cstr(String *string, const char *cs, Status *status) {
    string_init(string);
    return string_assign_cstr(string, cs, status);
}

static inline
bool string_init_from_cstr_full(String *string, const char *cs,
                                                size_t len,
                                                size_t byte_len,
                                                Status *status) {
    string_init(string);
    return string_assign_cstr_full(string, cs, len, byte_len, status);
}

static inline
bool string_init_from_utf8_data(String *string, const char *data,
                                                Status *status) {
    string_init(string);
    return string_assign_utf8_data(string, data, status);
}

static inline
bool string_init_from_utf8_data_full(String *string, const char *data,
                                                     size_t len,
                                                     size_t byte_len,
                                                     Status *status) {
    string_init(string);
    return string_assign_utf8_data_full(string, data, len, byte_len, status);
}

static inline
bool string_init_from_sslice(String *string, SSlice *sslice, Status *status) {
    string_init(string);
    return string_assign_sslice(string, sslice, status);
}

static inline
bool string_init_from_string(String *string, String *input, Status *status) {
    string_init(string);
    return string_assign_string(string, input, status);
}

static inline
bool string_init_from_slice(String *string, Slice *slice, const char *encoding,
                                                          Status *status) {
    string_init(string);
    return string_assign_slice(string, slice, encoding, status);
}

static inline
bool string_init_from_utf8_slice(String *string, Slice *slice,
                                                 Status *status) {
    string_init(string);
    return string_assign_utf8_slice(string, slice, status);
}

static inline
bool string_init_from_local_slice(String *string, Slice *slice, 
                                                  Status *status) {
    string_init(string);
    return string_assign_local_slice(string, slice, status);
}

static inline
bool string_init_from_buffer(String *string, Buffer *buffer, Status *status) {
    string_init(string);
    return string_assign_buffer(string, buffer, status);
}

static inline
bool string_init_from_utf8_buffer(String *string, Buffer *buffer,
                                                  Status *status) {
    string_init(string);
    return string_assign_utf8_buffer(string, buffer, status);
}

static inline
void string_init_from_local_buffer(String *string, Buffer *buffer,
                                                   Status *status) {
    string_init(string);
    return string_assign_local_buffer(string, buffer, status);
}

static inline
bool string_new(String **string, Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    string_init(*string);

    return status_ok(status);
}

static inline
bool string_new_alloc(String **string, size_t alloc, Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_alloc(*string);
}

static inline
bool string_new_from_cstr(String **string, const char *cs, Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_cstr(*string, cs, status);
}

bool string_new_from_cstr_full(String *string, const char *cs,
                                               size_t len,
                                               size_t byte_len,
                                               Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_cstr_full(*string, cs, len, byte_len, status);
}

static inline
bool string_new_from_utf8_data_full(String *string, const char *data,
                                                     size_t len,
                                                     size_t byte_len,
                                                     Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_utf8_data_full(*string, data, len, byte_len,
                                                               status);
}

static inline
bool string_new_from_sslice(String *string, SSlice *sslice, Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_sslice(*string, sslice, status);
}

static inline
bool string_new_from_string(String *string, String *input, Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_string(*string, input, status);
}

static inline
bool string_new_from_slice(String *string, Slice *slice, const char *encoding,
                                                          Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_slice(*string, slice, encoding, status);
}

static inline
bool string_new_from_utf8_slice(String *string, Slice *slice,
                                                 Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_utf8_slice(*string, slice, status);
}

static inline
bool string_new_from_local_slice(String *string, Slice *slice, 
                                                  Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_local_slice(*string, slice, status);
}

static inline
bool string_new_from_buffer(String *string, Buffer *buffer, Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_buffer(*string, buffer, status);
}

static inline
bool string_new_from_utf8_buffer(String *string, Buffer *buffer,
                                                  Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_utf8_buffer(*string, buffer, status);
}

static inline
void string_new_from_local_buffer(String *string, Buffer *buffer,
                                                   Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    return string_init_from_local_buffer(*string, buffer, status);
}

static inline
bool string_compact(String *string, Status *status) {
    return buffer_compact(&string->buffer, status);
}

static inline
void string_insert_cstr_full_fast(String *string, size_t index,
                                                  const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    buffer_insert_fast(&string->buffer, index, cs, byte_len + 1);
    string->len += len;
    string->byte_len += byte_len;
}

static inline
bool string_insert_cstr_full(String *string, size_t index, const char *cs,
                                                           size_t len,
                                                           size_t byte_len,
                                                           Status *status) {
    if (index > string->len) {
        return index_out_of_bounds(status);
    }

    if (!string_ensure_capacity(string, string->byte_len + sslice->byte_len,
                                        status)) {
        return false;
    }

    string_insert_cstr_full_fast(string, index, cs, len, byte_len);
}

static inline
bool string_insert_cstr(String *string, size_t index, const char *cs,
                                                      Status *status) {
    size_t len = 0;
    size_t byte_len = 0;

    if (cs) {
        if (!utf8_len_and_byte_len(cs, &len, &byte_len, status)) {
            return false;
        }
    }

    string_insert_cstr_full(string, index, cs, len, byte_len);
}

static inline
bool string_insert_utf8_data_full_fast(String *string, size_t index,
                                                       const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    buffer_insert_fast(string->buffer, index, cs, byte_len);
    buffer_insert_fast(string->buffer, index + byte_len, "\0", 1);
    string->len += len;
    string->byte_len += byte_len;
}

static inline
bool string_insert_utf8_data_full(String *string, size_t index,
                                                  const char *data,
                                                  size_t len,
                                                  size_t byte_len,
                                                  Status *status) {
    if (index > string->len) {
        return index_out_of_bounds(status);
    }

    if (!string_ensure_capacity(string, string->byte_len + byte_len, status)) {
        return false:
    }

    string_insert_utf8_data_full_fast(string, index, data, len, byte_len);
}

static inline
bool string_insert_utf8_data(String *string, size_t index, const char *data,
                                                           size_t byte_len,
                                                           Status *status) {

    size_t len = 0;

    if (data) {
        if (!utf8nlen(data, &len, status)) {
            return false;
        }
    }

    return string_insert_utf8_data(string, index, data, len, byte_len, status);
}

static inline
bool string_insert_sslice_fast(String *string, size_t index, SSlice *sslice,
                                                             Status *status) {
    return string_insert_utf8_data_full_fast(string, index, sslice->data,
                                                            sslice->len,
                                                            sslice->byte_len,
                                                            status);
}

static inline
bool string_insert_sslice(String *string, size_t index, SSlice *sslice,
                                                        Status *status) {
    return string_insert_utf8_data_full(string, index, sslice->data,
                                                       sslice->len,
                                                       sslice->byte_len,
                                                       status);
}

static inline
bool string_insert_string_fast(String *dst, size_t index, String *src,
                                                          Status *status) {
    return string_insert_cstr_full_fast(dst, index, src->buffer.data,
                                                    src->len,
                                                    src->byte_len,
                                                    status);
}

static inline
bool string_insert_string(String *dst, size_t index, String *src,
                                                     Status *status) {
    return string_insert_cstr_full(dst, index, src->buffer.data,
                                               src->len,
                                               src->byte_len,
                                               status);
}

static inline
bool string_insert_slice_fast(String *string, size_t index,
                                              Slice *slice,
                                              const char *encoding,
                                              Status *status) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return false;
    }

    if (!slice_encode(slice, encoding, "utf-8", &output, status)) {
        buffer_free(&output);
        return false;
    }

    string_insert_utf8_data_fast(string, index, output.array.data, status);
    buffer_free(&output);

    return status_ok(status);
}

static inline
bool string_insert_slice(String *string, size_t index, Slice *slice,
                                                       const char *encoding,
                                                       Status *status) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return false;
    }

    if ((!slice_encode(slice, encoding, "utf-8", &output, status)) ||
        (!string_insert_utf8_data(string, index, output.array.data, status))) {
        buffer_free(&output);
        return false;
    }

    buffer_free(&output);
    return status_ok(status);
}

static inline
bool string_insert_utf8_slice_fast(String *string, size_t index,
                                                   Slice *slice,
                                                   Status *status) {
    return string_insert_utf8_data_fast(string, index, slice->data, slice->len,
                                                                    status);
}

static inline
bool string_insert_utf8_slice(String *string, size_t index, Slice *slice,
                                                            Status *status) {
    return string_insert_utf8_data(string, index, slice->data, slice->len,
                                                               status);
}

static inline
bool string_insert_local_slice_fast(String *string, size_t index,
                                                    Slice *slice,
                                                    Status *status) {
    return string_insert_slice_fast(string, index, slice, "wchar_t", status);
}

static inline
bool string_insert_local_slice(String *string, size_t index, Slice *slice,
                                                             Status *status) {
    return string_insert_slice(string, index, slice, "wchar_t", status);
}

static inline
bool string_insert_buffer_fast(String *string, size_t index,
                                               Buffer *buffer,
                                               const char *encoding,
                                               Status *status) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return false;
    }

    if (!buffer_encode(buffer, encoding, "utf-8", &output, status)) {
        buffer_free(&output);
        return false;
    }

    string_insert_utf8_data_fast(string, index, output.array.data, status);
    buffer_free(&output);

    return status_ok(status);
}

static inline
bool string_insert_buffer(String *string, size_t index, Buffer *buffer,
                                                        const char *encoding,
                                                        Status *status) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return false;
    }

    if ((!buffer_encode(buffer, encoding, "utf-8", &output, status)) ||
        (!string_insert_utf8_data(string, index, output.array.data, status))) {
        buffer_free(&output);
        return false;
    }

    buffer_free(&output);
    return status_ok(status);
}

static inline
bool string_insert_utf8_buffer_fast(String *string, size_t index,
                                                    Buffer *buffer,
                                                    Status *status) {
    return string_insert_utf8_data_fast(string, index, buffer->data,
                                                       buffer->len,
                                                       status);
}

static inline
bool string_insert_utf8_buffer(String *string, size_t index, Buffer *buffer,
                                                             Status *status) {
    return string_insert_utf8_data(string, index, buffer->data, buffer->len,
                                                                status);
}

static inline
bool string_insert_local_buffer_fast(String *string, size_t index,
                                                     Buffer *buffer,
                                                     Status *status) {
    return string_insert_buffer_fast(string, index, buffer, "wchar_t", status);
}

static inline
bool string_insert_local_buffer(String *string, size_t index, Buffer *buffer,
                                                              Status *status) {
    return string_insert_buffer(string, index, buffer, "wchar_t", status);
}

static inline
bool string_insert_data_fast(String *string, size_t index,
                                             const char *data,
                                             size_t byte_len,
                                             const char *encoding,
                                             Status *status) {
    Slice slice;

    slice->data = data;
    slice->len = byte_len;

    return string_insert_slice_fast(string, index, &slice, encoding, status);
}

static inline
bool string_insert_data(String *string, size_t index, const char *data,
                                                      size_t byte_len,
                                                      const char *encoding,
                                                      Status *status) {
    Slice slice;

    slice->data = data;
    slice->len = byte_len;

    return string_insert_slice(string, index, &slice, encoding, status);
}

static inline
bool string_insert_local_data_fast(String *string, size_t index,
                                                   const char *data,
                                                   size_t byte_len,
                                                   Status *status) {
    return string_insert_data_fast(string, index, data, byte_len, "wchar_t",
                                                                  status);
}

static inline
bool string_insert_local_data(String *string, size_t index, const char *data,
                                                            size_t byte_len,
                                                            Status *status) {
    return string_insert_data(string, index, data, byte_len, "wchar_t",
                                                             status);
}

static inline
void string_prepend_cstr_full_fast(String *string, const char *cs,
                                                   size_t len,
                                                   size_t byte_len) {
    string_insert_cstr_full_fast(string, 0, cs, len, byte_len);
}

static inline
bool string_prepend_cstr_full(String *string, const char *cs, size_t len,
                                                              size_t byte_len,
                                                              Status *status) {
    return string_insert_cstr_full(string, 0, cs, len, byte_len, status);
}

static inline
bool string_prepend_cstr(String *string, const char *cs, Status *status) {
    return string_insert_cstr(string, 0, cs, status);
}

static inline
bool string_prepend_utf8_data_full_fast(String *string, const char *data,
                                                        size_t len,
                                                        size_t byte_len) {
    return string_insert_utf8_data_full_fast(string, 0, data, len, byte_len);
}

static inline
bool string_prepend_utf8_data_full(String *string, const char *data,
                                                   size_t len,
                                                   size_t byte_len,
                                                   Status *status) {
    return string_insert_utf8_data_full(string, 0, data, len, byte_len,
                                                              status);
}

static inline
bool string_prepend_utf8_data(String *string, const char *data,
                                              size_t byte_len,
                                              Status *status) {
    return string_insert_utf8_data(string, 0, data, byte_len, status);
}

static inline
bool string_prepend_sslice_fast(String *string, SSlice *sslice,
                                                Status *status) {
    return string_insert_sslice_fast(string, 0, sslice, status);
}

static inline
bool string_prepend_sslice(String *string, SSlice *sslice, Status *status) {
    return string_insert_sslice(string, 0, sslice, status);
}

static inline
bool string_prepend_string_fast(String *dst, String *src, Status *status) {
    return string_insert_string_fast(dst, 0, src, status);
}

static inline
bool string_prepend_string(String *dst, String *src, Status *status) {
    return string_insert_string(dst, 0, src, status);
}

static inline
bool string_prepend_slice_fast(String *string, Slice *slice,
                                               const char *encoding,
                                               Status *status) {
    return string_insert_slice_fast(string, 0, slice, encoding, status);
}

static inline
bool string_prepend_slice(String *string, Slice *slice, const char *encoding,
                                                        Status *status) {
    return string_insert_slice(string, 0, slice, encoding, status);
}

static inline
bool string_prepend_utf8_slice_fast(String *string, Slice *slice,
                                                    Status *status) {
    return string_insert_utf8_slice_fast(string, 0, slice->data, slice->len, status);
}

static inline
bool string_prepend_utf8_slice(String *string, size_t index, Slice *slice,
                                                             Status *status) {
    return string_insert_utf8_slice(string, 0, slice->data, slice->len, status);
}

static inline
bool string_prepend_local_slice_fast(String *string, Slice *slice,
                                                     Status *status) {
    return string_insert_local_slice_fast(string, 0, slice, status);
}

static inline
bool string_prepend_local_slice(String *string, Slice *slice, Status *status) {
    return string_insert_local_slice(string, 0, slice, status);
}

static inline
bool string_prepend_buffer_fast(String *string, Buffer *buffer,
                                                const char *encoding,
                                                Status *status) {
    return string_insert_buffer_fast(string, 0, buffer, encoding, status);
}

static inline
bool string_prepend_buffer(String *string, Buffer *buffer, const char *encoding,
                                                           Status *status) {
    return string_insert_buffer(string, 0, buffer, encoding, status);
}

static inline
bool string_prepend_utf8_buffer_fast(String *string, Buffer *buffer,
                                                     Status *status) {
    return string_insert_utf8_buffer_fast(string, 0, buffer, status);
}

static inline
bool string_prepend_utf8_buffer(String *string, Buffer *buffer,
                                                Status *status) {
    return string_insert_utf8_buffer(string, 0, buffer, status);
}

static inline
bool string_prepend_local_buffer_fast(String *string, Buffer *buffer,
                                                      Status *status) {
    return string_insert_local_buffer_fast(string, 0, buffer, status);
}

static inline
bool string_prepend_local_buffer(String *string, Buffer *buffer,
                                                 Status *status) {
    return string_insert_local_buffer(string, 0, buffer, status);
}

static inline
bool string_prepend_data_fast(String *string, const char *data,
                                              size_t byte_len,
                                              const char *encoding,
                                              Status *status) {
    return string_insert_data_fast(string, 0, data, byte_len, encoding,
                                                              status);
}

static inline
bool string_prepend_data(String *string, const char *data,
                                         size_t byte_len,
                                         const char *encoding,
                                         Status *status) {
    return string_insert_data(string, 0, data, byte_len, encoding, status);
}

static inline
bool string_prepend_local_data_fast(String *string, const char *data,
                                                    size_t byte_len,
                                                    Status *status) {
    return string_insert_local_data_fast(string, 0, data, byte_len, status);
}

static inline
bool string_prepend_local_data(String *string, const char *data,
                                               size_t byte_len,
                                               Status *status) {
    return string_insert_local_data(string, 0, data, byte_len, status);
}

static inline
void string_append_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    string_insert_cstr_full_fast(string, 0, cs, len, byte_len);
}

static inline
bool string_append_cstr_full(String *string, const char *cs, size_t len,
                                                             size_t byte_len,
                                                             Status *status) {
    return string_insert_cstr_full(string, 0, cs, len, byte_len, status);
}

static inline
bool string_append_cstr(String *string, const char *cs, Status *status) {
    return string_insert_cstr(string, 0, cs, status);
}

static inline
bool string_append_utf8_data_full_fast(String *string, const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    return string_insert_utf8_data_full_fast(string, 0, data, len, byte_len);
}

static inline
bool string_append_utf8_data_full(String *string, const char *data,
                                                  size_t len,
                                                  size_t byte_len,
                                                  Status *status) {
    return string_insert_utf8_data_full(string, 0, data, len, byte_len,
                                                              status);
}

static inline
bool string_append_utf8_data(String *string, const char *data,
                                             size_t byte_len,
                                             Status *status) {
    return string_insert_utf8_data(string, 0, data, byte_len, status);
}

static inline
bool string_append_sslice_fast(String *string, SSlice *sslice,
                                               Status *status) {
    return string_insert_sslice_fast(string, 0, sslice, status);
}

static inline
bool string_append_sslice(String *string, SSlice *sslice, Status *status) {
    return string_insert_sslice(string, 0, sslice, status);
}

static inline
bool string_append_string_fast(String *dst, String *src, Status *status) {
    return string_insert_string_fast(dst, 0, src, status);
}

static inline
bool string_append_string(String *dst, String *src, Status *status) {
    return string_insert_string(dst, 0, src, status);
}

static inline
bool string_append_slice_fast(String *string, Slice *slice,
                                              const char *encoding,
                                              Status *status) {
    return string_insert_slice_fast(string, 0, slice, encoding, status);
}

static inline
bool string_append_slice(String *string, Slice *slice, const char *encoding,
                                                       Status *status) {
    return string_insert_slice(string, 0, slice, encoding, status);
}

static inline
bool string_append_utf8_slice_fast(String *string, Slice *slice,
                                                   Status *status) {
    return string_insert_utf8_slice_fast(string, 0, slice->data, slice->len, status);
}

static inline
bool string_append_utf8_slice(String *string, size_t index, Slice *slice,
                                                            Status *status) {
    return string_insert_utf8_slice(string, 0, slice->data, slice->len, status);
}

static inline
bool string_append_local_slice_fast(String *string, Slice *slice,
                                                    Status *status) {
    return string_insert_local_slice_fast(string, 0, slice, status);
}

static inline
bool string_append_local_slice(String *string, Slice *slice, Status *status) {
    return string_insert_local_slice(string, 0, slice, status);
}

static inline
bool string_append_buffer_fast(String *string, Buffer *buffer,
                                               const char *encoding,
                                               Status *status) {
    return string_insert_buffer_fast(string, 0, buffer, encoding, status);
}

static inline
bool string_append_buffer(String *string, Buffer *buffer, const char *encoding,
                                                          Status *status) {
    return string_insert_buffer(string, 0, buffer, encoding, status);
}

static inline
bool string_append_utf8_buffer_fast(String *string, Buffer *buffer,
                                                    Status *status) {
    return string_insert_utf8_buffer_fast(string, 0, buffer, status);
}

static inline
bool string_append_utf8_buffer(String *string, Buffer *buffer,
                                               Status *status) {
    return string_insert_utf8_buffer(string, 0, buffer, status);
}

static inline
bool string_append_local_buffer_fast(String *string, Buffer *buffer,
                                                     Status *status) {
    return string_insert_local_buffer_fast(string, 0, buffer, status);
}

static inline
bool string_append_local_buffer(String *string, Buffer *buffer,
                                                Status *status) {
    return string_insert_local_buffer(string, 0, buffer, status);
}

static inline
bool string_append_data_fast(String *string, const char *data,
                                             size_t byte_len,
                                             const char *encoding,
                                             Status *status) {
    return string_insert_data_fast(string, 0, data, byte_len, encoding,
                                                              status);
}

static inline
bool string_append_data(String *string, const char *data,
                                        size_t byte_len,
                                        const char *encoding,
                                        Status *status) {
    return string_insert_data(string, 0, data, byte_len, encoding, status);
}

static inline
bool string_append_local_data_fast(String *string, const char *data,
                                                   size_t byte_len,
                                                   Status *status) {
    return string_insert_local_data_fast(string, 0, data, byte_len, status);
}

static inline
bool string_append_local_data(String *string, const char *data,
                                              size_t byte_len,
                                              Status *status) {
    return string_insert_local_data(string, 0, data, byte_len, status);
}

static inline
bool string_slice_fast(String *string, size_t index, size_t len,
                                                     SSlice *sslice,
                                                     ssize_t *error) {
    char *start = NULL;
    char *end = NULL;

    if (!utf8_slice_fast(s->data, index, len, &start, &end, error)) {
        return false;
    }

    sslice->len = len;
    sslice->byte_len = end - start;
    sslice->data = start;

    return true;
}

static inline
bool string_slice(String *s, size_t index, size_t len, SSlice *sslice,
                                                       Status *status) {
    ssize_t error;

    if (!string_slice_fast(s, index, len, sslice, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

static inline
void string_slice_full(String *string, SSlice *sslice) {
    sslice->data = s->data;
    sslice->len = s->len;
    sslice->byte_len = s->byte_len;
}

bool  string_printf(String *string, Status *status, const char *fmt, ...);
bool  string_vprintf(String *string, Status *status, const char *fmt,
                                                     va_list args);
bool  string_append_printf(String *string, Status *status, const char *fmt,
                                                           ...);
bool  string_append_vprintf(String *string, Status *status, const char *fmt,
                                                            va_list args);

static inline
bool string_delete_fast(String *string, size_t index, size_t len,
                                                      ssize_t *error) {
    char *start = NULL;
    char *end = NULL;

    size_t byte_index = 0;
    size_t byte_len = 0;

    if (!len) {
        return status_ok(status);
    }

    if (index) {
        if (!utf8_index_fast(string->buffer.array.data, index, &start,
                                                               error)) {
            return false;
        }

        byte_index = start - string->buffer.array.data;
    }

    if (!utf8_skip_fast(start, len, &end, error)) {
        return false;
    }

    byte_len = end - start;

    buffer_delete_fast(&string->buffer, byte_index, byte_len);

    string->len -= len;
    string->byte_len -= byte_len;

    return status_ok(status);
}

static inline
bool string_delete(String *s, size_t index, size_t len, Status *status) {
    ssize_t error;

    if ((index + len) > (string->len + 1)) {
        return index_out_of_bounds(status);
    }

    if (!string_delete_fast(string, index, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

static inline
bool string_get_first_rune(String *s, rune *r, Status *status) {
    if (string_empty(s)) {
        return empty(status);
    }

    return utf8_get_first_rune(s->data, r, status);
}

bool  string_encode(String *string, const char *encoding, Buffer *out,
                                                          Status *status);

void  string_free(String *string);

static inline
bool string_get_first_rune(String *string, rune *r, Status *status) {
    return sbuffer_get_first_rune(s->data, r, status);
}

static inline
void string_copy_fast(String *dst, String *src) {
    dst->len = src->len;
    dst->byte_len = src->byte_len;

    if (src->byte_len) {
        cbmemmove(dst->data, src->data, src->byte_len + 1);
    }
}

static inline
bool string_skip_runes(String *string, size_t rune_count, Status *status) {
    SSlice sslice;

    string_slice_full(string, &sslice);

    return (
        sslice_skip_runes(string, rune_count, status) &&
        string_assign_sslice(string, &sslice)
    );
}

static inline
bool string_skip_rune_if_equals(String *string, rune r, Status *status) {
    SSlice sslice;

    string_slice_full(string, &sslice);

    return (
        sslice_skip_rune_if_equals(string, r, status) &&
        string_assign_sslice(string, &sslice)
    );
}

static inline
bool string_pop_rune(String *string, rune *r, Status *status) {
    SSlice sslice;

    string_slice_full(string, &sslice);

    return (
        sslice_pop_rune(string, r, status) &&
        string_assign_sslice(string, &sslice)
    );
}

static inline
bool string_seek_to(String *string, rune r, Status *status) {
    SSlice sslice;

    string_slice_full(string, &sslice);

    return (
        sslice_seek_to(string, r, status) &&
        string_assign_sslice(string, &sslice)
    );
}

static inline
bool string_seek_to_cstr(String *string, const char *cs, Status *status) {
    SSlice sslice;

    string_slice_full(string, &sslice);

    return (
        sslice_seek_to_cstr(string, cs, status) &&
        string_assign_sslice(string, &sslice)
    );
}

static inline
bool string_truncate_runes(String *string, size_t rune_count, Status *status) {
    SSlice sslice;

    string_slice_full(string, &sslice);

    return (
        sslice_truncate_runes(string, rune_count, status) &&
        string_assign_sslice(string, &sslice)
    );
}

static inline
bool string_empty(String *string) {
    return sbuffer_empty(string->len, string->byte_len);
}

static inline
char* string_to_cstr(String *string) {
    return cbstrdup(s->data);
}

static inline
bool string_contents_equal(String *s1, String *s2) {
    return buffer_equals(&s1->buffer, &s2->buffer);
}

static inline
bool string_equals_cstr_len(String *string, const char *cs, size_t byte_len) {
    return buffer_equals_data(&string->buffer, cs, byte_len);
}

static inline
bool string_equals_cstr(String *string, const char *cs) {
    return buffer_equals_data(&string->buffer, cs, strlen(cs) + 1);
}

static inline
bool string_starts_with_cstr_len(String *string, const char *cs,
                                                 size_t byte_len,
                                                 bool *starts_with,
                                                 Status *status) {
    if (!buffer_equals_data_at(&string->buffer, 0, cs, byte_len, starts_with,
                                                                 status)) {
        if (status_match(status, "base", ERROR_OUT_OF_BOUNDS)) {
            status_clear(&status);
            *starts_with = false;
        }
        else {
            return false;
        }
    }

    return status_ok(status);
}

static inline
bool string_starts_with_cstr(String *string, const char *cs, bool *starts_with,
                                                             Status *status) {
    return string_starts_with_cstr_len(string, cs, strlen(cs), starts_with,
                                                               status);
}

static inline
bool string_ends_with_cstr_len(String *string, const char *cs,
                                               size_t byte_len,
                                               bool *ends_with,
                                               Status *status) {
    size_t index = string->buffer.len - byte_len;

    return buffer_equals_data_at(&string->buffer, index, byte_len, ends_with,
                                                                   status);
}

static inline
bool string_ends_with_cstr(String *string, const char *cs, bool *ends_with,
                                                           Status *status) {
    return string_ends_with_cstr_len(string, cs, strlen(cs) + 1, ends_with,
                                                                 status);
}

static inline
bool string_localize(String *string, Buffer *out, Status *status) {
    return string_encode(string, "wchar_t", out, status);
}

static inline
void string_clear(String *string) {
    buffer_clear_no_zero(&string->buffer);
    sbuffer_clear(&string->len, &string->byte_len);
    if (s->data) {
        *s->data = '\0';
    }
}

#endif

/* vi: set et ts=4 sw=4: */
