#pragma once

#ifndef _CBASE_INTERNAL_LOG_H__
#define _CBASE_INTERNAL_LOG_H__

#include "cbase/internal.h"

#include "cbase/logbase.h"

#if INTERNAL_LOGGER == LOG_DEFAULT

CBASE_API_STATIC CBASE_VPRINTF(2) void _internal_log_vmsg(LogLevel level,
                                                          const char *msg,
                                                          va_list args) {
    _default_log_vmsg(level, msg, args);
}

#else

#ifndef INTERNAL_LOGGER_LOG_LEVEL
#define INTERNAL_LOGGER_LOG_LEVEL CBASE_LOG_LEVEL_INFO
#endif

#if INTERNAL_LOGGER_LOG_LEVEL == LOG_LEVEL_RUNTIME
LogLevel _internal_log_get_level(void);
void _internal_log_set_level(LogLevel level);
#endif

#if INTERNAL_LOGGER == LOG_CUSTOM
LoggerFunc *_internal_log_get_logger(LogLevel level);
void _internal_log_set_logger(LogLevel level, LoggerFunc log);
VLoggerFunc *_internal_log_get_vlogger(LogLevel level);
void _internal_log_set_vlogger(LogLevel level, VLoggerFunc vlog);
#endif

CBASE_API_STATIC CBASE_VPRINTF(2) void _internal_log_vmsg(LogLevel level,
                                                          const char *msg,
                                                          va_list args) {
#if INTERNAL_LOGGER_LOG_LEVEL == LOG_LEVEL_RUNTIME
    if (level < _internal_log_get_level()) {
        return;
    }
#else
    if (level < INTERNAL_LOGGER_LOG_LEVEL) {
        return;
    }
#endif

#if INTERNAL_LOGGER == LOG_STDERR
    _vprintf_to_stderr(msg, args);
#elif INTERNAL_LOGGER == LOG_CUSTOM
    VLoggerFunc *vlog = _internal_log_get_vlogger(level);
    vlog(msg, args);
#endif
}

#endif

CBASE_API_STATIC CBASE_PRINTF(2, 3) void _internal_log_msg(LogLevel level,
                                                           const char *msg,
                                                           ...) {
    va_list args;

    va_start(args, msg);
    _internal_log_vmsg(level, msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_vdebug(const char *msg,
                                                            va_list args) {
    _internal_log_vmsg(CBASE_LOG_LEVEL_DEBUG, msg, args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_debug(const char *msg,
                                                           ...) {
    va_list args;

    va_start(args, msg);
    _internal_log_vdebug(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_vinfo(const char *msg,
                                                           va_list args) {
    _internal_log_vmsg(CBASE_LOG_LEVEL_INFO, msg, args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_info(const char *msg,
                                                          ...) {
    va_list args;

    va_start(args, msg);
    _internal_log_vinfo(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_vwarning(const char *msg,
                                                              va_list args) {
    _internal_log_vmsg(CBASE_LOG_LEVEL_WARNING, msg, args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_warning(const char *msg,
                                                             ...) {
    va_list args;

    va_start(args, msg);
    _internal_log_vwarning(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_vfailure(const char *msg,
                                                              va_list args) {
    _internal_log_vmsg(CBASE_LOG_LEVEL_FAILURE, msg, args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_failure(const char *msg,
                                                             ...) {
    va_list args;

    va_start(args, msg);
    _internal_log_vfailure(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_verror(const char *msg,
                                                            va_list args) {
    _internal_log_vmsg(CBASE_LOG_LEVEL_ERROR, msg, args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_error(const char *msg,
                                                           ...) {
    va_list args;

    va_start(args, msg);
    _internal_log_verror(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_vcritical(const char *msg,
                                                               va_list args) {
    _internal_log_vmsg(CBASE_LOG_LEVEL_CRITICAL, msg, args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_critical(const char *msg,
                                                              ...) {
    va_list args;

    va_start(args, msg);
    _internal_log_vcritical(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_vfatal(const char *msg,
                                                            va_list args) {
    _internal_log_vmsg(CBASE_LOG_LEVEL_FATAL, msg, args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _internal_log_fatal(const char *msg,
                                                           ...) {
    va_list args;

    va_start(args, msg);
    _internal_log_vfatal(msg, args);
    va_end(args);
}

#endif

/* vi: set et ts=4 sw=4: */
