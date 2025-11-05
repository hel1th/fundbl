#include "./include/comp_e.h"
#include "./include/comp_gamma.h"
#include "./include/comp_ln2.h"
#include "./include/comp_pi.h"
#include "./include/comp_sqrt2.h"
#include <stdio.h>

int main() {
  double eps = 1e-6;

  double e_lim = limit_e(eps);
  double e_ser = series_e(eps);
  double e_eq = equation_e(eps);
  printf("Number e as limit, series, and equation:\n");
  printf("e = %lf\n", e_lim);
  printf("e = %lf\n", e_ser);
  printf("e = %lf\n", e_eq);

  printf("-------------------\n");
  double pi_lim = limit_pi(eps);
  double pi_ser = series_pi(eps);
  double pi_eq = equation_pi(eps);
  printf("Number pi as limit, series, and equation:\n");
  printf("pi = %lf\n", pi_lim);
  printf("pi = %lf\n", pi_ser);
  printf("pi = %lf\n", pi_eq);

  printf("-------------------\n");
  double ln2_lim = limit_ln2(eps);
  double ln2_ser = series_ln2(eps);
  double ln2_eq = equation_ln2(eps);
  printf("Number ln2 as limit, series, and equation:\n");
  printf("ln2 = %lf\n", ln2_lim);
  printf("ln2 = %lf\n", ln2_ser);
  printf("ln2 = %lf\n", ln2_eq);

  printf("-------------------\n");
  double sqrt2_lim = limit_sqrt2(eps);
  double sqrt2_ser = series_sqrt2(eps);
  double sqrt2_eq = equation_sqrt2(eps);
  printf("Number sqrt2 as limit, series, and equation:\n");
  printf("sqrt2 = %lf\n", sqrt2_lim);
  printf("sqrt2 = %lf\n", sqrt2_ser);
  printf("sqrt2 = %lf\n", sqrt2_eq);

  printf("-------------------\n");
  double gamma_lim = limit_gamma(eps);
  double gamma_ser = series_gamma(eps);
  double gamma_eq = equation_gamma(eps);
  printf("Number gamma as limit, series, and equation:\n");
  printf("gamma = %lf\n", gamma_lim);
  printf("gamma = %lf\n", gamma_ser);
  printf("gamma = %lf\n", gamma_eq);
  printf("-------------------\n");

  printf("Epsilon is equal to %lf\n", eps);

  return 0;
}