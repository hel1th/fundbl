#ifndef FUNCS_H
#define FUNCS_H
#include <stdbool.h>

typedef enum {
  NUMBER_CONTAINS_NOT_DIGITS,
  NUMBER_OVERFLOW,
  NOT_POSITIVE_NUMBER,
  NUMBER_OK
} NumberValidateStatus;

NumberValidateStatus validateNumber(const char *numberStr, int *number);
typedef enum { STATUS_FAILED = -1, STATUS_OK } Status;
bool isPrimeNumber(long long number);
Status findNPrimes(int maxNumber, long long *primeNumbers);

#endif