#pragma once

#ifndef _CBASE_LOGBASE_H__
#define _CBASE_LOGBASE_H__

#include "cbase/internal.h"

#include <stdarg.h>
#include <stdio.h>

typedef enum
{
    CBASE_LOG_LEVEL_DEBUG = 1,
    CBASE_LOG_LEVEL_INFO,     /* General info */
    CBASE_LOG_LEVEL_WARNING,  /* Unexpected condition */
    CBASE_LOG_LEVEL_FAILURE,  /* Failed, could not continue */
    CBASE_LOG_LEVEL_ERROR,    /* Programming error */
    CBASE_LOG_LEVEL_CRITICAL, /* Possibly fatal; requires recovery */
    CBASE_LOG_LEVEL_FATAL,    /* Exits program */
    CBASE_LOG_LEVEL_MAX,
} LogLevel;

#if ((defined(CBASE_DUMP_LOGGING_ERRORS_TO_STDERR)) ||                        \
     (CBASE_DEFAULT_LOGGER == CBASE_LOG_STDERR) ||                            \
     (CBASE_DEFAULT_LOGGER == CBASE_LOG_CUSTOM) ||                            \
     (CBASE_INTERNAL_LOGGER == CBASE_LOG_STDERR) ||                           \
     (CBASE_INTERNAL_LOGGER == CBASE_LOG_CUSTOM) ||                           \
     (CBASE_LOGGER == CBASE_LOG_STDERR) ||                                    \
     (CBASE_LOGGER == CBASE_LOG_CUSTOM))
CBASE_API_STATIC CBASE_VPRINTF(1) void _vprintf_to_stderr(const char *msg,
                                                          va_list args) {
#ifdef CBASE_DUMP_LOGGING_ERRORS_TO_STDERR
    int res = vfprintf(stderr, msg, args);

    if (res != 0) {
        fprintf(stderr, "Got error %d writing to STDERR\n", ferror(stderr));
    }
#else
    vfprintf(stderr, msg, args);
#endif
    clearerr(stderr);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void _printf_to_stderr(const char *msg,
                                                           ...) {
    va_list args;

    va_start(args, msg);
    _vprintf_to_stderr(msg, args);
    va_end(args);
}
#endif

#if ((CBASE_DEFAULT_LOGGER == CBASE_LOG_CUSTOM) ||                            \
     (CBASE_INTERNAL_LOGGER == CBASE_LOG_CUSTOM) ||                           \
     (CBASE_LOGGER == CBASE_LOG_CUSTOM))
CBASE_PRINTF(1, 2)
typedef void(LoggerFunc)(const char *msg, ...);

CBASE_VPRINTF(1)
typedef void(VLoggerFunc)(const char *msg, va_list args);
#endif

#endif

/* vi: set et ts=4 sw=4: */
