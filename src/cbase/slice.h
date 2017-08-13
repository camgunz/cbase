#ifndef SLICE_H__
#define SLICE_H__

typedef struct {
    char *data;
    size_t len;
} Slice;

static inline
void slice_assign(Slice *slice, char *data, size_t len) {
    slice->data = data;
    slice->len = len;
}

static inline
void slice_clear(Slice *slice) {
    slice->len = 0;
}

static inline
bool slice_empty(Slice *slice) {
    return ((!slice->data) || (slice->len == 0));
}

static inline
bool slice_equals_data_at_fast(Slice *slice, size_t index, const void *data,
                                                           size_t len) {
    return memcmp(slice->data + index, data, len) == 0;
}

static inline
bool slice_equals_data_at(Slice *slice, size_t index, const void *data,
                                                      size_t len,
                                                      bool *equal,
                                                      Status *status) {
    if ((index + len) > slice->len) {
        return index_out_of_bounds(status);
    }

    *equal = slice_equals_data_at_fast(slice, index, data, len);

    return true;
}

static inline
bool slice_equals_data_fast(Slice *slice, const char *data, size_t len) {
    if (slice->len != len) {
        return false;
    }

    return slice_equals_data_at_fast(slice, 0, data, len);
}

static inline
bool slice_starts_with_data_fast(Slice *slice, const void *data, size_t len) {
    return slice_equals_data_at_fast(slice, 0, data, len);
}

static inline
bool slice_starts_with_data(Slice *slice, const void *data, size_t len,
                                                            bool *equal,
                                                            Status *status) {
    if (len > slice->len) {
        return index_out_of_bounds(status);
    }

    *equal = slice_starts_with_data_fast(slice, 0, data, len);

    return status_ok(status);
}

static inline
bool slice_equals(Slice *s1, Slice *s2) {
    return slice_equals_data(s1, s2->data, s2->len);
}

static inline
void slice_shallow_copy(Slice *dst, Slice *src) {
    dst->data = src->data;
    dst->len = src->len;
}

static inline
void slice_read_fast(Slice *slice, size_t index, size_t len, void *out) {
    cbmemmove(out, slice->data + index, len);
}

static inline
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

static inline
bool slice_encode(Slice *src, const char *src_encoding,
                              const char *dst_encoding,
                              Buffer *dst,
                              Status *status) {
    Slice dst_slice;

    while (true) {
        dst_slice.data = dst->array.data;
        dst_slice.len = dst->array.alloc;

        if (charset_convert_slice(&src_slice, src_encoding, to_encoding,
                                                            &dst_slice,
                                                            status)) {
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

#endif

/* vi: set et ts=4 sw=4: */
