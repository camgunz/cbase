#pragma once

#ifndef __TIMING_H
#define __TIMING_H

#include <stdint.h>

typedef void FuncType(void);

double time_func(FuncType func, unsigned int run_count);

#endif
