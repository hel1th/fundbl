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
  EqSol solves[5];
  double epsilon = 0, a = 0, b = 0, c = 0;
  int mult = 0, div = 0;
  bool isMult = false;
  double eps = 0, side1 = 0, side2 = 0, side3 = 0;
  bool isRight = false;

  if (argc < 2) {
    printf("Not enough args!\n");
    return INPUT_ERR;
  }
  FlagParseStatus flagStatus = parseFlag(argv[1], ALLOWED_FLAGS, &flag);
  if (flagStatus != FLAG_OK) {
    printf("Invalid flag: %s\n", argv[1]);
    return INPUT_ERR;
  }

  switch (flag) {
  case 'q':
    if (argc != 6) {
      printf("Wrong numbers of args! Must be:\n");
      printf("<program> -<flag> <eps> <a> <b> <c> or\n");
      printf("<program> /<flag> <eps> <a> <b> <c>\n");
      return INPUT_ERR;
    }
    NumberValidateStatus epsStatus = validateFloatNumber(argv[2], &eps);
    if (epsStatus != NUMBER_OK) {
      printf("Invalid number: %s\nNumber must be positive floating point\n",
             argv[2]);
      return INPUT_ERR;
    }
    NumberValidateStatus aStatus = validateFloatNumber(argv[3], &a);
    if (aStatus != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[3]);
      return INPUT_ERR;
    }
    NumberValidateStatus bStatus = validateFloatNumber(argv[4], &b);
    if (bStatus != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[4]);
      return INPUT_ERR;
    }
    NumberValidateStatus cStatus = validateFloatNumber(argv[5], &c);
    if (cStatus != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[5]);
      return INPUT_ERR;
    }
    StatusEquation statusEq = solveSixSqrEquations(eps, a, b, c, solves);
    if (statusEq != EQ_OK) {
      printf(
          "Something went wrong during solving equation.\nEps must be > 0!\n");
      return INPUT_ERR;
    }
    for (int i = 0; i < 6; i++) {
      printf("------------------\n");
      printEqSolution(solves[i]);
    }
    printf("------------------\n");
    break;
  case 'm':
    if (argc != 4) {
      printf("Wrong numbers of args! Must be:\n");
      printf("<program> -<flag> <a> <b> or\n");
      printf("<program> /<flag> <a> <b>\n");
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
      printf("Wrong numbers of args! Must be:\n");
      printf("<program> -<flag> <eps> <a> <b> <c> or\n");
      printf("<program> /<flag> <eps> <a> <b> <c>\n");
      return INPUT_ERR;
    }
    NumberValidateStatus epsilonStatus = validateFloatNumber(argv[2], &epsilon);
    if (epsilonStatus != NUMBER_OK) {
      printf("Invalid number: %s\nNumber must be positive floating point\n",
             argv[2]);
      return INPUT_ERR;
    }
    NumberValidateStatus side1Status = validateFloatNumber(argv[3], &side1);
    if (side1Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[3]);
      return INPUT_ERR;
    }
    NumberValidateStatus side2Status = validateFloatNumber(argv[4], &side2);
    if (side2Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[4]);
      return INPUT_ERR;
    }
    NumberValidateStatus side3Status = validateFloatNumber(argv[5], &side3);
    if (side3Status != NUMBER_OK) {
      printf("Invalid number: %s\n", argv[5]);
      return INPUT_ERR;
    }
    StatusTriangle trigStatus =
        isRightTriangle(epsilon, side1, side2, side3, &isRight);
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