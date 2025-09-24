#include "funcs.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum returnCode {
  OK,
  INPUT_ERR,
  OVERFLOW_ERR,
  FILE_OPEN_ERR,
  FILE_WRITE_ERR,
  FILENAME_ERR,
} returnCode;

int main(int argc, const char **argv) {
  if (argc < 2) {
    printf("Not enough args!\n");
    return INPUT_ERR;
  }
  const char *rawFlag = argv[1];
  char flag;
  const char *ALLOWED_FLAGS = "disa";
  char const *fileInName = argv[2];
  char fileOutName[255];
  bool isOutputNameGiven = false;
  FlagParseStatus flagStatus =
      parseFlag(argv[1], ALLOWED_FLAGS, &flag, &isOutputNameGiven);
  if (flagStatus != FLAG_OK) {
    printf("Invalid flag: %s\n", rawFlag);
    return INPUT_ERR;
  }

  if (isOutputNameGiven) {
    if (argc != 4) {
      printf("Wrong input! Must be:\n");
      printf("<program> -n<flag> <fileInput> <fileOutput>\n");
      return INPUT_ERR;
    }
    if (strlen(argv[3]) > 251) {
      printf("Filename is too long! Must be under 251 chars\n");
      return FILENAME_ERR;
    }
    strcpy(fileOutName, argv[3]);
  } else {
    if (argc != 3) {
      printf("Wrong input! Must be:\n");
      printf("<program> -<flag> <fileInput>\n");
      return INPUT_ERR;
    }
    strcpy(fileOutName, "out_");
    if (strlen(argv[2]) > 251) {
      printf("Filename is too long! Must be under 251 chars\n");
      return FILENAME_ERR;
    }
    strcat(fileOutName, argv[2]);
  }

  FILE *fileIn;
  if ((fileIn = fopen(argv[2], "r")) == NULL) {
    printf("Input file \"%s\" can't be open!\n", argv[2]);
    return FILE_OPEN_ERR;
  }

  FILE *fileOut;
  if ((fileOut = fopen(fileOutName, "w")) == NULL) {
    printf("Output file \"%s\" can't be open or created!\n", fileOutName);
    fclose(fileIn);
    return FILE_OPEN_ERR;
  }

  StatusRemove statusRemoveNums;
  switch (flag) {
  case 'd':
    statusRemoveNums = removeArabicNums(fileIn, fileOut);
    switch (statusRemoveNums) {
    case REMOVE_FILEOUT_ERR:
      printf("Something went wrong during writing to output file \"%s\"\n",
             fileOutName);
      fclose(fileIn);
      fclose(fileOut);
      return FILE_WRITE_ERR;
    case REMOVE_OK:
      printf("Arabic numerals successufully removed from \"%s\"\n", fileInName);
      printf("Output file is %s\n", fileOutName);
    }
    break;
  case 'i':
    break;
  case 's':
    break;
  case 'a':
    break;
  }
  fclose(fileIn);
  fclose(fileOut);
  return OK;
}
