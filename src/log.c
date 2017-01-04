#include <stdio.h>

#include "cbase.h"

void log_msg(LogLevel level, const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(level, msg, args);
    va_end(args);
}

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

void log_debug(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_DEBUG, msg, args);
    va_end(args);
}

void log_vdebug(const char *msg, va_list args) {
    log_vmsg(LOG_DEBUG, msg, args);
}

void log_info(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_INFO, msg, args);
    va_end(args);
}

void log_vinfo(const char *msg, va_list args) {
    log_vmsg(LOG_INFO, msg, args);
}

void log_warning(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_WARNING, msg, args);
    va_end(args);
}

void log_vwarning(const char *msg, va_list args) {
    log_vmsg(LOG_WARNING, msg, args);
}

void log_error(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_ERROR, msg, args);
    va_end(args);
}

void log_verror(const char *msg, va_list args) {
    log_vmsg(LOG_ERROR, msg, args);
}

void log_critical(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_CRITICAL, msg, args);
    va_end(args);
}

void log_vcritical(const char *msg, va_list args) {
    log_vmsg(LOG_CRITICAL, msg, args);
}

void log_fatal(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    log_vmsg(LOG_FATAL, msg, args);
    va_end(args);
}

void log_vfatal(const char *msg, va_list args) {
    log_vmsg(LOG_FATAL, msg, args);
}


/* vi: set et ts=4 sw=4: */
