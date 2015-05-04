// Author: Mingcheng Chen (linyufly@gmail.com)

#include "density_map.h"

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

      double coord[2];
      get_grid_point(curr_index[0], curr_index[1], coord);
    }
  }
}
