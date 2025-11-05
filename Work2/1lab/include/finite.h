#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {
  OK,
  ALLOC_ERR,
  CONVERT_ERR,
  OVERFLOW_ERR,
  UNKNOWN_ERR,
} ReturnCode;

ReturnCode areFinite(const int base, bool **res, const size_t count, ...);

long long gcd(long long a, long long b);

ReturnCode isFinite(const int base, const double num, bool *res);

ReturnCode approximate(const double eps, const double num, long long *p,
                       long long *q);
