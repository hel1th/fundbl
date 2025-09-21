#include "funcs.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum returnCode {
  OK,
  INPUT_ERR,
  OVERFLOW_ERR,
} returnCode;

int main(int argc, const char **argv) {
  char flag;
  const char *ALLOWED_FLAGS = "qmt";
  FlagParseStatus flagStatus = parseFlag(argv[1], ALLOWED_FLAGS, &flag);
  if (flagStatus != FLAG_OK) {
    printf("Invalid flag: %s", argv[1]);
    return INPUT_ERR;
  }
  int mult = 0, div = 0;
  bool isMult = false;
  double eps = 0, side1 = 0, side2 = 0, side3 = 0;
  bool isTriangle = false;

  switch (flag) {
  case 'q':
    // double res[8][2];
    // double eps, a, b, c;
    // solveSqrEquation(eps, a, b, c, res);
    break;
  case 'm':
    if (argc != 4) {
      printf("Wrong numbers of args!\n");
      return INPUT_ERR;
    }
    NumberValidateIntStatus number1Status = validateIntNumber(argv[2], &mult);
    if (number1Status != NUMBER_OK) {
      printf("Invalid number: %s\nNumber must be integer not equal 0", argv[2]);
      return INPUT_ERR;
    }
    NumberValidateIntStatus number2Status = validateIntNumber(argv[3], &div);
    if (number2Status != NUMBER_OK) {
      printf("Invalid number: %s\nNumber must be integer not equal 0", argv[3]);
      return INPUT_ERR;
    }

    StatusMultiple multStatus = isMultiple(mult, div, &isMult);
    switch (multStatus) {
    case A_LESS_B_FAULT:
      printf("First number must be greater or equal than second!\n");
      return INPUT_ERR;
    case NUMBER_ZERO_FAULT:
      printf("Numbers can't be zero!\n");
      return INPUT_ERR;
    case MULT_OK:
      if (isMult) {
        printf("%d is multiple of %d\n", mult, div);
      } else {
        printf("%d is not multiple of %d\n", mult, div);
      }
    }
    break;
  case 't':
    if (argc != 5) {
      printf("Wrong numbers of args!\n");
      return INPUT_ERR;
    }
    NumberValidateIntStatus epsStatus = validateIntNumber(argv[2], &eps);
    if (number1Status != NUMBER_OK) {
      printf("Invalid number: %s\nNumber must be positive integer", argv[2]);
      return INPUT_ERR;
    }
    NumberValidateIntStatus side1Status = validateIntNumber(argv[3], &side1);
    if (number1Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[2]);
      return INPUT_ERR;
    }
    NumberValidateIntStatus side2Status = validateIntNumber(argv[4], &side2);
    if (number2Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[3]);
      return INPUT_ERR;
    }
    NumberValidateIntStatus side3Status = validateIntNumber(argv[5], &side3);
    if (number2Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[3]);
      return INPUT_ERR;
    }
    StatusTriangle trigStatus =
        isTriangleSides(eps, side1, side2, side3, &isTriangle);
    break;
  }
  return OK;
}