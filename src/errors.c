#include "cbase/internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cbase/log.h"
#include "cbase/errors.h"

#ifdef ERRORS

#if (ERRORS == ERROR_LEVEL_RUNTIME) || (ERRORS == ERRORS_RUNTIME)
static LogLevel _error_log_levels[CBASE_ERROR_CODE_COUNT] = {
    CBASE_LOG_LEVEL_CRITICAL, /* CBASE_ERROR_OUT_OF_BOUNDS */
    CBASE_LOG_LEVEL_CRITICAL, /* CBASE_ERROR_MEMORY_ALLOC_FAILED */
    CBASE_LOG_LEVEL_FAILURE,  /* CBASE_ERROR_NOT_FOUND */
    CBASE_LOG_LEVEL_FAILURE,  /* CBASE_ERROR_NOT_EQUAL */
    CBASE_LOG_LEVEL_ERROR,    /* CBASE_ERROR_NUMERIC_OVERFLOW */
    CBASE_LOG_LEVEL_ERROR,    /* CBASE_ERROR_NULL_POINTER */
    CBASE_LOG_LEVEL_ERROR,    /* CBASE_ERROR_OVERLAPPING_MEMORY */
};

LogLevel errors_get_log_level(ErrorCode code) {
    return _error_log_levels[INT_MAX - code];
}

void errors_set_log_level(ErrorCode code, LogLevel level) {
    _error_log_levels[INT_MAX - code] = level;
}
#endif

#if ERRORS == ERRORS_RUNTIME
static ErrorHandler *_error_handlers[] = {
    _default_error_handler,
    _default_error_handler,
    _default_error_handler,
    _default_error_handler,
    _default_error_handler,
    _default_error_handler,
    _default_error_handler,
};

ErrorHandler *errors_get_handler(ErrorCode code) {
    return _error_handlers[INT_MAX - code];
}

void errors_set_handler(ErrorCode code, ErrorHandler handler) {
    _error_handlers[INT_MAX - code] = handler;
}

#endif

#endif
