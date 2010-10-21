#include "stats.h"

#include <math.h>

namespace {

// t-distribution for p = 0.05 (used to compute 95% confidence intervals). This table is
// based at df = 2.
static double t_dist[] = {
    4.3027, 3.1824, 2.7765, 2.5706, 2.4469, 2.3646, 2.3060, 2.2622, 2.2281, 2.2010, 2.1788,
    2.1604, 2.1448, 2.1315, 2.1199, 2.1098, 2.1009, 2.0930, 2.0860, 2.0796, 2.0739, 2.0687,
    2.0639, 2.0595, 2.0555, 2.0518, 2.0484, 2.0452, 2.0423, 2.0395, 2.0369, 2.0345, 2.0322,
    2.0301, 2.0281, 2.0262, 2.0244, 2.0227, 2.0211, 2.0195, 2.0181, 2.0167, 2.0154, 2.0141,
    2.0129, 2.0117, 2.0106, 2.0096, 2.0086, 2.0076, 2.0066, 2.0057, 2.0049, 2.0040, 2.0032,
    2.0025, 2.0017, 2.0010, 2.0003, 1.9996, 1.9990, 1.9983, 1.9977, 1.9971, 1.9966, 1.9960,
    1.9955, 1.9949, 1.9944, 1.9939, 1.9935, 1.9930, 1.9925, 1.9921, 1.9917, 1.9913, 1.9908,
    1.9905, 1.9901, 1.9897, 1.9893, 1.9890, 1.9886, 1.9883, 1.9879, 1.9876, 1.9873, 1.9870,
    1.9867, 1.9864, 1.9861, 1.9858, 1.9855, 1.9852, 1.9850, 1.9847, 1.9845, 1.9842, 1.9840
};

// Computes sample mean.
double ComputeMean(const std::vector<double>& data) {
  size_t n = data.size();
  double sum = 0.0;
  for (size_t i = 0; i < n; ++i) {
    sum += data[i];
  }
  return sum / n;
}

// Computes standard error.
double ComputeStdError(const std::vector<double>& data, double mean) {
  size_t n = data.size();
  double sum = 0.0;
  for (size_t i = 0; i < n; ++i) {
    double d = data[i] - mean;
    sum += d * d;
  }
  return sqrt(sum / n) / sqrt(n);
}

double ComputeT(int df) {
  return t_dist[df - 2];
}

} // namespace

bool ComputeStats(const std::vector<double>& data, Stats* stats) {
  size_t n = data.size();
  if (!stats || n < 2 || n > 100) {
    return false;
  }
  double mean = ComputeMean(data);
  double error = ComputeStdError(data, mean);
  double t = ComputeT(n - 1);
  stats->mean = mean;
  stats->lower_bound = mean - t * error;
  stats->upper_bound = mean + t * error;
  return true;
}
