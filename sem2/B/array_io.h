#include <stdio.h>
#include "help_funcs.h"

int read_matrix(double *a, int n, int m, const char * name);
void print_matrix(double *a, int n, int m, int p);
int init_matrix(double *a, int n, int m, int k);
void init_b_vector(double *a, double *b, int n);