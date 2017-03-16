#ifndef STATUS_H__
#define STATUS_H__

typedef enum {
    STATUS_OK,       /* OK, no info */
    STATUS_DEBUG,    /* Debugging info */
    STATUS_INFO,     /* General info */
    STATUS_FAILURE,  /* Failed, could not continue */
    STATUS_WARNING,  /* Unexpected condition */
    STATUS_ERROR,    /* Programming error */
    STATUS_CRITICAL, /* Possibly fatal to the program; requires recovery */
    STATUS_FATAL,    /* Exits program */
} StatusLevel;

typedef struct {
    StatusLevel  level;
    const char  *domain;
    int          code;
    const char  *message;
    const char  *file;
    int          line;
} Status;

struct StatusHandlerStruct;

typedef void(StatusHandlerFunc)(struct StatusHandlerStruct *status_handler,
                                Status *status);

struct StatusHandlerStruct {
    const char *domain;
    int code;
    void *data;
    StatusHandlerFunc *handler;
};

typedef struct StatusHandlerStruct StatusHandler;

#define status_new(level, domain, code, msg, new_st, st) \
    _status_new(level, domain, code, msg, __FILE__, __LINE__, new_st, st)
#define status_set(level, domain, code, msg) \
    _status_set(level, domain, code, msg, __FILE__, __LINE__)
#define status_debug(level, domain, code, msg) \
    _status_debug(level, domain, code, msg, __FILE__, __LINE__)
#define status_info(level, domain, code, msg) \
    _status_info(level, domain, code, msg, __FILE__, __LINE__)
#define status_warning(level, domain, code, msg) \
    _status_warning(level, domain, code, msg, __FILE__, __LINE__)
#define status_failure(level, domain, code, msg) \
    _status_failure(level, domain, code, msg, __FILE__, __LINE__)
#define status_error(level, domain, code, msg) \
    _status_error(level, domain, code, msg, __FILE__, __LINE__)
#define status_critical(level, domain, code, msg) \
    _status_critical(level, domain, code, msg, __FILE__, __LINE__)
#define status_fatal(level, domain, code, msg) \
    _status_fatal(level, domain, code, msg, __FILE__, __LINE__)
#define status_clear(status) status_init(status)

bool _status_new(StatusLevel level, const char *domain,
                                    int code,
                                    const char *message,
                                    const char *file,
                                    int line,
                                    Status **new_status,
                                    Status *status);
void status_init(Status *status);
void status_copy(Status *dst, Status *src);
bool status_is_ok(Status *status);
void _status_set(Status *status, StatusLevel level,
                                 const char *domain,
                                 int code,
                                 const char *message,
                                 const char *file,
                                 int line);
bool status_ok(Status *status);
bool _status_debug(Status *status, const char *domain,
                                   int code,
                                   const char *message,
                                   const char *file,
                                   int line);
bool _status_info(Status *status, const char *domain,
                                  int code,
                                  const char *message,
                                  const char *file,
                                  int line);
bool _status_warning(Status *status, const char *domain,
                                     int code,
                                     const char *message,
                                     const char *file,
                                     int line);
bool _status_failure(Status *status, const char *domain,
                                     int code,
                                     const char *message,
                                     const char *file,
                                     int line);
bool _status_error(Status *status, const char *domain,
                                   int code,
                                   const char *message,
                                   const char *file,
                                   int line);
bool _status_critical(Status *status, const char *domain,
                                      int code,
                                      const char *message,
                                      const char *file,
                                      int line);
bool _status_fatal(Status *status, const char *domain,
                                   int code,
                                   const char *message,
                                   const char *file,
                                   int line);
void status_handle(Status *status);
bool status_match(Status *status, const char *domain, int code);
bool status_set_handler(const char *domain, int code,
                                            void *data,
                                            StatusHandlerFunc *handler,
                                            Status *status);
void status_clear_handler(const char *domain, int code);

#define status_ok(st) true

#endif

/* vi: set et ts=4 sw=4: */
