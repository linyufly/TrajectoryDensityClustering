// Author: Mingcheng Chen (linyufly@gmail.com)

#include "density_map.h"

#include "math.h"
#include "segment_sampler.h"

#include <cstdio>

namespace {

const char *kTrajectoryFile = "data/atlantic_storms.txt";

const char *kDensityMapFile = "density_map.csv";

const int kXRes = 200;
const int kYRes = 200;

const double kStep = 0.001;
const double kGaussianDelta = 1.0;
}

void add_point_test() {
  printf("add_point_test {\n");

  FILE *fin = fopen(kTrajectoryFile, "r");

  double min_x, max_x, min_y, max_y, min_t, max_t;
  fscanf(fin, "%lf %lf %lf %lf %lf %lf",
         &min_y, &max_y, &min_x, &max_x, &min_t, &max_t);

  DensityMap density_map(kXRes, kYRes, min_x, max_x, min_y, max_y);
  SegmentSampler sampler;

  double last_x, last_y;
  double next_dist, total_dist;
  bool started = false;
  while (true) {
    double x, y, t;
    if (fscanf(fin, "%lf %lf %lf", &y, &x, &t) <= 0) {
      break;
    }
    if (x == 0.0 && y == 0.0 && t == 0.0) {
      started = false;
      continue;
    }

    if (!started) {
      sampler.add_sample(x, y);
      started = true;
      next_dist = kStep;
      total_dist = 0.0;
    } else {
      double dist = Math::distance_2d(last_x, last_y, x, y);
      sampler.sample_segment(last_x, last_y, x, y, next_dist - total_dist, kStep);
      total_dist += dist;
      for (; next_dist <= total_dist; next_dist += kStep) {}
    }

    last_x = x;
    last_y = y;
  }

  fclose(fin);

  printf("num of samples: %d\n", sampler.get_num_samples());

  for (int s = 0; s < sampler.get_num_samples(); s++) {
    double coord[2];
    sampler.get_sample(s, coord);
    density_map.add_point(coord);
  }

  density_map.gaussian_smoothing(kGaussianDelta);

  FILE *fout = fopen(kDensityMapFile, "w");

  for (int y = 0; y < kYRes; y++) {
    for (int x = 0; x < kXRes; x++) {
      if (x) {
        fprintf(fout, ", ");
      }
      fprintf(fout, "%lf", density_map[x][y]);
    }
    fprintf(fout, "\n");
  }

  fclose(fout);

  printf("} add_point_test\n");
}

int main() {
  add_point_test();

  return 0;
}

