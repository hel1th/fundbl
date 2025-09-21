
#ifndef FUNC_H
#define FUNC_H
#include <stddef.h>

typedef enum {
  CONTAINS_NOT_DIGITS,
  NUMBER_OVERFLOW,
  NOT_POSITIVE_NUMBER,
  NUMBER_OK
} NumberValidateStatus;
typedef enum { FLAG_UNKNOWN, FLAG_NOT_FOUND, FLAG_OK } FlagParseStatus;
typedef enum { MULTIPLES_OK, MULTIPLES_NOT_EXIST } MultiplesStatus;
typedef enum { PRIME_OK, PRIME_FAULT } PrimeStatus;
typedef enum { PRIME, COMPOSITE, NEITHER } isPrime;
typedef enum { HEX_OK, HEX_OVERFLOW } HexStatus;
typedef enum { POWERS_OK, POWERS_INVALID } PowersStatus;
typedef enum { SUM_OK, SUM_OVERFLOW } SumStatus;
typedef enum { FACT_OK, FACT_OVERFLOW } FactStatus;

FlagParseStatus parseFlag(const char *arg, const char *allowedFlags,
                          char *flag);
NumberValidateStatus validateNumber(const char *numberStr, int *number);

MultiplesStatus getMultiplesOfNumber(int number, int *multiples, size_t *count);
void printMultiples(int number, const int *multiples, size_t count);

PrimeStatus checkPrime(int number, isPrime *isPrime);
void printIsPrime(const int number, const isPrime status);

HexStatus toHexDigits(int number, char *digits, size_t *count);
void printHexDigits(const char *digits, size_t count);

PowersStatus generatePowersTable(int number, long long table[10][10]);
void printPowersTable(int number, const long long table[10][10]);

SumStatus sumUpToNumber(int number, unsigned long long *sum);
void printSum(int number, unsigned long long sum);

FactStatus computeFactorial(size_t num, unsigned long long *result);
void printFactorial(size_t number, unsigned long long result);

#endif
