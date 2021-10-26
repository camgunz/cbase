#pragma once

#ifndef _CBASE_ARRAY_H__
#define _CBASE_ARRAY_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_ARRAY_SLICE_DECL(_stype, _etype)                                \
    typedef struct _stype##Struct {                                           \
        size_t len;                                                           \
        _etype *data;                                                         \
    } _stype;

#define CBASE_STATIC_ARRAY_DECL(_atype, _etype, _acap)                        \
    typedef struct _atype##Struct {                                           \
        size_t len;                                                           \
        _etype data[_acap];                                                   \
    } _atype;

#define CBASE_DYNAMIC_ARRAY_DECL(_atype, _etype)                              \
    typedef struct _atype##Struct {                                           \
        size_t cap;                                                           \
        size_t len;                                                           \
        _etype *data;                                                         \
    } _atype;

#endif
