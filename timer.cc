#include "timer.h"

#if defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <CoreServices/CoreServices.h>
#else
#include <stdint.h>
#include <time.h>
#endif

namespace {

uint64_t ThreadNow() {
#if defined(__APPLE__)
  mach_msg_type_number_t infoCount = THREAD_BASIC_INFO_COUNT;
  thread_basic_info_data_t info;
  mach_port_t threadPort = mach_thread_self();
  if (thread_info(threadPort, THREAD_BASIC_INFO,
      reinterpret_cast<thread_info_t>(&info), &infoCount) != KERN_SUCCESS) {
    // TODO(knorton): Handle this better.
    return 0;
  }
  mach_port_deallocate(mach_task_self(), threadPort);
  return (static_cast<int64_t>(info.user_time.seconds) * Timer::kMicrosecondsPerSecond)
      + static_cast<int64_t>(info.user_time.microseconds)
      + (static_cast<int64_t>(info.system_time.seconds) * Timer::kMicrosecondsPerSecond)
      + static_cast<int64_t>(info.system_time.microseconds);
#else
  struct timespec ts = {0};
  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) != 0)
    return 0.0; // TODO(knorton): Handle this better.
  return static_cast<int64_t>(ts.tv_sec) * Timer::kMicrosecondsPerSecond +
      (static_cast<int64_t>(ts.tv_nsec) / Timer::kNanosecondsPerMicrosecond);
#endif
}

} // namespace

Timer::Timer() : start_time_(ThreadNow()) {
}

double Timer::GetElapsed() {
  return (ThreadNow() - start_time_) / Timer::kMillisecondsPerSecond;
}
