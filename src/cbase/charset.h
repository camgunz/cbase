#ifndef CHARSET_H__
#define CHARSET_H__

enum {
    CHARSET_UNSUPPORTED_CONVERSION = 1,
    CHARSET_INVALID_CHARACTER_SEQUENCE,
    CHARSET_INCOMPLETE_CHARACTER_SEQUENCE,
    CHARSET_INVALID_ICONV_HANDLE,
    CHARSET_UNKNOWN_ICONV_ERROR,
};

bool charset_convert(Slice *in, const char *from, const char *to,
                                                  Buffer *out,
                                                  Status *status);

bool charset_convert_to_string(Slice *in, const char *from, String *out,
                                                            Status *status);


static inline bool charset_localize(Slice *in, Buffer *out, Status *status) {
    return charset_convert(in, "UTF-8", "wchar_t", out, status);
}

static inline bool charset_unlocalize(Slice *in, Buffer *out,
                                                 Status *status) {
    return charset_convert(in, "wchar_t",  "UTF-8", out, status);
}

static inline bool charset_unlocalize_to_string(Slice *in, String *out,
                                                           Status *status) {
    return charset_convert_to_string(in, "wchar_t", out, status);
}

#endif

/* vi: set et ts=4 sw=4: */
