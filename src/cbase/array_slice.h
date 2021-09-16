#pragma once

#ifndef _CBASE_ARRAY_SLICE_H__
#define _CBASE_ARRAY_SLICE_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/common_slice.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_ARRAY_SLICE_IMPL_DECL(_api,                                     \
                                    _dname,                                   \
                                    _atype,                                   \
                                    _sname,                                   \
                                    _stype,                                   \
                                    _etype)                                   \
    _api void _sname##_assign_no_check(_stype *slice, const _atype *array);   \
                                                                              \
    _api int _sname##_assign(_stype *slice, const _atype *array);             \
                                                                              \
    _api void _sname##_seek_no_check(_stype *slice, const _atype *array);     \
                                                                              \
    _api int _sname##_seek(_stype *slice, const _atype *array);

#define CBASE_ARRAY_SLICE_IMPL_NO_DEPS(_api, _dname, _atype, _sname, _stype)  \
    _api void _sname##_assign_no_check(_stype *slice, const _atype *array) {  \
        _dname##_assign_no_check(&slice->data,                                \
                                 &slice->len,                                 \
                                 array->data,                                 \
                                 array->len);                                 \
    }                                                                         \
                                                                              \
    _api int _sname##_assign(_stype *slice, const _atype *array) {            \
        return _dname##_assign(&slice->data,                                  \
                               &slice->len,                                   \
                               array->data,                                   \
                               array->len);                                   \
    }                                                                         \
                                                                              \
    _api void _sname##_seek_no_check(_stype *slice, const _atype *array) {    \
        _dname##_seek_no_check(&slice->data,                                  \
                               slice->len,                                    \
                               array->data,                                   \
                               array->len);                                   \
    }                                                                         \
                                                                              \
    _api int _sname##_seek(_stype *slice, const _atype *array) {              \
        return _dname##_seek(&slice->data,                                    \
                             slice->len,                                      \
                             array->data,                                     \
                             array->len);                                     \
    }

#define CBASE_ARRAY_SLICE_IMPL(_api, _dname, _atype, _sname, _stype, _etype)  \
    CBASE_SLICE_IMPL_DEPS(_api, _dname, _sname, _stype, _etype)               \
    CBASE_ARRAY_SLICE_IMPL_NO_DEPS(_api, _dname, _atype, _sname, _stype)

#endif

/* vi: set et ts=4 sw=4: */
