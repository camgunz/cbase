#include "cbase/internal.h"

#include <errno.h>
#include <iconv.h>

#include "cbase/charset.h"

int charset_convert_data(const char *data,
                         size_t len,
                         const char *src_encoding,
                         const char *dst_encoding,
                         char *output_data,
                         size_t *output_len) {
    size_t original_len = *output_len;
    iconv_t cd = iconv_open(dst_encoding, src_encoding);

    if (cd == (iconv_t)-1) {
        if (errno == EINVAL) {
            return CBASE_CHARSET_UNSUPPORTED_CONVERSION;
        }

        return CBASE_CHARSET_UNKNOWN_ICONV_ERROR;
    }

    if (!output_data) {
        return CBASE_CHARSET_NULL_OUTPUT_BUFFER;
    }

    while (true) {
        size_t res;
        char **cursor = (char **)&data;

        res = iconv(cd, cursor, &len, &output_data, output_len);

        if (res == (size_t)-1) {
            switch (errno) {
            case EILSEQ:
                return CBASE_CHARSET_INVALID_CHARACTER_SEQUENCE;
            case EINVAL:
                return CBASE_CHARSET_INCOMPLETE_CHARACTER_SEQUENCE;
            case EBADF:
                return CBASE_CHARSET_INVALID_ICONV_HANDLE;
            case E2BIG:
                return CBASE_CHARSET_OUTPUT_BUFFER_TOO_SMALL;
            default:
                return CBASE_CHARSET_UNKNOWN_ICONV_ERROR;
            }
        }

        break;
    }

    if (iconv_close(cd)) {
        return CBASE_CHARSET_UNKNOWN_ICONV_ERROR;
    }

    *output_len = original_len - *output_len;

    return 0;
}

/* vi: set et ts=4 sw=4: */
