#include "funcs.h"
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

FlagParseStatus parseFlag(const char *arg, const char *allowedFlags,
                          char *flag) {
  if (arg[0] != '-' && arg[0] != '/') {
    return FLAG_NOT_FOUND;
  }
  if (arg[2] != '\0') {
    return FLAG_UNKNOWN;
  }
  const char *found = strchr(allowedFlags, arg[1]);
  if (!found) {
    return FLAG_UNKNOWN;
  }
  *flag = *found;
  return FLAG_OK;
}

NumberValidateStatus validateIntNumber(const char *numberStr, int *number) {
  char *endptr;
  errno = 0;
  long num = strtol(numberStr, &endptr, 10);

  if (errno == ERANGE) {
    return NUMBER_OVERFLOW;
  }
  if (*endptr != '\0') {
    return NUMBER_CONTAINS_NOT_DIGITS;
  }
  if (num > INT_MAX) {
    return NUMBER_OVERFLOW;
  }
  *number = (int)num;
  return NUMBER_OK;
}

NumberValidateStatus validateFloatNumber(const char *numberStr, double *value) {
  char *endptr;
  errno = 0;

  double num = strtod(numberStr, &endptr);

  if (errno == ERANGE) {
    return NUMBER_OVERFLOW;
  }
  if (*endptr != '\0') {
    return NUMBER_CONTAINS_NOT_DIGITS;
  }

  *value = num;
  return NUMBER_OK;
}

StatusMultiple isMultiple(int a, int b, bool *isMult) {
  if (abs(a - b) < 0) {
    return MULT_A_LESS_B_FAULT;
  }
  if (a * b == 0) {
    return MULT_NUMBER_ZERO_FAULT;
  }
  if (a % b == 0) {
    *isMult = true;
  } else {
    *isMult = false;
  }
  return MULT_OK;
}

StatusTriangle isRightTriangle(double eps, double a, double b, double c,
                               bool *isRight) {
  if (a <= 0 || b <= 0 || c <= 0 || eps <= 0) {
    return TRI_NEGATIVE_NUMS_FAULT;
  }
  *isRight = false;
  if (fabs(a * a + b * b - c * c) < eps || fabs(a * a + c * c - b * b) < eps ||
      fabs(b * b + c * c - a * a) < eps) {
    *isRight = true;
  }
  return TRI_OK;
}