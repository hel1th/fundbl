

#include <stdlib.h>
double factorial(int n) {
  double res = 1.0;
  for (int i = 1; i < n + 1; ++i)
    res *= i;
  return res;
}

int *findPrime(int count) {
  int *numbers = (int *)calloc(count, sizeof(int));

  for (int i = 2; i < count; ++i) {
    if (numbers[i]) {
      continue;
    }
    for (int j = i + i; j < count; j += i) {
      numbers[j] = 1;
    }
  }
  return numbers;
}