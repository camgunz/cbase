#include <stdio.h>

#include "cbase.h"

__attribute__((format(printf, 2, 3)))
void log_msg(LogLevel level, const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(level, msg, args);
    va_end(args);
}

__attribute__((format(printf, 2, 0)))
void log_vmsg(LogLevel level, const char *msg, va_list args) {
    switch(level) {
        case LOG_DEBUG:
        case LOG_INFO:
            vprintf(msg, args);
            break;
        case LOG_WARNING:
        case LOG_ERROR:
        case LOG_CRITICAL:
        case LOG_FATAL:
            vfprintf(stderr, msg, args);
            break;
    }
}

__attribute((format(printf, 1, 2)))
void log_debug(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_DEBUG, msg, args);
    va_end(args);
}

__attribute__((format(printf, 1, 0)))
void log_vdebug(const char *msg, va_list args) {
    log_vmsg(LOG_DEBUG, msg, args);
}

__attribute((format(printf, 1, 2)))
void log_info(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_INFO, msg, args);
    va_end(args);
}

__attribute__((format(printf, 1, 0)))
void log_vinfo(const char *msg, va_list args) {
    log_vmsg(LOG_INFO, msg, args);
}

__attribute((format(printf, 1, 2)))
void log_warning(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_WARNING, msg, args);
    va_end(args);
}

__attribute__((format(printf, 1, 0)))
void log_vwarning(const char *msg, va_list args) {
    log_vmsg(LOG_WARNING, msg, args);
}

__attribute((format(printf, 1, 2)))
void log_error(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_ERROR, msg, args);
    va_end(args);
}

__attribute__((format(printf, 1, 0)))
void log_verror(const char *msg, va_list args) {
    log_vmsg(LOG_ERROR, msg, args);
}

__attribute((format(printf, 1, 2)))
void log_critical(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_CRITICAL, msg, args);
    va_end(args);
}

__attribute__((format(printf, 1, 0)))
void log_vcritical(const char *msg, va_list args) {
    log_vmsg(LOG_CRITICAL, msg, args);
}

__attribute((format(printf, 1, 2)))
void log_fatal(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_FATAL, msg, args);
    va_end(args);
}

__attribute__((format(printf, 1, 0)))
void log_vfatal(const char *msg, va_list args) {
    log_vmsg(LOG_FATAL, msg, args);
}

/* vi: set et ts=4 sw=4: */
