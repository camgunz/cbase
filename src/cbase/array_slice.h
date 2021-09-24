#pragma once

#ifndef _CBASE_ARRAY_SLICE_H__
#define _CBASE_ARRAY_SLICE_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/common_array.h"
#include "cbase/data_slice.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_ARRAY_SLICE_DECL(_stype, _etype)                                \
    typedef struct _stype##Struct {                                           \
        size_t len;                                                           \
        _etype *data;                                                         \
    } _stype;

#define CBASE_ARRAY_SLICE_IMPL_DECL(_api, _dname, _aname, _atype, _etype)     \
    CBASE_COMMON_ARRAY_IMPL_DECL(_api, _dname, _aname, _atype, _etype)        \
                                                                              \
    _api void _aname##_assign_no_check(_atype *slice, const _atype *array);   \
                                                                              \
    _api int _aname##_assign(_atype *slice, const _atype *array);             \
                                                                              \
    _api void _aname##_skip_no_check(_atype *slice, size_t count);            \
                                                                              \
    _api int _aname##_skip(_atype *slice, size_t count);                      \
                                                                              \
    _api void _aname##_seek_no_check(_atype *slice, const _atype *array);     \
                                                                              \
    _api int _aname##_seek(_atype *slice, const _atype *array);               \
                                                                              \
    _api void _aname##_pop_left_no_zero_no_check(_atype *slice,               \
                                                 _dtype *element);            \
                                                                              \
    _api int _aname##_pop_left_no_zero(_atype *slice, _dtype *element);       \
                                                                              \
    _api void _aname##_pop_right_no_zero_no_check(_atype *slice,              \
                                                  _dtype *element);           \
                                                                              \
    _api int _aname##_pop_right_no_zero(_atype *slice, _dtype *element);

#define CBASE_ARRAY_SLICE_IMPL_DEPS(_api, _dname, _etype)                     \
    CBASE_COMMON_ARRAY_IMPL_DEPS(_api, _dname, _etype)                        \
    CBASE_DATA_SLICE_IMPL_DEPS(_api, _dname, _etype)

#define CBASE_ARRAY_SLICE_IMPL_NO_DEPS(_api, _dname, _aname, _atype, _etype)  \
    CBASE_COMMON_ARRAY_IMPL_NO_DEPS(_api, _dname, _aname, _atype, _etype)     \
                                                                              \
    _api void _aname##_assign_no_check(_atype *slice, const _atype *array) {  \
        _dname##_assign_no_check(&slice->data,                                \
                                 &slice->len,                                 \
                                 array->data,                                 \
                                 array->len);                                 \
    }                                                                         \
                                                                              \
    _api int _aname##_assign(_atype *slice, const _atype *array) {            \
        CBASE_DELEGATE(_dname##_assign(&slice->data,                          \
                                       &slice->len,                           \
                                       array->data,                           \
                                       array->len));                          \
    }                                                                         \
                                                                              \
    _api void _aname##_skip_no_check(_atype *slice, size_t count){            \
        _dname##_skip_no_check(&slice->data, &slice->len, count)}             \
                                                                              \
    _api int _aname##_skip(_atype *slice, size_t count) {                     \
        CBASE_DELEGATE(_dname##_skip(&slice->data, &slice->len, count));      \
    }                                                                         \
                                                                              \
    _api void _aname##_seek_no_check(_atype *slice, const _atype *array) {    \
        _dname##_seek_no_check(&slice->data,                                  \
                               &slice->len,                                   \
                               array->data,                                   \
                               array->len);                                   \
    }                                                                         \
                                                                              \
    _api int _aname##_seek(_atype *slice, const _atype *array) {              \
        CBASE_DELEGATE(_dname##_seek(&slice->data,                            \
                                     &slice->len,                             \
                                     array->data,                             \
                                     array->len));                            \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_left_no_zero_no_check(_atype *slice,               \
                                                 _dtype *element) {           \
        _dname##_pop_left_no_zero_no_check(&slice->data,                      \
                                           &slice->len,                       \
                                           element);                          \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_left_no_zero(_atype *slice, _dtype *element) {      \
        CBASE_DELEGATE(                                                       \
            _dname##_pop_left_no_zero(&slice->data, &slice->len, element));   \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_right_no_zero_no_check(_atype *slice,              \
                                                  _dtype *element) {          \
        _dname##_pop_right_no_zero_no_check(&slice->data,                     \
                                            &slice->len,                      \
                                            element);                         \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_right_no_zero(_atype *slice, _dtype *element) {     \
        CBASE_DELEGATE(_dname##_pop_right_no_zero_no_check(&slice->data,      \
                                                           &slice->len,       \
                                                           element));         \
    }

#define CBASE_ARRAY_SLICE_IMPL(_api, _dname, _aname, _atype, _etype)          \
    CBASE_ARRAY_SLICE_IMPL_DEPS(_api, _dname, _etype)                         \
    CBASE_ARRAY_SLICE_IMPL_NO_DEPS(_api, _dname, _atype, _aname, _atype)

#endif

/* vi: set et ts=4 sw=4: */
