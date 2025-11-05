#include "../include/finite.h"
#include "stdlib.h"
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>

#define EPS 1e-9
#define MAX_ITER 10000

ReturnCode areFinite(const int base, bool **res, const size_t count, ...) {
  if (base < 2) {
    return CONVERT_ERR;
  }
  double num;
  ReturnCode isFinStatus;
  bool isItFinite;

  va_list fraqs;
  va_start(fraqs, count);

  bool *finita = (bool *)malloc(sizeof(double) * count);
  for (size_t i = 0; i < count; i++) {
    num = va_arg(fraqs, double);

    if (num <= EPS || num >= 1.0 - EPS) {
      return CONVERT_ERR;
    }

    isFinStatus = isFinite(base, num, &isItFinite);
    if (isFinStatus != OK) {
      free(finita);
      return UNKNOWN_ERR;
    }

    finita[i] = isItFinite;
  }

  va_end(fraqs);
  *res = finita;
  return OK;
}

ReturnCode isFinite(const int base, const double num, bool *res) {
  const double eps = EPS;
  long long p, q, q0, x, y;
  approximate(eps, num, &p, &q);

  x = gcd(p, q);
  q0 = q / x;

  y = gcd(q0, base);
  while (y > 1) {
    q0 /= y;
    y = gcd(q0, base);
  }

  *res = (bool)(q0 == 1);
  return OK;
}
// 0.5
// base 6
// q0 = 12
// gcd - 6
// q0 2
// base 1

long long gcd(long long a, long long b) {
  long long tmp;

  while (b) {
    tmp = b;
    b = a % b;
    a = tmp;
  }

  return a;
}

ReturnCode approximate(const double eps, const double num, long long *p,
                       long long *q) {
  double fraq = num;
  long long n1 = 1, d1 = 0;
  long long n2 = 0, d2 = 1;
  long long n, d;

  while (1) {
    long long b_i = (long long)floor(fraq);

    if (b_i != 0 && (n1 > LLONG_MAX / b_i || d1 > LLONG_MAX / b_i))
      return OVERFLOW_ERR;

    n = b_i * n1 + n2;
    d = b_i * d1 + d2;

    double aprx = (double)n / d;
    if (fabs(aprx - fraq) < eps)
      break;

    n2 = n1;
    d2 = d1;
    n1 = n;
    d1 = d;

    double fraqPart = fraq - b_i;
    if (fabs(fraqPart) < eps)
      break;
    fraq = 1.0 / fraqPart;
  }
  *p = n;
  *q = d;

  return OK;
}
