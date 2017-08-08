#ifndef ALLOC_H__
#define ALLOC_H__

static inline bool __cbmemmove(void *dest, const void *src, size_t count,
                                                            size_t size) {
    if (!check_overflow(count, size)) {
        return false;
    }

    (void)memmove(dest, src, count * size);

    return true;
}

#ifndef cbmemmove
#define cbmemmove __cbmemmove
#endif

static inline void* __cbmalloc(size_t count, size_t size) {
    if (!check_overflow(count, size)) {
        errno = ENOMEM;
        return NULL;
    }

    return malloc(count * size);
}

#ifndef cbmalloc
#define cbmalloc __cbmalloc
#endif

static inline void* __cbcalloc(size_t count, size_t size) {
    if (!check_overflow(count, size)) {
        errno = ENOMEM;
        return NULL;
    }

    return calloc(count, size);
}

#ifndef cbcalloc
#define cbcalloc __cbcalloc
#endif

static inline void* __cbrealloc(void *ptr, size_t count, size_t size) {
    if (!check_overflow(count, size)) {
        errno = ENOMEM;
        return NULL;
    }

    return realloc(ptr, count * size);
}

#ifndef cbrealloc
#define cbrealloc __cbrealloc
#endif

static inline void __cbfree(void *ptr) {
    free(ptr);
}

#ifndef cbfree
#define cbfree __cbfree
#endif

static inline char* __cbstrndup(const char *cs, size_t len) {
    char *str = cbmalloc(len + 1, sizeof(char));

    if (!str) {
        return NULL;
    }

    cbmemmove(str, cs, len);

    *(str + len) = '\0';

    return str;
}

#ifndef cbstrndup
#define cbstrndup __cbstrndup
#endif

static inline void* cbmemcpy(void *dest, const void *src, size_t size) {
    return cbmemmove(dest, src, size);
}

static inline void* __cbmemdup(const void *ptr, size_t count) {
  void *buf = cbmalloc(count, 1);

  if (!buf) {
      return NULL;
  }

  cbmemmove(buf, ptr, count);

  return buf;
}

#ifndef cbmemdup
#define cbmemdup __cbmemdup
#endif

static inline char* cbstrdup(const char *cs) {
    return cbstrndup(cs, strlen(cs));
}

#endif

/* vi: set et ts=4 sw=4: */
