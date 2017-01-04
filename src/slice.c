#include "cbase.h"

void slice_assign(Slice *slice, char *data, size_t len) {
    slice->data = data;
    slice->len = len;
}

void slice_clear(Slice *slice) {
    slice->len = 0;
}

bool slice_empty(Slice *slice) {
    if (!slice->data) {
        return true;
    }

    if (slice->len == 0) {
        return true;
    }

    return false;
}

bool slice_equals_data(Slice *slice, const char *data, size_t len) {
    if (slice->len != len) {
        return false;
    }

    return memcmp(slice->data, data, len) == 0;
}

void slice_shallow_copy(Slice *dst, Slice *src) {
    dst->data = src->data;
    dst->len = src->len;
}

bool slice_deep_copy(Slice *dst, Slice *src, Status *status) {
    char *data = cbmalloc(src->len);

    if (!data) {
        return alloc_failure(status);
    }

    memmove(data, src->data, src->len);

    dst->data = data;
    dst->len = src->len;

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */
