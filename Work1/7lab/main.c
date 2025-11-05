#include "funcs.h"
#include <stdio.h>

typedef enum returnCode {
  OK,
  INPUT_ERR,
  OVERFLOW_ERR,
  FILE_OPEN_ERR,
  FILE_WRITE_ERR,
  FILENAME_ERR,
  XZ_ERR
} returnCode;

#define closeAll                                                               \
  fclose(fileIn);                                                              \
  fclose(fileOut)

int main(int argc, char **argv) {
  if (argc != 3) {
    usage();
    return INPUT_ERR;
  }
  StatusConvertFile statusConvFile;
  char *fileInName = argv[1], *fileOutName = argv[2];

  FILE *fileIn = fopen(fileInName, "r");
  if (!fileIn) {
    printOpenErr(fileInName);
    return FILE_OPEN_ERR;
  }
  FILE *fileOut = fopen(fileOutName, "w");
  if (!fileOut) {
    printOpenErr(fileOutName);
    fclose(fileIn);
    return FILE_OPEN_ERR;
  }

  statusConvFile = convertFile(fileIn, fileOut);
  switch (statusConvFile) {
  case CONVFILE_ALLOC_ERR:
    printf(" alloc\n");
    closeAll;
    return XZ_ERR;
  case CONVFILE_ERR:
    printf("err  kakaya\n");
    closeAll;
    return XZ_ERR;
  case CONVFILE_OK:
    printf("ok\n");
    closeAll;
    break;
  case CONVFILE_NUMBER_TOO_LONG:
    printf("number ploxa\n");
    closeAll;
    return XZ_ERR;
  case CONVFILE_INVALID_CHAR:
    printf("char ploxa\n");
    closeAll;
    return XZ_ERR;
  }
  closeAll;
  return OK;
}