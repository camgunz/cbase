#include "cbase.h"

inline
void buffer_assign_data_fast(Buffer *buffer, const char *bytes, size_t len) {
    array_assign_fast(&buffer->array, bytes, len);
}

inline
bool buffer_assign_data(Buffer *buffer, const char *bytes, size_t len,
                                                           Status *status) {
    return array_assign(&buffer->array, bytes, len, status);
}

inline
void buffer_assign_buffer_fast(Buffer *dst, Buffer *src) {
    array_assign_array_same_fast(&dst->array, &src->array);
}

inline
bool buffer_assign_buffer(Buffer *dst, Buffer *src, Status *status) {
    return array_assign_array_same(&dst->array, &src->array, status);
}

inline
void buffer_assign_slice_fast(Buffer *buffer, Slice *slice) {
    array_assign_fast(&buffer->array, slice->data, slice->len);
}

inline
bool buffer_assign_slice(Buffer *buffer, Slice *slice, Status *status) {
    return array_assign(&buffer->array, slice->data, slice->len, status);
}

inline
bool buffer_ensure_capacity(Buffer *buffer, size_t len, Status *status) {
    return array_ensure_capacity(&buffer->array, len, status);
}

inline
bool buffer_set_size(Buffer *buffer, size_t len, Status *status) {
    return array_set_size(&buffer->array, len, status);
}

inline
void buffer_init(Buffer *buffer) {
    array_init(&buffer->array, sizeof(char));
}

inline
bool buffer_init_alloc(Buffer *buffer, size_t alloc, Status *status) {
    return array_init_alloc(&buffer->array, sizeof(char), alloc, status);
}

inline
bool buffer_init_from_data(Buffer *buffer, const char *data, size_t len,
                                                             Status *status) {
    return (
        buffer_init_alloc(buffer, len, status) &&
        buffer_assign_data(buffer, data, len, status)
    );
}

inline
bool buffer_new(Buffer **buffer, Status *status) {
    if (!cbmalloc(1, sizeof(Buffer), (void **)buffer, status)) {
        return false;
    }

    buffer_init(*buffer);

    return status_ok(status);
}

inline
bool buffer_new_alloc(Buffer **buffer, size_t alloc, Status *status) {
    return (
        buffer_new(buffer, status) &&
        buffer_ensure_capacity(*buffer, alloc, status)
    );
}

inline
bool buffer_new_from_data(Buffer **buffer, const char *data, size_t len,
                                                             Status *status) {
    return (
        buffer_new_alloc(buffer, len, status) &&
        buffer_assign_data(*buffer, data, len, status)
    );
}

inline
bool buffer_compact(Buffer *buffer, Status *status) {
    return array_compact(&buffer->array, status);
}

inline
bool buffer_equals_data_at_fast(Buffer *buffer, size_t index,
                                                const void *data,
                                                size_t len) {
    return memcmp(array_index_fast(&buffer->array, index), data, len) == 0;
}

inline
bool buffer_equals_data_at(Buffer *buffer, size_t index, const void *data,
                                                         size_t len,
                                                         bool *equal,
                                                         Status *status) {
    if ((index + len) > buffer->array.len) {
        return index_out_of_bounds(status);
    }

    *equal = buffer_equals_data_at_fast(buffer, index, data, len);

    return true;
}

inline
bool buffer_equals_data(Buffer *buffer, const char *data, size_t len) {
    return buffer_equals_data_at_fast(buffer, 0, data, len);
}

inline
bool buffer_equals(Buffer *b1, Buffer *b2) {
    return (
        (b1->array.len == b2->array.len) &&
        buffer_equals_data(b1, b2->array.elements, b1->array.len)
    );
}

inline
bool buffer_starts_with_data_fast(Buffer *buffer, const void *data,
                                                  size_t len) {
    return buffer_equals_data_at_fast(buffer, 0, data, len);
}

inline
bool buffer_starts_with_data(Buffer *buffer, const void *data,
                                             size_t len,
                                             bool *equal,
                                             Status *status) {
    return buffer_equals_data_at(buffer, 0, data, len, equal, status);
}

inline
bool buffer_ends_with_data_fast(Buffer *buffer, const void *data, size_t len) {
    return buffer_equals_data_at_fast(buffer, buffer->array.len - len, data,
                                                                       len);
}

inline
bool buffer_ends_with_data(Buffer *buffer, const void *data, size_t len,
                                                             bool *equal,
                                                             Status *status) {
    if (len > buffer->array.len) {
        return index_out_of_bounds(status);
    }

    *equal = buffer_ends_with_data_fast(buffer, data, len);

    return status_ok(status);
}

inline
void buffer_read_fast(Buffer *buffer, size_t index, size_t len, void *out) {
    array_copy_elements_fast(&buffer->array, index, len, out);
}

inline
bool buffer_read(Buffer *buffer, size_t index, size_t len, void *out,
                                                              Status *status) {
    return array_copy_elements(&buffer->array, index, len, out, status);
}

inline
void buffer_slice_fast(Buffer *buffer, size_t index, size_t len,
                                                     Slice *slice) {
    slice->data = array_index_fast(&buffer->array, index);
    slice->len = len;
}

inline
bool buffer_slice(Buffer *buffer, size_t index, size_t len,
                                                Slice *slice,
                                                Status *status) {
    if ((index + len) > buffer->array.len) {
        return index_out_of_bounds(status);
    }

    buffer_slice_fast(buffer, index, len, slice);

    return status_ok(status);
}

inline
void buffer_slice_full(Buffer *buffer, Slice *slice) {
    slice->data = buffer->array.elements;
    slice->len = buffer->array.len;
}

inline
void buffer_delete_fast(Buffer *buffer, size_t index, size_t len) {
    array_delete_many_fast(&buffer->array, index, len);
}

inline
bool buffer_delete(Buffer *buffer, size_t index, size_t len,
                                                 Status *status) {
    return array_delete_many(&buffer->array, index, len, status);
}

inline
void buffer_clear_no_zero(Buffer *buffer) {
    array_clear_no_zero(&buffer->array);
}

inline
void buffer_clear(Buffer *buffer) {
    return array_clear(&buffer->array);
}

inline
void buffer_free(Buffer *buffer) {
    array_free(&buffer->array);
}

inline
void buffer_insert_data_fast(Buffer *buffer, size_t index, const char *bytes,
                                                           size_t count) {
    array_insert_many_fast(&buffer->array, index, bytes, count);
}

inline
bool buffer_insert_data(Buffer *buffer, size_t index, const char *bytes,
                                                      size_t count,
                                                      Status *status) {
    return array_insert_many(&buffer->array, index, bytes, count, status);
}

inline
void buffer_insert_blank_data_fast_no_zero(Buffer *buffer, size_t index,
                                                           size_t count) {
    array_shift_elements_down_fast_no_zero(&buffer->array, index, count);
}

inline
void buffer_insert_blank_data_fast(Buffer *buffer, size_t index,
                                                   size_t count) {
    array_shift_elements_down_fast(&buffer->array, index, count);
}

inline
bool buffer_insert_blank_data_no_zero(Buffer *buffer, size_t index,
                                                      size_t count,
                                                      Status *status) {
    return array_shift_elements_down_no_zero(&buffer->array, index, count,
                                                                    status);
}

inline
bool buffer_insert_blank_data(Buffer *buffer, size_t index, size_t count,
                                                            Status *status) {
    return array_shift_elements_down(&buffer->array, index, count, status);
}

inline
void buffer_insert_slice_fast(Buffer *buffer, size_t index, Slice *slice) {
    array_insert_many_fast(&buffer->array, index, slice->data, slice->len);
}

inline
bool buffer_insert_slice(Buffer *buffer, size_t index, Slice *slice,
                                                       Status *status) {
    return array_insert_many(&buffer->array, index, slice->data, slice->len,
                                                                 status);
}

inline
void buffer_prepend_data_fast(Buffer *buffer, const char *bytes, size_t count) {
    array_prepend_many_fast(&buffer->array, bytes, count);
}

inline
bool buffer_prepend_data(Buffer *buffer, const char *bytes, size_t count,
                                                      Status *status) {
    return array_prepend_many(&buffer->array, bytes, count, status);
}

inline
void buffer_prepend_slice_fast(Buffer *buffer, Slice *slice) {
    array_prepend_many_fast(&buffer->array, slice->data, slice->len);
}

inline
bool buffer_prepend_slice(Buffer *buffer, Slice *slice, Status *status) {
    return array_prepend_many(&buffer->array, slice->data, slice->len,
                                                                status);
}

inline
void buffer_append_data_fast(Buffer *buffer, const char *bytes, size_t count) {
    array_append_many_fast(&buffer->array, bytes, count);
}

inline
bool buffer_append_data(Buffer *buffer, const char *bytes, size_t count,
                                                           Status *status) {
    return array_append_many(&buffer->array, bytes, count, status);
}

inline
void buffer_append_slice_fast(Buffer *buffer, Slice *slice) {
    array_append_many_fast(&buffer->array, slice->data, slice->len);
}

inline
bool buffer_append_slice(Buffer *buffer, Slice *slice, Status *status) {
    return array_append_many(&buffer->array, slice->data, slice->len, status);
}

inline
void buffer_overwrite_data_fast(Buffer *buffer, size_t index, const char *bytes,
                                                              size_t count) {
    array_overwrite_many_fast(&buffer->array, index, bytes, count);
}

inline
bool buffer_overwrite_data(Buffer *buffer, size_t index, const char *bytes,
                                                         size_t count,
                                                         Status *status) {
    return array_overwrite_many(&buffer->array, index, bytes, count, status);
}

inline
void buffer_overwrite_slice_fast(Buffer *buffer, size_t index, Slice *slice) {
    array_overwrite_many_fast(&buffer->array, index, slice->data, slice->len);
}

inline
bool buffer_overwrite_slice(Buffer *buffer, size_t index, Slice *slice,
                                                          Status *status) {
    return array_overwrite_many(&buffer->array, index, slice->data, slice->len,
                                                                    status);
}

inline
void buffer_zero_section_fast(Buffer *buffer, size_t index, size_t len) {
    array_zero_elements_fast(&buffer->array, index, len);
}

inline
bool buffer_zero_section(Buffer *buffer, size_t index, size_t len,
                                                       Status *status) {
    return array_zero_elements(&buffer->array, index, len, status);
}

inline
void buffer_zero_fast(Buffer *buffer) {
    array_zero_elements_fast(&buffer->array, 0, buffer->array.len);
}

inline
bool buffer_zero(Buffer *buffer, Status *status) {
    return array_zero_elements(&buffer->array, 0, buffer->array.len, status);
}

bool buffer_encode(Buffer *src, const char *src_encoding,
                                const char *dst_encoding,
                                Buffer *dst,
                                Status *status) {
    while (true) {
        size_t len = dst->array.alloc;

        if (charset_convert_data(src->array.elements, src->array.len,
                                                      src_encoding,
                                                      dst_encoding,
                                                      dst->array.elements,
                                                      &len,
                                                      status)) {
            dst->array.len = len;
            break;
        }

        if (!status_match(status, "charset", CHARSET_OUTPUT_BUFFER_TOO_SMALL)) {
            return false;
        }

        if (!buffer_ensure_capacity(dst, dst->array.alloc * 2, status)) {
            return false;
        }
    }

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */
