#include "cbase.h"

bool buffer_encode(Buffer *src, const char *src_encoding,
                                const char *dst_encoding,
                                Buffer *dst,
                                Status *status) {
    while (true) {
        if (charset_convert_data(src->array.elements, src->array.len,
                                                      src_encoding,
                                                      dst_encoding,
                                                      dst->array.elements,
                                                      dst->array.len,
                                                      status)) {
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
