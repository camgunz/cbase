#pragma once

#ifndef _CBASE_MUTABLE_DATA_H__
#define _CBASE_MUTABLE_DATA_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/common_data.h"
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
    CBASE_COMMON_DATA_IMPL_DECL(_api, _dname, _dtype)                         \
                                                                              \
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
    _api int _dname##_ensure_capacity_no_zero_no_check(_dtype **data,         \
                                                       size_t *dcap,          \
                                                       size_t cap);           \
                                                                              \
    _api int _dname##_ensure_capacity_no_zero(_dtype **data,                  \
                                              size_t *dcap,                   \
                                              size_t cap);                    \
                                                                              \
    _api int _dname##_ensure_capacity_no_check(_dtype **data,                 \
                                               size_t *dcap,                  \
                                               size_t cap);                   \
                                                                              \
    _api int _dname##_ensure_capacity(_dtype **data,                          \
                                      size_t *dcap,                           \
                                      size_t cap);                            \
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
    _api void _dname##_truncate_no_check(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         size_t new_length);                  \
                                                                              \
    _api int _dname##_truncate(_dtype *data,                                  \
                               size_t *dlen,                                  \
                               size_t new_length);                            \
                                                                              \
    _api void _dname##_compact_no_check(size_t dlen, size_t *dcap);           \
                                                                              \
    _api int _dname##_compact(size_t dlen, size_t *dcap);                     \
                                                                              \
    _api void _dname##_move_right_no_zero_no_check(_dtype *data,              \
                                                   size_t *dlen,              \
                                                   size_t index,              \
                                                   size_t count);             \
                                                                              \
    _api int _dname##_move_right_no_zero(_dtype **data,                       \
                                         size_t *dlen,                        \
                                         size_t index,                        \
                                         size_t count);                       \
                                                                              \
    _api void _dname##_move_right_no_check(_dtype *data,                      \
                                           size_t *dlen,                      \
                                           size_t index,                      \
                                           size_t count);                     \
                                                                              \
    _api int _dname##_move_right(_dtype **data,                               \
                                 size_t *dlen,                                \
                                 size_t index,                                \
                                 size_t count);                               \
                                                                              \
    _api void _dname##_move_left_no_zero_no_check(_dtype *data,               \
                                                  size_t *dlen,               \
                                                  size_t index,               \
                                                  size_t count);              \
                                                                              \
    _api int _dname##_move_left_no_zero(_dtype *data,                         \
                                        size_t *dlen,                         \
                                        size_t index,                         \
                                        size_t count);                        \
                                                                              \
    _api void _dname##_move_left_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          size_t index,                       \
                                          size_t count);                      \
                                                                              \
    _api int _dname##_move_left(_dtype *data,                                 \
                                size_t *dlen,                                 \
                                size_t index,                                 \
                                size_t count);                                \
                                                                              \
    _api _dtype *_dname##_insert_slot_no_zero_no_check(_dtype *data,          \
                                                       size_t *dlen,          \
                                                       size_t index);         \
                                                                              \
    _api int _dname##_insert_slot_no_zero(_dtype **data,                      \
                                          size_t *dlen,                       \
                                          size_t index,                       \
                                          _dtype const **new_slot);           \
                                                                              \
    _api _dtype *_dname##_insert_slot_no_check(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index);                 \
                                                                              \
    _api int _dname##_insert_slot(_dtype **data,                              \
                                  size_t *dlen,                               \
                                  size_t index,                               \
                                  _dtype const **new_slot);                   \
                                                                              \
    _api void _dname##_insert_no_check(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       const _dtype *data2,                   \
                                       size_t count);                         \
                                                                              \
    _api int _dname##_insert(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             size_t index,                                    \
                             const _dtype *data2,                             \
                             size_t count);                                   \
                                                                              \
    _api _dtype *_dname##_prepend_slot_no_zero_check(_dtype *data, size_t *dlen);  \
                                                                              \
    _api int _dname##_prepend_slot_no_zero(_dtype **data,                     \
                                           size_t *dlen,                      \
                                           _dtype const **new_slot);          \
                                                                              \
    _api _dtype *_dname##_prepend_slot_no_check(_dtype *data, size_t *dlen);  \
                                                                              \
    _api void _dname##_prepend_no_check(_dtype *data,                         \
                                        size_t *dlen,                         \
                                        const _dtype *data2,                  \
                                        size_t count);                        \
                                                                              \
    _api int _dname##_prepend(_dtype **data,                                  \
                              size_t *dlen,                                   \
                              const _dtype *data2,                            \
                              size_t count);                                  \
                                                                              \
    _api _dtype *_dname##_append_slot_no_zero_no_check(_dtype *data,          \
                                                       size_t *dlen);         \
                                                                              \
    _api int _dname##_append_slot_no_zero(_dtype **data,                      \
                                          size_t *dlen,                       \
                                          _dtype const **new_slot);           \
                                                                              \
    _api _dtype *_dname##_append_slot_no_check(_dtype *data, size_t *dlen);   \
                                                                              \
    _api int _dname##_append_slot(_dtype **data,                              \
                                  size_t *dlen,                               \
                                  _dtype const **new_slot);                   \
                                                                              \
    _api void _dname##_append_no_check(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       const _dtype *data2,                   \
                                       size_t count);                         \
                                                                              \
    _api int _dname##_append(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             const _dtype *data2,                             \
                             size_t count);                                   \
                                                                              \
    _api void _dname##_delete_no_zero_no_check(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index,                  \
                                               size_t count);                 \
                                                                              \
    _api int _dname##_delete_no_zero(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t index,                            \
                                     size_t count);                           \
                                                                              \
    _api void _dname##_delete_no_check(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       size_t count);                         \
                                                                              \
    _api int _dname##_delete(_dtype *data,                                    \
                             size_t *dlen,                                    \
                             size_t index,                                    \
                             size_t count);                                   \
                                                                              \
    _api void _dname##_delete_until_no_zero_no_check(_dtype *data,            \
                                                     size_t *dlen,            \
                                                     size_t index,            \
                                                     const _dtype *data2,     \
                                                     size_t dlen2);           \
                                                                              \
    _api int _dname##_delete_until_no_zero(_dtype *data,                      \
                                           size_t *dlen,                      \
                                           size_t index,                      \
                                           const _dtype *data2,               \
                                           size_t dlen2);                     \
                                                                              \
    _api void _dname##_delete_until_no_check(_dtype *data,                    \
                                             size_t *dlen,                    \
                                             size_t index,                    \
                                             const _dtype *data2,             \
                                             size_t dlen2);                   \
                                                                              \
    _api int _dname##_delete_until(_dtype *data,                              \
                                   size_t *dlen,                              \
                                   size_t index,                              \
                                   const _dtype *data2,                       \
                                   size_t dlen2);                             \
                                                                              \
    _api void _dname##_delete_unordered_no_zero_no_check(_dtype *data,        \
                                                         size_t *dlen,        \
                                                         size_t index,        \
                                                         size_t count);       \
                                                                              \
    _api int _dname##_delete_unordered_no_zero(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index,                  \
                                               size_t count);                 \
                                                                              \
    _api void _dname##_delete_unordered_no_check(_dtype *data,                \
                                                 size_t *dlen,                \
                                                 size_t index,                \
                                                 size_t count);               \
                                                                              \
    _api int _dname##_delete_unordered(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       size_t count);                         \
                                                                              \
    _api int _dname##_replace_no_zero(_dtype **data,                          \
                                      size_t *dlen,                           \
                                      size_t index,                           \
                                      const _dtype *old_data,                 \
                                      size_t old_len,                         \
                                      const _dtype *new_data,                 \
                                      size_t new_len);                        \
                                                                              \
    _api int _dname##_replace(_dtype **data,                                  \
                              size_t *dlen,                                   \
                              size_t index,                                   \
                              const _dtype *old_data,                         \
                              size_t old_len,                                 \
                              const _dtype *new_data,                         \
                              size_t new_len);                                \
                                                                              \
    _api void _dname##_pop_no_zero_no_check(_dtype *data,                     \
                                            size_t *dlen,                     \
                                            size_t index,                     \
                                            _dtype *element);                 \
                                                                              \
    _api int _dname##_pop_no_zero(_dtype *data,                               \
                                  size_t *dlen,                               \
                                  size_t index,                               \
                                  _dtype *element);                           \
                                                                              \
    _api void _dname##_pop_no_check(_dtype *data,                             \
                                    size_t *dlen,                             \
                                    size_t index,                             \
                                    _dtype *element);                         \
                                                                              \
    _api int _dname##_pop(_dtype *data,                                       \
                          size_t *dlen,                                       \
                          size_t index,                                       \
                          _dtype *element);                                   \
                                                                              \
    _api void _dname##_pop_unordered_no_zero_no_check(_dtype *data,           \
                                                      size_t *dlen,           \
                                                      size_t index,           \
                                                      _dtype *element);       \
                                                                              \
    _api int _dname##_pop_unordered_no_zero(_dtype *data,                     \
                                            size_t *dlen,                     \
                                            size_t index,                     \
                                            _dtype *element);                 \
                                                                              \
    _api void _dname##_pop_unordered_no_check(_dtype *data,                   \
                                              size_t *dlen,                   \
                                              size_t index,                   \
                                              _dtype *element);               \
                                                                              \
    _api int _dname##_pop_unordered(_dtype *data,                             \
                                    size_t *dlen,                             \
                                    size_t index,                             \
                                    _dtype *element);                         \
                                                                              \
    _api void _dname##_pop_left_no_check(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         _dtype *element);                    \
                                                                              \
    _api int _dname##_pop_left(_dtype *data, size_t *dlen, _dtype *element);  \
                                                                              \
    _api void _dname##_pop_left_unordered_no_check(_dtype *data,              \
                                                   size_t *dlen,              \
                                                   _dtype *element);          \
                                                                              \
    _api int _dname##_pop_left_unordered(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         _dtype *element);                    \
                                                                              \
    _api void _dname##_pop_right_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          _dtype *element);                   \
                                                                              \
    _api int _dname##_pop_right(_dtype *data, size_t *dlen, _dtype *element); \
                                                                              \
    _api void _dname##_clear_no_check(_dtype *data, size_t *dlen);            \
                                                                              \
    _api int _dname##_clear(_dtype *data, size_t *dlen);

#define CBASE_MUTABLE_DATA_IMPL_DEPS(_api, _dname, _dtype)                    \
    CBASE_DATA_SLICE_IMPL_DEPS(_api, _dname, _dtype) \
    CBASE_DATA_SLICE_IMPL_NO_DEPS(_api, _dname, _dtype)

#define CBASE_MUTABLE_DATA_IMPL_NO_DEPS(_api, _dname, _dtype)                 \
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
    _api int _dname##_ensure_capacity_no_zero(_dtype **data,                  \
                                              size_t *dcap,                   \
                                              size_t cap) {                   \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero(data, dcap, cap));               \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_ensure_capacity_no_check(_dtype **data,                 \
                                               size_t *dcap,                  \
                                               size_t cap);                   \
                                                                              \
    _api int _dname##_ensure_capacity(_dtype **data,                          \
                                      size_t *dcap,                           \
                                      size_t cap) {                           \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
                                                                              \
        CBASE_PROPAGATE_ERROR(_dname##_ensure_capacity(data, dcap, cap));     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity_no_zero_no_check(_dtype **data,            \
                                                    size_t *dcap,             \
                                                    size_t cap) {             \
        if (cap < (*dcap)) {                                                  \
            (*dcap) = cap;                                                    \
        }                                                                     \
        else {                                                                \
            _CBASE_TRY_EXPAND_DATA_IF_NEEDED_NO_ZERO(_dname,                  \
                                                     data,                    \
                                                     dcap,                    \
                                                     cap);                    \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity_no_zero(_dtype **data,                     \
                                           size_t *dcap,                      \
                                           size_t cap) {                      \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_set_capacity_no_zero_no_check(data, dcap, cap));         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity_no_check(_dtype **data,                    \
                                            size_t *dcap,                     \
                                            size_t cap) {                     \
        if (cap < (*dcap)) {                                                  \
            _dname##_zero_no_check((*data), (*dcap), cap - (*dcap));          \
            (*dcap) = cap;                                                    \
        }                                                                     \
        else {                                                                \
            _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dcap, cap);        \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity(_dtype **data, size_t *dcap, size_t cap) { \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_set_capacity_no_check(data, dcap, cap));                 \
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
    _api void _dname##_truncate_no_check(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         size_t new_length) {                 \
        _dname##_zero_no_check(data, new_length, (*dlen) - new_length);       \
        _dname##_truncate_no_zero_no_check(dlen, new_length);                 \
    }                                                                         \
                                                                              \
    _api int _dname##_truncate(_dtype *data,                                  \
                               size_t *dlen,                                  \
                               size_t new_length) {                           \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_LENGTH_BOUNDS(*dlen, new_length);                         \
                                                                              \
        _dname##_truncate_no_check(data, dlen, new_length);                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_compact_no_check(size_t dlen, size_t *dcap) {          \
        (*dcap) = dlen;                                                       \
    }                                                                         \
                                                                              \
    _api int _dname##_compact(size_t dlen, size_t *dcap) {                    \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
                                                                              \
        if ((*dcap) > dlen) {                                                 \
            _dname##_compact_no_check(dlen, dcap);                            \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_move_right_no_zero_no_check(_dtype *data,              \
                                                   size_t *dlen,              \
                                                   size_t index,              \
                                                   size_t count) {            \
        cbbase_memmove(_dname##_mutable_index_no_check(data, index + count),  \
                       _dname##_index_no_check(data, index),                  \
                       ((*dlen) - index) * sizeof(_dtype));                   \
                                                                              \
        (*dlen) += count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_move_right_no_zero(_dtype **data,                       \
                                         size_t *dlen,                        \
                                         size_t index,                        \
                                         size_t count) {                      \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED_NO_ZERO(_dname, data, dlen, count);  \
                                                                              \
        _dname##_move_right_no_zero_no_check((*data), dlen, index, count);    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_move_right_no_check(_dtype *data,                      \
                                           size_t *dlen,                      \
                                           size_t index,                      \
                                           size_t count) {                    \
        _dname##_move_right_no_zero_no_check(data, dlen, index, count);       \
                                                                              \
        _dname##_zero_no_check(data, index, count);                           \
    }                                                                         \
                                                                              \
    _api int _dname##_move_right(_dtype **data,                               \
                                 size_t *dlen,                                \
                                 size_t index,                                \
                                 size_t count) {                              \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dlen, count);          \
                                                                              \
        _dname##_move_right_no_check((*data), dlen, index, count);            \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_move_left_no_zero_no_check(_dtype *data,               \
                                                  size_t *dlen,               \
                                                  size_t index,               \
                                                  size_t count) {             \
        if ((index + count) < (*dlen)) {                                      \
            cbbase_memmove(_dname##_mutable_index_no_check(data,              \
                                                           index - count),    \
                           _dname##_index_no_check(data, index),              \
                           ((*dlen) - index) * sizeof(_dtype));               \
        }                                                                     \
                                                                              \
        (*dlen) -= count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_move_left_no_zero(_dtype *data,                         \
                                        size_t *dlen,                         \
                                        size_t index,                         \
                                        size_t count) {                       \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        /* [FIXME] Custom bounds check */                                     \
        CBASE_ERROR_IF(count > index, CBASE_ERROR_OUT_OF_BOUNDS);             \
        CBASE_CHECK_INDEXED_LENGTH_BOUNDS(*dlen, index, count);               \
                                                                              \
        _dname##_move_left_no_zero_no_check(data, dlen, index, count);        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_move_left_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          size_t index,                       \
                                          size_t count) {                     \
        _dname##_move_left_no_zero_no_check(data, dlen, index, count);        \
        _dname##_zero_no_check(data, (*dlen), count);                         \
    }                                                                         \
                                                                              \
    _api int _dname##_move_left(_dtype *data,                                 \
                                size_t *dlen,                                 \
                                size_t index,                                 \
                                size_t count) {                               \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        /* [FIXME] Custom bounds check */                                     \
        CBASE_ERROR_IF(count > index, CBASE_ERROR_OUT_OF_BOUNDS);             \
        CBASE_CHECK_INDEXED_LENGTH_BOUNDS(*dlen, index, count);               \
                                                                              \
        _dname##_move_left_no_check(data, dlen, index, count);                \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api _dtype *_dname##_insert_slot_no_zero_no_check(_dtype *data,          \
                                                       size_t *dlen,          \
                                                       size_t index) {        \
        _dname##_move_right_no_zero_no_check(data, dlen, index, 1);           \
        return _dname##_mutable_index_no_check(data, index);                  \
    }                                                                         \
                                                                              \
    _api int _dname##_insert_slot_no_zero(_dtype **data,                      \
                                          size_t *dlen,                       \
                                          size_t index,                       \
                                          _dtype const **new_slot) {          \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_OUTPUT_ARGUMENT(new_slot);                                \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED_NO_ZERO(_dname, data, dlen, 1);      \
                                                                              \
        *new_slot =                                                           \
            _dname##_insert_slot_no_zero_no_check((*data), dlen, index);      \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api _dtype *_dname##_insert_slot_no_check(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index) {                \
        _dname##_move_right_no_check(data, dlen, index, 1);                   \
        return _dname##_mutable_index_no_check(data, index);                  \
    }                                                                         \
                                                                              \
    _api int _dname##_insert_slot(_dtype **data,                              \
                                  size_t *dlen,                               \
                                  size_t index,                               \
                                  _dtype const **new_slot) {                  \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_OUTPUT_ARGUMENT(new_slot);                                \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dlen, 1);              \
                                                                              \
        *new_slot = _dname##_insert_slot_no_check((*data), dlen, index);      \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_insert_no_check(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       const _dtype *data2,                   \
                                       size_t count) {                        \
        _dname##_move_right_no_zero_no_check(data, dlen, index, count);       \
        _dname##_set_no_check(data, index, data2, count);                     \
    }                                                                         \
                                                                              \
    _api int _dname##_insert(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             size_t index,                                    \
                             const _dtype *data2,                             \
                             size_t count) {                                  \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_INPUT_ARGUMENT(data2);                                    \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_MEMORY_OVERLAP((*data), *dlen, data2);                    \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dlen, count);          \
                                                                              \
        _dname##_move_right_no_zero_no_check((*data), dlen, index, count);    \
        _dname##_set_no_check((*data), index, data2, count);                  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api _dtype *_dname##_prepend_slot_no_zero_no_check(                      \
        _dtype **data,                                                        \
        size_t *dlen,                                                         \
        _dtype const **new_slot) {                                            \
        return _dname##_insert_slot_no_zero_no_check(data,                    \
                                                     dlen,                    \
                                                     0,                       \
                                                     new_slot);               \
    }                                                                         \
                                                                              \
    _api int _dname##_prepend_slot_no_zero(_dtype **data,                     \
                                           size_t *dlen,                      \
                                           _dtype const **new_slot) {         \
        return _dname##_insert_slot_no_zero(data, dlen, 0, new_slot);         \
    }                                                                         \
                                                                              \
    _api _dtype *_dname##_prepend_slot_no_check(_dtype *data, size_t *dlen) { \
        return _dname##_insert_slot_no_check(data, dlen, 0);                  \
    }                                                                         \
                                                                              \
    _api int _dname##_prepend_slot(_dtype **data,                             \
                                   size_t *dlen,                              \
                                   _dtype const **new_slot) {                 \
        return _dname##_insert_slot(data, dlen, 0, new_slot);                 \
    }                                                                         \
                                                                              \
    _api void _dname##_prepend_no_check(_dtype *data,                         \
                                        size_t *dlen,                         \
                                        const _dtype *data2,                  \
                                        size_t count) {                       \
        _dname##_insert_no_check(data, dlen, 0, data2, count);                \
    }                                                                         \
                                                                              \
    _api int _dname##_prepend(_dtype **data,                                  \
                              size_t *dlen,                                   \
                              const _dtype *data2,                            \
                              size_t count) {                                 \
        return _dname##_insert(data, dlen, 0, data2, count);                  \
    }                                                                         \
                                                                              \
    _api _dtype *_dname##_append_slot_no_zero_no_check(_dtype *data,          \
                                                       size_t *dlen) {        \
        (*dlen)++;                                                            \
        return _dname##_mutable_index_no_check(data, (*dlen) - 1);            \
    }                                                                         \
                                                                              \
    _api int _dname##_append_slot_no_zero(_dtype **data,                      \
                                          size_t *dlen,                       \
                                          _dtype const **new_slot) {          \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_OUTPUT_ARGUMENT(new_slot);                                \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED_NO_ZERO(_dname, data, dlen, 1);      \
                                                                              \
        *new_slot = _dname##_index_no_check((*data), (*dlen) - 1);            \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api _dtype *_dname##_append_slot_no_check(_dtype *data, size_t *dlen) {  \
        (*dlen)++;                                                            \
        _dname##_zero_no_check(data, (*dlen) - 1, 1);                         \
        return _dname##_mutable_index_no_check(data, (*dlen) - 1);            \
    }                                                                         \
                                                                              \
    _api int _dname##_append_slot(_dtype **data,                              \
                                  size_t *dlen,                               \
                                  _dtype const **new_slot) {                  \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_OUTPUT_ARGUMENT(new_slot);                                \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dlen, 1);              \
                                                                              \
        *new_slot = _dname##_index_no_check(*data, (*dlen) - 1);              \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_append_no_check(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       const _dtype *data2,                   \
                                       size_t count) {                        \
        (*dlen) += count;                                                     \
        _dname##_set_no_check(data, (*dlen) - count, data2, count);           \
    }                                                                         \
                                                                              \
    _api int _dname##_append(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             const _dtype *data2,                             \
                             size_t count) {                                  \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_INPUT_ARGUMENT(data2);                                    \
        CBASE_CHECK_MEMORY_OVERLAP((*data), *dlen, data2);                    \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dlen, count);          \
                                                                              \
        _dname##_append_no_check((*data), dlen, data2, count);                \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_no_zero_no_check(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index,                  \
                                               size_t count) {                \
        if ((index + count) < (*dlen)) {                                      \
            cbbase_memmove(_dname##_mutable_index_no_check(data,              \
                                                           index + count),    \
                           _dname##_index_no_check(data, index),              \
                           (((*dlen) - (index + count)) * sizeof(_dtype)));   \
        }                                                                     \
                                                                              \
        (*dlen) -= count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_no_zero(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t index,                            \
                                     size_t count) {                          \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_INDEXED_LENGTH_BOUNDS(*dlen, index, count);               \
                                                                              \
        _dname##_delete_no_zero_no_check((*data), dlen, index, count);        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_no_check(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       size_t count) {                        \
        _dname##_delete_no_zero_no_check(data, dlen, index, count);           \
        _dname##_zero_no_check(data, (*dlen), count);                         \
    }                                                                         \
                                                                              \
    _api int _dname##_delete(_dtype *data,                                    \
                             size_t *dlen,                                    \
                             size_t index,                                    \
                             size_t count) {                                  \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_INDEXED_LENGTH_BOUNDS(*dlen, index, count);               \
                                                                              \
        _dname##_delete_no_check(data, dlen, index, count);                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_until_no_zero_no_check(_dtype *data,            \
                                                     size_t *dlen,            \
                                                     size_t index,            \
                                                     const _dtype *data2,     \
                                                     size_t dlen2) {          \
        _dtype *cursor = NULL;                                                \
                                                                              \
        _dname##_find_no_check(data, *dlen, index, data2, dlen2, &cursor);    \
                                                                              \
        if (cursor) {                                                         \
            _dname##_delete_no_zero_no_check(data,                            \
                                             dlen,                            \
                                             cursor - data,                   \
                                             dlen2);                          \
        }                                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_until_no_zero(_dtype *data,                      \
                                           size_t *dlen,                      \
                                           size_t index,                      \
                                           const _dtype *data2,               \
                                           size_t dlen2) {                    \
        size_t offset = 0;                                                    \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_find_index(data, *dlen, index, data2, dlen2, &offset));  \
                                                                              \
        _dname##_delete_no_zero_no_check(data, dlen, offset, dlen2);          \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_until_no_check(_dtype *data,                    \
                                             size_t *dlen,                    \
                                             size_t index,                    \
                                             const _dtype *data2,             \
                                             size_t dlen2) {                  \
        _dtype *cursor = NULL;                                                \
                                                                              \
        _dname##_find_no_check(data, *dlen, index, data2, dlen2, &cursor);    \
                                                                              \
        if (cursor) {                                                         \
            _dname##_delete_no_check(data, dlen, cursor - data, dlen2);       \
        }                                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_until(_dtype *data,                              \
                                   size_t *dlen,                              \
                                   size_t index,                              \
                                   const _dtype *data2,                       \
                                   size_t dlen2) {                            \
        size_t offset = 0;                                                    \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_find_index(data, *dlen, index, data2, dlen2, &offset));  \
                                                                              \
        _dname##_delete_no_check(data, dlen, offset, dlen2);                  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_unordered_no_zero_no_check(_dtype *data,        \
                                                         size_t *dlen,        \
                                                         size_t index,        \
                                                         size_t count) {      \
        if ((index + count) < ((*dlen) - count)) {                            \
            cbbase_memmove(_dname##_mutable_index_no_check(data, index),      \
                           _dname##_index_no_check(data,                      \
                                                   (*dlen) - (count + 1)),    \
                           count * sizeof(_dtype));                           \
        }                                                                     \
                                                                              \
        (*dlen) -= count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_unordered_no_zero(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index,                  \
                                               size_t count) {                \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_INDEXED_LENGTH_BOUNDS(*dlen, index, count);               \
                                                                              \
        _dname##_delete_unordered_no_zero_no_check(data, dlen, index, count); \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_unordered_no_check(_dtype *data,                \
                                                 size_t *dlen,                \
                                                 size_t index,                \
                                                 size_t count) {              \
        _dname##_delete_unordered_no_zero_no_check(data, dlen, index, count); \
        _dname##_zero_no_check(data, (*dlen), count);                         \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_unordered(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       size_t count) {                        \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_INDEXED_LENGTH_BOUNDS(*dlen, index, count);               \
                                                                              \
        _dname##_delete_unordered_no_check(data, dlen, index, count);         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_replace_no_zero(_dtype **data,                          \
                                      size_t *dlen,                           \
                                      size_t index,                           \
                                      const _dtype *old_data,                 \
                                      size_t old_len,                         \
                                      const _dtype *new_data,                 \
                                      size_t new_len) {                       \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_INPUT_ARGUMENT(old_data);                                 \
        CBASE_CHECK_INPUT_ARGUMENT(new_data);                                 \
        CBASE_CHECK_INDEX_BOUNDS((*dlen), index);                             \
        CBASE_ERROR_IF(index == (*dlen), CBASE_ERROR_NOT_FOUND);              \
        CBASE_ERROR_IF(new_len == 0, CBASE_ERROR_NULL_POINTER);               \
        CBASE_ERROR_IF(((*dlen) - index) < old_len, CBASE_ERROR_NOT_FOUND);   \
        CBASE_CHECK_MEMORY_OVERLAP((*data), (*dlen), old_data);               \
        CBASE_CHECK_MEMORY_OVERLAP((*data), (*dlen), new_data);               \
                                                                              \
        bool found_once = false;                                              \
        size_t location = 0;                                                  \
        _dtype *cursor = NULL;                                                \
                                                                              \
        while (true) {                                                        \
            if (location >= (*dlen)) {                                        \
                break;                                                        \
            }                                                                 \
                                                                              \
            _dname##_find_no_check((*data),                                   \
                                   *dlen,                                     \
                                   location,                                  \
                                   old_data,                                  \
                                   old_len,                                   \
                                   &cursor);                                  \
                                                                              \
            CBASE_ERROR_IF(!found_once && !cursor, CBASE_ERROR_NOT_FOUND);    \
                                                                              \
            found_once = true;                                                \
                                                                              \
            if (!cursor) {                                                    \
                break;                                                        \
            }                                                                 \
                                                                              \
            if (new_len > old_len) {                                          \
                _dname##_delete_no_zero_no_check((*data),                     \
                                                 dlen,                        \
                                                 cursor - (*data),            \
                                                 new_len - old_len);          \
            }                                                                 \
            else if (old_len > new_len) {                                     \
                _dname##_move_right_no_zero_no_check((*data),                 \
                                                     dlen,                    \
                                                     cursor - (*data),        \
                                                     old_len - new_len);      \
            }                                                                 \
                                                                              \
            _dname##_set_no_check((*data),                                    \
                                  cursor - (*data),                           \
                                  new_data,                                   \
                                  new_len);                                   \
                                                                              \
            /* [FIXME] Should advance by 1 more to avoid infinite loop */     \
            location += (cursor - (*data));                                   \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_replace(_dtype **data,                                  \
                              size_t *dlen,                                   \
                              size_t index,                                   \
                              const _dtype *old_data,                         \
                              size_t old_len,                                 \
                              const _dtype *new_data,                         \
                              size_t new_len) {                               \
        _CBASE_DATA_CHECK_REALLOCATABLE_INPUT_ARGS(data, dlen);               \
        CBASE_CHECK_INPUT_ARGUMENT(old_data);                                 \
        CBASE_CHECK_INPUT_ARGUMENT(new_data);                                 \
        CBASE_CHECK_INDEX_BOUNDS((*dlen), index);                             \
        CBASE_ERROR_IF(index == (*dlen), CBASE_ERROR_NOT_FOUND);              \
        CBASE_ERROR_IF(new_len == 0, CBASE_ERROR_NULL_POINTER);               \
        CBASE_ERROR_IF(((*dlen) - index) < old_len, CBASE_ERROR_NOT_FOUND);   \
        CBASE_CHECK_MEMORY_OVERLAP((*data), (*dlen), old_data);               \
        CBASE_CHECK_MEMORY_OVERLAP((*data), (*dlen), new_data);               \
                                                                              \
        bool found_once = false;                                              \
        size_t location = 0;                                                  \
        _dtype *cursor = NULL;                                                \
                                                                              \
        while (true) {                                                        \
            if (location >= (*dlen)) {                                        \
                break;                                                        \
            }                                                                 \
                                                                              \
            _dname##_find_no_check((*data),                                   \
                                   *dlen,                                     \
                                   location,                                  \
                                   old_data,                                  \
                                   old_len,                                   \
                                   &cursor);                                  \
                                                                              \
            CBASE_ERROR_IF(!found_once && !cursor, CBASE_ERROR_NOT_FOUND);    \
                                                                              \
            found_once = true;                                                \
                                                                              \
            if (!cursor) {                                                    \
                break;                                                        \
            }                                                                 \
                                                                              \
            if (new_len > old_len) {                                          \
                _dname##_delete_no_check((*data),                             \
                                         dlen,                                \
                                         cursor - (*data),                    \
                                         new_len - old_len);                  \
            }                                                                 \
            else if (old_len > new_len) {                                     \
                _dname##_move_right_no_check((*data),                         \
                                             dlen,                            \
                                             cursor - (*data),                \
                                             old_len - new_len);              \
            }                                                                 \
                                                                              \
            _dname##_set_no_check((*data),                                    \
                                  cursor - (*data),                           \
                                  new_data,                                   \
                                  new_len);                                   \
                                                                              \
            /* [FIXME] Should advance by 1 more to avoid infinite loop */     \
            location += (cursor - (*data));                                   \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_no_zero_no_check(_dtype *data,                     \
                                            size_t *dlen,                     \
                                            size_t index,                     \
                                            _dtype *element) {                \
        _dname##_copy_no_check(data, index, 1, element);                      \
        _dname##_delete_no_check(data, dlen, index, 1);                       \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_no_zero(_dtype *data,                               \
                                  size_t *dlen,                               \
                                  size_t index,                               \
                                  _dtype *element) {                          \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_OUTPUT_ARGUMENT(element);                                 \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
                                                                              \
        _dname##_pop_no_zero_no_check(data, dlen, index, element);            \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_no_check(_dtype *data,                             \
                                    size_t *dlen,                             \
                                    size_t index,                             \
                                    _dtype *element) {                        \
        _dname##_copy_no_check(data, index, 1, element);                      \
        _dname##_zero_no_check(data, index, 1);                               \
        _dname##_delete_no_check(data, dlen, index, 1);                       \
    }                                                                         \
                                                                              \
    _api int _dname##_pop(_dtype *data,                                       \
                          size_t *dlen,                                       \
                          size_t index,                                       \
                          _dtype *element) {                                  \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_OUTPUT_ARGUMENT(element);                                 \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
                                                                              \
        _dname##_pop_no_check(data, dlen, index, element);                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_unordered_no_zero_no_check(_dtype *data,           \
                                                      size_t *dlen,           \
                                                      size_t index,           \
                                                      _dtype *element) {      \
        _dname##_copy_no_check(data, index, 1, element);                      \
        _dname##_delete_unordered_no_check(data, dlen, index, 1);             \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_unordered_no_zero(_dtype *data,                     \
                                            size_t *dlen,                     \
                                            size_t index,                     \
                                            _dtype *element) {                \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_OUTPUT_ARGUMENT(element);                                 \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
                                                                              \
        _dname##_pop_unordered_no_zero_no_check(data, dlen, index, element);  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_unordered_no_check(_dtype *data,                   \
                                              size_t *dlen,                   \
                                              size_t index,                   \
                                              _dtype *element) {              \
        _dname##_copy_no_check(data, index, 1, element);                      \
        _dname##_zero_no_check(data, index, 1);                               \
        _dname##_delete_unordered_no_check(data, dlen, index, 1);             \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_unordered(_dtype *data,                             \
                                    size_t *dlen,                             \
                                    size_t index,                             \
                                    _dtype *element) {                        \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_OUTPUT_ARGUMENT(element);                                 \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
                                                                              \
        _dname##_pop_unordered_no_check(data, dlen, index, element);          \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_left_no_check(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         _dtype *element) {                   \
        _dname##_pop_no_check(data, dlen, 0, element);                        \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_left(_dtype *data, size_t *dlen, _dtype *element) { \
        return _dname##_pop(data, dlen, 0, element);                          \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_left_unordered_no_check(_dtype *data,              \
                                                   size_t *dlen,              \
                                                   _dtype *element) {         \
        _dname##_pop_unordered_no_check(data, dlen, 0, element);              \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_left_unordered(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         _dtype *element) {                   \
        return _dname##_pop_unordered(data, dlen, 0, element);                \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_right_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          _dtype *element) {                  \
        _dname##_pop_no_check(data, dlen, (*dlen) - 1, element);              \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_right(_dtype *data,                                 \
                                size_t *dlen,                                 \
                                _dtype *element) {                            \
        _CBASE_DATA_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                     \
        CBASE_CHECK_OUTPUT_ARGUMENT(element);                                 \
        CBASE_ERROR_IF((*dlen) == 0, CBASE_ERROR_OUT_OF_BOUNDS);              \
                                                                              \
        _dname##_pop_right_no_check(data, dlen, element);                     \
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

#define CBASE_MUTABLE_DATA_IMPL(_api, _dname, _dtype)                         \
    CBASE_COMMON_DATA_IMPL_DEPS(_api, _dname, _dtype)                         \
    CBASE_MUTABLE_DATA_IMPL_NO_DEPS(_api, _dname, _dtype)

#endif

/* vi: set et ts=4 sw=4: */
