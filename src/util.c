#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

/*
 * Thanks to Colin Perciva for this code.  It's not guaranteed to work, but
 * is the best we can do without resorting to intrinsics or asm absent memset_s
 * and explicit_bzero.
 *
 * http://www.daemonology.net/blog/2014-09-04-how-to-zero-a-buffer.html
 */

static
void* (*const volatile memset_buf)(void *, int, size_t) = memset;

static
void secure_memzero(void *buf, size_t len) {
    (memset_buf)(buf, 0, len);
}

void zero_buf_fast(void *buf, size_t byte_count) {
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

