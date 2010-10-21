#ifndef STATS_H__
#define STATS_H__

#include <vector>

struct Stats {
  double mean;
  double lower_bound;
  double upper_bound;
};

bool ComputeStats(const std::vector<double>& data, Stats* stats);

#endif // STATS_H__
