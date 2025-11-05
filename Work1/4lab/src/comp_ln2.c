#include "../include/comp_ln2.h"
#include <math.h>

double limit_ln2_calc(double n) { return n * (pow(2, 1 / n) - 1); }

double limit_ln2(double eps) {
  double n = 1;
  double resPrev = limit_ln2_calc(n++);
  double res = limit_ln2_calc(n++);
  while (fabs(res - resPrev) >= eps) {
    resPrev = res;
    res = limit_ln2_calc(n++);
  }
  return res;
}

double ser_ln2_(double n) { return (pow(-1, n - 1)) / n; }

double series_ln2(double eps) {
  double n = 1;
  double resPrev = ser_ln2_(n++);
  double res = resPrev + ser_ln2_(n++);
  while (fabs(res - resPrev) >= eps) {
    resPrev = res;
    res = resPrev + ser_ln2_(n++);
  }
  return res;
}

double equation_ln2(double eps) {
  double mid, l = 0, r = 1;

  while (fabs(r - l) >= eps) {
    mid = (l + r) / 2.0;
    if (exp(mid) - 2 > 0) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return (l + r) / 2.0;
}