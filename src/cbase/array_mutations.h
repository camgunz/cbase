#pragma once

#ifndef _CBASE_ARRAY_MUTATIONS_H__
#define _CBASE_ARRAY_MUTATIONS_H__

/*
 * [TODO]
 * - truncate_at (uses find_*_reverse)
 */

#define CBASE_ARRAY_MUTATIONS_IMPL_DECL(_api, _aname, _atype, _etype, _dname) \
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
    _api void _aname##_compact_no_check(_atype *array);                       \
                                                                              \
    _api int _aname##_compact(_atype *array);                                 \
                                                                              \
    _api void _aname##_set_no_check(_atype *array,                            \
                                    size_t index,                             \
                                    const _etype *elements,                   \
                                    size_t element_count);                    \
                                                                              \
    _api int _aname##_set(_atype *array,                                      \
                          size_t index,                                       \
                          const _etype *elements,                             \
                          size_t element_count);                              \
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
                                                     const _etype *elements,  \
                                                     size_t element_count);   \
                                                                              \
    _api int _aname##_delete_until_no_zero(_atype *array,                     \
                                           size_t index,                      \
                                           const _etype *elements,            \
                                           size_t element_count);             \
                                                                              \
    _api void _aname##_delete_until_no_check(_atype *array,                   \
                                             size_t index,                    \
                                             const _etype *elements,          \
                                             size_t element_count);           \
                                                                              \
    _api int _aname##_delete_until(_atype *array,                             \
                                   size_t index,                              \
                                   const _etype *elements,                    \
                                   size_t element_count);                     \
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
    _api void _aname##_pop_left_no_zero_no_check(_atype *array,               \
                                                 _etype *element);            \
                                                                              \
    _api int _aname##_pop_left_no_zero(_atype *array, _etype *element);       \
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
    _api void _aname##_truncate_no_zero_no_check(_atype *array,               \
                                                 size_t new_length);          \
                                                                              \
    _api int _aname##_truncate_no_zero(_atype *array, size_t new_length);     \
                                                                              \
    _api void _aname##_truncate_no_check(_atype *array, size_t new_length);   \
                                                                              \
    _api int _aname##_truncate(_atype *array, size_t new_length);             \
                                                                              \
    _api void _aname##_clear_no_zero_no_check(_atype *array);                 \
                                                                              \
    _api int _aname##_clear_no_zero(_atype *array);                           \
                                                                              \
    _api void _aname##_clear_no_check(_atype *array);                         \
                                                                              \
    _api int _aname##_clear(_atype *array);

#define CBASE_ARRAY_MUTATIONS_IMPL(_api, _aname, _atype, _etype, _dname)      \
    _api _etype *_aname##_mutable_index_no_check(_atype *array,               \
                                                 size_t index) {              \
        CBASE_DELEGATE(_dname##_mutable_index_no_check(array->data, index));  \
    }                                                                         \
                                                                              \
    _api int _aname##_mutable_index(_atype *array,                            \
                                    size_t index,                             \
                                    _etype **element) {                       \
        CBASE_DELEGATE(                                                       \
            _dname##_mutable_index(array->data, array->len, index, element)); \
    }                                                                         \
                                                                              \
    _api void _aname##_zero_no_check(_atype *array,                           \
                                     size_t index,                            \
                                     size_t count) {                          \
        _dname##_zero_no_check(array->data, index, count);                    \
    }                                                                         \
                                                                              \
    _api int _aname##_zero(_atype *array, size_t index, size_t count) {       \
        CBASE_DELEGATE(_dname##_zero(array->data, array->len, index, count)); \
    }                                                                         \
                                                                              \
    _api void _aname##_compact_no_check(_atype *array) {                      \
        /* [FIXME] Is it... actually necessary to modify cap here? */         \
        _dname##_compact_no_check(array->len, &array->cap);                   \
    }                                                                         \
                                                                              \
    _api int _aname##_compact(_atype *array) {                                \
        /* [FIXME] Is it... actually necessary to modify cap here? */         \
        CBASE_DELEGATE(_dname##_compact(array->len, &array->cap));            \
    }                                                                         \
                                                                              \
    _api void _aname##_set_no_check(_atype *array,                            \
                                    size_t index,                             \
                                    const _etype *elements,                   \
                                    size_t element_count) {                   \
        _dname##_set_no_check(array->data, index, elements, element_count);   \
    }                                                                         \
                                                                              \
    _api int _aname##_set(_atype *array,                                      \
                          size_t index,                                       \
                          const _etype *elements,                             \
                          size_t element_count) {                             \
        CBASE_DELEGATE(_dname##_set(array->data,                              \
                                    array->len,                               \
                                    index,                                    \
                                    elements,                                 \
                                    element_count));                          \
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
        CBASE_DELEGATE(_dname##_move_left_no_zero(array->data,                \
                                                  &array->len,                \
                                                  index,                      \
                                                  count));                    \
    }                                                                         \
                                                                              \
    _api void _aname##_move_left_no_check(_atype *array,                      \
                                          size_t index,                       \
                                          size_t count) {                     \
        _dname##_move_left_no_check(array->data, &array->len, index, count);  \
    }                                                                         \
                                                                              \
    _api int _aname##_move_left(_atype *array,                                \
                                size_t index,                                 \
                                size_t count) {                               \
        CBASE_DELEGATE(                                                       \
            _dname##_move_left(array->data, &array->len, index, count));      \
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
        CBASE_DELEGATE(                                                       \
            _dname##_delete_no_zero(array->data, &array->len, index, count)); \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_no_check(_atype *array,                         \
                                       size_t index,                          \
                                       size_t count) {                        \
        _dname##_delete_no_check(array->data, &array->len, index, count);     \
    }                                                                         \
                                                                              \
    _api int _aname##_delete(_atype *array,                                   \
                             size_t index,                                    \
                             size_t count) {                                  \
        CBASE_DELEGATE(                                                       \
            _dname##_delete(array->data, &array->len, index, count));         \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_until_no_zero_no_check(_atype *array,           \
                                                     size_t index,            \
                                                     const _etype *elements,  \
                                                     size_t element_count) {  \
        _dname##_delete_until_no_zero_no_check(array->data,                   \
                                               &array->len,                   \
                                               index,                         \
                                               elements,                      \
                                               element_count);                \
    }                                                                         \
                                                                              \
    _api int _aname##_delete_until_no_zero(_atype *array,                     \
                                           size_t index,                      \
                                           const _etype *elements,            \
                                           size_t element_count) {            \
        CBASE_DELEGATE(_dname##_delete_until_no_zero(array->data,             \
                                                     &array->len,             \
                                                     index,                   \
                                                     elements,                \
                                                     element_count));         \
    }                                                                         \
                                                                              \
    _api void _aname##_delete_until_no_check(_atype *array,                   \
                                             size_t index,                    \
                                             const _etype *elements,          \
                                             size_t element_count) {          \
        _dname##_delete_until_no_check(array->data,                           \
                                       &array->len,                           \
                                       index,                                 \
                                       elements,                              \
                                       element_count);                        \
    }                                                                         \
                                                                              \
    _api int _aname##_delete_until(_atype *array,                             \
                                   size_t index,                              \
                                   const _etype *elements,                    \
                                   size_t element_count) {                    \
        CBASE_DELEGATE(_dname##_delete_until(array->data,                     \
                                             &array->len,                     \
                                             index,                           \
                                             elements,                        \
                                             element_count));                 \
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
        CBASE_DELEGATE(_dname##_delete_unordered_no_zero(array->data,         \
                                                         &array->len,         \
                                                         index,               \
                                                         count));             \
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
        CBASE_DELEGATE(_dname##_delete_unordered(array->data,                 \
                                                 &array->len,                 \
                                                 index,                       \
                                                 count));                     \
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
        CBASE_DELEGATE(                                                       \
            _dname##_pop_no_zero(array->data, &array->len, index, element));  \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_no_check(_atype *array,                            \
                                    size_t index,                             \
                                    _etype *element) {                        \
        _dname##_pop_no_check(array->data, &array->len, index, element);      \
    }                                                                         \
                                                                              \
    _api int _aname##_pop(_atype *array,                                      \
                          size_t index,                                       \
                          _etype *element) {                                  \
        CBASE_DELEGATE(                                                       \
            _dname##_pop(array->data, &array->len, index, element));          \
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
        CBASE_DELEGATE(_dname##_pop_unordered_no_zero(array->data,            \
                                                      &array->len,            \
                                                      index,                  \
                                                      element));              \
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
        CBASE_DELEGATE(_dname##_pop_unordered(array->data,                    \
                                              &array->len,                    \
                                              index,                          \
                                              element));                      \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_left_no_zero_no_check(_atype *array,               \
                                                 _etype *element) {           \
        _dname##_pop_left_no_zero_no_check(array->data,                      \
                                           &array->len,                       \
                                           element);                          \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_left_no_zero(_atype *array,                         \
                                       _etype *element) {                     \
        CBASE_DELEGATE(                                                       \
            _dname##_pop_left_no_zero(array->data, &array->len, element));  \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_left_no_check(_atype *array,                       \
                                         _etype *element) {                   \
        _dname##_pop_left_no_check(array->data, &array->len, element);        \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_left(_atype *array,                                 \
                               _etype *element) {                             \
        CBASE_DELEGATE(_dname##_pop_left(array->data, &array->len, element)); \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_left_unordered_no_check(_atype *array,             \
                                                   _etype *element) {         \
        _dname##_pop_left_unordered_no_check(array->data,                     \
                                             &array->len,                     \
                                             element);                        \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_left_unordered(_atype *array,                       \
                                         _etype *element) {                   \
        CBASE_DELEGATE(                                                       \
            _dname##_pop_left_unordered(array->data, &array->len, element));  \
    }                                                                         \
                                                                              \
    _api void _aname##_pop_right_no_check(_atype *array,                      \
                                          _etype *element) {                  \
        _dname##_pop_right_no_check(array->data, &array->len, element);       \
    }                                                                         \
                                                                              \
    _api int _aname##_pop_right(_atype *array,                                \
                                _etype *element) {                            \
        CBASE_DELEGATE(                                                       \
            _dname##_pop_right(array->data, &array->len, element));           \
    }                                                                         \
                                                                              \
    _api void _aname##_truncate_no_zero_no_check(_atype *array,               \
                                                 size_t new_length) {         \
        _dname##_truncate_no_zero_no_check(&array->len,                       \
                                           new_length);                       \
    }                                                                         \
                                                                              \
    _api int _aname##_truncate_no_zero(_atype *array,                         \
                                       size_t new_length) {                   \
        CBASE_DELEGATE(                                                       \
            _dname##_truncate_no_zero(&array->len, new_length)); \
    }                                                                         \
                                                                              \
    _api void _aname##_truncate_no_check(_atype *array,                       \
                                         size_t new_length) {                 \
        _dname##_truncate_no_check(array->data, &array->len, new_length);     \
    }                                                                         \
                                                                              \
    _api int _aname##_truncate(_atype *array,                                 \
                               size_t new_length) {                           \
        CBASE_DELEGATE(                                                       \
            _dname##_truncate(array->data, &array->len, new_length));         \
    }                                                                         \
                                                                              \
    _api void _aname##_clear_no_zero_no_check(_atype *array) {                \
        _dname##_clear_no_zero_no_check(&array->len);                         \
    }                                                                         \
                                                                              \
    _api int _aname##_clear_no_zero(_atype *array) {                          \
        CBASE_DELEGATE(_dname##_clear_no_zero(&array->len));                  \
    }                                                                         \
                                                                              \
    _api void _aname##_clear_no_check(_atype *array) {          \
        _dname##_clear_no_check(array->data, &array->len);                    \
    }                                                                         \
                                                                              \
    _api int _aname##_clear(_atype *array) {                    \
        CBASE_DELEGATE(_dname##_clear(array->data, &array->len));             \
    }

#endif
