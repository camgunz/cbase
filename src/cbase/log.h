#pragma once

#ifndef _CBASE_LOG_H__
#define _CBASE_LOG_H__

#include "cbase/internal.h"
#include "cbase/logbase.h"

#ifdef CBASE_DEFAULT_LOGGER
#include "cbase/default_log.h"
#endif

#ifdef CBASE_INTERNAL_LOGGER
#include "cbase/internal_log.h"
#endif

#ifdef CBASE_LOGGER
#include "cbase/cbase_log.h"
#endif

#endif

/* vi: set et ts=4 sw=4: */
