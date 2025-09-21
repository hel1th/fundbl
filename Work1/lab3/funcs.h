#include <stdbool.h>

typedef enum {
  NUMBER_CONTAINS_NOT_DIGITS,
  NUMBER_OVERFLOW,
  NOT_POSITIVE_NUMBER,
  NUMBER_OK
} NumberValidateStatus;
NumberValidateStatus validateIntNumber(const char *numberStr, int *number);
NumberValidateStatus validateFloatNumber(const char *numberStr, double *number);

typedef enum { FLAG_UNKNOWN, FLAG_NOT_FOUND, FLAG_OK } FlagParseStatus;
FlagParseStatus parseFlag(const char *arg, const char *allowedFlags,
                          char *flag);
typedef enum { EQ_OK = 0, EQ_FAULT } StatusEquation;

StatusEquation **solveSqrEquation(double eps, double a, double b, double c,
                                  double *res[8][2]);
typedef enum {
  MULT_OK,
  MULT_A_LESS_B_FAULT,
  MULT_NUMBER_ZERO_FAULT,
} StatusMultiple;
StatusMultiple isMultiple(int a, int b, bool *isMult);

typedef enum { TRI_OK, TRI_NEGATIVE_NUMS_FAULT } StatusTriangle;
StatusTriangle isRightTriangle(double eps, double a, double b, double c,
                               bool *isRight);