#ifndef FORMAT_H__
#define FORMAT_H__

#include <iostream>
#include <iomanip>

#include "stats.h"

enum FormatType {
  FORMAT_JSON,
  FORMAT_CSV,
  FORMAT_TEXT
};

class Formatter {
 public:
  Formatter(std::ostream* stream) : stream_(stream) {}
  virtual ~Formatter() {}
  virtual void EmitStats(const Stats& stats) = 0;
  std::ostream* stream() { return stream_; }
  static Formatter* Create(FormatType format);
 private:
  std::ostream* stream_;
};

#endif // FORMAT_H__
