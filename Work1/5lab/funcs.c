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
// -d
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
// -i
StatusAlpha countAlphaChars(FILE *fileIn, FILE *fileOut) {
  char buffer[1024];
  char *ch = buffer;
  bool isEndLine = false;
  size_t i = 0;
  size_t count = 0;
  char tmp;
  while (fgets(buffer, 1024, fileIn) != NULL) {
    while (*(ch + i) != '\0') {
      tmp = tolower(*(ch + i));
      if (tmp == '\n') {
        isEndLine = true;
        break;
      }
      if ('a' <= tmp && tmp <= 'z') {
        ++count;
      }

      ++i;
    }
    if (isEndLine || feof(fileIn)) {
      sprintf(buffer, "%zu\n", count);
      isEndLine = false;
      count = 0;
      i = 0;
      if (fputs(buffer, fileOut) == EOF) {
        return ALPHA_FILEOUT_ERR;
      }
    }

    if (feof(fileIn)) {
      break;
    }
  }
  return ALPHA_OK;
}

// -s
StatusSpecial countSpecialChars(FILE *fileIn, FILE *fileOut) {
  char buffer[1024];
  char *ch = buffer;
  bool isEndLine = false;
  size_t i = 0;
  size_t count = 0;
  char tmp;
  while (fgets(buffer, 1024, fileIn) != NULL) {
    while (*(ch + i) != '\0') {
      tmp = tolower(*(ch + i));
      if (tmp == '\n') {
        isEndLine = true;
        break;
      }
      if (!('a' <= tmp && tmp <= 'z') && !('0' <= tmp && tmp <= '9') &&
          tmp != ' ') {
        ++count;
      }

      ++i;
    }
    if (isEndLine || feof(fileIn)) {
      sprintf(buffer, "%zu\n", count);
      isEndLine = false;
      count = 0;
      i = 0;
      if (fputs(buffer, fileOut) == EOF) {
        return SPECIAL_FILEOUT_ERR;
      }
    }
  }
  return SPECIAL_OK;
}

// -a
StatusReplace replaceWithHex(FILE *fileIn, FILE *fileOut) {
  char tmpStr[3];
  char c;
  StatusHex statusHex;
  while ((c = getc(fileIn)) != EOF) {
    if ((c != ' ' && c != '\n' && c != '\t') && !('0' <= c && c <= '9')) {

      statusHex = charToHex(c, tmpStr);
      if (statusHex == HEX_OVERFLOW) {
        return REPLACE_FAULT;
      }
    } else {
      tmpStr[0] = c;
      tmpStr[1] = '\0';
    }
    fputs(tmpStr, fileOut);
  }
  return REPLACE_OK;
}
// -a
StatusHex charToHex(char ch, char *res) {
  int temp = (int)ch, i = 0;
  while (temp > 0) {
    ++i;
    temp /= 16;
  }
  if (i-- > 2)
    return HEX_OVERFLOW;
  temp = (int)ch;
  while (temp > 0) {
    int rem = temp % 16;
    *(res + i--) = (rem < 10) ? ('0' + rem) : ('A' + (rem % 10));
    temp /= 16;
  }
  *(res + i) = '\0';
  return HEX_OK;
}
