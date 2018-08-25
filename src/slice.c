#include "cbase.h"

void slice_assign_data(Slice *slice, char *data, size_t len) {
    slice->data = data;
    slice->len = len;
}

void slice_assign_slice(Slice *dst, Slice *src) {
    dst->data = src->data;
    dst->len = src->len;
}

bool slice_equals_data_at_fast(Slice *slice, size_t index, size_t len,
                                                           const void *data) {
    return memcmp(slice->data + index, data, len) == 0;
}

bool slice_equals_data_at(Slice *slice, size_t index, size_t len,
                                                      const void *data,
                                                      bool *equal,
                                                      Status *status) {
    if ((index + len) > slice->len) {
        return index_out_of_bounds(status);
    }

    *equal = slice_equals_data_at_fast(slice, index, len, data);

    return true;
}

bool slice_equals_data(Slice *slice, const char *data) {
    return slice_equals_data_at_fast(slice, 0, slice->len, data);
}

bool slice_equals(Slice *s1, Slice *s2) {
    return slice_equals_data(s1, s2->data);
}

bool slice_starts_with_data_fast(Slice *slice, const void *data, size_t len) {
    return slice_equals_data_at_fast(slice, 0, len, data);
}

bool slice_starts_with_data(Slice *slice, const void *data, size_t len,
                                                            bool *equal,
                                                            Status *status) {
    if (len > slice->len) {
        return index_out_of_bounds(status);
    }

    *equal = slice_starts_with_data_fast(slice, data, len);

    return status_ok(status);
}

bool slice_ends_with_data_fast(Slice *slice, const void *data, size_t len) {
    return slice_equals_data_at_fast(slice, slice->len - len, len, data);
}

bool slice_ends_with_data(Slice *slice, const void *data, size_t len,
                                                          bool *equal,
                                                          Status *status) {
    if (len > slice->len) {
        return index_out_of_bounds(status);
    }

    *equal = slice_ends_with_data_fast(slice, data, len);

    return status_ok(status);
}

void slice_read_fast(Slice *slice, size_t index, size_t len, void *out) {
    cbbase_memmove(out, slice->data + index, len);
}

bool slice_read(Slice *slice, size_t index, size_t len, void *out,
                                                        Status *status) {
    if ((index + len) > slice->len) {
        return index_out_of_bounds(status);
    }

    if (!len) {
        return status_ok(status);
    }

    slice_read_fast(slice, index, len, out);

    return status_ok(status);
}

bool slice_encode(Slice *src, const char *src_encoding,
                              const char *dst_encoding,
                              Buffer *dst,
                              Status *status) {
    while (true) {
        size_t len = dst->array.alloc;

        if (charset_convert_data(src->data, src->len, src_encoding,
                                                      dst_encoding,
                                                      dst->array.elements,
                                                      &len,
                                                      status)) {
            dst->array.len = len;
            break;
        }

        if (status_match(status, "charset", CHARSET_OUTPUT_BUFFER_TOO_SMALL)) {
            if (!buffer_ensure_capacity(dst, dst->array.alloc * 2, status)) {
                return false;
            }
        }
        else {
            return false;
        }
    }

    return status_ok(status);
}

void slice_clear(Slice *slice) {
    slice->data = NULL;
    slice->len = 0;
}

/* vi: set et ts=4 sw=4: */
