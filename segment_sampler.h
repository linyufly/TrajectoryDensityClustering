// Author: Mingcheng Chen (linyufly@gmail.com)

#ifndef SEGMENT_SAMPLER_H_
#define SEGMENT_SAMPLER_H_

#include <algorithm>
#include <vector>

class SegmentSampler {
 public:
  void clear() {
    samples_.clear();
  }

  // The segment is from (x_1, y_1) to (x_2, y_2).
  // The first sample is start_distance from (x_1, y_1).
  void sample_segment(
      double x_1, double y_1, double x_2, double y_2,
      double start_distance, double step);

  void add_sample(double x, double y) {
    samples_.push_back(std::pair<double, double>(x, y));
  }

  int get_num_samples() const {
    return samples_.size();
  }

  void get_sample(int index, double *coord) const {
    coord[0] = samples_[index].first;
    coord[1] = samples_[index].second;
  }

 private:
  std::vector<std::pair<double, double> > samples_;
};

#endif  // SEGMENT_SAMPLER_H_

