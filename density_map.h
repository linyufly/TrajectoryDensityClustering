// Author: Mingcheng Chen (linyufly@gmail.com)

#ifndef DENSITY_MAP_H_
#define DENSITY_MAP_H_

#include "util.h"

class DensityMap {
 public:
  DensityMap() {
    density_map_ = NULL;
    spacing_ = NULL;
    origin_ = NULL;
    dimensions_ = NULL;
  }

  DensityMap(
      int nx, int ny, double min_x, double max_x, double min_y, double max_y) {
    dimensions_ = new int[2];
    dimensions_[0] = nx;
    dimensions_[1] = ny;

    double dx = (max_x - min_x) / (nx - 1);
    double dy = (max_y - min_y) / (ny - 1);
    spacing_ = new double[2];
    spacing_[0] = dx;
    spacing_[1] = dy;

    origin_ = new double[2];
    origin_[0] = min_x;
    origin_[1] = min_y;

    density_map_ = create_matrix<double>(nx, ny);
    for (int x = 0; x < nx; x++) {
      for (int y = 0; y < ny; y++) {
        density_map_[x][y] = 0.0;
      }
    }
  }

  ~DensityMap() {
    destroy();
  }

  bool outside(const int *index) const {
    for (int d = 0; d < 2; d++) {
      if (index[d] < 0 || index[d] >= dimensions_[d]) {
        return true;
      }
    }

    return false;
  }

  void get_grid_point(int x, int y, double *coord) const {
    int index[] = {x, y};
    for (int d = 0; d < 2; d++) {
      coord[d] = origin_[d] + spacing_[d] * index[d];
    }
  }

  void deep_copy(const DensityMap &other);

  void add_point(const double *coord);

  void gaussian_smoothing(double delta);

  double *operator [] (int row) const {
    return density_map_[row];
  }

 private:
  void destroy() {
    if (density_map_) {
      delete_matrix(density_map_);
    }

    if (spacing_) {
      delete [] spacing_;
    }

    if (origin_) {
      delete [] origin_;
    }

    if (dimensions_) {
      delete [] dimensions_;
    }
  }

  double **density_map_;
  double *spacing_;
  double *origin_;
  int *dimensions_;
};

#endif  // DENSITY_MAP_H_

