// Author: Mingcheng Chen (linyufly@gmail.com)

#include "segment_sampler.h"

#include "math.h"

namespace {

const double kEpsilon = 1e-8;

}

void SegmentSampler::sample_segment(
    double x_1, double y_1, double x_2, double y_2,
    double start_distance, double step) {
  double length = distance_2d(x_1, y_1, x_2, y_2);

  if (length <= kEpsilon || length < start_distance) {
    return;
  }

  double d_x = (x_2 - x_1) / length;
  double d_y = (y_2 - y_1) / length;

  for (double dist = start_distance; dist <= length; dist += step) {
    double x = x_1 + d_x * dist;
    double y = y_1 + d_y * dist;

    samples_.push_back(std::pair<double, double>(x, y));
  }
}

