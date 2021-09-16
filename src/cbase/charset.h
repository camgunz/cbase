#pragma once

#ifndef _CBASE_CHARSET_H__
#define _CBASE_CHARSET_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stdlib.h>

enum
{
    CBASE_CHARSET_UNSUPPORTED_CONVERSION = 21000,
    CBASE_CHARSET_INVALID_CHARACTER_SEQUENCE,
    CBASE_CHARSET_INCOMPLETE_CHARACTER_SEQUENCE,
    CBASE_CHARSET_INVALID_ICONV_HANDLE,
    CBASE_CHARSET_UNKNOWN_ICONV_ERROR,
    CBASE_CHARSET_BUFFER_DATA_UNINITIALIZED,
    CBASE_CHARSET_OUTPUT_BUFFER_TOO_SMALL,
    CBASE_CHARSET_NULL_OUTPUT_BUFFER,
};

CBASE_API
int cb_charset_convert_data(const char *data,
                            size_t len,
                            const char *src_encoding,
                            const char *dst_encoding,
                            char *output_data,
                            size_t *output_len) CBASE_API_ATTRS;

#endif
