#include "funcs.h"
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StatusConvertTen convertToTen(const char *numStr, int base, long long *res) {
  *res = 0;
  int digit = 0;
  long long result = 0;
  for (int i = 0; numStr[i] != '\0'; i++) {
    char c = numStr[i];
    if (isdigit(c)) {
      digit = c - '0';
    } else if (isalpha(c)) {
      digit = c - 'a';
    } else {
      return CONV_TEN_OUT_OF_RANGE;
    }
    if (base <= digit)
      return CONV_TEN_OUT_OF_RANGE;

    if (*res >= (LLONG_MAX - digit) / base)
      return CONV_TEN_OVERFLOW;

    result = result * base + digit;
  }
  *res = result;
  return CONV_TEN_OK;
}

StatusMax printMaxNumber(numCont *maxN) {
  long long num10 = maxN->numRes10;
  char *numStr = (char *)malloc(sizeof(char) * 65);
  printf("Max absolute number is: ");
  printf("%lld\n", num10);

  convertToBaseN(maxN, 9, numStr);
  printf("Base 9: %s\n", numStr);

  convertToBaseN(maxN, 18, numStr);
  printf("Base 18: %s\n", numStr);

  convertToBaseN(maxN, 27, numStr);
  printf("Base 27: %s\n", numStr);

  convertToBaseN(maxN, 36, numStr);
  printf("Base 36: %s\n", numStr);
  free(numStr);
  return MAX_OK;
}

StatusConvertN convertToBaseN(const numCont *maxN, int toBase, char *resStr) {
  int i = 0;
  long long numTmp = maxN->numRes10;
  if (numTmp == 0) {
    strcpy(resStr, "0");
    return BASE_N_OK;
  }
  while (numTmp != 0) {
    numTmp /= toBase;
    i++;
  }
  if (maxN->isNeg) {
    numTmp = -maxN->numRes10;
    ++i;
    resStr[0] = '-';
  } else {
    numTmp = maxN->numRes10;
  }

  resStr[i--] = '\0';
  while (numTmp != 0) {
    int digit = numTmp % toBase;
    resStr[i--] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
    numTmp /= toBase;
  }

  return BASE_N_OK;
}