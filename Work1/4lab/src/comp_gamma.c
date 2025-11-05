#include "../include/comp_gamma.h"
#include "../include/comp_pi.h"
#include "../include/utils.h"
#include <math.h>
#include <stdlib.h>

double lim_gamma_(int m) {
  double sum = 0;

  for (int k = 1; k <= m; ++k) {
    double combs = (factorial(m)) / (factorial(m - k) * factorial(k));
    sum += (combs * (pow(-1, k) / k)) * log(factorial(k));
  }
  return sum;
}

double limit_gamma(double eps) {
  int m = 1;
  double resPrev = lim_gamma_(m++);
  double res = lim_gamma_(m++);

  while (fabs(res - resPrev) >= eps) {
    resPrev = res;
    res = lim_gamma_(m++);
    if (isinf(res) || isnan(res) || isnan(-res))
      return resPrev;
  }
  return res;
}

double ser_gamma_(int k) {
  int sqrt_k = sqrt(k);
  return (1.0 / (sqrt_k * sqrt_k) - 1.0 / k);
}

double series_gamma(double eps) {
  int k = 2;
  double resPrevPrev = ser_gamma_(k++);
  double resPrev = resPrevPrev + ser_gamma_(k++);
  double res = resPrev + ser_gamma_(k++);

  while (fabs(res - resPrev) >= eps || fabs(resPrev - resPrevPrev) >= eps) {
    resPrevPrev = resPrev;
    resPrev = res;
    res = resPrev + ser_gamma_(k++);
  }
  return (equation_pi(eps) * equation_pi(eps)) / (-6) + res;
}

double eq_gamma_(int t, int *primeNums) {
  double mult = 1.0;
  for (int p = 2; p < t; p++) {
    if (primeNums[p] == 0) {
      mult *= ((p - 1.0) / ((double)(p)));
    }
  }
  return log(t) * mult;
}

double equation_gamma(double e) {
  int t_max = 1e6;
  int *primeNums = findPrime(t_max);
  if (!primeNums) {
    return -1;
  }

  double limitVal = eq_gamma_(t_max, primeNums);

  double l = 0;
  double r = 1;
  double mid;

  while (fabs(r - l) >= e) {
    mid = (l + r) / 2.0;
    if (exp(-mid) - limitVal > 0) {
      l = mid;
    } else {
      r = mid;
    }
  }

  free(primeNums);
  return (l + r) / 2.0;
}
