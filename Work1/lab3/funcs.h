#include <stdbool.h>

typedef enum {
  CONTAINS_NOT_DIGITS,
  NUMBER_OVERFLOW,
  NOT_POSITIVE_NUMBER,
  NUMBER_OK
} NumberValidateIntStatus;
NumberValidateIntStatus validateNumber(const char *numberStr, int *number);

typedef enum { FLAG_UNKNOWN, FLAG_NOT_FOUND, FLAG_OK } FlagParseStatus;
FlagParseStatus parseFlag(const char *arg, const char *allowedFlags,
                          char *flag);
typedef enum { EQ_OK = 0, EQ_FAULT } StatusEquation;

StatusEquation **solveSqrEquation(double eps, double a, double b, double c,
                                  double *res[8][2]);
typedef enum {
  MULT_OK,
  A_LESS_B_FAULT,
  NUMBER_ZERO_FAULT,
} StatusMultiple;
StatusMultiple isMultiple(int a, int b, bool *isMult);

typedef enum { TRI_OK, TRI_FAULT } StatusTriangle;
StatusTriangle isTriangleSides(double eps, double a, double b, double c,
                               bool *isTriangle);