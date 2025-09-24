#include <stdbool.h>
#include <stdio.h>
typedef enum {
  FLAG_UNKNOWN,
  FLAG_NOT_FOUND,
  FLAG_OK,
} FlagParseStatus;
FlagParseStatus parseFlag(const char *arg, const char *allowedFlags, char *flag,
                          bool *isNAdded);
typedef enum {
  REMOVE_OK,
  REMOVE_FILEOUT_ERR,
} StatusRemove;
StatusRemove removeArabicNums(FILE *fileIn, FILE *fileOut);