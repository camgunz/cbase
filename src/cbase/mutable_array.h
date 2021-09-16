#pragma once

#ifndef _CBASE_MUTABLE_ARRAY_H__
#define _CBASE_MUTABLE_ARRAY_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/common_array.h"
#include "cbase/mutable_data.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_MUTABLE_ARRAY_IMPL_DECL(_api, _dname, _aname, _atype, _etype)   \
    _api _etype *_aname##_mutable_index_no_check(_atype *array,               \
                                                 size_t index);               \
                                                                              \
    _api int _aname##_mutable_index(_atype *array,                            \
                                    size_t index,                             \
                                    _etype **element);                        \
                                                                              \
    _api void _aname##_zero_no_check(_atype *array,                           \
                                     size_t index,                            \
                                     size_t count);                           \
                                                                              \
    _api int _aname##_zero(_atype *array, size_t index, size_t count);        \
                                                                              \
    _api int _aname##_ensure_capacity_no_zero_no_check(_atype *array,         \
                                                       size_t *dcap,          \
                                                       size_t cap);           \
                                                                              \
    _api int _aname##_ensure_capacity_no_check(_atype *array,                 \
                                               size_t *dcap,                  \
                                               size_t cap);                   \
                                                                              \
    _api int _aname##_ensure_capacity_no_zero(_atype *array,                  \
                                              size_t *dcap,                   \
                                              size_t cap);                    \
                                                                              \
    _api int _aname##_ensure_capacity(_atype *array,                          \
                                      size_t *dcap,                           \
                                      size_t cap);                            \
                                                                              \
    _api int _aname##_set_capacity_no_zero_no_check(_atype *array,            \
                                                    size_t *dcap,             \
                                                    size_t cap);              \
                                                                              \
    _api int _aname##_set_capacity_no_zero(_atype *array,                     \
                                           size_t *dcap,                      \
                                           size_t cap);                       \
                                                                              \
    _api int _aname##_set_capacity_no_check(_atype *array,                    \
                                            size_t *dcap,                     \
                                            size_t cap);                      \
                                                                              \
    _api int _aname##_set_capacity(_atype *array, size_t *dcap, size_t cap);  \
                                                                              \
    _api void _aname##_set_no_check(_atype *array,                            \
                                    size_t index,                             \
                                    _etype *data2,                            \
                                    size_t count);                            \
                                                                              \
    _api int _aname##_set(_atype *array,                                      \
                          size_t index,                                       \
                          _etype *data2,                                      \
                          size_t count);                                      \
                                                                              \
    _api void _aname##_truncate_no_check(_atype *array, size_t new_length);   \
                                                                              \
    _api int _aname##_truncate(_atype *array, size_t new_length);             \
                                                                              \
    _api void _aname##_compact_no_check(size_t *dcap);                        \
                                                                              \
    _api int _aname##_compact(size_t *dcap);                                  \
                                                                              \
    _api void _aname##_move_right_no_zero_no_check(_atype *array,             \
                                                   size_t index,              \
                                                   size_t count);             \
                                                                              \
    _api int _aname##_move_right_no_zero(_atype *array,                       \
                                         size_t index,                        \
                                         size_t count);                       \
                                                                              \
    _api void _aname##_move_right_no_check(_atype *array,                     \
                                           size_t index,                      \
                                           size_t count);                     \
                                                                              \
    _api int _aname##_move_right(_atype *array, size_t index, size_t count);  \
                                                                              \
    _api void _aname##_move_left_no_zero_no_check(_atype *array,              \
                                                  size_t index,               \
                                                  size_t count);              \
                                                                              \
    _api int _aname##_move_left_no_zero(_atype *array,                        \
                                        size_t index,                         \
                                        size_t count);                        \
                                                                              \
    _api void _aname##_move_left_no_check(_atype *array,                      \
                                          size_t index,                       \
                                          size_t count);                      \
                                                                              \
    _api int _aname##_move_left(_atype *array, size_t index, size_t count);   \
                                                                              \
    _api _etype *_aname##_insert_slot_no_zero_no_check(_atype *array,         \
                                                       size_t index);         \
                                                                              \
    _api int _aname##_insert_slot_no_zero(_atype *array,                      \
                                          size_t index,                       \
                                          _etype const **new_slot);           \
                                                                              \
    _api _etype *_aname##_insert_slot_no_check(_atype *array, size_t index);  \
                                                                              \
    _api int _aname##_insert_slot(_atype *array,                              \
                                  size_t index,                               \
                                  _etype const **new_slot);                   \
                                                                              \
    _api void _aname##_insert_no_check(_atype *array,                         \
                                       size_t index,                          \
                                       _etype *data2,                         \
                                       size_t count);                         \
                                                                              \
    _api int _aname##_insert(_atype *array,                                   \
                             size_t index,                                    \
                             _etype *data2,                                   \
                             size_t count);                                   \
                                                                              \
    _api _etype *_aname##_prepend_slot_no_check(_atype *array);               \
                                                                              \
    _api int _aname##_prepend_slot(_atype *array, _etype const **new_slot);   \
                                                                              \
    _api int _aname##_prepend_slot_no_zero(_atype *array,                     \
                                           _etype const **new_slot);          \
                                                                              \
    _api void _aname##_prepend_no_check(_atype *array,                        \
                                        _etype *data2,                        \
                                        size_t count);                        \
                                                                              \
    _api int _aname##_prepend(_atype *array, _etype *data2, size_t count);    \
                                                                              \
    _api _etype *_aname##_append_slot_no_zero_no_check(                       \
        _atype *array,                                                        \
        _etype const **new_slot);                                             \
                                                                              \
    _api int _aname##_append_slot_no_zero(_atype *array,                      \
                                          _etype const **new_slot);           \
                                                                              \
    _api _etype *_aname##_append_slot_no_check(_atype *array);                \
                                                                              \
    _api int _aname##_append_slot(_atype *array, _etype const **new_slot);    \
                                                                              \
    _api void _aname##_append_no_check(_atype *array,                         \
                                       _etype *data2,                         \
                                       size_t count);                         \
                                                                              \
    _api int _aname##_append(_atype *array, _etype *data2, size_t count);     \
                                                                              \
    _api void _aname##_delete_no_zero_no_check(_atype *array,                 \
                                               size_t index,                  \
                                               size_t count);                 \
                                                                              \
    _api int _aname##_delete_no_zero(_atype *array,                           \
                                     size_t index,                            \
                                     size_t count);                           \
                                                                              \
    _api void _aname##_delete_no_check(_atype *array,                         \
                                       size_t index,                          \
                                       size_t count);                         \
                                                                              \
    _api int _aname##_delete(_atype *array, size_t index, size_t count);      \
                                                                              \
    _api void _aname##_delete_until_no_zero_no_check(_atype *array,           \
                                                     size_t index,            \
                                                     _etype *data2,           \
                                                     size_t dlen2);           \
                                                                              \
    _api int _aname##_delete_until_no_zero(_atype *array,                     \
                                           size_t index,                      \
                                           _etype *data2,                     \
                                           size_t dlen2);                     \
                                                                              \
    _api void _aname##_delete_until_no_check(_atype *array,                   \
                                             size_t index,                    \
                                             _etype *data2,                   \
                                             size_t dlen2);                   \
                                                                              \
    _api int _aname##_delete_until(_atype *array,                             \
                                   size_t index,                              \
                                   _etype *data2,                             \
                                   size_t dlen2);                             \
                                                                              \
    _api void _aname##_delete_unordered_no_zero_no_check(_atype *array,       \
                                                         size_t index,        \
                                                         size_t count);       \
                                                                              \
    _api int _aname##_delete_unordered_no_zero(_atype *array,                 \
                                               size_t index,                  \
                                               size_t count);                 \
                                                                              \
    _api void _aname##_delete_unordered_no_check(_atype *array,               \
                                                 size_t index,                \
                                                 size_t count);               \
                                                                              \
    _api int _aname##_delete_unordered(_atype *array,                         \
                                       size_t index,                          \
                                       size_t count);                         \
                                                                              \
    _api int _aname##_replace_no_zero(_atype *array,                          \
                                      size_t index,                           \
                                      const _etype *old_data,                 \
                                      size_t old_len,                         \
                                      const _etype *new_data,                 \
                                      size_t new_len);                        \
                                                                              \
    _api int _aname##_replace(_atype *array,                                  \
                              size_t index,                                   \
                              const _etype *old_data,                         \
                              size_t old_len,                                 \
                              const _etype *new_data,                         \
                              size_t new_len);                                \
                                                                              \
    _api void _aname##_pop_no_zero_no_check(_atype *array,                    \
                                            size_t index,                     \
                                            _etype *element);                 \
                                                                              \
    _api int _aname##_pop_no_zero(_atype *array,                              \
                                  size_t index,                               \
                                  _etype *element);                           \
                                                                              \
    _api void _aname##_pop_no_check(_atype *array,                            \
                                    size_t index,                             \
                                    _etype *element);                         \
                                                                              \
    _api int _aname##_pop(_atype *array, size_t index, _etype *element);      \
                                                                              \
    _api void _aname##_pop_unordered_no_zero_no_check(_atype *array,          \
                                                      size_t index,           \
                                                      _etype *element);       \
                                                                              \
    _api int _aname##_pop_unordered_no_zero(_atype *array,                    \
                                            size_t index,                     \
                                            _etype *element);                 \
                                                                              \
    _api void _aname##_pop_unordered_no_check(_atype *array,                  \
                                              size_t index,                   \
                                              _etype *element);               \
                                                                              \
    _api int _aname##_pop_unordered(_atype *array,                            \
                                    size_t index,                             \
                                    _etype *element);                         \
                                                                              \
    _api void _aname##_pop_left_no_check(_atype *array, _etype *element);     \
                                                                              \
    _api int _aname##_pop_left(_atype *array, _etype *element);               \
                                                                              \
    _api void _aname##_pop_left_unordered_no_check(_atype *array,             \
                                                   _etype *element);          \
                                                                              \
    _api int _aname##_pop_left_unordered(_atype *array, _etype *element);     \
                                                                              \
    _api void _aname##_pop_right_no_check(_atype *array, _etype *element);    \
                                                                              \
    _api int _aname##_pop_right(_atype *array, _etype *element);              \
                                                                              \
    _api void _aname##_clear_no_check(_atype *array);                         \
                                                                              \
    _api int _aname##_clear(_atype *array);

#define CBASE_MUTABLE_ARRAY_IMPL_DEPS(_api, _dname, _aname, _atype, _etype)   \
    CBASE_COMMON_DATA_IMPL(_api, _dname, _etype)                              \
    CBASE_COMMON_ARRAY_IMPL_NO_DEPS(_api, _dname, _aname, _atype, _etype)     \
    CBASE_MUTABLE_DATA_IMPL_NO_DEPS(_api, _dname, _dtype)

#define CBASE_MUTABLE_ARRAY_IMPL_NO_DEPS(_api,                                \
                                         _dname,                              \
                                         _aname,                              \
                                         _atype,                              \
                                         _etype)                              \
    _api _etype *_aname##_mutable_index_no_check(_atype *array,               \
                                                 size_t index) {              \
        return _dname##_mutable_index_no_check(array->data, index);           \
    }                                                                         \
                                                                              \
    _api int _aname##_mutable_index(_atype *array,                            \
                                    size_t index,                             \
                                    _etype **element) {                       \
        return _dname##_mutable_index(array->data,                            \
                                      array->len,                             \
                                      index,                                  \
                                      *element);                              \
    }                                                                         \
                                                                              \
    _api void _aname##_zero_no_check(_atype *array,                           \
                                     size_t index,                            \
                                     size_t count) {                          \
        return _dname##_zero_no_check(array->data, index, count);             \
    }                                                                         \
                                                                              \
    _api int _aname##_zero(_atype *array, size_t index, size_t count) {       \
        return _dname##_zero(array->data, array->len, index, count);          \
    }                                                                         \
                                                                              \
    _api int _aname##_ensure_capacity_no_zero_no_check(_atype *array,         \
                                                       size_t *dcap,          \
                                                       size_t cap);           \
                                                                              \
    _api int _aname##_ensure_capacity_no_check(_atype *array,                 \
                                               size_t *dcap,                  \
                                               size_t cap);                   \
                                                                              \
    _api int _aname##_ensure_capacity_no_zero(_atype *array,                  \
                                              size_t *dcap,                   \
                                              size_t cap) {                   \
        return _dname##_ensure_capacity_no_zero(_etype * *data,               \
                                                size_t * dcap,                \
                                                size_t cap);                  \
    }                                                                         \
                                                                              \
    _api int _aname##_ensure_capacity(_atype *array,                          \
                                      size_t *dcap,                           \
                                      size_t cap) {                           \
        return _dname##_ensure_capacity(&array->data, dcap, cap);             \
    }                                                                         \
                                                                              \
    _api int _aname##_set_capacity_no_zero_no_check(_atype *array,            \
                                                    size_t *dcap,             \
                                                    size_t cap) {             \
        return _dname##_set_capacity_no_zero_no_check(&array->data,           \
                                                      *dcap,                  \
                                                      cap);                   \
    }                                                                         \
                                                                              \
    _api int _aname##_set_capacity_no_zero(_atype *array,                     \
                                           size_t *dcap,                      \
                                           size_t cap) {                      \
        return _dname##_set_capacity_no_zero(&array->data, dcap, cap);        \
    }                                                                         \
                                                                              \
    _api int _aname##_set_capacity_no_check(_atype *array,                    \
                                            size_t *dcap,                     \
                                            size_t cap) {                     \
        return _dname##_set_capacity_no_check(&array->data, dcap, cap);       \
    }                                                                         \
                                                                              \
    _api int _aname##_set_capacity(_atype *array, size_t *dcap, size_t cap) { \
        return _dname##_set_capacity(&array->data, dcap, cap);                \
    }                                                                         \
                                                                              \
    _api void _aname##_set_no_check(_atype *array,                            \
                                    size_t index,                             \
                                    _etype *data2,                            \
                                    size_t count) {                           \
        _dname##_set_no_check(array->data, index, data2, count);              \
    }                                                                         \
                                                                              \
    _api int _aname##_set(_atype *array,                                      \
                          size_t index,                                       \
                          _etype *data2,                                      \
                          size_t count) {                                     \
        return _dname##_set(array->data, array->len, index, data2, count);    \
    }                                                                         \
                                                                              \
    _api void _aname##_truncate_no_check(_atype *array, size_t new_length) {  \
        _dname##_truncate_no_check(array->data, &array->len, new_length);     \
    }                                                                         \
                                                                              \
    _api int _aname##_truncate(_atype *array, size_t new_length) {            \
        return _dname##_truncate(array->data, &array->len, new_length);       \
    }                                                                         \
                                                                              \
    _api void _aname##_compact_no_check(size_t *dcap) {                       \
        _dname##_compact_no_check(array->len, dcap);                          \
    }                                                                         \
                                                                              \
    _api int _aname##_compact(size_t *dcap) {                                 \
        return _dname##_compact(array->len, dcap);                            \
    }                                                                         \
                                                                              \
    _api void _aname##_move_right_no_zero_no_check(_atype *array,             \
                                                   size_t index,              \
                                                   size_t count) {            \
        _dname##_move_right_no_zero_no_check(array->data,                     \
                                             &array->len,                     \
                                             index,                           \
                                             count);                          \
    }                                                                         \
                                                                              \
    _api int _aname##_move_right_no_zero(_atype *array,                       \
                                         size_t index,                        \
                                         size_t count) {                      \
        return _dname##_move_right_no_zero(_etype * *data,                    \
                                           &array->len,                       \
                                           index,                             \
                                           count);                            \
    }                                                                         \
                                                                              \
    _api void _aname##_move_right_no_check(_atype *array,                     \
                                           size_t index,                      \
                                           size_t count) {                    \
        _dname##_move_right_no_check(array->data, &array->len, index, count); \
    }                                                                         \
                                                                              \
    _api int _aname##_move_right(_atype *array, size_t index, size_t count) { \
        return _dname##_move_right(_etype * *data,                            \
                                   &array->len,                               \
                                   index,                                     \
                                   count);                                    \
    }                                                                         \
                                                                              \
    _api void _aname##_move_left_no_zero_no_check(_atype *array,              \
                                                  size_t index,               \
                                                  size_t count) {             \
        _dname##_move_left_no_zero_no_check(array->data,                      \
                                            &array->len,                      \
                                            index,                            \
                                            count);                           \
    }                                                                         \
                                                                              \
    _api int _aname##_move_left_no_zero(_atype *array,                        \
                                        size_t index,                         \
                                        size_t count) {                       \
        return _dname##_move_left_no_zero(array->data,                        \
                                          &array->len,                        \
                                          index,                              \
                                          count);                             \
    }                                                                         \
                                                                              \
    _api void _aname##_move_left_no_check(_atype *array,                      \
                                          size_t index,                       \
                                          size_t count) {                     \
        _dname##_move_left_no_check(array->data, &array->len, index, count);  \
    }                                                                         \
                                                                              \
    _api int _aname##_move_left(_atype *array, size_t index, size_t count) {  \
        return _dname##_move_left(array->data, &array->len, index, count);    \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_insert_slot_no_zero_no_check(_atype *array,         \
                                                       size_t index) {        \
        return _dname##_insert_slot_no_zero_no_check(array->data,             \
                                                     &array->len,             \
                                                     index);                  \
    }                                                                         \
                                                                              \
    _api int _aname##_insert_slot_no_zero(_atype *array,                      \
                                          size_t index,                       \
                                          _etype const **new_slot) {          \
        return _dname##_insert_slot_no_zero(_etype * *data,                   \
                                            &array->len,                      \
                                            index,                            \
                                            _etype const **new_slot);         \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_insert_slot_no_check(_atype *array, size_t index) { \
        return _dname##_insert_slot_no_check(array->data,                     \
                                             &array->len,                     \
                                             index);                          \
    }                                                                         \
                                                                              \
    _api int _aname##_insert_slot(_atype *array,                              \
                                  size_t index,                               \
                                  _etype const **new_slot) {                  \
        return _dname##_insert_slot(_etype * *data,                           \
                                    &array->len,                              \
                                    index,                                    \
                                    _etype const **new_slot);                 \
    }                                                                         \
                                                                              \
    _api void _aname##_insert_no_check(_atype *array,                         \
                                       size_t index,                          \
                                       _etype *data2,                         \
                                       size_t count) {                        \
        _dname##_insert_no_check(array->data,                                 \
                                 &array->len,                                 \
                                 index,                                       \
                                 data2,                                       \
                                 count);                                      \
    }                                                                         \
                                                                              \
    _api int _aname##_insert(_atype *array,                                   \
                             size_t index,                                    \
                             _etype *data2,                                   \
                             size_t count) {                                  \
        return _dname##_insert(_etype * *data,                                \
                               &array->len,                                   \
                               index,                                         \
                               data2,                                         \
                               count);                                        \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_prepend_slot_no_check(_atype *array) {              \
        return _dname##_prepend_slot_no_check(array->data, &array->len);      \
    }                                                                         \
                                                                              \
    _api int _aname##_prepend_slot(_atype *array, _etype const **new_slot) {  \
        return _dname##_prepend_slot(_etype * *data,                          \
                                     &array->len,                             \
                                     _etype const **new_slot);                \
    }                                                                         \
                                                                              \
    _api int _aname##_prepend_slot_no_zero(_atype *array,                     \
                                           _etype const **new_slot) {         \
        return _dname##_prepend_slot_no_zero(_etype * *data,                  \
                                             &array->len,                     \
                                             _etype const **new_slot);        \
    }                                                                         \
                                                                              \
    _api void _aname##_prepend_no_check(_atype *array,                        \
                                        _etype *data2,                        \
                                        size_t count) {                       \
        _dname##_prepend_no_check(array->data, &array->len, data2, count);    \
    }                                                                         \
                                                                              \
    _api int _aname##_prepend(_atype *array, _etype *data2, size_t count) {   \
        return _dname##_prepend(_etype * *data, &array->len, data2, count);   \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_append_slot_no_zero_no_check(_atype *array) {       \
        return _dname##_append_slot_no_zero_no_check(array->data,             \
                                                     &array->len);            \
    }                                                                         \
                                                                              \
    _api int _aname##_append_slot_no_zero(_atype *array,                      \
                                          _etype const **new_slot) {          \
        return _dname##_append_slot_no_zero(_etype * *data,                   \
                                            &array->len,                      \
                                            _etype const **new_slot);         \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_append_slot_no_check(_atype *array) {               \
        return _dname##_append_slot_no_check(array->data, &array->len);       \
    }                                                                         \
                                                                              \
    _api int _aname##_append_slot(_atype *array, _etype const **new_slot) {   \
        return _dname##_append_slot(_etype * *data,                           \
                                    &array->len,                              \
                                    _etype const **new_slot);                 \
    }                                                                         \
                                                                              \
    _api void _aname##_append_no_check(_atype *array,                         \
                                       _etype *data2,                         \
                                       size_t count) {                        \
        _dname##_append_no_check(array->data, &array->len, data2, count);     \
    }                                                                         \
                                                                              \
    _api int _aname##_append(_atype *array, _etype *data2, size_t count) {    \
        return _dname##_append(_etype * *data, &array->len, data2, count);    \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_no_zero_no_check(_atype *array,                 \
                                               size_t index,                  \
                                               size_t count) {                \
        _dname##_delete_no_zero_no_check(array->data,                         \
                                         &array->len,                         \
                                         index,                               \
                                         count);                              \
    }                                                                         \
                                                                              \
    _api int _aname##_delete_no_zero(_atype *array,                           \
                                     size_t index,                            \
                                     size_t count) {                          \
        return _dname##_delete_no_zero(_etype * *data,                        \
                                       &array->len,                           \
                                       index,                                 \
                                       count);                                \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_no_check(_atype *array,                         \
                                       size_t index,                          \
                                       size_t count) {                        \
        _dname##_delete_no_check(array->data, &array->len, index, count);     \
    }                                                                         \
                                                                              \
    _api int _aname##_delete(_atype *array, size_t index, size_t count) {     \
        return _dname##_delete(array->data, &array->len, index, count);       \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_until_no_zero_no_check(_atype *array,           \
                                                     size_t index,            \
                                                     _etype *data2,           \
                                                     size_t dlen2) {          \
        _dname##_delete_until_no_zero_no_check(array->data,                   \
                                               &array->len,                   \
                                               index,                         \
                                               data2,                         \
                                               dlen2);                        \
    }                                                                         \
                                                                              \
    _api int _aname##_delete_until_no_zero(_atype *array,                     \
                                           size_t index,                      \
                                           _etype *data2,                     \
                                           size_t dlen2) {                    \
        return _dname##_delete_until_no_zero(array->data,                     \
                                             &array->len,                     \
                                             index,                           \
                                             data2,                           \
                                             dlen2);                          \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_until_no_check(_atype *array,                   \
                                             size_t index,                    \
                                             _etype *data2,                   \
                                             size_t dlen2) {                  \
        _dname##_delete_until_no_check(array->data,                           \
                                       &array->len,                           \
                                       index,                                 \
                                       data2,                                 \
                                       dlen2);                                \
    }                                                                         \
                                                                              \
    _api int _aname##_delete_until(_atype *array,                             \
                                   size_t index,                              \
                                   _etype *data2,                             \
                                   size_t dlen2) {                            \
        return _dname##_delete_until(array->data,                             \
                                     &array->len,                             \
                                     index,                                   \
                                     data2,                                   \
                                     dlen2);                                  \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_unordered_no_zero_no_check(_atype *array,       \
                                                         size_t index,        \
                                                         size_t count) {      \
        _dname##_delete_unordered_no_zero_no_check(array->data,               \
                                                   &array->len,               \
                                                   index,                     \
                                                   count);                    \
    }                                                                         \
                                                                              \
    _api int _aname##_delete_unordered_no_zero(_atype *array,                 \
                                               size_t index,                  \
                                               size_t count) {                \
        return _dname##_delete_unordered_no_zero(array->data,                 \
                                                 &array->len,                 \
                                                 index,                       \
                                                 count);                      \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_unordered_no_check(_atype *array,               \
                                                 size_t index,                \
                                                 size_t count) {              \
        _dname##_delete_unordered_no_check(array->data,                       \
                                           &array->len,                       \
                                           index,                             \
                                           count);                            \
    }                                                                         \
                                                                              \
    _api int _aname##_delete_unordered(_atype *array,                         \
                                       size_t index,                          \
                                       size_t count) {                        \
        return _dname##_delete_unordered(array->data,                         \
                                         &array->len,                         \
                                         index,                               \
                                         count);                              \
    }                                                                         \
                                                                              \
    _api int _aname##_replace_no_zero(_atype *array,                          \
                                      size_t index,                           \
                                      const _etype *old_data,                 \
                                      size_t old_len,                         \
                                      const _etype *new_data,                 \
                                      size_t new_len) {                       \
        return _dname##_replace_no_zero(&array->data,                         \
                                        &array->len,                          \
                                        index,                                \
                                        old_data,                             \
                                        old_len,                              \
                                        new_data,                             \
                                        new_len);                             \
    }                                                                         \
                                                                              \
    _api int _aname##_replace(_atype *array,                                  \
                              size_t index,                                   \
                              const _etype *old_data,                         \
                              size_t old_len,                                 \
                              const _etype *new_data,                         \
                              size_t new_len) {                               \
        return _dname##_replace(&array->data,                                 \
                                &array->len,                                  \
                                index,                                        \
                                old_data,                                     \
                                old_len,                                      \
                                new_data,                                     \
                                new_len);                                     \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_no_zero_no_check(_atype *array,                    \
                                            size_t index,                     \
                                            _etype *element) {                \
        _dname##_pop_no_zero_no_check(array->data,                            \
                                      &array->len,                            \
                                      index,                                  \
                                      element);                               \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_no_zero(_atype *array,                              \
                                  size_t index,                               \
                                  _etype *element) {                          \
        return _dname##_pop_no_zero(array->data,                              \
                                    &array->len,                              \
                                    index,                                    \
                                    element);                                 \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_no_check(_atype *array,                            \
                                    size_t index,                             \
                                    _etype *element) {                        \
        _dname##_pop_no_check(array->data, &array->len, index, element);      \
    }                                                                         \
                                                                              \
    _api int _aname##_pop(_atype *array, size_t index, _etype *element) {     \
        return _dname##_pop(array->data, &array->len, index, element);        \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_unordered_no_zero_no_check(_atype *array,          \
                                                      size_t index,           \
                                                      _etype *element) {      \
        _dname##_pop_unordered_no_zero_no_check(array->data,                  \
                                                &array->len,                  \
                                                index,                        \
                                                element);                     \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_unordered_no_zero(_atype *array,                    \
                                            size_t index,                     \
                                            _etype *element) {                \
        return _dname##_pop_unordered_no_zero(array->data,                    \
                                              &array->len,                    \
                                              index,                          \
                                              element);                       \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_unordered_no_check(_atype *array,                  \
                                              size_t index,                   \
                                              _etype *element) {              \
        _dname##_pop_unordered_no_check(array->data,                          \
                                        &array->len,                          \
                                        index,                                \
                                        element);                             \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_unordered(_atype *array,                            \
                                    size_t index,                             \
                                    _etype *element) {                        \
        return _dname##_pop_unordered(array->data,                            \
                                      &array->len,                            \
                                      index,                                  \
                                      element);                               \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_left_no_check(_atype *array, _etype *element) {    \
        _dname##_pop_left_no_check(array->data, &array->len, element);        \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_left(_atype *array, _etype *element) {              \
        return _dname##_pop_left(array->data, &array->len, element);          \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_left_unordered_no_check(_atype *array,             \
                                                   _etype *element) {         \
        _dname##_pop_left_unordered_no_check(array->data,                     \
                                             &array->len,                     \
                                             element);                        \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_left_unordered(_atype *array, _etype *element) {    \
        return _dname##_pop_left_unordered(array->data,                       \
                                           &array->len,                       \
                                           element);                          \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_right_no_check(_atype *array, _etype *element) {   \
        _dname##_pop_right_no_check(array->data, &array->len, element);       \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_right(_atype *array, _etype *element) {             \
        return _dname##_pop_right(array->data, &array->len, element);         \
    }                                                                         \
                                                                              \
    _api void _aname##_clear_no_check(_atype *array) {                        \
        _dname##_clear_no_check(array->data, &array->len);                    \
    }                                                                         \
                                                                              \
    _api int _aname##_clear(_atype *array) {                                  \
        return _dname##_clear(array->data, &array->len);                      \
    }

#define CBASE_MUTABLE_ARRAY_IMPL(_api, _dname, _aname, _atype, _etype)        \
    CBASE_MUTABLE_ARRAY_IMPL_DEPS(_api, _dname, _aname, _atype, _etype)       \
    CBASE_MUTABLE_ARRAY_IMPL_NO_DEPS(_api, _dname, _aname, _atype, _etype)

#endif

/* vi: set et ts=4 sw=4: */
