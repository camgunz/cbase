#include "cbase.h"

static Array *status_handlers = NULL;

static StatusHandler* get_status_handler(const char *domain, int code) {
    if (!status_handlers) {
        return NULL;
    }

    for (size_t i = 0; i < status_handlers->len; i++) {
        StatusHandler *sh = array_index_fast(status_handlers, i);

        if (sh->code != code) {
            continue;
        }

        if ((!sh->domain) && (!domain)) {
            return sh;
        }

        if (sh->domain && domain && strcmp(sh->domain, domain) == 0) {
            return sh;
        }
    }

    return NULL;
}

static bool get_status_handler_index(const char *domain, int code,
                                                         size_t *index) {
    if (!status_handlers) {
        return false;
    }

    for (size_t i = 0; i < status_handlers->len; i++) {
        StatusHandler *sh = array_index_fast(status_handlers, i);

        if (sh->code != code) {
            continue;
        }

        if ((!sh->domain) && (!domain)) {
            *index = i;
            return true;
        }

        if (sh->domain && domain && strcmp(sh->domain, domain) == 0) {
            *index = i;
            return true;
        }
    }

    return false;
}

bool status_set_handler(const char *domain, int code,
                                            void *data,
                                            StatusHandlerFunc handler,
                                            Status *status) {
    if (!status_handlers) {
        bool res = false;

        res = array_new_alloc(
            &status_handlers,
            sizeof(StatusHandler),
            1,
            status
        );
        if (!res) {
            return false;
        }
    }

    StatusHandler *sh = get_status_handler(domain, code);

    if (!sh) {
        if (!array_append(status_handlers, (void **)&sh, status)) {
            return false;
        }

        sh->code = code;
        sh->domain = domain;
    }

    sh->data = data;
    sh->handler = handler;

    return status_ok(status);
}

void status_clear_handler(const char *domain, int code) {
    size_t index = 0;

    if (get_status_handler_index(domain, code, &index)) {
        array_delete_fast(status_handlers, index);
    }
}

bool _status_new(StatusLevel level, const char *domain, int code,
                                                        const char *message,
                                                        const char *file,
                                                        int line,
                                                        Status **new_status,
                                                        Status *status) {
    *new_status = cbmalloc(1, sizeof(Status));

    if (!(*new_status)) {
        return alloc_failure(status);
    }

    _status_set((*new_status), level, domain, code, message, file, line);

    return status_ok(status);
}

void status_init(Status *status) {
    status->level = STATUS_OK;
    status->code = 0;
    status->domain = NULL;
    status->message = NULL;
    status->file = NULL;
    status->line = 0;
}

void status_copy(Status *dst, Status *src) {
    dst->level = src->level;
    dst->code = src->code;
    dst->domain = src->domain;
    dst->message = src->message;
    dst->file = src->file;
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
                                                    int line) {
    status->level = level;
    status->domain = domain;
    status->code = code;
    status->message = message;
    status->file = file;
    status->line = line;
}

bool _status_debug(Status *status, const char *domain, int code,
                                                       const char *message,
                                                       const char *file,
                                                       int line) {
    if (status) {
        _status_set(status, STATUS_DEBUG, domain, code, message, file, line);
        status_handle(status);
    }
    else {
        Status s;

        _status_set(&s, STATUS_DEBUG, domain, code, message, file, line);
        status_handle(&s);
    }

    return true;
}

bool _status_info(Status *status, const char *domain, int code,
                                                      const char *message,
                                                      const char *file,
                                                      int line) {
    if (status) {
        _status_set(status, STATUS_INFO, domain, code, message, file, line);
        status_handle(status);
    }
    else {
        Status s;

        _status_set(&s, STATUS_INFO, domain, code, message, file, line);
        status_handle(&s);
    }

    return true;
}

bool _status_warning(Status *status, const char *domain, int code,
                                                         const char *message,
                                                         const char *file,
                                                         int line) {
    if (status) {
        _status_set(status, STATUS_WARNING, domain, code, message, file, line);
        status_handle(status);
    }
    else {
        Status s;

        _status_set(&s, STATUS_WARNING, domain, code, message, file, line);
        status_handle(&s);
    }

    return true;
}

bool _status_error(Status *status, const char *domain, int code,
                                                       const char *message,
                                                       const char *file,
                                                       int line) {
    if (status) {
        _status_set(status, STATUS_ERROR, domain, code, message, file, line);
        status_handle(status);
    }
    else {
        Status s;

        _status_set(&s, STATUS_ERROR, domain, code, message, file, line);
        status_handle(&s);
    }

    return false;
}

bool _status_failure(Status *status, const char *domain, int code,
                                                         const char *message,
                                                         const char *file,
                                                         int line) {
    if (status) {
        _status_set(status, STATUS_FAILURE, domain, code, message, file, line);
        status_handle(status);
    }
    else {
        Status s;

        _status_set(&s, STATUS_FAILURE, domain, code, message, file, line);
        status_handle(&s);
    }

    return false;
}

bool _status_critical(Status *status, const char *domain, int code,
                                                          const char *message,
                                                          const char *file,
                                                          int line) {
    if (status) {
        _status_set(status, STATUS_CRITICAL, domain, code, message, file, line);
        status_handle(status);
    }
    else {
        Status s;

        _status_set(&s, STATUS_CRITICAL, domain, code, message, file, line);
        status_handle(&s);
    }

    return false;
}

bool _status_fatal(Status *status, const char *domain, int code,
                                                       const char *message,
                                                       const char *file,
                                                       int line) {
    if (status) {
        _status_set(status, STATUS_FATAL, domain, code, message, file, line);
        status_handle(status);
    }
    else {
        Status s;

        _status_set(&s, STATUS_FATAL, domain, code, message, file, line);
        status_handle(&s);
    }

    return false;
}

void status_handle(Status *status) {
    const char *domain = "-";
    const char *msg = "-";

    if (status->domain) {
        domain = status->domain;
    }

    if (status->message) {
        msg = status->message;
    }

    StatusHandler *status_handler = get_status_handler(
        status->domain,
        status->code
    );

    if (status_handler) {
        status_handler->handler(status_handler, status);
        return;
    }

    switch (status->level) {
        case STATUS_DEBUG:
            log_debug("%s (%d) %s", domain, status->code, msg);
            break;
        case STATUS_INFO:
            log_info("%s (%d) %s", domain, status->code, msg);
            break;
        case STATUS_WARNING:
             log_warning("%s (%d) %s", domain, status->code, msg);
           break;
        case STATUS_ERROR:
            log_error("%s (%d) %s", domain, status->code, msg);
            break;
        case STATUS_CRITICAL:
            log_critical("%s (%d) %s", domain, status->code, msg);
            break;
        case STATUS_FATAL:
            log_fatal("%s (%d) %s", domain, status->code, msg);
            break;
        case STATUS_OK:
        case STATUS_FAILURE:
        default:
            break;
    }
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
