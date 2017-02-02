#ifndef ALLOC_H__
#define ALLOC_H__

#ifndef cbmalloc
#define cbmalloc malloc
#endif

#ifndef cbcalloc
#define cbcalloc calloc
#endif

#ifndef cbrealloc
#define cbrealloc realloc
#endif

#ifndef cbfree
#define cbfree free
#endif

#ifndef cbstrdup
#define cbstrdup _cbstrdup
#endif

#ifdef strdup
#define _cbstrdup strdup
#else
#define _cbstrdup __cbstrdup
#endif

#ifndef cbstrndup
#define cbstrndup _cbstrndup
#endif

#ifdef strndup
#define _cbstrndup strndup
#else
#define _cbstrndup __cbstrndup
#endif

char* __cbstrdup(const char *cs);
char* __cbstrndup(const char *cs, size_t len);

char* bufdup(const char *buf, size_t size);

#endif

/* vi: set et ts=4 sw=4: */
