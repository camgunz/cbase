#pragma once

#ifndef _CBASE_MUTATE_DATA_H__
#define _CBASE_MUTATE_DATA_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/base_data.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define _CBASE_TRY_EXPAND_DATA_IF_NEEDED_NO_ZERO(_dname,                      \
                                                 _data,                       \
                                                 _dcap,                       \
                                                 _excap)                      \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(                                                \
            cbase_safe_add((*(_dcap)), (_excap), &_slot_count));              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check((_data),                \
                                                      (_dcap),                \
                                                      _slot_count));          \
    } while (0)

#define _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, _data, _dcap, _excap)        \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(                                                \
            cbase_safe_add((*(_dcap)), (_excap), &_slot_count));              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check((_data),                \
                                                      (_dcap),                \
                                                      _slot_count));          \
    } while (0)

#define CBASE_MUTABLE_DATA_IMPL_DECL(_api, _dname, _dtype)                    \
    _api _dtype *_dname##_mutable_index_no_check(_dtype *data, size_t index); \
                                                                              \
    _api int _dname##_mutable_index(_dtype *data,                             \
                                    size_t dlen,                              \
                                    size_t index,                             \
                                    _dtype **element);                        \
                                                                              \
    _api void _dname##_zero_no_check(_dtype *data,                            \
                                     size_t index,                            \
                                     size_t count);                           \
                                                                              \
    _api int _dname##_zero(_dtype *data,                                      \
                           size_t dlen,                                       \
                           size_t index,                                      \
                           size_t count);                                     \
                                                                              \
    _api void _dname##_set_no_check(_dtype *data,                             \
                                    size_t index,                             \
                                    const _dtype *data2,                      \
                                    size_t count);                            \
                                                                              \
    _api int _dname##_set(_dtype *data,                                       \
                          size_t dlen,                                        \
                          size_t index,                                       \
                          const _dtype *data2,                                \
                          size_t count);                                      \
                                                                              \
    _api void _dname##_clear_no_check(_dtype *data, size_t *dlen);            \
                                                                              \
    _api int _dname##_clear(_dtype *data, size_t *dlen);

#define CBASE_MUTABLE_DATA_IMPL(_api, _dname, _dtype)                         \
    _api _dtype *_dname##_mutable_index_no_check(_dtype *data,                \
                                                 size_t index) {              \
        return data + index;                                                  \
    }                                                                         \
                                                                              \
    _api int _dname##_mutable_index(_dtype *data,                             \
                                    size_t dlen,                              \
                                    size_t index,                             \
                                    _dtype **element) {                       \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_OUTPUT_ARGUMENT(element);                                 \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
                                                                              \
        *element = _dname##_mutable_index_no_check(data, index);              \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_zero_no_check(_dtype *data,                            \
                                     size_t index,                            \
                                     size_t count) {                          \
        zero_buf_no_check(_dname##_mutable_index_no_check(data, index),       \
                          count * sizeof(_dtype));                            \
    }                                                                         \
                                                                              \
    _api int _dname##_zero(_dtype *data,                                      \
                           size_t dlen,                                       \
                           size_t index,                                      \
                           size_t count) {                                    \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
        CBASE_CHECK_INDEXED_LENGTH_BOUNDS(dlen, index, count);                \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            zero_buf(_dname##_mutable_index_no_check(data, index),            \
                     count,                                                   \
                     sizeof(_dtype)));                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_set_no_check(_dtype *data,                             \
                                    size_t index,                             \
                                    const _dtype *data2,                      \
                                    size_t count) {                           \
        cbbase_memmove(_dname##_mutable_index_no_check(data, index),          \
                       data2,                                                 \
                       count * sizeof(_dtype));                               \
    }                                                                         \
                                                                              \
    _api int _dname##_set(_dtype *data,                                       \
                          size_t dlen,                                        \
                          size_t index,                                       \
                          const _dtype *data2,                                \
                          size_t count) {                                     \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(data2);                                    \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
        CBASE_CHECK_INDEXED_LENGTH_BOUNDS(dlen, index, count);                \
                                                                              \
        _dname##_set_no_check(data, index, data2, count);                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_clear_no_check(_dtype *data, size_t *dlen) {           \
        _dname##_truncate_no_check(data, dlen, 0);                            \
    }                                                                         \
                                                                              \
    _api int _dname##_clear(_dtype *data, size_t *dlen) {                     \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
                                                                              \
        _dname##_clear_no_check(data, dlen);                                  \
                                                                              \
        return 0;                                                             \
    }

#endif

/* vi: set et ts=4 sw=4: */
