#ifndef _CBASE_ARRAY_STATIC_MUTATIONS_H__
#define _CBASE_ARRAY_STATIC_MUTATIONS_H__

#define CBASE_ARRAY_STATIC_MUTATIONS_IMPL_DECL(_api,                          \
                                               _aname,                        \
                                               _atype,                        \
                                               _etype,                        \
                                               _dname)                        \
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
    _api _etype *_aname##_insert_slot_no_zero_no_check(_atype *array,         \
                                                       size_t index);         \
                                                                              \
    _api int _aname##_insert_slot_no_zero(_atype *array,                      \
                                          size_t index,                       \
                                          _etype **new_slot);                 \
                                                                              \
    _api _etype *_aname##_insert_slot_no_check(_atype *array, size_t index);  \
                                                                              \
    _api int _aname##_insert_slot(_atype *array,                              \
                                  size_t index,                               \
                                  _etype **new_slot);                         \
                                                                              \
    _api void _aname##_insert_no_check(_atype *array,                         \
                                       size_t index,                          \
                                       const _etype *elements,                \
                                       size_t element_count);                 \
                                                                              \
    _api int _aname##_insert(_atype *array,                                   \
                             size_t index,                                    \
                             const _etype *elements,                          \
                             size_t element_count);                           \
                                                                              \
    _api _etype *_aname##_prepend_slot_no_zero_no_check(_atype *array);       \
                                                                              \
    _api int _aname##_prepend_slot_no_zero(_atype *array, _etype **new_slot); \
                                                                              \
    _api _etype *_aname##_prepend_slot_no_check(_atype *array);               \
                                                                              \
    _api int _aname##_prepend_slot(_atype *array, _etype **new_slot);         \
                                                                              \
    _api void _aname##_prepend_no_check(_atype *array,                        \
                                        const _etype *elements,               \
                                        size_t element_count);                \
                                                                              \
    _api int _aname##_prepend(_atype *array,                                  \
                              const _etype *elements,                         \
                              size_t element_count);                          \
                                                                              \
    _api _etype *_aname##_append_slot_no_zero_no_check(_atype *array);        \
                                                                              \
    _api int _aname##_append_slot_no_zero(_atype *array, _etype **new_slot);  \
                                                                              \
    _api _etype *_aname##_append_slot_no_check(_atype *array);                \
                                                                              \
    _api int _aname##_append_slot(_atype *array, _etype **new_slot);          \
                                                                              \
    _api void _aname##_append_no_check(_atype *array,                         \
                                       const _etype *elements,                \
                                       size_t element_count);                 \
                                                                              \
    _api int _aname##_append(_atype *array,                                   \
                             const _etype *elements,                          \
                             size_t element_count);                           \
                                                                              \
    _api int _aname##_replace_no_zero(_atype *array,                          \
                                      size_t index,                           \
                                      const _etype *old_elements,             \
                                      size_t old_element_count,               \
                                      const _etype *new_elements,             \
                                      size_t new_element_count);              \
                                                                              \
    _api int _aname##_replace(_atype *array,                                  \
                              size_t index,                                   \
                              const _etype *old_elements,                     \
                              size_t old_element_count,                       \
                              const _etype *new_elements,                     \
                              size_t new_element_count);

#define CBASE_ARRAY_STATIC_MUTATIONS_IMPL(_api,                               \
                                          _aname,                             \
                                          _atype,                             \
                                          _etype,                             \
                                          _dname)                             \
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
        CBASE_DELEGATE(_dname##_move_right_no_zero(&array->data,              \
                                                   &array->len,               \
                                                   index,                     \
                                                   count));                   \
    }                                                                         \
                                                                              \
    _api void _aname##_move_right_no_check(_atype *array,                     \
                                           size_t index,                      \
                                           size_t count) {                    \
        _dname##_move_right_no_check(array->data, &array->len, index, count); \
    }                                                                         \
                                                                              \
    _api int _aname##_move_right(_atype *array, size_t index, size_t count) { \
        CBASE_DELEGATE(                                                       \
            _dname##_move_right(&array->data, &array->len, index, count));    \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_insert_slot_no_zero_no_check(_atype *array,         \
                                                       size_t index) {        \
        CBASE_DELEGATE(_dname##_insert_slot_no_zero_no_check(array->data,     \
                                                             &array->len,     \
                                                             index));         \
    }                                                                         \
                                                                              \
    _api int _aname##_insert_slot_no_zero(_atype *array,                      \
                                          size_t index,                       \
                                          _etype **new_slot) {                \
        CBASE_DELEGATE(_dname##_insert_slot_no_zero(&array->data,             \
                                                    &array->len,              \
                                                    index,                    \
                                                    new_slot));               \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_insert_slot_no_check(_atype *array, size_t index) { \
        CBASE_DELEGATE(                                                       \
            _dname##_insert_slot_no_check(array->data, &array->len, index));  \
    }                                                                         \
                                                                              \
    _api int _aname##_insert_slot(_atype *array,                              \
                                  size_t index,                               \
                                  _etype **new_slot) {                        \
        CBASE_DELEGATE(_dname##_insert_slot(&array->data,                     \
                                            &array->len,                      \
                                            index,                            \
                                            new_slot));                       \
    }                                                                         \
                                                                              \
    _api void _aname##_insert_no_check(_atype *array,                         \
                                       size_t index,                          \
                                       const _etype *elements,                \
                                       size_t element_count) {                \
        _dname##_insert_no_check(&array->data,                                \
                                 &array->len,                                 \
                                 index,                                       \
                                 elements,                                    \
                                 element_count);                              \
    }                                                                         \
                                                                              \
    _api int _aname##_insert(_atype *array,                                   \
                             size_t index,                                    \
                             const _etype *elements,                          \
                             size_t element_count) {                          \
        CBASE_DELEGATE(_dname##_insert(&array->data,                          \
                                       &array->len,                           \
                                       index,                                 \
                                       elements,                              \
                                       element_count));                       \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_prepend_slot_no_zero_no_check(_atype *array) {      \
        CBASE_DELEGATE(_dname##_prepend_slot_no_zero_no_check(array->data,    \
                                                              &array->len));  \
    }                                                                         \
                                                                              \
    _api int _aname##_prepend_slot_no_zero(_atype *array,                     \
                                           _etype **new_slot) {               \
        CBASE_DELEGATE(_dname##_prepend_slot_no_zero(&array->data,            \
                                                     &array->len,             \
                                                     new_slot));              \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_prepend_slot_no_check(_atype *array) {              \
        CBASE_DELEGATE(                                                       \
            _dname##_prepend_slot_no_check(array->data, &array->len));        \
    }                                                                         \
                                                                              \
    _api int _aname##_prepend_slot(_atype *array, _etype **new_slot) {        \
        CBASE_DELEGATE(                                                       \
            _dname##_prepend_slot(&array->len, &array->data, new_slot));      \
    }                                                                         \
                                                                              \
    _api void _aname##_prepend_no_check(_atype *array,                        \
                                        const _etype *elements,               \
                                        size_t element_count) {               \
        _dname##_prepend_no_check(array->data,                                \
                                  &array->len,                                \
                                  elements,                                   \
                                  element_count);                             \
    }                                                                         \
                                                                              \
    _api int _aname##_prepend(_atype *array,                                  \
                              const _etype *elements,                         \
                              size_t element_count) {                         \
        CBASE_DELEGATE(_dname##_prepend(&array->data,                         \
                                        &array->len,                          \
                                        elements,                             \
                                        element_count));                      \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_append_slot_no_zero_no_check(_atype *array) {       \
        CBASE_DELEGATE(                                                       \
            _dname##_append_slot_no_zero_no_check(array->data, &array->len)); \
    }                                                                         \
                                                                              \
    _api int _aname##_append_slot_no_zero(_atype *array, _etype **new_slot) { \
        CBASE_DELEGATE(_dname##_append_slot_no_zero(&array->data, new_slot)); \
    }                                                                         \
                                                                              \
    _api _etype *_aname##_append_slot_no_check(_atype *array) {               \
        CBASE_DELEGATE(                                                       \
            _dname##_append_slot_no_check(&array->data, &array->len));        \
    }                                                                         \
                                                                              \
    _api int _aname##_append_slot(_atype *array, _etype **new_slot) {         \
        CBASE_DELEGATE(                                                       \
            _dname##_append_slot(&array->data, &array->len, new_slot));       \
    }                                                                         \
                                                                              \
    _api void _aname##_append_no_check(_atype *array,                         \
                                       const _etype *elements,                \
                                       size_t element_count) {                \
        _dname##_append_no_check(array->data,                                 \
                                 &array->len,                                 \
                                 elements,                                    \
                                 element_count);                              \
    }                                                                         \
                                                                              \
    _api int _aname##_append(_atype *array,                                   \
                             const _etype *elements,                          \
                             size_t element_count) {                          \
        CBASE_DELEGATE(_dname##_append(&array->data,                          \
                                       &array->len,                           \
                                       elements,                              \
                                       element_count));                       \
    }                                                                         \
                                                                              \
    _api int _aname##_replace_no_zero(_atype *array,                          \
                                      size_t index,                           \
                                      const _etype *old_elements,             \
                                      size_t old_element_count,               \
                                      const _etype *new_elements,             \
                                      size_t new_element_count) {             \
        CBASE_DELEGATE(_dname##_replace_no_zero(&array->data,                 \
                                                &array->len,                  \
                                                index,                        \
                                                old_elements,                 \
                                                old_element_count,            \
                                                new_elements,                 \
                                                new_element_count));          \
    }                                                                         \
                                                                              \
    _api int _aname##_replace(_atype *array,                                  \
                              size_t index,                                   \
                              const _etype *old_elements,                     \
                              size_t old_element_count,                       \
                              const _etype *new_elements,                     \
                              size_t new_element_count) {                     \
        CBASE_DELEGATE(_dname##_replace(&array->data,                         \
                                        &array->len,                          \
                                        index,                                \
                                        old_elements,                         \
                                        old_element_count,                    \
                                        new_elements,                         \
                                        new_element_count));                  \
    }

#endif
