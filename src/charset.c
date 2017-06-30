#include "cbase.h"

#include <iconv.h>

#define unsupported_charset_conversion(status) status_error( \
    status,                                                  \
    "charset",                                               \
    CHARSET_UNSUPPORTED_CONVERSION,                          \
    "unsupported charset conversion"                         \
)

#define invalid_character_sequence(status) status_error( \
    status,                                              \
    "charset",                                           \
    CHARSET_INVALID_CHARACTER_SEQUENCE,                  \
    "invalid character sequence"                         \
)

#define incomplete_character_sequence(status) status_error( \
    status,                                                 \
    "charset",                                              \
    CHARSET_INCOMPLETE_CHARACTER_SEQUENCE,                  \
    "incomplete character sequence"                         \
)

#define invalid_iconv_handle(status) status_error( \
    status,                                        \
    "charset",                                     \
    CHARSET_INVALID_ICONV_HANDLE,                  \
    "invalid iconv handle"                         \
)

#define unknown_iconv_error(status) status_error( \
    status,                                       \
    "charset",                                    \
    CHARSET_UNKNOWN_ICONV_ERROR,                  \
    "unknown iconv error"                         \
)

bool convert_charset(Buffer *in, const char *from, const char *to,
                                                   Buffer *out,
                                                   Status *status) {
    iconv_t cd = iconv_open(to, from);

    if (cd == (iconv_t)-1) {
        if (errno == EINVAL) {
            return unsupported_charset_conversion(status);
        }

        return unknown_iconv_error(status);
    }

    while (true) {
        char *in_buf = in->data;
        size_t in_buf_size = in->len;
        char *out_buf = out->data;
        size_t out_buf_size = out->alloc;
        size_t res;

        res = iconv(cd, &in_buf, &in_buf_size, &out_buf, &out_buf_size);

        if (res == (size_t)-1) {
            if (errno == EILSEQ) {
                return invalid_character_sequence(status);
            }

            if (errno == EINVAL) {
                return incomplete_character_sequence(status);
            }

            if (errno == EBADF) {
                return invalid_iconv_handle(status);
            }

            if (errno == E2BIG) {
                if (!buffer_ensure_capacity(out, out->alloc * 2, status)) {
                    return false;
                }
                continue;
            }

            return unknown_iconv_error(status);
        }

        out->len = out->alloc - out_buf_size;

        break;
    }

    if (iconv_close(cd)) {
        return unknown_iconv_error(status);
    }

    return true;
}

bool charset_convert_from_string(SSlice *in, const char *to, Buffer *out,
                                                             Status *status) {
    iconv_t cd = iconv_open(to, "UTF-8");

    if (cd == (iconv_t)-1) {
        if (errno == EINVAL) {
            return unsupported_charset_conversion(status);
        }

        return unknown_iconv_error(status);
    }

    while (true) {
        char *in_buf = in->data;
        size_t in_buf_size = in->len;
        char *out_buf = out->data;
        size_t out_buf_size = out->alloc;
        size_t res;

        res = iconv(cd, &in_buf, &in_buf_size, &out_buf, &out_buf_size);

        if (res == (size_t)-1) {
            if (errno == EILSEQ) {
                return invalid_character_sequence(status);
            }

            if (errno == EINVAL) {
                return incomplete_character_sequence(status);
            }

            if (errno == EBADF) {
                return invalid_iconv_handle(status);
            }

            if (errno == E2BIG) {
                if (!buffer_ensure_capacity(out, out->alloc * 2, status)) {
                    return false;
                }
                continue;
            }

            return unknown_iconv_error(status);
        }

        out->len = out->alloc - out_buf_size;

        break;
    }

    if (iconv_close(cd)) {
        return unknown_iconv_error(status);
    }

    return true;
}

bool charset_convert_to_string(Slice *in, const char *from, String *out,
                                                            Status *status) {
    iconv_t cd = iconv_open("UTF-8", from);

    if (cd == (iconv_t)-1) {
        if (errno == EINVAL) {
            return unsupported_charset_conversion(status);
        }

        return unknown_iconv_error(status);
    }

    while (true) {
        char *in_buf = in->data;
        size_t in_buf_size = in->len;
        char *out_buf = out->data;
        size_t out_buf_size = out->alloc;
        size_t res;

        res = iconv(cd, &in_buf, &in_buf_size, &out_buf, &out_buf_size);

        if (res == (size_t)-1) {
            if (errno == EILSEQ) {
                return invalid_character_sequence(status);
            }

            if (errno == EINVAL) {
                return incomplete_character_sequence(status);
            }

            if (errno == EBADF) {
                return invalid_iconv_handle(status);
            }

            if (errno == E2BIG) {
                if (!string_ensure_capacity(out, out->alloc * 2, status)) {
                    return false;
                }
                continue;
            }

            return unknown_iconv_error(status);
        }

        out->byte_len = out->alloc - out_buf_size;

        if (!utf8len(out->data, &out->len, status)) {
            return false;
        }

        break;
    }

    if (iconv_close(cd)) {
        return unknown_iconv_error(status);
    }

    return true;
}

/* vi: set et ts=4 sw=4: */
