#include "timer.h"

#include <mach/mach.h>
#include <mach/mach_time.h>
#include <CoreServices/CoreServices.h>

Timer::Timer() : start_time_(mach_absolute_time()) {
}

double Timer::GetElapsed() {
  uint64_t elapsed = mach_absolute_time() - start_time_;
  Nanoseconds nanos = AbsoluteToNanoseconds(*(AbsoluteTime*)&elapsed);
  return (*(uint64_t*)&nanos) / 1000000.0;
}
