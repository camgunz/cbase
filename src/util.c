#include "cbase/internal.h"

#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "cbase/checks.h"
#include "cbase/errors.h"

/*
 * Thanks to Colin Percival for this code.  It's not guaranteed to work, but
 * is the best we can do without resorting to intrinsics or asm absent
 * platform-specific functions.
 *
 * http://www.daemonology.net/blog/2014-09-04-how-to-zero-a-buffer.html
 *
 * [TODO]
 * - Look for those buffer zeroing intrinsics
 */

static
void* (*const volatile memset_buf)(void *, int, size_t) = memset;

static
void secure_memzero(void *buf, size_t len) {
    (memset_buf)(buf, 0, len);
}

void zero_buf_no_check(void *buf, size_t byte_count) {
    /* [TODO] Handle errors */
#if defined(_MSC_VER)
    (void)SecureZeroMemory(buf, byte_count);
#elif defined(HAVE_EXPLICIT_BZERO)
    (void)explicit_bzero(buf, byte_count);
#elif defined(HAVE_MEMSET_S)
    (void)memset_s(buf, byte_count, 0, byte_count);
#else
    secure_memzero(buf, byte_count);
#endif
}

void* _cbmemmem(const void *haystack, size_t hlen,
                const void *needle,   size_t nlen) {
    if (!haystack) {
        return NULL;
    }

    if (!hlen) {
        return NULL;
    }

    if (!needle) {
        return NULL;
    }

    if (!nlen) {
        return NULL;
    }

    const unsigned char *cursor = (const unsigned char *)haystack;
    const unsigned char *end = cursor + (hlen - nlen);

    for (; cursor <= end; cursor++) {

        if (cursor[0] != ((const unsigned char *)needle)[0]) {
            continue;
        }

        if (memcmp(cursor, needle, nlen)) {
            continue;
        }

        return (void *)cursor;
    }

    return NULL;
}

void cbmemmem_no_check(const void *haystack, size_t hlen,
                   const void *needle,   size_t nlen,
                                         void **location) {
    *location = memmem(haystack, hlen, needle, nlen);
}

int cbmemmem(const void *haystack, size_t hlen,
             const void *needle,   size_t nlen,
                                   void **location) {
    CBASE_CHECK_INPUT_OBJECT(haystack);
    CBASE_CHECK_INPUT_OBJECT(needle);
    CBASE_CHECK_OUTPUT_ARGUMENT(location);
    CBASE_ERROR_IF(nlen == 0, CBASE_ERROR_NULL_POINTER);

    CBASE_ERROR_IF(nlen > hlen, CBASE_ERROR_NOT_FOUND);

    void *location2 = NULL;

    cbmemmem_no_check(haystack, hlen, needle, nlen, &location2);

    if (!location2) {
        CBASE_ERROR(CBASE_ERROR_NOT_FOUND);
    }

    *location = location2;

    return 0;
}
