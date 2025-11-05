#include <stdbool.h>
#include <stdio.h>

void usage();
void printOpenErr(const char *file);

typedef struct {
  char *numStrBase;
  bool isNeg;
  char *noLead0;
  long long numRes10;
} numCont;

typedef enum {
  CONVFILE_OK,
  CONVFILE_ALLOC_ERR,
  CONVFILE_ERR,
  CONVFILE_NUMBER_TOO_LONG,
  CONVFILE_INVALID_CHAR,
} StatusConvertFile;
StatusConvertFile convertFile(FILE *fileIn, FILE *fileOut);

typedef enum {
  FIND_OK,
  FIND_OUT_OF_RANGE,
} StatusFindBase;
StatusFindBase findMinBase(char *chPtr, int *res);

typedef enum {
  CONV_TEN_OK,
  CONV_TEN_OVERFLOW,
  CONV_TEN_ERR,
} StatusConvertTen;
StatusConvertTen convertToTen(const char *numStr, int base, bool isNeg,
                              long long *res);