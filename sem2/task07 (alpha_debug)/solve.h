int solve1(double *a, double *x0, double *x, double **x_m, int n, int m, double *r1);
double* solve2(double *a, double *b, double *x0, double *m1, int n, int m, double t);
double* solve3(double *a, double *b, double *x, double *m1, double *m2, int n, int m);
double* solve4(double *a, double *b, double *x, double *m1, double *m2, int n, int m);

void multiply_diag(double *a, double *x, int n);
void multiply_diag_inv(double *a, double *x, int n);
double get_scalar_product_spec5(double *a, double *u, int n);
double* solve5(double *a, double *b, double *x, double *m1, double *m2, int n, int m);
double get_scalar_product_spec6(double *v, double *a, double *u, int n);
double* solve6(double *a, double *b, double *x, double *m1, double *m2, int n, int m);
double* solve7(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double t);

int solve_system_DL(double *a, double *x, double *b, double tb, int n);
int solve8(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t);
int solve_system_DR(double *a, double *x, double *b, double tb, int n);
int solve9(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t);
int solve10(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t);
