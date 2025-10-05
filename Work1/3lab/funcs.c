#include "funcs.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

FlagParseStatus parseFlag(const char *arg, const char *allowedFlags,
                          char *flag) {
  if (arg[0] != '-' && arg[0] != '/') {
    return FLAG_NOT_FOUND;
  }
  if (arg[2] != '\0') {
    return FLAG_UNKNOWN;
  }
  const char *found = strchr(allowedFlags, arg[1]);
  if (!found) {
    return FLAG_UNKNOWN;
  }
  *flag = *found;
  return FLAG_OK;
}

NumberValidateStatus validateIntNumber(const char *numberStr, int *number) {
  char *endptr;
  long num = strtol(numberStr, &endptr, 10);

  if (*endptr != '\0') {
    return NUMBER_CONTAINS_NOT_DIGITS;
  }
  if (num > INT_MAX || num < INT_MIN) {
    return NUMBER_OVERFLOW;
  }
  *number = (int)num;
  return NUMBER_OK;
}

NumberValidateStatus validateFloatNumber(const char *numberStr, double *value) {
  char *endptr;
  double num = strtod(numberStr, &endptr);
  if (isinf(num)) {
    return NUMBER_OVERFLOW;
  }
  if (*endptr != '\0') {
    return NUMBER_CONTAINS_NOT_DIGITS;
  }

  *value = num;
  return NUMBER_OK;
}

void solveEq(double eps, double a, double b, double c, EqSol *solve) {
  solve->a = a;
  solve->b = b;
  solve->c = c;

  if (fabs(a) < eps) {
    if (fabs(b) < eps) {
      if (fabs(c) < eps) {
        solve->type = INFINITY_ROOTS;
        return;
      } else {
        solve->type = NO_ROOTS;
        return;
      }
    }
    solve->type = ONE_ROOT;
    solve->x1 = -c / b;
    solve->x2 = solve->x1;
    return;
  }

  double D = b * b - 4 * a * c;
  if (D < -eps) {
    solve->type = NO_ROOTS;
    solve->x1 = 0;
    solve->x2 = 0;
    return;
  }
  if (fabs(D) < eps) {
    solve->type = ONE_ROOT;
    solve->x1 = -b / (2 * a);
    solve->x2 = solve->x1;
    return;
  }
  solve->type = TWO_ROOTS;
  solve->x1 = (-b + sqrt(D)) / (2 * a);
  solve->x2 = (-b - sqrt(D)) / (2 * a);
  return;
}

StatusEquation solveSixSqrEquations(double eps, double a, double b, double c,
                                    EqSol *res) {
  if (eps <= 0) {
    return EQ_EPS_ZERO;
  }
  double coeff[] = {a, b, c};
  int permutations[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
                            {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
  double a1, b1, c1;
  EqSol solve;
  for (int i = 0; i < 6; ++i) {
    a1 = coeff[permutations[i][0]];
    b1 = coeff[permutations[i][1]];
    c1 = coeff[permutations[i][2]];
    solveEq(eps, a1, b1, c1, &solve);
    *(res + i) = solve;
  };
  return EQ_OK;
}
void printEqSolution(EqSol solve) {
  printf("Quadratic equation %.3lfx^2 + (%.3lfx) + (%.3lf) = 0.\nSolution: ",
         solve.a, solve.b, solve.c);
  switch (solve.type) {
  case NO_ROOTS:
    printf("There are no roots.\n");
    break;
  case INFINITY_ROOTS:
    printf("There are infinity roots.\n");
    break;
  case ONE_ROOT:
    printf("There is one root x1 = %.3lf.\n", solve.x1);
    break;
  case TWO_ROOTS:
    printf("There are two roots x1 = %.3lf and x2 = %.3lf.\n", solve.x1,
           solve.x2);
    break;
  }
}

StatusMultiple isMultiple(int a, int b, bool *isMult) {
  if (abs(a - b) < 0) {
    return MULT_A_LESS_B_FAULT;
  }
  if (a * b == 0) {
    return MULT_NUMBER_ZERO_FAULT;
  }
  if (a % b == 0) {
    *isMult = true;
  } else {
    *isMult = false;
  }
  return MULT_OK;
}

StatusTriangle isRightTriangle(double eps, double a, double b, double c,
                               bool *isRight) {
  if (eps < 0 || a < eps || b < eps || c < eps) {
    return TRI_NEGATIVE_NUMS_FAULT;
  }
  *isRight = false;
  if (fabs(a * a + b * b - c * c) < eps || fabs(a * a + c * c - b * b) < eps ||
      fabs(b * b + c * c - a * a) < eps) {
    *isRight = true;
  }
  return TRI_OK;
}