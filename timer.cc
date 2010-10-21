#include "timer.h"

#if defined(__APPLE__)
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

#else

#include <stdint.h>
#include <time.h>

namespace {

uint64_t Now() {
  struct timespec ts = {0};
  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) != 0)
    return 0.0; // TODO(knorton): Handle this better.
  return static_cast<int64_t>(ts.tv_sec) * Timer::kMicrosecondsPerSecond +
      (static_cast<int64_t>(ts.tv_nsec) / Timer::kNanosecondsPerMicrosecond);
}

} // namespace

Timer::Timer() : start_time_(Now()) {
}

double Timer::GetElapsed() {
  return (Now() - start_time_) / Timer::kMillisecondsPerSecond;
}

#endif
