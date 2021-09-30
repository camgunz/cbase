#pragma once

#ifndef _CBASE_DATA_STATIC_MANAGEMENT_H__
#define _CBASE_DATA_STATIC_MANAGEMENT_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/data_base.h"
#include "cbase/data_ownership_management.h"
#include "cbase/errors.h"

#define CBASE_DATA_STATIC_MANAGEMENT_IMPL_DECL(_api,                          \
                                               _dname,                        \
                                               _dtype,                        \
                                               _dmaxcap)                      \
    _api int _dname##_ensure_capacity_no_zero_no_check(_dtype **data,         \
                                                       size_t *dcap,          \
                                                       size_t cap);           \
                                                                              \
    _api int _dname##_ensure_capacity_no_check(_dtype **data,                 \
                                               size_t *dcap,                  \
                                               size_t cap);                   \
                                                                              \
    _api int _dname##_set_capacity_no_zero_no_check(_dtype **data,            \
                                                    size_t *dcap,             \
                                                    size_t cap);              \
                                                                              \
    _api int _dname##_set_capacity_no_zero(_dtype **data,                     \
                                           size_t *dcap,                      \
                                           size_t cap);                       \
                                                                              \
    _api int _dname##_set_capacity_no_check(_dtype **data,                    \
                                            size_t *dcap,                     \
                                            size_t cap);                      \
                                                                              \
    _api int _dname##_set_capacity(_dtype **data, size_t *dcap, size_t cap);  \
                                                                              \
    _api void _dname##_init_no_check(size_t *dlen);                           \
                                                                              \
    _api int _dname##_init(size_t *dlen);                                     \
                                                                              \
    _api int _dname##_init_from_data_no_check(_dtype **data,                  \
                                              size_t *dlen,                   \
                                              const _dtype *data2,            \
                                              size_t dlen2);                  \
                                                                              \
    _api int _dname##_init_from_data(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     const _dtype *data2,                     \
                                     size_t dlen2);                           \
                                                                              \
    _api void _dname##_free_no_zero_no_check(_dtype *data, size_t *dlen);     \
                                                                              \
    _api int _dname##_free_no_zero(_dtype *data, size_t *dlen);               \
                                                                              \
    _api void _dname##_free_no_check(_dtype *data, size_t *dlen);             \
                                                                              \
    _api int _dname##_free(_dtype *data, size_t *dlen);                       \
                                                                              \
    _api void _dname##_destroy_no_zero_no_check(_dtype **data, size_t *dlen); \
                                                                              \
    _api int _dname##_destroy_no_zero(_dtype **data, size_t *dlen);           \
                                                                              \
    _api void _dname##_destroy_no_check(_dtype **data, size_t *dlen);         \
                                                                              \
    _api int _dname##_destroy(_dtype **data, size_t *dlen;

#define CBASE_DATA_STATIC_MANAGEMENT_IMPL(_api, _dname, _dtype, _dmaxcap)     \
    _api int _dname##_ensure_capacity_no_zero_no_check(_dtype **data,         \
                                                       size_t *dcap,          \
                                                       size_t cap) {          \
        CBASE_ERROR_IF((cap > _dmaxcap), CBASE_ERROR_OUT_OF_BOUNDS);          \
                                                                              \
        (void)data;                                                           \
                                                                              \
        (*dcap) = cap;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_ensure_capacity_no_check(_dtype **data,                 \
                                               size_t *dcap,                  \
                                               size_t cap) {                  \
        CBASE_ERROR_IF((cap > _dmaxcap), CBASE_ERROR_OUT_OF_BOUNDS);          \
                                                                              \
        (void)data;                                                           \
                                                                              \
        _dname##_zero_no_check((*data), (*dcap), cap - (*dcap));              \
                                                                              \
        (*dcap) = cap;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_init_no_check(size_t *dlen) {                          \
        (*dlen) = 0;                                                          \
    }                                                                         \
                                                                              \
    _api int _dname##_init(size_t *dlen) {                                    \
        CBASE_CHECK_INPUT_ARGUMENT(dlen);                                     \
                                                                              \
        _dname##_init_no_check(dlen);                                         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_from_data_no_check(_dtype **data,                  \
                                              size_t *dlen,                   \
                                              const _dtype *data2,            \
                                              size_t dlen2) {                 \
        _dname##_init_no_check(dlen);                                         \
                                                                              \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED_NO_ZERO(_dname, data, dlen, dlen2);  \
                                                                              \
        _dname##_set_no_check((*data), 0, data2, dlen2);                      \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_from_data(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     const _dtype *data2,                     \
                                     size_t dlen2) {                          \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(data2);                                    \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_from_data_no_check(data, dlen, data2, dlen2));      \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_free_no_zero_no_check(_dtype *data, size_t *dlen) {    \
        cbfree(data);                                                         \
        _dname##_init_no_check(dlen);                                         \
    }                                                                         \
                                                                              \
    _api int _dname##_free_no_zero(_dtype *data, size_t *dlen) {              \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
                                                                              \
        _dname##_free_no_zero_no_check(data, dlen);                           \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_free_no_check(_dtype *data, size_t *dlen) {            \
        _dname##_zero_no_check(data, 0, (*dlen));                             \
        _dname##_free_no_zero_no_check(data, dlen);                           \
    }                                                                         \
                                                                              \
    _api int _dname##_free(_dtype *data, size_t *dlen) {                      \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
                                                                              \
        _dname##_free_no_check(data, dlen);                                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_destroy_no_zero_no_check(_dtype **data,                \
                                                size_t *dlen) {               \
        _dname##_free((*data), dlen);                                         \
        *data = NULL;                                                         \
    }                                                                         \
                                                                              \
    _api int _dname##_destroy_no_zero(_dtype **data, size_t *dlen) {          \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
                                                                              \
        _dname##_destroy_no_zero_no_check(data, dlen);                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_destroy_no_check(_dtype **data, size_t *dlen) {        \
        _dname##_zero_no_check(*data, 0, (*dlen));                            \
        _dname##_destroy_no_zero(data, dlen);                                 \
    }                                                                         \
                                                                              \
    _api int _dname##_destroy(_dtype **data, size_t *dlen) {                  \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
                                                                              \
        _dname##_destroy_no_check(data, dlen);                                \
                                                                              \
        return 0;                                                             \
    }

#endif

/* vi: set et ts=4 sw=4: */
