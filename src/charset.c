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

#define null_output_buffer(status) status_failure( \
    status,                                        \
    "charset",                                     \
    CHARSET_BUFFER_DATA_UNINITIALIZED,             \
    "output buffer's data is uninitialized"        \
)

#define output_buffer_too_small(status) status_failure( \
    status,                                             \
    "charset",                                          \
    CHARSET_OUTPUT_BUFFER_TOO_SMALL,                    \
    "output buffer is too small"                        \
)

bool charset_convert_data(const char *data, size_t len,
                                            const char *src_encoding,
                                            const char *dst_encoding,
                                            char *output_data,
                                            size_t *output_len,
                                            Status *status) {
    size_t original_len = *output_len;
    iconv_t cd = iconv_open(dst_encoding, src_encoding);

    if (cd == (iconv_t)-1) {
        if (errno == EINVAL) {
            return unsupported_charset_conversion(status);
        }

        return unknown_iconv_error(status);
    }

    if (!output_data) {
        return null_output_buffer(status);
    }

    while (true) {
        size_t res;
        char **cursor = (char **)&data;

        res = iconv(cd, cursor, &len, &output_data, output_len);

        if (res == (size_t)-1) {
            switch (errno) {
                case EILSEQ:
                    return invalid_character_sequence(status);
                case EINVAL:
                    return incomplete_character_sequence(status);
                case EBADF:
                    return invalid_iconv_handle(status);
                case E2BIG:
                    return output_buffer_too_small(status);
                default:
                    return unknown_iconv_error(status);
            }
        }

        break;
    }

    if (iconv_close(cd)) {
        return unknown_iconv_error(status);
    }

    *output_len = original_len - *output_len;

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */
