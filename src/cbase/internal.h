#pragma once

#ifndef _CBASE_INTERNAL_H__
#define _CBASE_INTERNAL_H__

#include <stdint.h>
#include <stdlib.h>

#define CBASE_LOG_DEFAULT              20003
#define CBASE_LOG_STDERR               20004
#define CBASE_LOG_CUSTOM               20005
#define CBASE_LOG_LEVEL_RUNTIME        20006
#define CBASE_ERROR_LEVEL_DEFAULTS     20007
#define CBASE_ERROR_LEVEL_CONFIGURABLE 20008
#define CBASE_ERRORS_CONFIGURABLE      20009
#define CBASE_FLATTEN_FUNCTIONS        20010
#define CBASE_INLINE_FUNCTIONS         20011
#define CBASE_NORMAL_INLINE_FUNCTIONS  20012
#define CBASE_NEVER_INLINE_FUNCTIONS   20013

#ifdef CBASE_HAVE_CONFIG_H
#include "cbase_config.h"
#endif

#ifdef HAVE_128BIT_INTEGERS
__extension__ typedef __int128 int128_t;
__extension__ typedef unsigned __int128 uint128_t;
#endif

#ifdef HAVE_FORMAT_FUNCTION_ATTRIBUTE
#define CBASE_PRINTF(format_arg, args_arg)                                    \
    __attribute__((format(printf, format_arg, args_arg)))

#define CBASE_VPRINTF(format_arg)                                             \
    __attribute__((format(printf, format_arg, 0)))
#else
#define CBASE_PRINTF(format_arg, args_arg)
#define CBASE_VPRINTF(format_arg)
#endif

#ifdef HAVE_FLATTEN_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_FLATTEN __attribute__((flatten))
#else
#define CBASE_ATTR_FLATTEN
#endif

#ifdef HAVE_UNUSED_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_UNUSED __attribute__((unused))
#else
#define CBASE_ATTR_UNUSED
#endif

#ifdef HAVE_NOINLINE_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_NOINLINE __attribute__((noinline))
#else
#define CBASE_ATTR_NOINLINE
#endif

#ifdef HAVE_MALLOC_FUNCTION_ATTRIBUTE
/*
 * GCC's malloc attribute will accept a deallocator and an allocated pointer
 * parameter index; but Clang's doesn't, and there's no way to check for it
 * without checking explicitly for GCC.  Therefore, just stick w/ no arguments
 * for now
 */
#define CBASE_ATTR_MALLOC(_dealloc, _pidx) __attribute__((malloc))
#else
#define CBASE_ATTR_MALLOC(_dealloc, _pidx)
#endif

#ifdef HAVE_NONNULL_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_NONNULL(...) __attribute__((nonnull (__VA_ARGS__)))
#endif

#ifdef HAVE_RETURNS_NONNULL_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_RETURNS_NONNULL __attribute__((returns_nonnull))
#endif

#ifdef HAVE_WARN_UNUSED_RESULT_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#endif

/*
 * [TODO]
 * - Figure out how to use warn_unused_result. It only makes sense on functions
 *   that return a value, but we don't have a function preamble only for those
 *   just now.
 */

#define CBASE_API
#define CBASE_API_MALLOC CBASE_ATTR_MALLOC
#define CBASE_API_DEALLOC
#define CBASE_TMPL_API

#if CBASE_INLINING == CBASE_FLATTEN_FUNCTIONS
#define CBASE_API_ATTRS
#define CBASE_API_STATIC static inline CBASE_ATTR_FLATTEN CBASE_ATTR_UNUSED
#define CBASE_TMPL_API_STATIC CBASE_ATTR_FLATTEN CBASE_ATTR_UNUSED
#elif CBASE_INLINING == CBASE_INLINE_FUNCTIONS
#define CBASE_API_ATTRS
#define CBASE_API_STATIC static inline CBASE_ATTR_UNUSED
#define CBASE_TMPL_API_STATIC CBASE_ATTR_UNUSED
#elif CBASE_INLINING == CBASE_NEVER_INLINE_FUNCTIONS
#define CBASE_API_ATTRS CBASE_ATTR_NOINLINE
#define CBASE_API_STATIC static inline CBASE_ATTR_UNUSED CBASE_ATTR_NOINLINE
#define CBASE_TMPL_API_STATIC CBASE_ATTR_UNUSED CBASE_ATTR_NOINLINE
#endif

#define CBASE_TMPL_SCOPE_NORMAL
#define CBASE_TMPL_SCOPE_STATIC static

/*
#ifdef _WIN32
#define UNICODE
#endif
*/

#endif
