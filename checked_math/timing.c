#include <mach/mach_time.h>
#include "timing.h"

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
