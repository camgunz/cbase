#pragma once

#ifndef _CBASE_ARRAY_MANAGEMENT_H__
#define _CBASE_ARRAY_MANAGEMENT_H__

#define CBASE_ARRAY_MANAGEMENT_IMPL_DECL(_api,                                \
                                         _aname,                              \
                                         _atype,                              \
                                         _etype,                              \
                                         _dname)                              \
    _api void _aname##_assign_no_check(_atype *array,                         \
                                       _etype *elements,                      \
                                       size_t element_count);                 \
                                                                              \
    _api int _aname##_assign(_atype *array,                                   \
                             _etype *elements, size_t element_count);

#endif
