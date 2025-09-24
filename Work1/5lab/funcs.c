#include "funcs.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

FlagParseStatus parseFlag(const char *arg, const char *allowedFlags, char *flag,
                          bool *isNAdded) {
  if (arg[0] != '-' && arg[0] != '/') {
    return FLAG_NOT_FOUND;
  }
  switch (strlen(arg)) {
  case 2:
    break;
  case 3:
    if (arg[1] == 'n') {
      *isNAdded = true;
      break;
    }
    return FLAG_UNKNOWN;
    break;
  default:
    return FLAG_UNKNOWN;
  }
  const char *found = strchr(allowedFlags, *isNAdded ? arg[2] : arg[1]);
  if (!found) {
    return FLAG_UNKNOWN;
  }
  *flag = *found;
  return FLAG_OK;
}

StatusRemove removeArabicNums(FILE *fileIn, FILE *fileOut) {
  char buffer[1024];
  char *ch = buffer;
  size_t i;
  while (fgets(buffer, 1024, fileIn) != NULL) {
    i = 0;
    while (*(ch + i) != '\0') {
      if (isdigit(*(ch + i))) {
        *(ch + i) = ' ';
      }
      ++i;
    }

    if (fputs(buffer, fileOut) == EOF) {
      return REMOVE_FILEOUT_ERR;
    }

    if (feof(fileIn)) {
      break;
    }
  }
  return REMOVE_OK;
}