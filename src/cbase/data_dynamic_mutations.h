#pragma once

#ifndef _CBASE_DATA_STATIC_MUTATIONS_H__
#define _CBASE_DATA_STATIC_MUTATIONS_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/data_base.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_DATA_DYNAMIC_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)          \
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
    _api _dtype *_dname##_prepend_slot_no_zero_check(_dtype *data,            \
                                                     size_t *dlen);           \
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
                              size_t new_len);

#define CBASE_DATA_DYNAMIC_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)          \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dlen, count);          \
                                                                              \
        _dname##_move_right_no_check((*data), dlen, index, count);            \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_OUTPUT_POINTER(new_slot);                                 \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_OUTPUT_POINTER(new_slot);                                 \
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
        CBASE_CHECK_INPUT_POINTER(data);                                      \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_INPUT_POINTER(data2);                                     \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_OUTPUT_POINTER(new_slot);                                 \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_OUTPUT_POINTER(new_slot);                                 \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_INPUT_POINTER(data2);                                     \
        CBASE_CHECK_MEMORY_OVERLAP((*data), *dlen, data2);                    \
        _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dlen, count);          \
                                                                              \
        _dname##_append_no_check((*data), dlen, data2, count);                \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_INPUT_POINTER(old_data);                                  \
        CBASE_CHECK_INPUT_POINTER(new_data);                                  \
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
        CBASE_CHECK_INPUT_DOUBLE_POINTER(data);                               \
        CBASE_CHECK_INPUT_POINTER(dlen);                                      \
        CBASE_CHECK_INPUT_POINTER(old_data);                                  \
        CBASE_CHECK_INPUT_POINTER(new_data);                                  \
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
#endif