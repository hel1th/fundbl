#include "../include/comp_e.h"
#include <math.h>

double lim_e_(double n) { return pow(1 + 1.0 / n, n); }

double limit_e(const double eps) {
  double n = 1;
  double resPrev, res = lim_e_(n++);

  do {
    resPrev = res;
    n *= 2;
    res = lim_e_(n);
  } while (fabs(res - resPrev) >= eps);
  return res;
}

double series_e(double eps) {
  double n = 2, factorial = 1;
  double resPrev = 1.0 / factorial;
  double res = 1.0 / factorial + resPrev;
  while (fabs(res - resPrev) >= eps) {
    resPrev = res;
    factorial *= n++;
    res = 1.0 / factorial + resPrev;
  }
  return res;
}

double equation_e(double eps) {
  double l = 2;
  double r = 3;

  double mid;
  while (fabs(r - l) >= eps) {
    mid = (l + r) / 2.0;
    if (log(mid) - 1 > 0) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return (l + r) / 2.0;
}