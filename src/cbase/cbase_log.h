#pragma once

#ifndef _CBASE_CBASE_LOG_H__
#define _CBASE_CBASE_LOG_H__

#include "cbase/internal.h"
#include "cbase/logbase.h"

#if LOGGER == LOG_DEFAULT

CBASE_API_STATIC CBASE_VPRINTF(2) void log_vmsg(LogLevel level,
                                                const char *msg,
                                                va_list args) {
    _default_log_vmsg(level, msg, args);
}

#else

#ifndef LOGGER_LOG_LEVEL
#define LOGGER_LOG_LEVEL CBASE_LOG_LEVEL_INFO
#endif

#if LOGGER_LOG_LEVEL == LOG_LEVEL_RUNTIME
CBASE_API
LogLevel log_get_level(void);

CBASE_API
void log_set_level(LogLevel level);
#endif

#if LOGGER == LOG_CUSTOM
CBASE_API
LoggerFunc *log_get_logger(LogLevel level);

CBASE_API
void log_set_logger(LogLevel level, LoggerFunc log);

CBASE_API
VLoggerFunc *log_get_vlogger(LogLevel level);

CBASE_API
void log_set_vlogger(LogLevel level, VLoggerFunc vlog);
#endif

CBASE_API_STATIC CBASE_VPRINTF(2) void log_vmsg(LogLevel level,
                                                const char *msg,
                                                va_list args) {
#if LOGGER_LOG_LEVEL == _LOG_LEVEL_RUNTIME
    if (level < log_get_level()) {
        return;
    }
#else
    if (level < LOGGER_LOG_LEVEL) {
        return;
    }
#endif

#if LOGGER == LOG_STDERR
    _vprintf_to_stderr(msg);
#elif LOGGER == LOG_CUSTOM
    VLoggerFunc *vlog = log_get_vlogger(level);
    vlog(msg, args);
#endif
}

#endif

CBASE_API_STATIC CBASE_PRINTF(2, 3) void log_msg(LogLevel level,
                                                 const char *msg,
                                                 ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(level, msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void log_vdebug(const char *msg,
                                                  va_list args) {
    log_vmsg(CBASE_LOG_LEVEL_DEBUG, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void log_debug(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vdebug(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void log_vinfo(const char *msg,
                                                 va_list args) {
    log_vmsg(CBASE_LOG_LEVEL_INFO, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void log_info(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vinfo(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void log_vwarning(const char *msg,
                                                    va_list args) {
    log_vmsg(CBASE_LOG_LEVEL_WARNING, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void log_warning(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vwarning(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void log_vfailure(const char *msg,
                                                    va_list args) {
    log_vmsg(CBASE_LOG_LEVEL_FAILURE, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void log_failure(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vfailure(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void log_verror(const char *msg,
                                                  va_list args) {
    log_vmsg(CBASE_LOG_LEVEL_ERROR, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void log_error(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_verror(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void log_vcritical(const char *msg,
                                                     va_list args) {
    log_vmsg(CBASE_LOG_LEVEL_CRITICAL, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void log_critical(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vcritical(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void log_vfatal(const char *msg,
                                                  va_list args) {
    log_vmsg(CBASE_LOG_LEVEL_FATAL, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void log_fatal(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vfatal(msg, args);
    va_end(args);
}

#endif

/* vi: set et ts=4 sw=4: */
