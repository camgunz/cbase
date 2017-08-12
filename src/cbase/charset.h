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

bool charset_convert_data(const char *data, size_t len,
                                            const char *src_encoding,
                                            const char *dst_encoding,
                                            Slice *out,
                                            Status *status);

static inline
bool charset_convert_slice(Slice *in, const char *src_encoding,
                                      const char *dst_encoding,
                                      Slice *out,
                                      Status *status) {
    return charset_convert_data(in->data, in->len, src_encoding, dst_encoding,
                                                                 out,
                                                                 status);
}

#endif

/* vi: set et ts=4 sw=4: */
