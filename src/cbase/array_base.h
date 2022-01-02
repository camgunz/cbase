#pragma once

#ifndef _CBASE_ARRAY_BASE_H__
#define _CBASE_ARRAY_BASE_H__

#define CBASE_ARRAY_BASE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)      \
    _api const _etype *_aname##_index_no_check(const _atype *array,           \
                                               size_t index);                 \
                                                                              \
    _api int _aname##_index(const _atype *array,                              \
                            size_t index,                                     \
                            _etype const **element);                          \
                                                                              \
    _api void _aname##_slice_no_check(const _atype *array,                    \
                                      size_t index,                           \
                                      size_t len,                             \
                                      _etype const **data2,                   \
                                      size_t *dlen2);                         \
                                                                              \
    _api int _aname##_slice(const _atype *array,                              \
                            size_t index,                                     \
                            size_t len,                                       \
                            _etype const **data2,                             \
                            size_t *dlen2);                                   \
                                                                              \
    _api void _aname##_copy_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     size_t count,                            \
                                     _etype *data2);                          \
                                                                              \
    _api int _aname##_copy(const _atype *array,                               \
                           size_t index,                                      \
                           size_t count,                                      \
                           _etype *data2,                                     \
                           size_t dlen2);                                     \
                                                                              \
    _api bool _aname##_equals_no_check(const _atype *array,                   \
                                       size_t index,                          \
                                       const _etype *data2,                   \
                                       size_t dlen2);                         \
                                                                              \
    _api int _aname##_equals(const _atype *array,                             \
                             size_t index,                                    \
                             const _etype *data2,                             \
                             size_t dlen2,                                    \
                             bool *equal);                                    \
                                                                              \
    _api bool _aname##_starts_with_no_check(const _atype *array,              \
                                            const _etype *data2,              \
                                            size_t dlen2);                    \
                                                                              \
    _api int _aname##_starts_with(const _atype *array,                        \
                                  const _etype *data2,                        \
                                  size_t dlen2,                               \
                                  bool *equal);                               \
                                                                              \
    _api bool _aname##_ends_with_no_check(const _atype *array,                \
                                          const _etype *data2,                \
                                          size_t dlen2);                      \
                                                                              \
    _api int _aname##_ends_with(const _atype *array,                          \
                                const _etype *data2,                          \
                                size_t dlen2,                                 \
                                bool *equal);                                 \
                                                                              \
    _api void _aname##_find_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     const _etype *data2,                     \
                                     size_t dlen2,                            \
                                     _etype **cursor);                        \
                                                                              \
    _api int _aname##_find(const _atype *array,                               \
                           size_t index,                                      \
                           const _etype *data2,                               \
                           size_t dlen2,                                      \
                           _etype **cursor);                                  \
                                                                              \
    _api void _aname##_find_index_no_check(const _atype *array,               \
                                           size_t index,                      \
                                           const _etype *data2,               \
                                           size_t dlen2,                      \
                                           size_t *location);                 \
                                                                              \
    _api int _aname##_find_index(const _atype *array,                         \
                                 size_t index,                                \
                                 const _etype *data2,                         \
                                 size_t dlen2,                                \
                                 size_t *location);

#define CBASE_ARRAY_BASE_IMPL(_api, _aname, _atype, _etype, _dname)           \
    _api const _etype *_aname##_index_no_check(const _atype *array,           \
                                               size_t index) {                \
        CBASE_DELEGATE(_dname##_index_no_check(array->data, index));          \
    }                                                                         \
                                                                              \
    _api int _aname##_index(const _atype *array,                              \
                            size_t index,                                     \
                            _etype const **element) {                         \
        CBASE_DELEGATE(                                                       \
            _dname##_index(array->data, array->len, index, element));         \
    }                                                                         \
                                                                              \
    _api void _aname##_slice_no_check(const _atype *array,                    \
                                      size_t index,                           \
                                      size_t len,                             \
                                      _etype const **data2,                   \
                                      size_t *dlen2) {                        \
        _dname##_slice_no_check(array->data, index, len, data2, dlen2);       \
    }                                                                         \
                                                                              \
    _api int _aname##_slice(const _atype *array,                              \
                            size_t index,                                     \
                            size_t len,                                       \
                            _etype const **data2,                             \
                            size_t *dlen2) {                                  \
        CBASE_DELEGATE(_dname##_slice(array->data,                            \
                                      array->len,                             \
                                      index,                                  \
                                      len,                                    \
                                      data2,                                  \
                                      dlen2));                                \
    }                                                                         \
                                                                              \
    _api void _aname##_copy_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     size_t count,                            \
                                     _etype *data2) {                         \
        _dname##_copy_no_check(array->data, index, count, data2);             \
    }                                                                         \
                                                                              \
    _api int _aname##_copy(const _atype *array,                               \
                           size_t index,                                      \
                           size_t count,                                      \
                           _etype *data2,                                     \
                           size_t dlen2) {                                    \
        CBASE_DELEGATE(_dname##_copy(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     count,                                   \
                                     data2,                                   \
                                     dlen2));                                 \
    }                                                                         \
                                                                              \
    _api bool _aname##_equals_no_check(const _atype *array,                   \
                                       size_t index,                          \
                                       const _etype *data2,                   \
                                       size_t dlen2) {                        \
        CBASE_DELEGATE(                                                       \
            _dname##_equals_no_check(array->data, index, data2, dlen2));      \
    }                                                                         \
                                                                              \
    _api int _aname##_equals(const _atype *array,                             \
                             size_t index,                                    \
                             const _etype *data2,                             \
                             size_t dlen2,                                    \
                             bool *equal) {                                   \
        CBASE_DELEGATE(_dname##_equals(array->data,                           \
                                       array->len,                            \
                                       index,                                 \
                                       data2,                                 \
                                       dlen2,                                 \
                                       equal));                               \
    }                                                                         \
                                                                              \
    _api bool _aname##_starts_with_no_check(const _atype *array,              \
                                            const _etype *data2,              \
                                            size_t dlen2) {                   \
        CBASE_DELEGATE(                                                       \
            _dname##_starts_with_no_check(array->data, data2, dlen2));        \
    }                                                                         \
                                                                              \
    _api int _aname##_starts_with(const _atype *array,                        \
                                  const _etype *data2,                        \
                                  size_t dlen2,                               \
                                  bool *equal) {                              \
        CBASE_DELEGATE(_dname##_starts_with(array->data,                      \
                                            array->len,                       \
                                            data2,                            \
                                            dlen2,                            \
                                            equal));                          \
    }                                                                         \
                                                                              \
    _api bool _aname##_ends_with_no_check(const _atype *array,                \
                                          const _etype *data2,                \
                                          size_t dlen2) {                     \
        CBASE_DELEGATE(_dname##_ends_with_no_check(array->data,               \
                                                   array->len,                \
                                                   data2,                     \
                                                   dlen2));                   \
    }                                                                         \
                                                                              \
    _api int _aname##_ends_with(const _atype *array,                          \
                                const _etype *data2,                          \
                                size_t dlen2,                                 \
                                bool *equal) {                                \
        CBASE_DELEGATE(_dname##_ends_with(array->data,                        \
                                          array->len,                         \
                                          data2,                              \
                                          dlen2,                              \
                                          equal));                            \
    }                                                                         \
                                                                              \
    _api void _aname##_find_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     const _etype *data2,                     \
                                     size_t dlen2,                            \
                                     _etype **cursor) {                       \
        _dname##_find_no_check(array->data,                                   \
                               array->len,                                    \
                               index,                                         \
                               data2,                                         \
                               dlen2,                                         \
                               cursor);                                       \
    }                                                                         \
                                                                              \
    _api int _aname##_find(const _atype *array,                               \
                           size_t index,                                      \
                           const _etype *data2,                               \
                           size_t dlen2,                                      \
                           _etype **cursor) {                                 \
        CBASE_DELEGATE(_dname##_find(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     data2,                                   \
                                     dlen2,                                   \
                                     cursor));                                \
    }                                                                         \
                                                                              \
    _api void _aname##_find_index_no_check(const _atype *array,               \
                                           size_t index,                      \
                                           const _etype *data2,               \
                                           size_t dlen2,                      \
                                           size_t *location) {                \
        _dname##_find_index_no_check(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     data2,                                   \
                                     dlen2,                                   \
                                     location);                               \
    }                                                                         \
                                                                              \
    _api int _aname##_find_index(const _atype *array,                         \
                                 size_t index,                                \
                                 const _etype *data2,                         \
                                 size_t dlen2,                                \
                                 size_t *location) {                          \
        CBASE_DELEGATE(_dname##_find_index(array->data,                       \
                                           array->len,                        \
                                           index,                             \
                                           data2,                             \
                                           dlen2,                             \
                                           location));                        \
    }

#endif
