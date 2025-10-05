#include <stdbool.h>
#include <stdio.h>

void printOpenErr(const char *file);

typedef struct {
  char *numStrBase;
  bool isNeg;
  char *noLead0;
  long long numRes10;
} numCont;

typedef enum {
  CONV_TEN_OK,
  CONV_TEN_OVERFLOW,
  CONV_TEN_OUT_OF_RANGE,
} StatusConvertTen;
StatusConvertTen convertToTen(const char *numStr, const int base,
                              long long *res);

typedef enum { MAX_OK, MAX_ERR } StatusMax;
StatusMax printMaxNumber(numCont *maxN);

typedef enum {
  BASE_N_OK,
  BASE_N_OVERFLOW,
  BASE_N_OUT_OF_RANGE,
} StatusConvertN;
StatusConvertN convertToBaseN(const numCont *maxN, int toBase, char *resStr);
