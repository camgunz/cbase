#include "timing.h"

#ifdef HAVE_CLOCK_MONOTONIC
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double time_func(FuncType func, unsigned int run_count) {
  struct timespec start = { 0 };
  struct timespec end = { 0 };
  int err = 0;

  err = clock_gettime(CLOCK_MONOTONIC, &start);
  if (err != 0) {
    fprintf(stderr, "Error getting start time: %s\n", strerror(errno));
    exit(-1);
  }

  for (unsigned int i = 0; i < run_count; i++) {
    func();
  }

  err = clock_gettime(CLOCK_MONOTONIC, &end);
  if (err != 0) {
    fprintf(stderr, "Error getting end time: %s\n", strerror(errno));
    exit(-1);
  }

  return (
    ((double)(end.tv_sec - start.tv_sec)) +
    (((double)(end.tv_nsec - start.tv_nsec)) / 1000000000.0)
  ) / (double)run_count;
}
#else
#include <mach/mach_time.h>

double time_func(FuncType func, unsigned int run_count) {
  static mach_timebase_info_data_t timebase_info = { 0 };

  uint64_t start = mach_absolute_time();

  for (unsigned int i = 0; i < run_count; i++) {
    func();
  }

  uint64_t end = mach_absolute_time();
  uint64_t elapsed = end - start;

  if (timebase_info.denom == 0) {
    (void)mach_timebase_info(&timebase_info);
  }

  return (
      (
          (double)elapsed *
          (double)timebase_info.numer /
          (double)timebase_info.denom
      ) /
      (double)run_count
  );
}
#endif
