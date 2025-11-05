#include "../include/comp_sqrt2.h"
#include <math.h>

double lim_sqrt2_(double x) { return x - (x * x) / 2 + 1; }

double limit_sqrt2(double eps) {
  double resPrev = -0.5;
  double res = lim_sqrt2_(resPrev);
  while (fabs(res - resPrev) >= eps) {
    resPrev = res;
    res = lim_sqrt2_(resPrev);
  }
  return res;
}

double ser_sqrt2_(double k) { return pow(2, pow(2, -k)); }

double series_sqrt2(double eps) {
  double k = 2;
  double resPrev = ser_sqrt2_(k++);
  double res = resPrev * ser_sqrt2_(k++);
  while (fabs(res - resPrev) >= eps) {
    resPrev = res;
    res = resPrev * ser_sqrt2_(k++);
  }
  return res;
}

double equation_sqrt2(double eps) {
  double l = 1, r = 2;

  double mid;
  while (fabs(r - l) >= eps) {
    mid = (l + r) / 2.0;
    if (mid * mid - 2 > 0) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return (l + r) / 2.0;
}