double get_eps(void);

int solve1(double a, double b, double eps, int MaxIt, double (*f)(double), double *x);
int solve2(double x0, double eps, int MaxIt, double (*f)(double), double (*d)(double), double *x_s);
int solve3(double a, double b, double eps, int MaxIt, double (*f)(double), double *x);
int solve4(double a, double b, double eps, int MaxIt, double (*f)(double), double *x);
int lagrange_interpolation(const double x0, double *x, double *y, int n, double *res);
int solve5(double a, double b, double eps, int MaxIt, double (*f)(double), double *x);
int solve6(double a, double b, double eps, int MaxIt, int m, double *d, double (*f)(double), double *x);
int solve7(double x0, double eps, int MaxIt, double (*f)(double), double *x_s);

int solve8(double a, double b, double eps, int MaxIt, double (*f)(double), double *x);
int solve9(double a, double b, double eps, int MaxIt, double (*f)(double), double *x);
double get_lagr2(double fx[2], double x[2]);
double get_lagr3(double fx[3], double x[3]);
int solve10(double a, double b, double eps, int MaxIt, double (*f)(double), double *x);

