#include "funcs.h"
#include <limits.h>
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

NumberValidateIntStatus validateIntNumber(const char *numberStr, int *number) {
  char *endptr;
  long num = strtol(numberStr, &endptr, 10);

  if (*endptr != '\0') {
    return CONTAINS_NOT_DIGITS;
  }
  if (num > INT_MAX) {
    return NUMBER_OVERFLOW;
  }
  *number = (int)num;
  return NUMBER_OK;
}

StatusMultiple isMultiple(int a, int b, bool *isMult) {
  if (abs(a - b) < 0) {
    return A_LESS_B_FAULT;
  }
  if (a * b == 0) {
    return NUMBER_ZERO_FAULT;
  }
  if (a % b == 0) {
    *isMult = true;
  } else {
    *isMult = false;
  }
  return MULT_OK;
}
