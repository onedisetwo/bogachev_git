double get_eps(void);

int solve1(double x, double h, double (*f)(double), double *res);
int solve2(double x, double h, double (*f)(double), double *res);
int solve3(double x, double h, double (*f)(double), double *res);

int solve4(double a, double b, int n, double (*f)(double), double *res);
int solve5(double a, double b, int n, double (*f)(double), double *res);

double sign(double x);
int solve6(double a, double b, int n, double (*f)(double), double *res);
double get_lagr2(double fx[2], double);
double get_lagr3(double fx[3], double);
int solve7(double a, double b, int n, double (*f)(double), double *res);

int solve8(double a, double b, double eps, double (*f)(double), double *res, int *it);
int solve9(double a, double b, double eps, double (*f)(double), double *res, int *it);

int solve10(double a, const double eps, double (*f)(double), double *res, double *b);
int solve11(double a, const double eps, double (*f)(double), double *res, double *b);

double get_length(double x1, double y1, double x2, double y2);
int solve12(double a, double b, const double eps, double (*fx)(double), double (*fy)(double),
		double *res, int *it);

int lagrange_interpolation(const double x0, double *x, double *y, int n, double *res);

