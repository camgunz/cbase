#pragma once

#ifndef _CBASE_ARRAY_H__
#define _CBASE_ARRAY_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/errors.h"
#include "cbase/util.h"

/*
 * [TODO]
 * - Rebase on readable/writable/dynamic_data
 */

#define CBASE_ARRAY_IMPL(_atype, _aname, _etype)                               \
    CBASE_ARRAY_BASE_IMPL(CBASE_IMPL_NORMAL, _atype, _aname, _etype)

#define CBASE_ARRAY_STATIC_IMPL(_atype, _aname, _etype)                        \
    CBASE_ARRAY_BASE_IMPL(CBASE_IMPL_STATIC, _atype, _aname, _etype)

#define CBASE_ARRAY_STATIC_DEF(_atype, _aname, _etype)                         \
    CBASE_ARRAY_DECL(_atype, _etype)                                           \
    CBASE_ARRAY_STATIC_IMPL(_atype, _aname, _etype)

#endif

/* vi: set et ts=4 sw=4: */
