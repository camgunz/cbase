#pragma once

#ifndef _CBASE_COMMON_SLICE_H__
#define _CBASE_COMMON_SLICE_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/data_slice.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_SLICE_DECL(_stype, _etype)                                      \
    typedef struct _stype##Struct {                                           \
        size_t len;                                                           \
        _etype *data;                                                         \
    } _stype;

#define CBASE_COMMON_SLICE_IMPL_DECL(_api, _dname, _sname, _stype, _etype)    \
    _api void _sname##_skip_no_check(_stype *slice, size_t count);            \
                                                                              \
    _api int _sname##_skip(_stype *slice, size_t count);                      \
                                                                              \
    _api void _sname##_pop_left_no_zero_no_check(_stype *slice,               \
                                                 _etype *element);            \
                                                                              \
    _api int _sname##_pop_left_no_zero(_stype *slice, _etype *element);       \
                                                                              \
    _api void _sname##_pop_right_no_zero_no_check(_stype *slice,              \
                                                  _etype *element);           \
                                                                              \
    _api int _sname##_pop_right_no_zero(_stype *slice, _etype *element);

#define CBASE_SLICE_IMPL_DEPS(_api, _dname, _sname, _stype, _etype)           \
    CBASE_COMMON_DATA_IMPL(_api, _dname, _etype)                              \
    CBASE_DATA_SLICE_IMPL_NO_DEPS(_api, _dname, _etype)

#define CBASE_COMMON_SLICE_IMPL_NO_DEPS(_api, _dname, _etype)                 \
    _api void _sname##_skip_no_check(_stype *slice, size_t count) {           \
        _dname##_skip_no_check(&slice->data, &slice->len, count);             \
    }                                                                         \
                                                                              \
    _api int _sname##_skip(_stype *slice, size_t count) {                     \
        return _dname##_skip(&slice->data, &slice->len, count);               \
    }                                                                         \
                                                                              \
    _api void _sname##_pop_left_no_zero_no_check(_stype *slice,               \
                                                 _etype *element) {           \
        _dname##_pop_left_no_zero_no_check(&slice->data,                      \
                                           &slice->len,                       \
                                           _etype *element);                  \
    }                                                                         \
                                                                              \
    _api int _sname##_pop_left_no_zero(_stype *slice, _etype *element) {      \
        return _dname##_pop_left_no_zero(&slice->data,                        \
                                         &slice->len,                         \
                                         _etype * element);                   \
    }                                                                         \
                                                                              \
    _api void _sname##_pop_right_no_zero_no_check(_stype *slice,              \
                                                  _etype *element) {          \
        _dname##_pop_right_no_zero_no_check(slice->data,                      \
                                            &slice->len,                      \
                                            _etype *element);                 \
    }                                                                         \
                                                                              \
    _api int _sname##_pop_right_no_zero(_stype *slice, _etype *element) {     \
        return _dname##_pop_right_no_zero(slice->data,                        \
                                          &slice->len,                        \
                                          _etype * element);                  \
    }

#define CBASE_COMMON_SLICE_IMPL(_api, _dname, _sname, _stype, _etype)         \
    CBASE_COMMON_SLICE_IMPL_DEPS(_api, _dname, _sname, _stype, _etype)        \
    CBASE_COMMON_SLICE_IMPL_NO_DEPS(_api, _dname, _sname, _stype, _etype)

#endif

/* vi: set et ts=4 sw=4: */
