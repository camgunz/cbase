#pragma once

#ifndef _CBASE_ARRAY_SLICE_MUTATIONS_H__
#define _CBASE_ARRAY_SLICE_MUTATIONS_H__

#define CBASE_ARRAY_SLICE_MUTATIONS_IMPL_DECL(_api,                           \
                                              _aname,                         \
                                              _atype,                         \
                                              _etype,                         \
                                              _dname)                         \
    _api void _aname##_skip_no_check(_atype *array, size_t count);            \
                                                                              \
    _api int _aname##_skip(_atype *array, size_t count);                      \
                                                                              \
    _api void _aname##_seek_no_check(_atype *array,                           \
                                     const _etype *elements,                  \
                                     size_t element_count);                   \
                                                                              \
    _api int _aname##_seek(_atype *array,                                     \
                           const _etype *elements,                            \
                           size_t element_count);

#define CBASE_ARRAY_SLICE_MUTATIONS_IMPL(_api,                                \
                                         _aname,                              \
                                         _atype,                              \
                                         _etype,                              \
                                         _dname)                              \
    _api void _aname##_skip_no_check(_atype *array, size_t count) {           \
        _dname##_skip_no_check(&array->data, &array->len, count);             \
    }                                                                         \
                                                                              \
    _api int _aname##_skip(_atype *array, size_t count) {                     \
        CBASE_DELEGATE(_dname##_skip(&array->data, &array->len, count));      \
    }                                                                         \
                                                                              \
    _api void _aname##_seek_no_check(_atype *array,                           \
                                     const _etype *elements,                  \
                                     size_t element_count) {                  \
        _dname##_seek_no_check(&array->data,                                  \
                               &array->len,                                   \
                               elements,                                      \
                               element_count);                                \
    }                                                                         \
                                                                              \
    _api int _aname##_seek(_atype *array,                                     \
                           const _etype *elements,                            \
                           size_t element_count) {                            \
        CBASE_DELEGATE(_dname##_seek(&array->data,                            \
                                     &array->len,                             \
                                     elements,                                \
                                     element_count));                         \
    }

#endif
