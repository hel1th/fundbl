#include "funcs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OK = 0,
  INPUT_ERR,
  ALLOC_ERR,
  OVERFLOW_ERR,
  XZ_ERR,
} ReturnCode;

int main() {
  int base;
  char stop[] = "Stop";
  numCont n0 = {
      .numRes10 = 0, .isNeg = false, .noLead0 = "0", .numStrBase = NULL};
  numCont *maxNum = &n0;
  if (scanf("%d", &base) != 1 || base < 2 || base > 36) {
    printf("Invalid base! Enter the base from 2 to 36!\n");
    return INPUT_ERR;
  }

  size_t size = 0;
  size_t capacity = 5;
  numCont *container = (numCont *)malloc(capacity * sizeof(numCont));
  if (!container) {
    printf("Error while allocating memory!\n");
    return ALLOC_ERR;
  }

  char buff[100];
  while (1) {
    if (scanf("%99s", buff) != 1) {
      free(container);
      return INPUT_ERR;
    }
    if (!strcmp(stop, buff))
      break;

    numCont n1;
    n1.numStrBase = NULL;
    char *p = buff;
    n1.isNeg = false;
    if (*p == '-') {
      n1.isNeg = true;
      ++p;
    }
    while (*p == '0' && *(p + 1) != '\0') {
      ++p;
    }
    n1.noLead0 = p;
    if (*n1.noLead0 == '\0') {
      n1.noLead0 = "0";
      n1.numRes10 = 0;
      n1.isNeg = false;
    } else {
      n1.numStrBase = (char *)malloc(strlen(buff) + 1);
      if (!n1.numStrBase) {
        for (size_t i = 0; i < size; ++i) {
          free(container[i].numStrBase);
        }
        free(container);
        return ALLOC_ERR;
      }
      strcpy(n1.numStrBase, buff);
      n1.noLead0 = n1.numStrBase + (p - buff);
      StatusConvertTen status10 =
          convertToTen(n1.noLead0, base, &(n1.numRes10));
      switch (status10) {
      case CONV_TEN_OVERFLOW:
        printf("The number can't be below -2^63 and above 2^63 - 1!\n");
        for (size_t i = 0; i < size; ++i) {
          free(container[i].numStrBase);
        }
        free(container);
        return OVERFLOW_ERR;
      case CONV_TEN_OUT_OF_RANGE:
        printf("Digits must be from 0-9 to a(10)-z(35)!\n");
        for (size_t i = 0; i < size; ++i) {
          free(container[i].numStrBase);
        }
        free(container);
        return INPUT_ERR;
      case CONV_TEN_OK:
        if (n1.isNeg && n1.numRes10 != 0) {
          n1.numRes10 = -n1.numRes10;
        }
        break;
      }
    }

    if (size >= capacity) {
      capacity *= 2;
      numCont *tmp = (numCont *)realloc(container, capacity * sizeof(numCont));
      if (!tmp) {
        printf("Error while reallocation memory!\n");
        for (size_t i = 0; i < size; ++i) {
          free(container[i].numStrBase);
        }
        free(container);
        return ALLOC_ERR;
      }
      container = tmp;
    }
    container[size] = n1;
    if (llabs(n1.numRes10) > llabs(maxNum->numRes10)) {
      maxNum = &container[size];
    }
    ++size;
  }

  printMaxNumber(maxNum);

  for (size_t i = 0; i < size; ++i) {
    free(container[i].numStrBase);
  }
  free(container);
  return OK;
}