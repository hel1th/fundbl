#include "funcs.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef enum {
  OK = 0,
  INPUT_ERR,
  ALLOC_ERR,
  OVERFLOW_ERR,
  XZ_ERR,
} ReturnCode;

int main() {
  int base;
  char stop[] = "Stop\n";
  numCont n0 = {.numRes10 = 0};
  numCont *maxNum = &n0;
  char baseChar = 0;

  if (scanf("%c", &baseChar) != 1)
    return INPUT_ERR;

  if (isdigit(baseChar)) {
    base = baseChar - '0';
  } else if (isalpha(baseChar)) {
    base = tolower(baseChar) - 'a';
  } else {
    printf("Invalid char:\"%c\"! Enter the base from 2 to 36 (ex: Z[=35])!\n",
           baseChar);
    return INPUT_ERR;
  }

  size_t size = 0;
  char *p = NULL;
  size_t capacity = 5;
  char buff[100];
  bool isNeg;
  numCont *container = (numCont *)malloc(sizeof(numCont) * capacity);
  while (1) {
    isNeg = false;
    numCont n1;
    scanf("%s", buff);
    if (!strcmp(stop, buff))
      break;
    n1.numStrBase = buff;
    p = buff;
    if (*p == '-') {
      isNeg = true;
      ++p;
    }
    n1.isNeg = isNeg;
    while (*p == 0 && (*(p + 1) != '\0' || *(p + 1) != '\n')) {
      ++p;
    }
    n1.noLead0 = p;
    StatusConvertTen status10 = convertToTen(n1.noLead0, base, &(n1.numRes10));
    switch (status10) {
    case CONV_TEN_OVERFLOW:
      printf("The number can't be below -2^63 and above 2^63 - 1!\n");
      free(container);
      return OVERFLOW_ERR;
    case CONV_TEN_OUT_OF_RANGE:
      printf("Digits must be from 0-9 to A(10)-Z(35)!\n");
      free(container);
      return INPUT_ERR;
    case CONV_TEN_OK:
      break;
    }

    if (llabs(n1.numRes10) > llabs(maxNum->numRes10)) {
      maxNum = &n1;
    }

    if (size >= capacity) {
      numCont *tmp;
      capacity *= 2;
      tmp = (numCont *)realloc(container, capacity * sizeof(numCont));
      if (!tmp) {
        printf("Error while reallocation memory!\n");
        return ALLOC_ERR;
      }
      container = tmp;
    }
    container[size++] = n1;
  }

  printMaxNumber(maxNum);

  free(container);
  return OK;
}