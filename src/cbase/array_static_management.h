#pragma once

#ifndef _CBASE_ARRAY_STATIC_MANAGEMENT_H__
#define _CBASE_ARRAY_STATIC_MANAGEMENT_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/data_base.h"
#include "cbase/data_ownership_management.h"
#include "cbase/errors.h"

#define CBASE_ARRAY_STATIC_MANAGEMENT_IMPL_DECL(_api,                         \
                                                _dname,                       \
                                                _etype,                       \
                                                _dmaxcap,                     \
                                                _aname,                       \
                                                _atype)                       \
    _api int _aname##_ensure_capacity_no_zero_no_check(_atype *array,         \
                                                       size_t cap);           \
                                                                              \
    _api int _aname##_ensure_capacity_no_check(_atype *array, size_t cap);    \
                                                                              \
    _api int _aname##_set_capacity_no_zero_no_check(_atype *array,            \
                                                    size_t cap);              \
                                                                              \
    _api int _aname##_set_capacity_no_zero(_atype *array, size_t cap);        \
                                                                              \
    _api int _aname##_set_capacity_no_check(_atype *array, size_t cap);       \
                                                                              \
    _api int _aname##_set_capacity(_atype *array, size_t cap);                \
                                                                              \
    _api void _aname##_init_no_check(_atype *array);                          \
                                                                              \
    _api int _aname##_init(_atype *array);                                    \
                                                                              \
    _api int _aname##_init_from_array_no_check(_atype *array,                 \
                                               const _atype *array2);         \
                                                                              \
    _api int _aname##_init_from_array(_atype *array,                          \
                                      size_t *dlen,                           \
                                      const _atype *array2);                  \
                                                                              \
    _api void _aname##_free_no_zero_no_check(_atype *array);                  \
                                                                              \
    _api int _aname##_free_no_zero(_atype *array);                            \
                                                                              \
    _api void _aname##_free_no_check(_atype *array);                          \
                                                                              \
    _api int _aname##_free(_atype *array);                                    \
                                                                              \
    _api void _aname##_destroy_no_zero_no_check(_atype *array);               \
                                                                              \
    _api int _aname##_destroy_no_zero(_atype *array);                         \
                                                                              \
    _api void _aname##_destroy_no_check(_atype *array);                       \
                                                                              \
    _api int _aname##_destroy(_atype *array);

#define CBASE_ARRAY_STATIC_MANAGEMENT_IMPL(_api,                              \
                                           _dname,                            \
                                           _etype,                            \
                                           _dmaxcap,                          \
                                           _aname,                            \
                                           _atype)

#endif

/* vi: set et ts=4 sw=4: */
