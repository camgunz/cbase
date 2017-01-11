#include "cbase.h"

char* __cbstrdup(const char *cs) {
    return strndup(cs, strlen(cs));
}

char* __cbstrndup(const char *cs, size_t len) {
    char *str = cbmalloc(len + 1);

    if (!str) {
        return NULL;
    }

    strncpy(str, cs, len);

    *(str + len) = '\0';

    return str;
}

/* vi: set et ts=4 sw=4: */
