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

typedef enum {
  ALPHA_OK,
  ALPHA_FILEOUT_ERR,
} StatusAlpha;
StatusAlpha countAlphaChars(FILE *fileIn, FILE *fileOut);

typedef enum {
  SPECIAL_OK,
  SPECIAL_FILEOUT_ERR,
} StatusSpecial;
StatusSpecial countSpecialChars(FILE *fileIn, FILE *fileOut);

typedef enum {
  HEX_OK,
  HEX_OVERFLOW,
} StatusHex;
StatusHex charToHex(const char ch, char *res);
typedef enum {
  REPLACE_OK,
  REPLACE_FAULT,
} StatusReplace;
StatusReplace replaceWithHex(FILE *fileIn, FILE *fileOut);