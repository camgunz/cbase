#include "cbase.h"

bool slice_encode(Slice *src, const char *src_encoding,
                              const char *dst_encoding,
                              Buffer *dst,
                              Status *status) {
    while (true) {
        if (charset_convert_data(src.data, src.len, src_encoding,
                                                    dst_encoding,
                                                    &dst->array.data,
                                                    &dst->array.len,
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

/* vi: set et ts=4 sw=4: */
