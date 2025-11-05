#include "funcs.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
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

NumberValidateStatus validateNumber(const char *numberStr, int *number) {
  char *endptr;
  long num = strtol(numberStr, &endptr, 10);

  if (*endptr != '\0') {
    return NUMBER_CONTAINS_NOT_DIGITS;
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

MultiplesStatus getMultiplesOfNumber(int number, int *multiples,
                                     size_t *count) {
  *count = 0;
  if (number > 100) {
    return MULTIPLES_NOT_EXIST;
  }
  for (int multiple = number; multiple <= 100; multiple += number) {
    multiples[(*count)++] = multiple;
  }
  return (*count > 0) ? MULTIPLES_OK : MULTIPLES_NOT_EXIST;
}

void printMultiples(int number, const int *multiples, size_t count) {
  printf("Multiples of %d up to 100:\n", number);
  for (size_t i = 0; i < count; i++) {
    printf("%d ", multiples[i]);
  }
}

PrimeStatus checkPrime(const int number, isPrime *isPrime) {
  if (number < 2) {
    *isPrime = NEITHER;
    return PRIME_OK;
  }
  if (number == 2) {
    *isPrime = PRIME;
    return PRIME_OK;
  }
  if (number % 2 == 0) {
    *isPrime = COMPOSITE;
    return PRIME_OK;
  }
  *isPrime = COMPOSITE;
  for (int i = 3; i * i <= number; i += 2) {
    if (number % i == 0) {
      *isPrime = PRIME;
      return PRIME_OK;
    }
  }
  return PRIME_FAULT;
}

void printIsPrime(const int number, const isPrime isPrime) {
  switch (isPrime) {
  case PRIME:
    printf("%d is a prime number", number);
    break;
  case COMPOSITE:
    printf("%d is a composite number", number);
    break;
  case NEITHER:
    printf("%d is neither prime or composite", number);
    break;
  }
}

HexStatus toHexDigits(int number, char *digits, size_t *count) {
  *count = 0;
  if (number == 0) {
    return HEX_OK;
  }
  int temp = number;
  while (temp > 0) {
    (*count)++;
    temp /= 16;
  }
  if (*count > 32) {
    return HEX_OVERFLOW;
  }
  int idx = (int)*count - 1;
  temp = number;
  while (temp > 0) {
    int rem = temp % 16;
    digits[idx--] = (rem < 10) ? ('0' + rem) : ('A' + (rem % 10));
    temp /= 16;
  }
  digits[*count] = '\0';
  return HEX_OK;
}

void printHexDigits(const char *digits, size_t count) {
  for (size_t i = 0; i < count; i++) {
    printf("%c ", digits[i]);
  }
}

PowersStatus generatePowersTable(int number, long long table[10][10]) {
  if (number < 1 || number > 10) {
    return POWERS_INVALID;
  }
  for (int exp = 1; exp <= number; exp++) {
    for (int base = 1; base <= 10; base++) {
      long long result = 1;
      for (int i = 0; i < exp; i++) {
        result *= base;
        if (result < 0) {
          return POWERS_INVALID;
        }
      }
      table[exp - 1][base - 1] = result;
    }
  }
  return POWERS_OK;
}

void printPowersTable(int number, const long long table[10][10]) {
  printf("    |");
  for (int base = 1; base <= 10; base++) {
    printf("%12d|", base);
  }
  printf("\n");

  printf("-----");
  for (int i = 0; i < 10; i++) {
    printf("-------------");
  }
  printf("\n");

  for (int exp = 1; exp <= number; exp++) {
    printf(" %3d|", exp);
    for (int base = 1; base <= 10; base++) {
      printf(" %11lld|", table[exp - 1][base - 1]);
    }
    printf("\n");
  }
}

SumStatus sumUpToNumber(int number, unsigned long long *sum) {
  // переполнение не проверя. т.к int * int <= ull_max
  *sum = number * ((double)(number + 1) / 2);
  return SUM_OK;
}

void printSum(int number, unsigned long long sum) {
  printf("Sum from 1 to %d is equal to %llu", number, sum);
}

FactStatus computeFactorial(size_t num, unsigned long long *result) {
  *result = 1;
  for (size_t i = 2; i <= num; i++) {
    if (*result > ULLONG_MAX / i) {
      return FACT_OVERFLOW;
    }
    *result *= i;
  }
  return FACT_OK;
}

void printFactorial(size_t number, unsigned long long result) {
  printf("Factorial of %zu is %llu", number, result);
}