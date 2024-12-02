#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "norm.h"

int set_r1(double *a, double *b, double *x, int n, double *r1, double Eps);
void set_r2(double *x, int n, double *r2);
int calculate_r(double *a, double *x, double *b, int n, double *r1, double *r2, double Eps);
int check(double *a, int n, double Eps_norm);
int main_0(int argc, char **argv, int task, int (*solve)(double *, double *, double *, int));