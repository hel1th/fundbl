#include "funcs.h"
#include <math.h>
#include <stdio.h>

void test(double eps, double a, double b, double c, bool expected) {
  bool result = false;
  StatusTriangle status = isRightTriangle(eps, a, b, c, &result);

  if (status != TRI_OK) {
    printf("FAIL: invalid input for (%.2f, %.2f, %.2f)\n", a, b, c);
    return;
  }

  if (result == expected) {
    printf("PASS: (%.2f, %.2f, %.2f)\n", a, b, c);
  } else {
    printf("FAIL: (%.2f, %.2f, %.2f) -> got %d, expected %d\n", a, b, c, result,
           expected);
  }
}

int main() {
  double eps = 1e-6;

  test(eps, 3.0, 4.0, 5.0, true);

  test(eps, 5.0, 12.0, 13.0, true);

  test(eps, 22.0, 22.0, 22.0, false);

  test(eps, 1.0, 2.0, 3.0, false);

  test(eps, 1.0, 1.0, sqrt(2.0), true);

  return 0;
}