#include "cbase/internal.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "cbase/alloc.h"
#include "cbase/checked_math.h"
#include "cbase/errors.h"

#ifndef cb_sysfree
CBASE_API_DEALLOC
void cb_sysfree(void *ptr) {
    free(ptr);
}
#endif

#ifndef cb_sysmalloc
CBASE_API_MALLOC(cb_sysfree, 1)
void *cb_sysmalloc(size_t size) {
    return malloc(size);
}
#endif

#ifndef cb_syscalloc
CBASE_API_MALLOC(cb_sysfree, 1)
void *cb_syscalloc(size_t count, size_t size) {
    return calloc(count, size);
}
#endif

#ifndef cb_sysrealloc
CBASE_API void *cb_sysrealloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}
#endif

#ifndef cb_sysmemcpy
CBASE_API void *cb_sysmemcpy(void * restrict dest,
                             const void * restrict src,
                             size_t size) {
    return memmove(dest, src, size);
}
#endif
