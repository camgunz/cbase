#pragma once

#ifndef _CBASE_DATA_SLICE_H__
#define _CBASE_DATA_SLICE_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/common_data.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_DATA_SLICE_IMPL_DECL(_api, _dname, _dtype)                  \
    CBASE_COMMON_DATA_IMPL_DECL(_api, _dname, _dtype)                         \
    _api void _dname##_assign_no_check(_dtype **data,                         \
                                       size_t *dlen,                          \
                                       _dtype *data2,                         \
                                       size_t dlen2);                         \
                                                                              \
    _api int _dname##_assign(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             _dtype *data2,                                   \
                             size_t dlen2);                                   \
                                                                              \
    _api void _dname##_skip_no_check(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t count);                           \
                                                                              \
    _api int _dname##_skip(_dtype **data, size_t *dlen, size_t count);        \
                                                                              \
    _api void _dname##_seek_no_check(_dtype **data,                           \
                                     size_t dlen,                             \
                                     const _dtype *data2,                     \
                                     size_t dlen2);                           \
                                                                              \
    _api int _dname##_seek(_dtype **data,                                     \
                           size_t dlen,                                       \
                           const _dtype *data2,                               \
                           size_t dlen2);                                     \
                                                                              \
    _api void _dname##_pop_left_no_zero_no_check(_dtype **data,               \
                                                 size_t *dlen,                \
                                                 _dtype *element);            \
                                                                              \
    _api int _dname##_pop_left_no_zero(_dtype **data,                         \
                                       size_t *dlen,                          \
                                       _dtype *element);                      \
                                                                              \
    _api void _dname##_pop_right_no_zero_no_check(_dtype *data,               \
                                                  size_t *dlen,               \
                                                  _dtype *element);           \
                                                                              \
    _api int _dname##_pop_right_no_zero(_dtype *data,                         \
                                        size_t *dlen,                         \
                                        _dtype *element);

#define CBASE_DATA_SLICE_IMPL_DEPS(_api, _dname, _dtype)                  \
    CBASE_COMMON_DATA_IMPL(_api, _dname, _dtype)

#define CBASE_DATA_SLICE_IMPL_NO_DEPS(_api, _dname, _dtype)               \
    CBASE_COMMON_DATA_IMPL(_api, _dname, _dtype)                              \
    _api void _dname##_assign_no_check(_dtype **data,                         \
                                       size_t *dlen,                          \
                                       _dtype *data2,                         \
                                       size_t dlen2) {                        \
        (*data) = data2;                                                      \
        (*dlen) = dlen2;                                                      \
    }                                                                         \
                                                                              \
    _api int _dname##_assign(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             _dtype *data2,                                   \
                             size_t dlen2) {                                  \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
                                                                              \
        _dname##_assign_no_check(data, dlen, data2, dlen2);                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_skip_no_check(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t count) {                          \
        (*data) += count;                                                     \
        (*dlen) -= count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_skip(_dtype **data, size_t *dlen, size_t count) {       \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_LENGTH_BOUNDS(*dlen, count);                              \
                                                                              \
        (*data) += count;                                                     \
        (*dlen) -= count;                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_seek_no_check(_dtype **data,                           \
                                     size_t dlen,                             \
                                     const _dtype *data2,                     \
                                     size_t dlen2) {                          \
        _dname##_find_no_check((*data), dlen, 0, data2, dlen2, data);         \
    }                                                                         \
                                                                              \
    _api int _dname##_seek(_dtype **data,                                     \
                           size_t dlen,                                       \
                           const _dtype *data2,                               \
                           size_t dlen2) {                                    \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_find((*data), dlen, 0, data2, dlen2, data));             \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_left_no_zero_no_check(_dtype **data,               \
                                                 size_t *dlen,                \
                                                 _dtype *element) {           \
        _dname##_copy_no_check((*data), 0, 1, element);                       \
        _dname##_skip_no_check(data, dlen, 1);                                \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_left_no_zero(_dtype **data,                         \
                                       size_t *dlen,                          \
                                       _dtype *element) {                     \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_OUTPUT_ARGUMENT(element);                                 \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, 0);                                   \
                                                                              \
        _dname##_pop_left_no_zero_no_check(data, dlen, element);              \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_right_no_zero_no_check(_dtype *data,               \
                                                  size_t *dlen,               \
                                                  _dtype *element) {          \
        _dname##_copy_no_check(data, (*dlen) - 1, 1, element);                \
        _dname##_truncate_no_zero_no_check(dlen, (*dlen) - 1);                \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_right_no_zero(_dtype *data,                         \
                                        size_t *dlen,                         \
                                        _dtype *element) {                    \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_OUTPUT_ARGUMENT(element);                                 \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, 0);                                   \
                                                                              \
        _dname##_pop_right_no_zero_no_check(data, dlen, element);             \
                                                                              \
        return 0;                                                             \
    }

#define CBASE_DATA_SLICE_IMPL(_api, _dname, _dtype)                       \
    CBASE_DATA_SLICE_IMPL_DEPS(_api, _dname, _dtype)                      \
    CBASE_DATA_SLICE_IMPL_NO_DEPS(_api, _dname, _dtype)

#endif

/* vi: set et ts=4 sw=4: */
