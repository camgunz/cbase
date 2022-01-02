#pragma once

#ifndef _CBASE_ARRAY_OWNERSHIP_MANAGEMENT_H__
#define _CBASE_ARRAY_OWNERSHIP_MANAGEMENT_H__

#define CBASE_ARRAY_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api,                      \
                                                   _aname,                    \
                                                   _atype,                    \
                                                   _etype,                    \
                                                   _dname)                    \
    _api int _aname##_ensure_capacity_no_zero(_atype *array, size_t cap);     \
                                                                              \
    _api int _aname##_ensure_capacity(_atype *array, size_t cap);             \
                                                                              \
    _api int _aname##_set_length_no_zero_no_check(_atype *array, size_t len); \
                                                                              \
    _api int _aname##_set_length_no_zero(_atype *array, size_t len);          \
                                                                              \
    _api int _aname##_set_length_no_check(_atype *array, size_t len);         \
                                                                              \
    _api int _aname##_set_length(_atype *array, size_t len);

#endif
