#include <stddef.h>
void usage();
typedef enum {
  NUMBER_CONTAINS_NOT_DIGITS,
  NUMBER_OVERFLOW,
  NOT_POSITIVE_NUMBER,
  NUMBER_OK
} StatusNumberValidate;
StatusNumberValidate validateFloatNumber(const char *numberStr, double *value);

typedef enum {
  FUNC_OK,
  FUNC_DIV_BY_ZERO_ERR,
  FUNC_OVERFLOW,
  FUNC_UNDEFIND,
} StatusFunc;
StatusFunc func_a(double eps, double x, double *res);
StatusFunc func_b(double eps, double x, double *res);
StatusFunc func_c(double eps, double x, double *res);
StatusFunc func_d(double eps, double x, double *res);

typedef enum {
  TRAP_OK,
  TRAP_FUNC_ERR,
  TRAP_OVERFLOW,
  TRAP_ERR,
} StatusTrap;
StatusTrap trapeziodMethod(const double a, const double b, int n,
                           StatusFunc (*func)(double eps, double x,
                                              double *res));

typedef enum {
  COMP_OK,
  COMP_TRAP_ERR,
  COMP_OVERFLOW,
} StatusCompute;
StatusCompute computeIntegral(const double eps,
                              StatusFunc (*func)(double, double, double *),
                              unsigned long long *n, double *res);