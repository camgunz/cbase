#pragma once

#ifndef _CBASE_ARRAY_SLICE_MANAGEMENT_H__
#define _CBASE_ARRAY_SLICE_MANAGEMENT_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "cbase/data_base.h"

#define CBASE_ARRAY_SLICE_MANAGEMENT_IMPL_DECL(_api, _aname, _atype)          \
    _api void _aname##_assign_no_check(_atype *array, _atype *array2);        \
                                                                              \
    _api int _aname##_assign(_atype *array, _atype *array2);

#define CBASE_ARRAY_SLICE_MANAGEMENT_IMPL(_api,                               \
                                          _dname,                             \
                                          _etype,                             \
                                          _aname,                             \
                                          _atype)                             \
    _api void _aname##_assign_no_check(_atype *array, _atype *array2) {       \
        _dname##_assign_no_check(&array->data,                                \
                                 &array->len,                                 \
                                 array2->data,                                \
                                 array2->len);                                \
    }                                                                         \
                                                                              \
    _api int _aname##_assign(_atype *array, _atype *array2) {                 \
        CBASE_DELEGATE(_dname##_assign(&array->data,                          \
                                       &array->len,                           \
                                       array2->data,                          \
                                       array2->len));                         \
    }

#endif
