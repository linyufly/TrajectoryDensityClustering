// Author: Mingcheng Chen (linyufly@gmail.com)

#include "math.h"

#include <cmath>

#include <vtkMath.h>

double Math::square(double value) {
  return value * value;
}

void Math::fit_quadratic(const double x[3], const double y[3],
                         double coefficients[3]) {
  double van[3][3] = {{1.0, x[0], square(x[0])},
                      {1.0, x[1], square(x[1])},
                      {1.0, x[2], square(x[2])}};

  vtkMath::LinearSolve3x3(van, y, coefficients);
}

double Math::gaussian(double x, double a, double b, double c) {
  return a * exp(-square(x - b) / (2 * square(c)));
}

double Math::distance_2d(double x_1, double y_1, double x_2, double y_2) {
  return sqrt(square(x_1 - x_2) + square(y_1 - y_2));
}

