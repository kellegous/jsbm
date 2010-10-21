#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "base/scoped_ptr.h"
#include "engine.h"
#include "format.h"
#include "stats.h"

namespace {

void PrintUsage() {
  std::cerr << "Usage: jsbm [-n #] filename" << std::endl;
}

bool ReadFileIntoString(const char* filename, std::string* out) {
  std::ifstream file(filename, std::ios::in);
  if (!file.is_open())
    return false;

  // Obtain file size.
  file.seekg(0, std::ios::end);
  int size = file.tellg();
  file.seekg(0, std::ios::beg);

  // Read somez dataz.
  scoped_array<char> buffer(new char[size]);
  file.read(buffer.get(), size);

  out->assign(buffer.get(), size);
  return true;
}

bool ExecuteTrials(Engine* engine, const std::string& script, int n, Stats* stats) {
  std::vector<double> samples;
  double elapsed;
  for (int i = 0; i < n; ++i) {
    if (!engine->Execute(script, &elapsed))
      return false;
    samples.push_back(elapsed);
  }
  return ComputeStats(samples, stats);
}

}  // namespace

int main(int argc, char* argv[]) {
  int n = 20, c;
  FormatType format = FORMAT_TEXT;

  while ((c = getopt(argc, argv, "cjn:")) != -1) {
    switch (c) {
    case 'n':
      n = atoi(optarg);
      break;
    case 'j':
      format = FORMAT_JSON;
      break;
    case 'c':
      format = FORMAT_CSV;
      break;
    default:
      PrintUsage();
      return 1;
      break;
    }
  }

  if ((argc - optind) != 1) {
    PrintUsage();
    return 1;
  }

  const char* filename = argv[optind];
  std::string script;
  if (!ReadFileIntoString(filename, &script)) {
    std::cerr << "Unable to read file (" << filename << ")" << std::endl;
    return 1;
  }

  Stats stats;
  scoped_ptr<Engine> engine(new Engine);
  scoped_ptr<Formatter> formatter(Formatter::Create(format));
  ExecuteTrials(engine.get(), script, n, &stats);
  formatter->EmitStats(stats);

  return 0;
}
