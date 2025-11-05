#include "funcs.h"
#include <stdio.h>

typedef enum returnCode {
  OK,
  INPUT_ERR,
  OVERFLOW_ERR,
  FILE_OPEN_ERR,
  FILE_WRITE_ERR,
  FILENAME_ERR,
} returnCode;

int main(int argc, char **argv) {
  if (argc != 2) {
    usage();
    return INPUT_ERR;
  }
  unsigned long long n;
  StatusCompute statusComp;
  const char *epsRaw = argv[1];
  double eps = 0.0, res = 0.0;
  StatusNumberValidate epsStatus = validateFloatNumber(epsRaw, &eps);
  if (epsStatus != NUMBER_OK) {
    printf("Wrong input %s\n Eps must be positive float number.\n", epsRaw);
  }
  statusComp = computeIntegral(eps, func_a, &n, &res);
  if (statusComp != COMP_OK) {
    printf("Something went wrond during computing!\n");
  } else {
    printf("Result of integral A) is I = %lf reached by n = %llu\n", res, n);
  }
  statusComp = computeIntegral(eps, func_b, &n, &res);
  if (statusComp != COMP_OK) {
    printf("Something went wrond during computing!\n");
  } else {
    printf("Result of integral B) is I = %lf reached by n = %llu\n", res, n);
  }
  statusComp = computeIntegral(eps, func_c, &n, &res);
  if (statusComp != COMP_OK) {
    printf("Something went wrond during computing!\n");
  } else {
    printf("Result of integral C) is I = %lf reached by n = %llu\n", res, n);
  }
  statusComp = computeIntegral(eps, func_d, &n, &res);
  if (statusComp != COMP_OK) {
    printf("Something went wrond during computing!\n");
  } else {
    printf("Result of integral D) is I = %lf reached by n = %llu\n", res, n);
  }

  return OK;
}