#ifndef TIMER_H__
#define TIMER_H__

#include <memory>

class Timer {
 public:
  Timer();

  double GetElapsed();

 private:
  uint64_t start_time_;
};

#endif // TIMER_H__
