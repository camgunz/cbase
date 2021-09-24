#pragma once

#ifndef _CBASE_DYNAMIC_DATA_H__
#define _CBASE_DYNAMIC_DATA_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/mutable_data.h"
#include "cbase/errors.h"

/* [TODO] Look at aligned allocation */

#define _CBASE_DYNAMIC_DATA_CHECK_MUTABLE_INPUT_ARGS(_inobj,                  \
                                                     _inarg1,                 \
                                                     _inarg2)                 \
    _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(_inobj, _inarg1);                    \
    CBASE_CHECK_INPUT_ARGUMENT(_inarg2)

#define _CBASE_DYNAMIC_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(_inobj,            \
                                                           _inarg1,           \
                                                           _inarg2)           \
    _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(_inobj, _inarg1);              \
    CBASE_CHECK_INPUT_ARGUMENT(_inarg2)

#define CBASE_DYNAMIC_DATA_IMPL_DECL(_api, _dname, _dtype)                    \
    CBASE_MUTABLE_DATA_IMPL_DECL(_api, _dname, _dtype)                        \
    _api void _dname##_init_no_check(size_t *dlen, size_t *dcap);             \
                                                                              \
    _api int _dname##_init(size_t *dlen, size_t *dcap);                       \
                                                                              \
    _api int _dname##_init_capacity_no_check(_dtype **data,                   \
                                             size_t *dlen,                    \
                                             size_t *dcap,                    \
                                             size_t cap);                     \
                                                                              \
    _api int _dname##_init_capacity(_dtype **data,                            \
                                    size_t *dlen,                             \
                                    size_t *dcap,                             \
                                    size_t cap);                              \
                                                                              \
    _api int _dname##_init_from_data_no_check(_dtype **data,                  \
                                              size_t *dlen,                   \
                                              size_t *dcap,                   \
                                              const _dtype *data2,            \
                                              size_t len2);                   \
                                                                              \
    _api void _dname##_free_no_zero_no_check(_dtype *data,                    \
                                             size_t *dlen,                    \
                                             size_t *dcap);                   \
                                                                              \
    _api int _dname##_free_no_zero(_dtype *data, size_t *dlen, size_t *dcap); \
                                                                              \
    _api void _dname##_free_no_check(_dtype *data,                            \
                                     size_t *dlen,                            \
                                     size_t *dcap);                           \
                                                                              \
    _api int _dname##_free(_dtype *data, size_t *dlen, size_t *dcap);         \
                                                                              \
    _api void _dname##_destroy_no_zero_no_check(_dtype **data,                \
                                                size_t *dlen,                 \
                                                size_t *dcap);                \
                                                                              \
    _api int _dname##_destroy_no_zero(_dtype **data,                          \
                                      size_t *dlen,                           \
                                      size_t *dcap);                          \
                                                                              \
    _api void _dname##_destroy_no_check(_dtype **data,                        \
                                        size_t *dlen,                         \
                                        size_t *dcap);                        \
                                                                              \
    _api int _dname##_destroy(_dtype **data, size_t *dlen, size_t *dcap);

#define CBASE_DYNAMIC_DATA_IMPL(_api, _dname, _dtype)                         \
    CBASE_MUTABLE_DATA_IMPL(_api, _dname, _dtype)                             \
    _api int _dname##_ensure_capacity_no_zero_no_check(_dtype **data,         \
                                                       size_t *dcap,          \
                                                       size_t cap) {          \
        if ((*dcap) < cap) {                                                  \
            if (!(*data)) {                                                   \
                CBASE_PROPAGATE_ERROR(cbmalloc(cap, sizeof(_dtype), data));   \
            }                                                                 \
            else {                                                            \
                CBASE_PROPAGATE_ERROR(cbrealloc(cap, sizeof(_dtype), data));  \
            }                                                                 \
                                                                              \
            (*dcap) = cap;                                                    \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_ensure_capacity_no_check(_dtype **data,                 \
                                               size_t *dcap,                  \
                                               size_t cap) {                  \
        if ((*dcap) < cap) {                                                  \
            if (!(*data)) {                                                   \
                CBASE_PROPAGATE_ERROR(cbcalloc(cap, sizeof(_dtype), data));   \
            }                                                                 \
            else {                                                            \
                CBASE_PROPAGATE_ERROR(cbrealloc(cap, sizeof(_dtype), data));  \
                _dname##_zero_no_check((*data), (*dcap), cap - (*dcap));      \
            }                                                                 \
                                                                              \
            (*dcap) = cap;                                                    \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_init_no_check(size_t *dlen, size_t *dcap) {            \
        (*dlen) = 0;                                                          \
        (*dcap) = 0;                                                          \
    }                                                                         \
                                                                              \
    _api int _dname##_init(size_t *dlen, size_t *dcap) {                      \
        CBASE_CHECK_INPUT_ARGUMENT(dlen);                                     \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
        CBASE_CHECK_LENGTH_BOUNDS((*dcap), (*dlen));                          \
                                                                              \
        _dname##_init_no_check(dlen, dcap);                                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_capacity_no_check(_dtype **data,                   \
                                             size_t *dlen,                    \
                                             size_t *dcap,                    \
                                             size_t cap) {                    \
        _dname##_init_no_check(dlen, dcap);                                   \
                                                                              \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dcap, cap);            \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_capacity(_dtype **data,                            \
                                    size_t *dlen,                             \
                                    size_t *dcap,                             \
                                    size_t cap) {                             \
        _CBASE_DYNAMIC_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen, dcap);       \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_capacity_no_check(data, dlen, dcap, cap));          \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_from_data_no_check(_dtype **data,                  \
                                              size_t *dlen,                   \
                                              size_t *dcap,                   \
                                              const _dtype *data2,            \
                                              size_t len2) {                  \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_capacity_no_check(data, dlen, dcap, len2));         \
                                                                              \
        _dname##_set_no_check((*data), 0, data2, len2);                       \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_from_data(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t *dcap,                            \
                                     const _dtype *data2,                     \
                                     size_t len2) {                           \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_capacity(data, dlen, dcap, len2));                  \
                                                                              \
        _dname##_set_no_check((*data), 0, data2, len2);                       \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_free_no_zero_no_check(_dtype *data,                    \
                                             size_t *dlen,                    \
                                             size_t *dcap) {                  \
        cbfree(data);                                                         \
        _dname##_init_no_check(dlen, dcap);                                   \
    }                                                                         \
                                                                              \
    _api int _dname##_free_no_zero(_dtype *data,                              \
                                   size_t *dlen,                              \
                                   size_t *dcap) {                            \
        _CBASE_DYNAMIC_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen, dcap);       \
                                                                              \
        _dname##_free_no_zero_no_check(data, dlen, dcap);                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_free_no_check(_dtype *data,                            \
                                     size_t *dlen,                            \
                                     size_t *dcap) {                          \
        _dname##_zero_no_check(data, 0, (*dlen));                             \
        _dname##_free_no_zero(data, dlen, dcap);                              \
    }                                                                         \
                                                                              \
    _api int _dname##_free(_dtype *data, size_t *dlen, size_t *dcap) {        \
        _CBASE_DYNAMIC_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen, dcap);       \
                                                                              \
        _dname##_free_no_check(data, dlen, dcap);                             \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_destroy_no_zero_no_check(_dtype **data,                \
                                                size_t *dlen,                 \
                                                size_t *dcap) {               \
        _dname##_free((*data), dlen, dcap);                                   \
        *data = NULL;                                                         \
    }                                                                         \
                                                                              \
    _api int _dname##_destroy_no_zero(_dtype **data,                          \
                                      size_t *dlen,                           \
                                      size_t *dcap) {                         \
        _CBASE_DYNAMIC_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen, dcap); \
                                                                              \
        _dname##_destroy_no_zero_no_check(data, dlen, dcap);                  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_destroy_no_check(_dtype **data,                        \
                                        size_t *dlen,                         \
                                        size_t *dcap) {                       \
        _dname##_zero_no_check(*data, 0, (*dlen));                            \
        _dname##_destroy_no_zero(data, dlen, dcap);                           \
    }                                                                         \
                                                                              \
    _api int _dname##_destroy(_dtype **data, size_t *dlen, size_t *dcap) {    \
        _CBASE_DYNAMIC_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen, dcap);       \
                                                                              \
        _dname##_destroy_no_check(data, dlen, dcap);                          \
                                                                              \
        return 0;                                                             \
    }

#endif

/* vi: set et ts=4 sw=4: */
