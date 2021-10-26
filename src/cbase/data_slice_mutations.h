#pragma once

#ifndef _CBASE_DATA_SLICE_MUTATIONS_H__
#define _CBASE_DATA_SLICE_MUTATIONS_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/data_base.h"
#include "cbase/errors.h"
#include "cbase/util.h"

/*
 * [TODO]
 * - truncate_at (uses find_*_reverse)
 */

#define CBASE_DATA_SLICE_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)            \
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
    _api void _dname##_truncate_no_zero_no_check(_dtype *data,                \
                                                 size_t *dlen,                \
                                                 size_t new_length);          \
                                                                              \
    _api int _dname##_truncate_no_zero(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t new_length);                    \
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
                                        _dtype *element);                     \
                                                                              \
    _api void _dname##_clear_no_zero_no_check(size_t *dlen);                  \
                                                                              \
    _api int _dname##_clear_no_zero(size_t *dlen);                            \
                                                                              \
    _api void _dname##_clear_no_check(_dtype *data, size_t *dlen);            \
                                                                              \
    _api int _dname##_clear(_dtype *data, size_t *dlen);

#define CBASE_DATA_SLICE_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)            \
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
        CBASE_DELEGATE(_dname##_find((*data), dlen, 0, data2, dlen2, data));  \
    }                                                                         \
                                                                              \
    _api void _dname##_truncate_no_zero_no_check(size_t *dlen,                \
                                                 size_t new_length) {         \
        (*dlen) = new_length;                                                 \
    }                                                                         \
                                                                              \
    _api int _dname##_truncate_no_zero(size_t *dlen, size_t new_length) {     \
        CBASE_CHECK_INPUT_ARGUMENT(dlen);                                     \
        CBASE_CHECK_LENGTH_BOUNDS(*dlen, new_length);                         \
                                                                              \
        _dname##_truncate_no_zero_no_check(dlen, new_length);                 \
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
    }                                                                         \
                                                                              \
    _api void _dname##_clear_no_zero_no_check(size_t *dlen) {                 \
        _dname##_truncate_no_zero_no_check(dlen, 0);                          \
    }                                                                         \
                                                                              \
    _api int _dname##_clear_no_zero(size_t *dlen) {                           \
        CBASE_CHECK_INPUT_ARGUMENT(dlen);                                     \
                                                                              \
        _dname##_clear_no_zero_no_check(dlen);                                \
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
