#pragma once

#ifndef _CBASE_ARRAY_OWNERSHIP_MANAGEMENT_H__
#define _CBASE_ARRAY_OWNERSHIP_MANAGEMENT_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/checked_math.h"
#include "cbase/checks.h"
#include "cbase/errors.h"

#define CBASE_ARRAY_OWNERSHIP_MANAGEMENT_DECL(_api,                           \
                                              _dname,                         \
                                              _etype,                         \
                                              _aname,                         \
                                              _atype)                         \
    _api int _aname##_ensure_capacity_no_zero(_atype *array, size_t cap);     \
                                                                              \
    _api int _aname##_ensure_capacity(_atype *array, size_t cap); \
                                                                              \
    _api int _aname##_set_length_no_zero_no_check(_atype *array, size_t len); \
                                                                              \
    _api int _aname##_set_length_no_zero(_atype *array, size_t len);          \
                                                                              \
    _api int _aname##_set_length_no_check(_atype *array, size_t len);         \
                                                                              \
    _api int _aname##_set_length(_atype *array, size_t len);

#define CBASE_ARRAY_OWNERSHIP_MANAGEMENT_IMPL(_api, _dname, _etype, _aname, _atype) \
    _api int _aname##_set_length_no_zero_no_check(_atype *array, size_t len) { \
      CBASE_DELEGATE(_dname##_set_length_no_zero_no_check(&array->data, &array->dlen, len); \
    } \
                                                                              \
    _api int _aname##_set_length_no_zero(_atype *array, size_t len) {          \
      CBASE_DELEGATE(_dname##_set_length_no_zero(_atype *array, size_t len)); \
    } \
                                                                              \
    _api int _aname##_set_length_no_check(_atype *array, size_t len) {         \
      CBASE_DELEGATE(_dname##_set_length_no_check(_atype *array, size_t len)); \
    } \
                                                                              \
    _api int _aname##_set_length(_atype *array, size_t len) { \
      CBASE_DELEGATE(_dname##_set_length(_atype *array, size_t len)); \
    } \

#define CBASE_ARRAY_STATIC_MANAGEMENT_IMPL(_api,                              \
                                           _dname,                            \
                                           _etype,                            \
                                           _aname,                            \
                                           _atype)                            \
    _api int _aname##_ensure_capacity_no_zero(_atype *array, size_t cap) {    \
        CBASE_DELEGATE(_dname##_ensure_capacity_no_zero(&array->data,         \
                                                        &array->len,          \
                                                        cap));                \
    }                                                                         \
                                                                              \
    _api int _aname##_ensure_capacity(_atype *array, size_t cap) {            \
        CBASE_DELEGATE(                                                       \
            _dname##_ensure_capacity(&array->data, &array->len, cap));        \
    }

#define CBASE_ARRAY_DYNAMIC_MANAGEMENT_IMPL(_api,                             \
                                            _dname,                           \
                                            _etype,                           \
                                            _aname,                           \
                                            _atype)                           \
    _api int _aname##_ensure_capacity_no_zero(_atype *array, size_t cap) {    \
        CBASE_DELEGATE(_dname##_ensure_capacity_no_zero(&array->data,         \
                                                        &array->cap,          \
                                                        cap));                \
    }                                                                         \
                                                                              \
    _api int _aname##_ensure_capacity(_atype *array, size_t cap) {            \
        CBASE_DELEGATE(                                                       \
            _dname##_ensure_capacity(&array->data, &array->cap, cap));        \
    }

#endif
