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
  bool isRight = false;

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
    NumberValidateStatus number1Status = validateIntNumber(argv[2], &mult);
    if (number1Status != NUMBER_OK) {
      printf("Invalid number: %s\nNumber must be integer not equal 0", argv[2]);
      return INPUT_ERR;
    }
    NumberValidateStatus number2Status = validateIntNumber(argv[3], &div);
    if (number2Status != NUMBER_OK) {
      printf("Invalid number: %s\nNumber must be integer not equal 0", argv[3]);
      return INPUT_ERR;
    }

    StatusMultiple multStatus = isMultiple(mult, div, &isMult);
    switch (multStatus) {
    case MULT_A_LESS_B_FAULT:
      printf("First number must be greater or equal than second!\n");
      return INPUT_ERR;
    case MULT_NUMBER_ZERO_FAULT:
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
    if (argc != 6) {
      printf("Wrong numbers of args!\n");
      return INPUT_ERR;
    }
    NumberValidateStatus epsStatus = validateFloatNumber(argv[2], &eps);
    if (epsStatus != NUMBER_OK) {
      printf("Invalid number: %s\nNumber must be positive integer", argv[2]);
      return INPUT_ERR;
    }
    NumberValidateStatus side1Status = validateFloatNumber(argv[3], &side1);
    if (side1Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[2]);
      return INPUT_ERR;
    }
    NumberValidateStatus side2Status = validateFloatNumber(argv[4], &side2);
    if (side2Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[3]);
      return INPUT_ERR;
    }
    NumberValidateStatus side3Status = validateFloatNumber(argv[5], &side3);
    if (side3Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[3]);
      return INPUT_ERR;
    }
    StatusTriangle trigStatus =
        isRightTriangle(eps, side1, side2, side3, &isRight);
    if (trigStatus == TRI_NEGATIVE_NUMS_FAULT) {
      printf("Invalid numbers! Number must be positive");
    }
    if (trigStatus == TRI_OK) {
      printf("Triangle with sides %.2lf %.2lf %.2lf", side1, side2, side3);
      if (isRight) {
        printf(" can ");
      } else {
        printf(" can't ");
      }
      printf("be right triangle");
    }
    break;
  }
  return OK;
}