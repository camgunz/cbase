#pragma once

#ifndef LOG_H__
#define LOG_H__

typedef enum {
    LOG_DEBUG = 1,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL,
    LOG_FATAL,
} LogLevel;

void log_msg(LogLevel level, const char *msg, ...);
void log_vmsg(LogLevel level, const char *msg, va_list args);
void log_debug(const char *msg, ...);
void log_vdebug(const char *msg, va_list args);
void log_info(const char *msg, ...);
void log_vinfo(const char *msg, va_list args);
void log_warning(const char *msg, ...);
void log_vwarning(const char *msg, va_list args);
void log_error(const char *msg, ...);
void log_verror(const char *msg, va_list args);
void log_critical(const char *msg, ...);
void log_vcritical(const char *msg, va_list args);
void log_fatal(const char *msg, ...);
void log_vfatal(const char *msg, va_list args);

#endif

/* vi: set et ts=4 sw=4: */
