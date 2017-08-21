#include "cbase.h"

#define empty(status) status_failure( \
    status,                           \
    "strbase",                        \
    STRBASE_EMPTY,                    \
    "String data is empty"            \
)

