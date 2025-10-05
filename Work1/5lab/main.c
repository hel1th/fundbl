#include "funcs.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define closeAll                                                               \
  fclose(fileIn);                                                              \
  fclose(fileOut)

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
  const char prefix[] = "out_";
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
    if (strlen(argv[3]) > strlen(fileOutName) - 1) {
      printf("Filename is too long! Must be under 254 chars\n");
      return FILENAME_ERR;
    }
    strcpy(fileOutName, argv[3]);
  } else {
    if (argc != 3) {
      printf("Wrong input! Must be:\n");
      printf("<program> -<flag> <fileInput>\n");
      return INPUT_ERR;
    }
    strcpy(fileOutName, prefix);
    if (strlen(argv[2]) > strlen(fileOutName) - strlen(prefix) - 1) {
      printf("Filename is too long! Must be under 250 chars\n");
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
  StatusAlpha statusCountLetters;
  StatusSpecial statusCountSpecials;
  StatusReplace statusReplace;
  switch (flag) {
  case 'd':
    statusRemoveNums = removeArabicNums(fileIn, fileOut);
    switch (statusRemoveNums) {
    case REMOVE_FILEOUT_ERR:
      printf("Something went wrong during writing to output file \"%s\"\n",
             fileOutName);
      closeAll;
      return FILE_WRITE_ERR;
    case REMOVE_OK:
      printf("Arabic numerals successufully removed from \"%s\"\n", fileInName);
      printf("Output file is %s\n", fileOutName);
    }
    break;
  case 'i':
    statusCountLetters = countAlphaChars(fileIn, fileOut);
    switch (statusCountLetters) {
    case ALPHA_FILEOUT_ERR:
      printf("Something went wrong during writing to output file \"%s\"\n",
             fileOutName);
      closeAll;
      return FILE_WRITE_ERR;
    case ALPHA_OK:
      printf("Letters was successfully counted from \"%s\"\n", fileInName);
      printf("Output file is: %s\n", fileOutName);
    }
    break;
  case 's':
    statusCountSpecials = countSpecialChars(fileIn, fileOut);
    switch (statusCountSpecials) {
    case SPECIAL_FILEOUT_ERR:
      printf("Something went wrong during writing to output file \"%s\"\n",
             fileOutName);
      closeAll;
      return FILE_WRITE_ERR;
    case SPECIAL_OK:
      printf("Special chars was successfully counted from \"%s\"\n",
             fileInName);
      printf("Output file is: %s\n", fileOutName);
      break;
    }
    break;
  case 'a':
    statusReplace = replaceWithHex(fileIn, fileOut);
    switch (statusReplace) {
    case REPLACE_FAULT:
      printf("Something went wrong during writing to output file \"%s\"\n",
             fileOutName);
      closeAll;
      return FILE_WRITE_ERR;
    case REPLACE_OK:
      printf("Special chars was successfully replaced from \"%s\"\n",
             fileInName);
      printf("Output file is: %s\n", fileOutName);
      break;
    }

    break;
  }
  closeAll;
  return OK;
}
