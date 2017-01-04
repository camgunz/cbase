#include "cbase.h"

#ifndef strdup
char* __cbstrdup(const char *cs) {
    size_t len = strlen(cs) + 1;
    char *str = cbmalloc(len);

    if (!str) {
        return NULL;
    }

    strcpy(str, cs);

    *(str + len) = '\0';

    return str;
}
#endif

#ifndef strndup
char* __cbstrndup(const char *cs, size_t len) {
    char *str = cbmalloc(len + 1);

    if (!str) {
        return NULL;
    }

    strncpy(str, cs, len);

    *(str + len) = '\0';

    return str;
}
#endif

/* vi: set et ts=4 sw=4: */
