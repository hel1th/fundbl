#include "funcs.h"
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

void usage() {
  printf("Wrong input!\n");
  printf("Must be: <program> <file input> <file output>\n");
}

void printOpenErr(const char *file) {
  printf("Error during opening file %s !\n", file);
}

StatusConvertFile convertFile(FILE *fileIn, FILE *fileOut) {
  char c;
  size_t size = 0;
  size_t p = 0;
  char numStr[255];
  int base;
  long long resNum = 0;
  bool isNeg = false;

  do {

    c = getc(fileIn);
    c = tolower(c);
    if (isalnum(c) || c == '-') {
      if (size >= sizeof(numStr) - 1) {
        return CONVFILE_NUMBER_TOO_LONG;
      }
      if (c == '-') {
        if (size > 0) {
          return CONVFILE_INVALID_CHAR;
        }
        isNeg = true;
      }
      numStr[size++] = c;
      continue;
    } else if (isspace(c)) {
      if (size > 0) {
        numStr[size] = '\0';
      } else {
        continue;
      }

      p = 0;
      if (isNeg) {
        p++;
      }
      while (numStr[p] == '0' && numStr[p + 1] != '\0')
        p++;
      char *strNumNo0 = numStr + p;

      if (findMinBase(strNumNo0, &base) != FIND_OK) {
        return CONVFILE_ERR;
      }

      if (convertToTen(strNumNo0, base, isNeg, &resNum) != CONV_TEN_OK) {
        return CONVFILE_ERR;
      }

      if (fprintf(
              fileOut,
              "Given str: %s | original base is %d | result in base10 = %lld\n",
              strNumNo0, base, resNum) < 0) {
        return CONVFILE_ERR;
      }
      isNeg = false;
      size = 0;
      continue;
    } else {
      return CONVFILE_INVALID_CHAR;
    }
  } while (c != EOF);
  return CONVFILE_OK;
}

StatusFindBase findMinBase(char *chPtr, int *res) {
  int minBase = 0, base = 0;
  size_t i = 0;
  while (*(chPtr + i) != '\0') {
    char tmp = *(chPtr + i++);

    if (isdigit(tmp)) {
      base = tmp - '0';
    } else if (isalpha(tmp)) {
      base = tmp - 'a' + 10;
    } else {
      return FIND_OUT_OF_RANGE;
    }

    minBase = minBase > base ? minBase : base;
  }

  *res = minBase + 1;
  return FIND_OK;
}

StatusConvertTen convertToTen(const char *numStr, int base, bool isNeg,
                              long long *res) {
  long long result = 0;
  int digit;

  for (int i = 0; numStr[i] != '\0'; i++) {
    char c = numStr[i];

    if (isdigit(c)) {
      digit = c - '0';
    } else if (isalpha(c)) {
      digit = c - 'a';
    } else {
      return CONV_TEN_ERR;
    }

    if (result >= (LLONG_MAX - digit) / base) {
      return CONV_TEN_OVERFLOW;
    }

    result = result * base + digit;
  }
  if (isNeg) {
    result *= -1;
  }
  *res = result;
  return CONV_TEN_OK;
}