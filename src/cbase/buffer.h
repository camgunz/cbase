#ifndef BUFFER_H__
#define BUFFER_H__

typedef struct {
    char *data;
    size_t len;
    size_t alloc;
} Buffer;

void buffer_init(Buffer *buffer);
bool buffer_init_alloc(Buffer *buffer, size_t alloc, Status *status);
bool buffer_new(Buffer **new_buffer, Status *status);
bool buffer_new_alloc(Buffer **new_buffer, size_t alloc, Status *status);
bool buffer_ensure_capacity(Buffer *buffer, size_t len, Status *status);
bool buffer_shrink(Buffer *buffer, Status *status);
bool buffer_copy(Buffer *dst, Buffer *src, Status *status);
bool buffer_zero_section(Buffer *buffer, size_t index, size_t len,
                                                       Status *status);
bool buffer_shift_right(Buffer *buffer, size_t len, Status *status);
bool buffer_shift_right_no_zero(Buffer *buffer, size_t len, Status *status);
bool buffer_slice(Buffer *buffer, size_t index, size_t len, Slice *slice,
                                                            Status *status);
bool buffer_insert(Buffer *buffer, size_t pos, char *bytes, size_t count,
                                                            Status *status);
bool buffer_delete(Buffer *buffer, size_t index, size_t len,
                                                 Status *status);
bool buffer_delete_no_zero(Buffer *buffer, size_t index, size_t len,
                                                         Status *status);
bool buffer_read(Buffer *buffer, size_t index, size_t len, void *out,
                                                           Status *status);
void buffer_clear(Buffer *buffer);
void buffer_free(Buffer *buffer);

static inline void buffer_read_fast(Buffer *buffer, size_t index, size_t len,
                                                                  void *out) {
    cbmemmove(out, buffer->data + index, len);
}

static inline void buffer_copy_fast(Buffer *dst, Buffer *src) {
    buffer_read_fast(dst, 0, src->len, src->data);
    dst->len = src->len;
}

static inline void buffer_copy_buffer_len_fast(Buffer *dst, Buffer *src,
                                                            size_t len) {
    cbmemmove(dst->data, src->data, len);
    dst->len = src->len;
}

static inline void buffer_zero(Buffer *buffer) {
    memset(buffer->data, 0, buffer->len);
}

static inline void buffer_zero_section_fast(Buffer *buffer, size_t index,
                                                            size_t len) {
    memset(buffer->data + index, 0, len);
}

static inline void buffer_delete_fast(Buffer *buffer, size_t index, size_t len) {
    cbmemmove(buffer->data + index, buffer->data + index + len, len);
    buffer->len -= len;
}

static inline bool buffer_shift_left(Buffer *buffer, size_t len,
                                                     Status *status) {
    return buffer_delete(buffer, 0, len, status);
}

static inline bool buffer_shift_left_no_zero(Buffer *buffer, size_t len,
                                                             Status *status) {
    return buffer_delete_no_zero(buffer, 0, len, status);
}

static inline void buffer_shift_left_fast(Buffer *buffer, size_t len) {
    buffer_delete_fast(buffer, 0, len);
}

static inline void buffer_shift_right_fast(Buffer *buffer, size_t len) {
    cbmemmove(buffer->data + len, buffer->data, len);
    buffer->len += len;
}

static inline void buffer_slice_fast(Buffer *buffer, size_t index,
                                                     size_t len,
                                                     Slice *slice) {
    slice->data = buffer->data + index;
    slice->len = len;
}

static inline void buffer_insert_fast(Buffer *buffer, size_t pos,
                                                      char *bytes,
                                                      size_t count) {
    cbmemmove(buffer->data + pos + count, buffer->data + pos, count);
    cbmemmove(buffer->data + pos, bytes, count);
    buffer->len += count;
}

static inline bool buffer_insert_slice(Buffer *buffer, size_t pos,
                                                       Slice *slice,
                                                       Status *status) {
    return buffer_insert(buffer, pos, slice->data, slice->len, status);
}

static inline void buffer_insert_slice_fast(Buffer *buffer, size_t pos,
                                                            Slice *slice) {
    buffer_insert_fast(buffer, pos, slice->data, slice->len);
}

static inline bool buffer_prepend(Buffer *buffer, char *bytes,
                                                  size_t count,
                                                  Status *status) {
    return buffer_insert(buffer, 0, bytes, count, status);
}

static inline void buffer_prepend_fast(Buffer *buffer, char *bytes,
                                                       size_t count) {
    buffer_insert_fast(buffer, 0, bytes, count);
}

static inline bool buffer_prepend_slice(Buffer *buffer, Slice *slice,
                                                        Status *status) {
    return buffer_prepend(buffer, slice->data, slice->len, status);
}

static inline void buffer_prepend_slice_fast(Buffer *buffer, Slice *slice) {
    buffer_prepend_fast(buffer, slice->data, slice->len);
}

static inline bool buffer_append(Buffer *buffer, char *bytes, size_t count,
                                                              Status *status) {
    return buffer_insert(buffer, buffer->len, bytes, count, status);
}

static inline void buffer_append_fast(Buffer *buffer, char *bytes,
                                                      size_t count) {
    buffer_insert_fast(buffer, buffer->len, bytes, count);
}

static inline bool buffer_append_slice(Buffer *buffer, Slice *slice,
                                                       Status *status) {
    return buffer_append(buffer, slice->data, slice->len, status);
}

static inline void buffer_append_slice_fast(Buffer *buffer, Slice *slice) {
    buffer_append_fast(buffer, slice->data, slice->len);
}

#endif

/* vi: set et ts=4 sw=4: */
