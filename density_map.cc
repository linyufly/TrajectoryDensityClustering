// Author: Mingcheng Chen (linyufly@gmail.com)

#include "density_map.h"

#include "math.h"

void DensityMap::add_point(const double *coord) {
  int index[2];
  for (int d = 0; d < 2; d++) {
    index[d] = static_cast<int>((coord[d] - origin_[d]) / spacing_[d]);

    if (index[d] < 0) {
      index[d] = 0;
    }

    if (index[d] >= dimensions_[d]) {
      index[d] = dimensions_[d] - 1;
    }
  }

  for (int dx = 0; dx < 2; dx++) {
    for (int dy = 0; dy < 2; dy++) {
      int curr_index[] = {index[0] + dx, index[1] + dy};
      if (outside(curr_index)) {
        continue;
      }

      density_map_[curr_index[0]][curr_index[1]]++;
    }
  }
}

void DensityMap::deep_copy(const DensityMap &other) {
  if (this == &other) {
    return;
  }

  destroy();

  dimensions_ = new int[2];
  spacing_ = new double[2];
  origin_ = new double[2];
  density_map_ = create_matrix<double>(
      other.dimensions_[0], other.dimensions_[1]);

  for (int d = 0; d < 2; d++) {
    dimensions_[d] = other.dimensions_[d];
    spacing_[d] = other.spacing_[d];
    origin_[d] = other.origin_[d];
  }

  for (int x = 0; x < dimensions_[0]; x++) {
    for (int y = 0; y < dimensions_[1]; y++) {
      density_map_[x][y] = other.density_map_[x][y];
    }
  }
}

void gaussian_smoothing(double delta) {
  int nx = dimensions_[0];
  int ny = dimensions_[1];
  double dx = spacing_[0];
  double dy = spacing_[1];

  double *x_sum = create_matrix<double>(nx, ny);

  for (int x = 0; x < nx; x++) {
    for (int y = 0; y < ny; y++) {
      x_sum[x][y] = 0.0;
      for (int k = 0; k < ny; k++) {
        x_sum[x][y] +=
            density_map_[x][k] * Math::gaussian(dy * (k - y), 1.0, 0.0, delta);
      }
    }
  }

  for (int x = 0; x < nx; x++) {
    for (int y = 0; y < ny; y++) {
      density_map_[x][y] = 0.0;
      for (int k = 0; k < nx; k++) {
        density_map_[x][y] +=
            x_sum[k][y] * Math::gaussian(dx * (k - x), 1.0, 0.0, delta);
      }
    }
  }

  delete_matrix(x_sum);
}

