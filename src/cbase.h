#pragma once

#ifndef CBASE_H__
#define CBASE_H__

#ifdef _WIN32
#define UNICODE
#endif

#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "cbase/status.h"
#include "cbase/errors.h"
#include "cbase/util.h"
#include "cbase/types.h"
#include "cbase/swap.h"
#include "cbase/log.h"
#include "cbase/rune.h"
#include "cbase/charset.h"

#include "cbase/utf8.h"

#include "cbase/alloc.h"
#include "cbase/array.h"
#include "cbase/hash.h"
#include "cbase/list.h"
#include "cbase/parray.h"
#include "cbase/slice.h"
#include "cbase/buffer.h"
#include "cbase/strbase.h"
#include "cbase/sslice.h"
#include "cbase/str.h"
#include "cbase/table.h"

#include "cbase/file.h"

#endif

/* vi: set et ts=4 sw=4: */
