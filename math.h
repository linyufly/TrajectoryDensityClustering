// Author: Mingcheng Chen (linyufly@gmail.com)

#ifndef MATH_H_
#define MATH_H_

class Math {
 public:
  static double square(double value);

  // Fit a quadratic function
  // y = coefficient[0] + coefficient[1] * x + coefficient[2] * x^2
  static void fit_quadratic(const double x[3], const double y[3],
                            double coefficients[3]);

  // a is the height of the curve's peak.
  // b is the position of the center of the peak.
  // c is the standard deviation, which controls the width of the bell.
  static double gaussian(double x, double a, double b, double c);

  // (x_1, y_1) is the first point.
  // (x_2, y_2) is the second point.
  static double distance_2d(double x_1, double y_1, double x_2, double y_2);
};

#endif  // MATH_H_
