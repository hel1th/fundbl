#include "../include/comp_pi.h"
#include "../include/utils.h"
#include <math.h>

double lim_pi_(int n) {
  double numer = pow(pow(2, n) * factorial(n), 4);
  double denom = n * pow(factorial(2 * n), 2);
  double result = numer / denom;
  return result;
}

double limit_pi(double eps) {
  int n = 1;
  double resPrev = lim_pi_(n++);
  double res = lim_pi_(n++);

  while (fabs(res - resPrev) >= eps) {
    resPrev = res;
    res = lim_pi_(n++);
    if (isinf(res) || isnan(res)) {
      return resPrev;
    }
  }
  return res;
}

double ser_pi_(int n) { return (pow(-1, n - 1)) / (2.0 * n - 1); }

double series_pi(double eps) {
  int n = 1;
  double resPrev = ser_pi_(n++);
  double res = resPrev + ser_pi_(n++);
  while (fabs(res - resPrev) >= eps) {
    resPrev = res;
    res = ser_pi_(n++) + resPrev;
  }
  return 4 * res;
}

double equation_pi(double eps) {
  double mid, l = -2, r = 0;

  while (fabs(r - l) >= eps) {
    mid = (l + r) / 2.0;
    if (cos(mid) > 0) {
      r = mid;
    } else {
      l = mid;
    }
  }

  return (l + r) * -1;
}
