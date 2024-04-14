#pragma once

#ifndef _CBASE_ARRAY_H__
#define _CBASE_ARRAY_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checked_math.h"
#include "cbase/checks.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#include "cbase/data.h"
#include "cbase/data_base.h"
#include "cbase/data_dynamic_management.h"
#include "cbase/data_dynamic_mutations.h"
#include "cbase/data_management.h"
#include "cbase/data_mutations.h"
#include "cbase/data_ownership_management.h"
#include "cbase/data_slice_mutations.h"
#include "cbase/data_static_management.h"
#include "cbase/data_static_mutations.h"
#include "cbase/array_base.h"
#include "cbase/array_dynamic_management.h"
#include "cbase/array_dynamic_mutations.h"
#include "cbase/array_management.h"
#include "cbase/array_mutations.h"
#include "cbase/array_ownership_management.h"
#include "cbase/array_slice_mutations.h"
#include "cbase/array_static_management.h"
#include "cbase/array_static_mutations.h"

#define CBASE_STATIC_ARRAY_DECL(_atype, _etype, _amaxcap)                     \
    typedef struct _atype##Struct {                                           \
        size_t len;                                                           \
        _etype const data[_amaxcap];                                          \
    } _atype;

#define CBASE_MUTABLE_STATIC_ARRAY_DECL(_atype, _etype, _amaxcap)             \
    typedef struct _atype##Struct {                                           \
        size_t len;                                                           \
        _etype data[_amaxcap];                                                \
    } _atype;

#define CBASE_DYNAMIC_ARRAY_DECL(_atype, _etype)                              \
    typedef struct _atype##Struct {                                           \
        size_t cap;                                                           \
        size_t len;                                                           \
        _etype const *data;                                                   \
    } _atype;

#define CBASE_MUTABLE_DYNAMIC_ARRAY_DECL(_atype, _etype)                      \
    typedef struct _atype##Struct {                                           \
        size_t cap;                                                           \
        size_t len;                                                           \
        _etype *data;                                                         \
    } _atype;

#define CBASE_ARRAY_SLICE_DECL(_atype, _etype)                                \
    typedef struct _atype##Struct {                                           \
        size_t len;                                                           \
        _etype const *data;                                                   \
    } _atype;

#define CBASE_MUTABLE_ARRAY_SLICE_DECL(_atype, _etype)                        \
    typedef struct _atype##Struct {                                           \
        size_t len;                                                           \
        _etype *data;                                                         \
    } _atype;

#define CBASE_STATIC_ARRAY_IMPL_DECL(_api,                                    \
                                     _aname,                                  \
                                     _atype,                                  \
                                     _etype,                                  \
                                     _dname,                                  \
                                     _amaxcap)                                \
    CBASE_STATIC_DATA_IMPL_DECL(_api, _dname, _etype, _amaxcap)               \
    CBASE_ARRAY_BASE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_MANAGEMENT_IMPL_DECL(_api, _aname, _atype, _etype, _dname)    \
    CBASE_ARRAY_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api,                          \
                                               _aname,                        \
                                               _atype,                        \
                                               _etype,                        \
                                               _dname)                        \
    CBASE_ARRAY_STATIC_MANAGEMENT_IMPL_DECL(_api,                             \
                                            _aname,                           \
                                            _atype,                           \
                                            _etype,                           \
                                            _dname,                           \
                                            _amaxcap)

#define CBASE_STATIC_ARRAY_IMPL(_api,                                         \
                                _aname,                                       \
                                _atype,                                       \
                                _etype,                                       \
                                _dname,                                       \
                                _amaxcap)                                     \
    CBASE_STATIC_DATA_IMPL(_api, _dname, _etype, _amaxcap)                    \
    CBASE_ARRAY_BASE_IMPL(_api, _aname, _atype, _etype, _dname)               \
    CBASE_ARRAY_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api,                          \
                                               _aname,                        \
                                               _atype,                        \
                                               _etype,                        \
                                               _dname)                        \
    CBASE_ARRAY_STATIC_MANAGEMENT_IMPL(_api,                                  \
                                       _aname,                                \
                                       _atype,                                \
                                       _etype,                                \
                                       _dname,                                \
                                       _amaxcap)

#define CBASE_STATIC_ARRAY_DEF(_api,                                          \
                               _aname,                                        \
                               _atype,                                        \
                               _etype,                                        \
                               _dname,                                        \
                               _amaxcap)                                      \
    CBASE_STATIC_ARRAY_DECL(_atype, _etype, _amaxcap)                         \
    CBASE_STATIC_ARRAY_IMPL_DECL(_api,                                        \
                                 _aname,                                      \
                                 _atype,                                      \
                                 _etype,                                      \
                                 _dname,                                      \
                                 _amaxcap)                                    \
    CBASE_STATIC_ARRAY_IMPL(_api, _aname, _atype, _etype, _dname, _amaxcap)

#define CBASE_MUTABLE_STATIC_ARRAY_IMPL_DECL(_api,                            \
                                             _aname,                          \
                                             _atype,                          \
                                             _etype,                          \
                                             _dname,                          \
                                             _amaxcap)                        \
    CBASE_MUTABLE_STATIC_DATA_IMPL_DECL(_api, _dname, _etype, _amaxcap)       \
    CBASE_ARRAY_BASE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_MANAGEMENT_IMPL_DECL(_api, _aname, _atype, _etype, _dname)    \
    CBASE_ARRAY_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api,                          \
                                               _aname,                        \
                                               _atype,                        \
                                               _etype,                        \
                                               _dname)                        \
    CBASE_ARRAY_STATIC_MANAGEMENT_IMPL_DECL(_api,                             \
                                            _aname,                           \
                                            _atype,                           \
                                            _etype,                           \
                                            _dname,                           \
                                            _amaxcap)                         \
    CBASE_ARRAY_MUTATIONS_IMPL_DECL(_api, _aname, _atype, _etype, _dname)     \
    CBASE_ARRAY_STATIC_MUTATIONS_IMPL_DECL(_api,                              \
                                           _aname,                            \
                                           _atype,                            \
                                           _etype,                            \
                                           _dname,                            \
                                           _amaxcap)

#define CBASE_MUTABLE_STATIC_ARRAY_IMPL(_api,                                 \
                                        _aname,                               \
                                        _atype,                               \
                                        _etype,                               \
                                        _dname,                               \
                                        _amaxcap)                             \
    CBASE_MUTABLE_STATIC_DATA_IMPL(_api, _dname, _etype, _amaxcap)            \
    CBASE_ARRAY_BASE_IMPL(_api, _aname, _atype, _etype, _dname)               \
    CBASE_ARRAY_STATIC_MANAGEMENT_IMPL(_api,                                  \
                                       _aname,                                \
                                       _atype,                                \
                                       _etype,                                \
                                       _dname,                                \
                                       _amaxcap)                              \
    CBASE_ARRAY_MUTATIONS_IMPL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_STATIC_MUTATIONS_IMPL(_api,                                   \
                                      _aname,                                 \
                                      _atype,                                 \
                                      _etype,                                 \
                                      _dname,                                 \
                                      _amaxcap)

#define CBASE_MUTABLE_STATIC_ARRAY_DEF(_api,                                  \
                                       _aname,                                \
                                       _atype,                                \
                                       _etype,                                \
                                       _dname,                                \
                                       _amaxcap)                              \
    CBASE_MUTABLE_STATIC_ARRAY_DECL(_atype, _etype, _amaxcap)                 \
    CBASE_MUTABLE_STATIC_ARRAY_IMPL_DECL(_api,                                \
                                         _aname,                              \
                                         _atype,                              \
                                         _etype,                              \
                                         _dname,                              \
                                         _amaxcap)                            \
    CBASE_MUTABLE_STATIC_ARRAY_IMPL(_api,                                     \
                                    _aname,                                   \
                                    _atype,                                   \
                                    _etype,                                   \
                                    _dname,                                   \
                                    _amaxcap)

#define CBASE_DYNAMIC_ARRAY_IMPL_DECL(_api, _aname, _atype, _etype, _dname)   \
    CBASE_DYNAMIC_DATA_IMPL_DECL(_api, _dname, _etype)                        \
    CBASE_ARRAY_BASE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_MANAGEMENT_IMPL_DECL(_api, _aname, _atype, _etype, _dname)    \
    CBASE_ARRAY_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api,                          \
                                               _aname,                        \
                                               _atype,                        \
                                               _etype,                        \
                                               _dname)                        \
    CBASE_ARRAY_DYNAMIC_MANAGEMENT_IMPL_DECL(_api,                            \
                                             _aname,                          \
                                             _atype,                          \
                                             _etype,                          \
                                             _dname)

#define CBASE_DYNAMIC_ARRAY_IMPL(_api, _aname, _atype, _etype, _dname)        \
    CBASE_DYNAMIC_DATA_IMPL(_api, _dname, _etype)                             \
    CBASE_ARRAY_BASE_IMPL(_api, _aname, _atype, _etype, _dname)               \
    CBASE_ARRAY_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api,                          \
                                               _aname,                        \
                                               _atype,                        \
                                               _etype,                        \
                                               _dname)                        \
    CBASE_ARRAY_DYNAMIC_MANAGEMENT_IMPL(_api, _aname, _atype, _etype, _dname)

#define CBASE_DYNAMIC_ARRAY_DEF(_api, _aname, _atype, _etype, _dname)         \
    CBASE_DYNAMIC_ARRAY_DECL(_atype, _etype)                                  \
    CBASE_DYNAMIC_ARRAY_IMPL_DECL(_api, _aname, _atype, _etype, _dname)       \
    CBASE_DYNAMIC_ARRAY_IMPL(_api, _aname, _atype, _etype, _dname)

#define CBASE_MUTABLE_DYNAMIC_ARRAY_IMPL_DECL(_api,                           \
                                              _aname,                         \
                                              _atype,                         \
                                              _etype,                         \
                                              _dname)                         \
    CBASE_MUTABLE_DYNAMIC_DATA_IMPL_DECL(_api, _dname, _etype)                \
    CBASE_ARRAY_BASE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_MANAGEMENT_IMPL_DECL(_api, _aname, _atype, _etype, _dname)    \
    CBASE_ARRAY_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api,                          \
                                               _aname,                        \
                                               _atype,                        \
                                               _etype,                        \
                                               _dname)                        \
    CBASE_ARRAY_DYNAMIC_MANAGEMENT_IMPL_DECL(_api,                            \
                                             _aname,                          \
                                             _atype,                          \
                                             _etype,                          \
                                             _dname)                          \
    CBASE_ARRAY_MUTATIONS_IMPL_DECL(_api, _aname, _atype, _etype, _dname)     \
    CBASE_ARRAY_DYNAMIC_MUTATIONS_IMPL_DECL(_api,                             \
                                            _aname,                           \
                                            _atype,                           \
                                            _etype,                           \
                                            _dname)

#define CBASE_MUTABLE_DYNAMIC_ARRAY_IMPL(_api,                                \
                                         _aname,                              \
                                         _atype,                              \
                                         _etype,                              \
                                         _dname)                              \
    CBASE_MUTABLE_DYNAMIC_DATA_IMPL(_api, _dname, _etype)                     \
    CBASE_ARRAY_BASE_IMPL(_api, _aname, _atype, _etype, _dname)               \
    CBASE_ARRAY_DYNAMIC_MANAGEMENT_IMPL(_api, _aname, _atype, _etype, _dname) \
    CBASE_ARRAY_MUTATIONS_IMPL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_DYNAMIC_MUTATIONS_IMPL(_api, _aname, _atype, _etype, _dname)

#define CBASE_MUTABLE_DYNAMIC_ARRAY_DEF(_api, _aname, _atype, _etype, _dname) \
    CBASE_MUTABLE_DYNAMIC_ARRAY_DECL(_atype, _etype)                          \
    CBASE_MUTABLE_DYNAMIC_ARRAY_IMPL_DECL(_api,                               \
                                          _aname,                             \
                                          _atype,                             \
                                          _etype,                             \
                                          _dname)                             \
    CBASE_MUTABLE_DYNAMIC_ARRAY_IMPL(_api, _aname, _atype, _etype, _dname)

#define CBASE_ARRAY_SLICE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)     \
    CBASE_DATA_SLICE_IMPL_DECL(_api, _dname, _etype)                          \
    CBASE_ARRAY_BASE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_MANAGEMENT_IMPL_DECL(_api, _aname, _atype, _etype, _dname)

#define CBASE_ARRAY_SLICE_IMPL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_DATA_SLICE_IMPL(_api, _dname, _etype)                               \
    CBASE_ARRAY_BASE_IMPL(_api, _aname, _atype, _etype, _dname)

#define CBASE_ARRAY_SLICE_DEF(_api, _aname, _atype, _etype, _dname)           \
    CBASE_ARRAY_SLICE_DECL(_atype, _etype)                                    \
    CBASE_ARRAY_SLICE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)         \
    CBASE_ARRAY_SLICE_IMPL(_api, _aname, _atype, _etype, _dname)

#define CBASE_MUTABLE_ARRAY_SLICE_IMPL_DECL(_api,                             \
                                            _aname,                           \
                                            _atype,                           \
                                            _etype,                           \
                                            _dname)                           \
    CBASE_MUTABLE_DATA_SLICE_IMPL_DECL(_api, _dname, _etype)                  \
    CBASE_ARRAY_BASE_IMPL_DECL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_MANAGEMENT_IMPL_DECL(_api, _aname, _atype, _etype, _dname)    \
    CBASE_ARRAY_MUTATIONS_IMPL_DECL(_api, _aname, _atype, _etype, _dname)     \
    CBASE_ARRAY_SLICE_MUTATIONS_IMPL_DECL(_api, _aname, _atype, _etype, _dname)

#define CBASE_MUTABLE_ARRAY_SLICE_IMPL(_api, _aname, _atype, _etype, _dname)  \
    CBASE_MUTABLE_DATA_SLICE_IMPL(_api, _dname, _etype)                       \
    CBASE_ARRAY_BASE_IMPL(_api, _aname, _atype, _etype, _dname)               \
    CBASE_ARRAY_MANAGEMENT_IMPL_DECL(_api, _aname, _atype, _etype, _dname)    \
    CBASE_ARRAY_MUTATIONS_IMPL(_api, _aname, _atype, _etype, _dname)          \
    CBASE_ARRAY_SLICE_MUTATIONS_IMPL_DECL(_api, _aname, _atype, _etype, _dname)

#define CBASE_MUTABLE_ARRAY_SLICE_DEF(_api, _aname, _atype, _etype, _dname)   \
    CBASE_MUTABLE_ARRAY_SLICE_DECL(_atype, _etype)                            \
    CBASE_MUTABLE_ARRAY_SLICE_IMPL_DECL(_api, _aname, _atype, _etype, _dname) \
    CBASE_MUTABLE_ARRAY_SLICE_IMPL(_api, _aname, _atype, _etype, _dname)

#endif
