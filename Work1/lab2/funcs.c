#include "funcs.h"
#include <limits.h>
#include <stdlib.h>

Status findNPrimes(const int maxN0, long long *primeNumbers) {
  long long curNumber = 1;
  int curCountN0 = 0;
  while (curCountN0 < maxN0) {
    while (1) {
      if (isPrimeNumber(curNumber)) {
        primeNumbers[curCountN0++] = curNumber++;
        break;
      } else {
        ++curNumber;
      }
    }
  }
  return STATUS_OK;
}

bool isPrimeNumber(long long number) {
  if (number < 2) {
    return false;
  } else if (number == 2) {
    return true;
  } else if (number % 2 == 0) {
    return false;
  }

  for (int i = 3; i * i <= number; i += 2) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}

NumberValidateStatus validateNumber(const char *numberStr, int *number) {
  char *endptr;
  long num = strtol(numberStr, &endptr, 10);

  if (*endptr != '\0' && *endptr != '\n') {
    return CONTAINS_NOT_DIGITS;
  }
  if (num <= 0) {
    return NOT_POSITIVE_NUMBER;
  }
  if (num > INT_MAX) {
    return NUMBER_OVERFLOW;
  }
  *number = (int)num;
  return NUMBER_OK;
}