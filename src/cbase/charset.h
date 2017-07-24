#ifndef CHARSET_H__
#define CHARSET_H__

enum {
    CHARSET_UNSUPPORTED_CONVERSION = 1,
    CHARSET_INVALID_CHARACTER_SEQUENCE,
    CHARSET_INCOMPLETE_CHARACTER_SEQUENCE,
    CHARSET_INVALID_ICONV_HANDLE,
    CHARSET_UNKNOWN_ICONV_ERROR,
    CHARSET_BUFFER_DATA_UNINITIALIZED,
    CHARSET_OUTPUT_BUFFER_TOO_SMALL,
};

bool charset_convert(Slice *in, const char *from, const char *to,
                                                  Slice *out,
                                                  Status *status);

#endif

/* vi: set et ts=4 sw=4: */
