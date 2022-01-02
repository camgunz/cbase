#include "cbase/internal.h"

#include <stdio.h>

#include "cbase/logbase.h"

#if CBASE_DEFAULT_LOGGER_LOG_LEVEL == CBASE_LOG_LEVEL_RUNTIME
static LogLevel _default_log_level = CBASE_LOG_LEVEL_INFO;

LogLevel _default_log_get_level(void) {
    return _default_log_level;
}

void _default_log_set_level(LogLevel level) {
    _default_log_level = level;
}
#endif

#if CBASE_DEFAULT_LOGGER == CBASE_LOG_CUSTOM
static LoggerFunc *_default_loggers[CBASE_LOG_LEVEL_MAX] = {
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
};

static VLoggerFunc *_default_vloggers[CBASE_LOG_LEVEL_MAX] = {
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
};

LoggerFunc *_default_log_get_logger(LogLevel level) {
    return _default_loggers[level];
}

void _default_set_logger(LogLevel level, LoggerFunc log) {
    _default_loggers[level] = log;
}

VLoggerFunc *_default_log_get_vlogger(LogLevel level) {
    return _default_vloggers[level];
}

void _default_log_set_vlogger(LogLevel level, VLoggerFunc vlog) {
    _default_vloggers[level] = vlog;
}

#endif

#if CBASE_INTERNAL_LOGGER_LOG_LEVEL == CBASE_LOG_LEVEL_RUNTIME
static LogLevel _internal_log_level = CBASE_LOG_LEVEL_INFO;

LogLevel _internal_log_get_level(void) {
    return _internal_log_level;
}

void _internal_log_set_level(LogLevel level) {
    _internal_log_level = level;
}
#endif

#if CBASE_INTERNAL_LOGGER == CBASE_LOG_CUSTOM
static LoggerFunc *_internal_loggers[CBASE_LOG_LEVEL_MAX] = {
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
};

static VLoggerFunc *_internal_vloggers[CBASE_LOG_LEVEL_MAX] = {
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
};

LoggerFunc *_internal_log_get_logger(LogLevel level) {
    return _internal_loggers[level];
}

void _internal_set_logger(LogLevel level, LoggerFunc log) {
    _internal_loggers[level] = log;
}

VLoggerFunc *_internal_log_get_vlogger(LogLevel level) {
    return _internal_vloggers[level];
}

void _internal_log_set_vlogger(LogLevel level, VLoggerFunc vlog) {
    _internal_vloggers[level] = vlog;
}
#endif

#if CBASE_LOG_LEVEL == CBASE_LOG_LEVEL_RUNTIME
static LogLevel _log_level = CBASE_LOG_LEVEL_INFO;

LogLevel log_get_level(void) {
    return _log_level;
}

void log_set_level(LogLevel level) {
    _log_level = level;
}
#endif

#if CBASE_LOGGER == CBASE_LOG_CUSTOM
static LoggerFunc *loggers[CBASE_LOG_LEVEL_MAX] = {
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
    _printf_to_stderr,
};

static VLoggerFunc *vloggers[CBASE_LOG_LEVEL_MAX] = {
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
    _vprintf_to_stderr,
};

LoggerFunc *log_get_logger(LogLevel level) {
    return loggers[level];
}

void log_set_logger(LogLevel level, LoggerFunc log) {
    loggers[level] = log;
}

VLoggerFunc *log_get_vlogger(LogLevel level) {
    return vloggers[level];
}

void log_set_vlogger(LogLevel level, VLoggerFunc vlog) {
    vloggers[level] = vlog;
}
#endif
