#include "cbase.h"

bool _status_new(StatusLevel level, const char *domain, int code,
                                                        const char *message,
                                                        const char *file,
                                                        const char *func,
                                                        int line,
                                                        Status **new_status,
                                                        Status *status) {
    if (!cbmalloc(1, sizeof(Status), new_status, status)) {
        return false;
    }

    _status_set((*new_status), level, domain, code, message, file, func, line);

    return status_ok(status);
}

void status_init(Status *status) {
    status->level = STATUS_OK;
    status->code = 0;
    status->domain = NULL;
    status->message = NULL;
    status->file = NULL;
    status->func = NULL;
    status->line = 0;
}

void status_copy(Status *dst, Status *src) {
    dst->level = src->level;
    dst->code = src->code;
    dst->domain = src->domain;
    dst->message = src->message;
    dst->file = src->file;
    dst->func = src->func;
    dst->line = src->line;
}

bool status_is_ok(Status *status) {
    return status->level == STATUS_OK &&
           status->code == 0 &&
           status->domain == NULL &&
           status->message == NULL;
}

void _status_set(Status *status, StatusLevel level, const char *domain,
                                                    int code,
                                                    const char *message,
                                                    const char *file,
                                                    const char *func,
                                                    int line) {
    status->level = level;
    status->domain = domain;
    status->code = code;
    status->message = message;
    status->file = file;
    status->func = func;
    status->line = line;
}

bool _status_debug(Status *status, const char *domain, int code,
                                                       const char *message,
                                                       const char *file,
                                                       const char *func,
                                                       int line) {
    if (status) {
        _status_set(
            status, STATUS_DEBUG, domain, code, message, file, func, line
        );
    }

    return true;
}

bool _status_info(Status *status, const char *domain, int code,
                                                      const char *message,
                                                      const char *file,
                                                      const char *func,
                                                      int line) {
    if (status) {
        _status_set(
            status, STATUS_INFO, domain, code, message, file, func, line
        );
    }

    return true;
}

bool _status_warning(Status *status, const char *domain, int code,
                                                         const char *message,
                                                         const char *file,
                                                         const char *func,
                                                         int line) {
    if (status) {
        _status_set(
            status, STATUS_WARNING, domain, code, message, file, func, line
        );
    }

    return true;
}

bool _status_error(Status *status, const char *domain, int code,
                                                       const char *message,
                                                       const char *file,
                                                       const char *func,
                                                       int line) {
    if (status) {
        _status_set(
            status, STATUS_ERROR, domain, code, message, file, func, line
        );
    }

    return false;
}

bool _status_failure(Status *status, const char *domain, int code,
                                                         const char *message,
                                                         const char *file,
                                                         const char *func,
                                                         int line) {
    if (status) {
        _status_set(
            status, STATUS_FAILURE, domain, code, message, file, func, line
        );
    }

    return false;
}

bool _status_critical(Status *status, const char *domain, int code,
                                                          const char *message,
                                                          const char *file,
                                                          const char *func,
                                                          int line) {
    if (status) {
        _status_set(
            status, STATUS_CRITICAL, domain, code, message, file, func, line
        );
    }

    return false;
}

bool _status_fatal(Status *status, const char *domain, int code,
                                                       const char *message,
                                                       const char *file,
                                                       const char *func,
                                                       int line) {
    if (status) {
        _status_set(
            status, STATUS_FATAL, domain, code, message, file, func, line
        );
    }

    return false;
}

bool status_match(Status *status, const char *domain, int code) {
    if (code != status->code) {
        return false;
    }

    if (domain && status->domain) {
        if (strcmp(domain, status->domain) == 0)  {
            return true;
        }
    }
    else if ((!domain) && (!status->domain)) {
        return true;
    }

    return false;
}



/* vi: set et ts=4 sw=4: */
