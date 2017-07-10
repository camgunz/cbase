#include "cbase.h"

void buffer_init(Buffer *buffer) {
    buffer->data = NULL;
    buffer->len = 0;
    buffer->alloc = 0;
}

bool buffer_init_alloc(Buffer *buffer, size_t alloc, Status *status) {
    buffer_init(buffer);
    return buffer_ensure_capacity(buffer, alloc, status);
}

bool buffer_new(Buffer **new_buffer, Status *status) {
    Buffer *buffer = cbmalloc(1, sizeof(Buffer));

    if (!buffer) {
        return alloc_failure(status);
    }

    buffer_init(buffer);

    *new_buffer = buffer;

    return status_ok(status);
}

bool buffer_new_alloc(Buffer **new_buffer, size_t alloc, Status *status) {
    return buffer_new(new_buffer, status) &&
           buffer_ensure_capacity(*new_buffer, alloc, status);
}

bool buffer_ensure_capacity(Buffer *buffer, size_t len, Status *status) {
    if (buffer->alloc < len) {
        void *new_data = cbrealloc(buffer->data, len, sizeof(char));

        if (!new_data) {
            return alloc_failure(status);
        }

        buffer->data = new_data;
        buffer->alloc = len;
    }

    return status_ok(status);
}

bool buffer_shrink(Buffer *buffer, Status *status) {
    if (buffer->alloc > buffer->len) {
        char *new_data = cbrealloc(buffer->data, buffer->len, sizeof(char));

        if (!new_data) {
            return alloc_failure(status);
        }

        buffer->data = new_data;
        buffer->alloc = buffer->len;
    }

    return status_ok(status);
}

bool buffer_copy(Buffer *dst, Buffer *src, Status *status) {
    if (!buffer_ensure_capacity(dst, src->len, status)) {
        return false;
    }

    buffer_copy_fast(dst, src);

    return status_ok(status);
}

bool buffer_zero_section(Buffer *buffer, size_t index,
                                         size_t len,
                                         Status *status) {
    if ((index + len) >= buffer->len) {
        return index_out_of_bounds(status);
    }

    buffer_zero_section_fast(buffer, index, len);

    return status_ok(status);
}

bool buffer_shift_right(Buffer *buffer, size_t len, Status *status) {
    if (!buffer_ensure_capacity(buffer, buffer->len + len, status)) {
        return false;
    }

    buffer_shift_right_fast(buffer, len);
    buffer_zero_section_fast(buffer, 0, len);

    return status_ok(status);
}

bool buffer_shift_right_no_zero(Buffer *buffer, size_t len,
                                                Status *status) {
    if (!buffer_ensure_capacity(buffer, buffer->len + len, status)) {
        return false;
    }

    buffer_shift_right_fast(buffer, len);

    return status_ok(status);
}

bool buffer_slice(Buffer *buffer, size_t index,
                                  size_t len,
                                  Slice *slice,
                                  Status *status) {
    if ((index + len) >= buffer->len) {
        return index_out_of_bounds(status);
    }

    buffer_slice_fast(buffer, index, len, slice);

    return status_ok(status);
}

bool buffer_insert(Buffer *buffer, size_t pos, char *bytes, size_t count,
                                                            Status *status) {
    if (!buffer_ensure_capacity(buffer, buffer->len + count, status)) {
        return false;
    }

    buffer_insert_fast(buffer, pos, bytes, count);

    return status_ok(status);
}

bool buffer_delete(Buffer *buffer, size_t index,
                                   size_t len,
                                   Status *status) {
    if ((index + len) >= buffer->len) {
        return index_out_of_bounds(status);
    }

    if (!len) {
        return status_ok(status);
    }

    buffer_delete_fast(buffer, index, len);
    buffer_zero_section_fast(buffer, buffer->len - 1, len);

    return status_ok(status);
}

bool buffer_delete_no_zero(Buffer *buffer, size_t index,
                                           size_t len,
                                           Status *status) {
    if ((index + len) >= buffer->len) {
        return index_out_of_bounds(status);
    }

    if (!len) {
        return status_ok(status);
    }

    buffer_delete_fast(buffer, index, len);

    return status_ok(status);
}

bool buffer_read(Buffer *buffer, size_t index, size_t len, void *out,
                                                           Status *status) {
    if ((index + len) >= buffer->len) {
        return index_out_of_bounds(status);
    }

    if (!len) {
        return status_ok(status);
    }

    buffer_read_fast(buffer, index, len, out);

    return status_ok(status);
}

void buffer_clear(Buffer *buffer) {
    buffer->len = 0;
}

void buffer_free(Buffer *buffer) {
    cbfree(buffer->data);
    buffer_init(buffer);
}

/* vi: set et ts=4 sw=4: */
