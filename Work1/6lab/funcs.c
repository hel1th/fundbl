#include "funcs.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void usage() {
  printf("Wrong input!\n");
  printf("Must be: <program> <eps>\n");
}

StatusNumberValidate validateFloatNumber(const char *numberStr, double *value) {
  char *endptr;
  double num = strtod(numberStr, &endptr);
  if (isinf(num)) {
    return NUMBER_OVERFLOW;
  }
  if (*endptr != '\0') {
    return NUMBER_CONTAINS_NOT_DIGITS;
  }

  *value = num;
  return NUMBER_OK;
}

StatusFunc func_a(double eps, double x, double *res) {
  if (x <= -1.0 - eps)
    return FUNC_UNDEFIND;

  if (fabs(x) < eps) {
    *res = 1.0;
    return FUNC_OK;
  }

  *res = log1p(x) / x;
  return FUNC_OK;
}

StatusFunc func_b(double eps, double x, double *res) {
  *res = exp(-0.5 * x * x);
  return FUNC_OK;
}

StatusFunc func_c(double eps, double x, double *res) {
  if (x >= 1.0) {
    x = 1.0 - eps;
  }
  *res = log(1.0 / (1.0 - x));
  return FUNC_OK;
}

StatusFunc func_d(double eps, double x, double *res) {
  if (x <= 0.0) {
    x = eps;
  }

  *res = pow(x, x);
  if (isinf(*res) || isnan(*res)) {
    return FUNC_OVERFLOW;
  }

  return FUNC_OK;
}

StatusTrap trapezoidMethod(const double eps, const double a, const double b,
                           unsigned long long n,
                           StatusFunc (*func)(double, double, double *),
                           double *res) {
  double resA, resB, resX;
  StatusFunc statusA = func(eps, a, &resA), statusB = func(eps, b, &resB),
             statusX;
  if (statusA != FUNC_OK || statusB != FUNC_OK) {
    return TRAP_FUNC_ERR;
  }

  double h = (b - a) / n;
  double sum = 0.5 * (resA + resB);
  for (unsigned long long i = 1; i < n; i++) {
    double x = a + i * h;
    statusX = func(eps, x, &resX);
    if (statusX != FUNC_OK) {
      return TRAP_FUNC_ERR;
    }
    sum += resX;
    if (isinf(sum))
      return TRAP_OVERFLOW;
  }
  *res = sum * h;
  if (isinf(*res))
    return TRAP_OVERFLOW;

  return TRAP_OK;
}

StatusCompute computeIntegral(const double eps,
                              StatusFunc (*func)(double, double, double *),
                              unsigned long long *n, double *res) {
  const double a = 0.0, b = 1.0 - eps;
  *n = 2;
  double resPrev, resCur;
  StatusTrap statusPrev, statusCur;

  statusPrev = trapezoidMethod(eps, a, b, *n, *func, &resPrev);
  if (statusPrev != TRAP_OK)
    return COMP_TRAP_ERR;

  while (true) {
    *n *= 2;
    statusCur = trapezoidMethod(eps, a, b, *n, *func, &resCur);
    if (statusCur != TRAP_OK)
      return COMP_TRAP_ERR;
    if (isinf(resCur) || isnan(resCur))
      return COMP_OVERFLOW;
    if (fabs(resCur - resPrev) < eps)
      break;

    resPrev = resCur;
  }
  *res = resCur;
  return COMP_OK;
}