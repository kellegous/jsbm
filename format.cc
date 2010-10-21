#include "format.h"

namespace {

class TextFormatter : public Formatter {
 public:
  TextFormatter(std::ostream* stream) : Formatter(stream) {}
  void EmitStats(const Stats& stats) {
    std::ostream& s = *stream();
    s << std::setiosflags(std::ios::fixed) << std::setprecision(2)
      << stats.mean << "ms [" << stats.lower_bound << "ms <= mean <= "
      << stats.upper_bound << "ms]" << std::endl;
  }
};

class CsvFormatter : public Formatter {
 public:
  CsvFormatter(std::ostream* stream) : Formatter(stream) {}
  void EmitStats(const Stats& stats) {
    std::ostream& s = *stream();
    s << stats.mean << ", " << stats.lower_bound << ", " << stats.upper_bound
      << std::endl;
  }
};

// This formatter made a lot more sense when I had multiple engines.
class JsonFormatter : public Formatter {
 public:
  JsonFormatter(std::ostream* stream) : Formatter(stream) {}
  void EmitStats(const Stats& stats) {
    std::ostream& s = *stream();
    s << "{\"mean\" : " << stats.mean << ", \"lower\" : " << stats.lower_bound
      << ", \"upper\" : " << stats.upper_bound << "}" << std::endl;
  }
};

} // namespace

Formatter* Formatter::Create(FormatType format) {
  switch (format) {
  case FORMAT_JSON:
    return new JsonFormatter(&std::cout);
  case FORMAT_CSV:
    return new CsvFormatter(&std::cout);
  default:
    return new TextFormatter(&std::cout);
  }
}

