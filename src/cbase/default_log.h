#pragma once

#ifndef _CBASE_DEFAULT_LOG_H__
#define _CBASE_DEFAULT_LOG_H__

#include "cbase/internal.h"

#include "cbase/logbase.h"

#ifndef DEFAULT_LOGGER_LOG_LEVEL
#define DEFAULT_LOGGER_LOG_LEVEL CBASE_LOG_LEVEL_INFO
#endif

#if DEFAULT_LOGGER_LOG_LEVEL == LOG_LEVEL_RUNTIME
CBASE_API
LogLevel _default_log_get_level(void);

CBASE_API
void _default_log_set_level(LogLevel level);
#endif

#if DEFAULT_LOGGER == LOG_CUSTOM
CBASE_API
LoggerFunc *_default_log_get_logger(LogLevel level);

CBASE_API
void _default_log_set_logger(LogLevel level, LoggerFunc log);

CBASE_API
VLoggerFunc *_default_log_get_vlogger(LogLevel level);

CBASE_API
void _default_log_set_vlogger(LogLevel level,
                              VLoggerFunc vlog);
#endif

CBASE_API_STATIC CBASE_VPRINTF(2) void _default_log_vmsg(LogLevel level,
                                                         const char *msg,
                                                         va_list args) {
#if DEFAULT_LOGGER_LOG_LEVEL == LOG_LEVEL_RUNTIME
    if (level < _default_log_get_level()) {
        return;
    }
#else
    if (level < DEFAULT_LOGGER_LOG_LEVEL) {
        return;
    }
#endif

#if DEFAULT_LOGGER == LOG_STDERR
    _vprintf_to_stderr(msg, args);
#elif DEFAULT_LOGGER == LOG_CUSTOM
    VLoggerFunc *vlog = _default_log_get_vlogger(level);
    vlog(msg, args);
#endif
}

CBASE_API_STATIC CBASE_PRINTF(2, 3) void _default_log_msg(LogLevel level,
                                                          const char *msg,
                                                          ...) {
    va_list args;

    va_start(args, msg);
    _default_log_vmsg(level, msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _default_log_vdebug(const char *msg,
                                                           va_list args) {
    _default_log_vmsg(CBASE_LOG_LEVEL_DEBUG, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void _default_log_debug(const char *msg,
                                                            ...) {
    va_list args;

    va_start(args, msg);
    _default_log_vdebug(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _default_log_vinfo(const char *msg,
                                                          va_list args) {
    _default_log_vmsg(CBASE_LOG_LEVEL_INFO, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void _default_log_info(const char *msg,
                                                           ...) {
    va_list args;

    va_start(args, msg);
    _default_log_vinfo(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _default_log_vwarning(const char *msg,
                                                             va_list args) {
    _default_log_vmsg(CBASE_LOG_LEVEL_WARNING, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void _default_log_warning(const char *msg,
                                                              ...) {
    va_list args;

    va_start(args, msg);
    _default_log_vwarning(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _default_log_vfailure(const char *msg,
                                                             va_list args) {
    _default_log_vmsg(CBASE_LOG_LEVEL_FAILURE, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void _default_log_failure(const char *msg,
                                                              ...) {
    va_list args;

    va_start(args, msg);
    _default_log_vfailure(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _default_log_verror(const char *msg,
                                                           va_list args) {
    _default_log_vmsg(CBASE_LOG_LEVEL_ERROR, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void _default_log_error(const char *msg,
                                                            ...) {
    va_list args;

    va_start(args, msg);
    _default_log_verror(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _default_log_vcritical(const char *msg,
                                                              va_list args) {
    _default_log_vmsg(CBASE_LOG_LEVEL_CRITICAL, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void _default_log_critical(const char *msg,
                                                               ...) {
    va_list args;

    va_start(args, msg);
    _default_log_vcritical(msg, args);
    va_end(args);
}

CBASE_API_STATIC CBASE_VPRINTF(1) void _default_log_vfatal(const char *msg,
                                                           va_list args) {
    _default_log_vmsg(CBASE_LOG_LEVEL_FATAL, msg, args);
}

CBASE_API_STATIC CBASE_PRINTF(1, 2) void _default_log_fatal(const char *msg,
                                                            ...) {
    va_list args;

    va_start(args, msg);
    _default_log_vfatal(msg, args);
    va_end(args);
}

#endif
