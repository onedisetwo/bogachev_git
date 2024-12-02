double get_scalar_product(double *a, double *b, int n);
        // returns scalar product of vectors (a, b) with length n

int solve1(double *a, double *x0, double *x, double **x_m, int n, int m, double *r1);
void solve2(double *a, double *b, double *x0, double *m1, int n, int m, double t, double **x_m);
int solve3(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double **x_m);
int solve4(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double **x_m);

void multiply_diag(double *a, double *x, int n);
int multiply_diag_inv(double *a, double *x, double *res, int n);
//double get_scalar_product_spec5(double *a, double *u, int n);
int solve5(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double **x_m);
//double get_scalar_product_spec6(double *v, double *a, double *u, int n);
int solve6(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double **x_m);
int solve7(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double t, double **x_m);

int solve_system_DL(double *a, double *x, double *b, double tb, int n);
int solve8(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t);
int solve_system_DR(double *a, double *x, double *b, double tb, int n);
int solve9(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t);
int solve10(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t);
