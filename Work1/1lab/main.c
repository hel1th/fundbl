#include "funcs.h"
#include <stdio.h>

typedef enum ReturnCode {
  OK,
  OVERFLOW,
  MEMORY_FAULT,
  INVALID_INPUT,
  UNKNOWN_FAULT,
} ReturnCode;

int main(int argc, const char **argv) {
  const char *ALLOWED_FLAGS = "hpseaf";
  char flag = '\0';
  int number = 0;

  if (argc != 3) {
    printf("Wrong input\nExample: %s <number> -<flag>\n", argv[0]);
    return INVALID_INPUT;
  }

  NumberValidateStatus numberStatus = validateNumber(argv[1], &number);
  switch (numberStatus) {
  case NUMBER_OK:
    break;
  case NUMBER_CONTAINS_NOT_DIGITS:
    printf("First argument contains non-digits: %s\n", argv[1]);
    return INVALID_INPUT;
  case NUMBER_OVERFLOW:
    printf("Number overflow: %s\n", argv[1]);
    return OVERFLOW;
  case NOT_POSITIVE_NUMBER:
    printf("Number must be positive: %s\n", argv[1]);
    return INVALID_INPUT;
  }

  FlagParseStatus flagStatus = parseFlag(argv[2], ALLOWED_FLAGS, &flag);
  switch (flagStatus) {
  case FLAG_OK:
    break;
  case FLAG_UNKNOWN:
    printf("Unknown flag: %s\n", argv[2]);
    return INVALID_INPUT;
  case FLAG_NOT_FOUND:
    printf("Second argument is not a flag: %s\n", argv[2]);
    return INVALID_INPUT;
  }

  switch (flag) {
  case 'h': {
    int multiples[100];
    size_t count;
    MultiplesStatus status = getMultiplesOfNumber(number, multiples, &count);
    if (status == MULTIPLES_NOT_EXIST) {
      printf("There are no multiples of %d below or equal to 100", number);
      return OK;
    }
    printMultiples(number, multiples, count);
    break;
  }
  case 'p': {
    isPrime primeType;
    PrimeStatus status = checkPrime(number, &primeType);
    if (status == PRIME_FAULT) {
      printf("Error checking prime\n");
      return 1;
    }
    printIsPrime(number, primeType);
    break;
  }
  case 's': {
    char digits[33];
    size_t count;
    HexStatus status = toHexDigits(number, digits, &count);
    if (status == HEX_OVERFLOW) {
      printf("Number too large for hex conversion\n");
      return 1;
    }
    printHexDigits(digits, count);
    break;
  }
  case 'e': {
    long long table[10][10];
    PowersStatus status = generatePowersTable(number, table);
    if (status == POWERS_INVALID) {
      printf("Number must be between 1 and 10 inclusive\n");
      return 1;
    }
    printPowersTable(number, table);
    break;
  }
  case 'a': {
    unsigned long long sum;
    SumStatus status = sumUpToNumber(number, &sum);
    if (status == SUM_OVERFLOW) {
      printf("Sum overflow for number %d\n", number);
      return OVERFLOW;
    }
    printSum(number, sum);
    break;
  }
  case 'f': {
    unsigned long long result;
    FactStatus status = computeFactorial(number, &result);
    if (status == FACT_OVERFLOW) {
      printf("Factorial overflow for number %d\n", number);
      return OVERFLOW;
    }
    printFactorial(number, result);
    break;
  }
  default:
    printf("Unknown flag processing error\n");
    return INVALID_INPUT;
  }
  printf("\n");
  return OK;
}