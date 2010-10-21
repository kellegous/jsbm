#ifndef TIMER_H__
#define TIMER_H__

#include <memory>
#include <stdint.h>

class Timer {
 public:
  static const int64_t kMillisecondsPerSecond = 1000;
  static const int64_t kMicrosecondsPerMillisecond = 1000;
  static const int64_t kMicrosecondsPerSecond = kMicrosecondsPerMillisecond *
                                              kMillisecondsPerSecond;
  static const int64_t kMicrosecondsPerMinute = kMicrosecondsPerSecond * 60; 
  static const int64_t kMicrosecondsPerHour = kMicrosecondsPerMinute * 60; 
  static const int64_t kMicrosecondsPerDay = kMicrosecondsPerHour * 24; 
  static const int64_t kMicrosecondsPerWeek = kMicrosecondsPerDay * 7;
  static const int64_t kNanosecondsPerMicrosecond = 1000;
  static const int64_t kNanosecondsPerSecond = kNanosecondsPerMicrosecond *
                                             kMicrosecondsPerSecond;
  Timer();

  double GetElapsed();

 private:
  uint64_t start_time_;
};

#endif // TIMER_H__
