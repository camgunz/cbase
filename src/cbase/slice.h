#ifndef SLICE_H__
#define SLICE_H__

typedef struct {
    char *data;
    size_t len;
} Slice;

static inline void slice_assign(Slice *slice, char *data, size_t len) {
    slice->data = data;
    slice->len = len;
}

static inline void slice_clear(Slice *slice) {
    slice->len = 0;
}

static inline bool slice_empty(Slice *slice) {
    if (!slice->data) {
        return true;
    }

    if (slice->len == 0) {
        return true;
    }

    return false;
}

static inline bool slice_equals_data(Slice *slice, const char *data,
                                                   size_t len) {
    if (slice->len != len) {
        return false;
    }

    return memcmp(slice->data, data, len) == 0;
}

static inline bool slice_equals(Slice *s1, Slice *s2) {
    return slice_equals_data(s1, s2->data, s2->len);
}

static inline void slice_shallow_copy(Slice *dst, Slice *src) {
    dst->data = src->data;
    dst->len = src->len;
}

static inline bool slice_deep_copy(Slice *dst, Slice *src, Status *status) {
    char *data = cbmalloc(src->len, sizeof(char));

    if (!data) {
        return alloc_failure(status);
    }

    cbmemmove(data, src->data, src->len);

    dst->data = data;
    dst->len = src->len;

    return status_ok(status);
}

static inline void slice_read_fast(Slice *slice, size_t index, size_t len,
                                                               void *out) {
    cbmemmove(out, slice->data + index, len);
}

static inline bool slice_read(Slice *slice, size_t index, size_t len,
                                                          void *out,
                                                          Status *status) {
    if ((index + len) >= slice->len) {
        return index_out_of_bounds(status);
    }

    if (!len) {
        return status_ok(status);
    }

    slice_read_fast(slice, index, len, out);

    return status_ok(status);
}

#endif

/* vi: set et ts=4 sw=4: */
