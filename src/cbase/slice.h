#pragma once

#ifndef _CBASE_SLICE_H__
#define _CBASE_SLICE_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/common_slice.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_SLICE_IMPL_DECL(_api, _dname, _sname, _stype, _etype)           \
    _api void _sname##_assign_no_check(_stype *slice,                         \
                                       _etype *data,                          \
                                       size_t dlen);                          \
                                                                              \
    _api int _sname##_assign(_stype *slice, _etype *data, size_t dlen);       \
                                                                              \
    _api void _sname##_seek_no_check(_stype *slice,                           \
                                     const _etype *data,                      \
                                     size_t dlen);                            \
                                                                              \
    _api int _sname##_seek(_stype *slice, const _etype *data, size_t dlen);

#define CBASE_SLICE_IMPL_NO_DEPS(_api, _dname, _etype)                        \
    _api void _sname##_assign_no_check(_stype *slice,                         \
                                       _etype *data,                          \
                                       size_t dlen) {                         \
        _dname##_assign_no_check(&slice->data, &slice->len, data, dlen);      \
    }                                                                         \
                                                                              \
    _api int _sname##_assign(_stype *slice, _etype *data, size_t dlen) {      \
        return _dname##_assign(&slice->data, &slice->len, data, dlen);        \
    }                                                                         \
                                                                              \
    _api void _sname##_seek_no_check(_stype *slice,                           \
                                     const _etype *data,                      \
                                     size_t dlen) {                           \
        _dname##_seek_no_check(&slice->data, slice->len, data, dlen);         \
    }                                                                         \
                                                                              \
    _api int _sname##_seek(_stype *slice, const _etype *data, size_t dlen) {  \
        return _dname##_seek(&slice->data, slice->len, data, dlen);           \
    }

#define CBASE_SLICE_IMPL(_api, _dname, _sname, _stype, _etype)                \
    CBASE_SLICE_IMPL_DEPS(_api, _dname, _sname, _stype, _etype)               \
    CBASE_SLICE_IMPL_NO_DEPS(_api, _dname, _sname, _stype, _etype)

#endif

/* vi: set et ts=4 sw=4: */
