#ifndef SLICE_H__
#define SLICE_H__

typedef struct {
    char *data;
    size_t len;
} Slice;

void slice_assign(Slice *slice, char *data, size_t len);
void slice_clear(Slice *slice);
bool slice_empty(Slice *slice);
bool slice_equals_data(Slice *s, const char *data, size_t len);
void slice_shallow_copy(Slice *dst, Slice *src);
bool slice_deep_copy(Slice *dst, Slice *src, Status *status);

static inline bool slice_equals(Slice *s1, Slice *s2) {
    return slice_equals_data(s1, s2->data, s2->len);
}

#endif

/* vi: set et ts=4 sw=4: */
