#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum ReturnCode {
  MEMORY_FAULT,
  INVALID_INPUT,
  UNKNOWN_FAULT,
  OK
} ReturnCode;

int main() {
  char numStr[31];
  int num = 0, maxN0 = 0;
  printf("Enter amount of lines to input: ");
  fgets(numStr, 30, stdin);

  NumberValidateStatus numberStatus = validateNumber(numStr, &num);

  if (numberStatus != NUMBER_OK) {
    printf("Wrong input: %s\nEnter integer number > 0\n", numStr);
    return INVALID_INPUT;
  }

  int *primeN0 = (int *)malloc(num * sizeof(int));
  for (int i = 0; i < num; i++) {
    char tmpStr[31];
    int tmpInt;
    fgets(tmpStr, 30, stdin);

    NumberValidateStatus numberStatus = validateNumber(tmpStr, &tmpInt);

    if (numberStatus != NUMBER_OK) {
      printf("Wrong input: %s\n", tmpStr);
      printf("Enter integer number > 0\n");
      free(primeN0);
      return INVALID_INPUT;
    } else {
    }
    maxN0 = tmpInt > maxN0 ? tmpInt : maxN0;
    primeN0[i] = tmpInt;
  }

  long long *primeNumbers = malloc(maxN0 * sizeof(long long));
  if (!primeNumbers) {
    printf("Memory was not allocated!\n");
    free(primeN0);
    return MEMORY_FAULT;
  }

  Status status = findNPrimes(maxN0, primeNumbers);
  if (status == STATUS_FAILED) {
    printf("Prime generation failed!\n");
    free(primeNumbers);
    free(primeN0);
    return UNKNOWN_FAULT;
  }

  printf("==================\n");
  for (int i = 0; i < num; i++) {
    int idx = primeN0[i] - 1;
    printf("The %d-th prime number is %lld\n", primeN0[i], primeNumbers[idx]);
  }

  free(primeNumbers);
  free(primeN0);
  return OK;
}
