double get_eps(void);

int solve1(const double x0, double *x, double *y, int n, double *res);
int solve2(const double x0, double *x, double *y, int n, double *res);
int solve3(const double x0, double *x, double *y, int n, double *res);
int solve4(const double x0, double *x, double *y, double *d, int n, double *res);

double m_sin(double x, double eps);
double m_cos(double x, double eps);
double m_exp(double x, double eps);
int m_log(double x, double eps, double *res);

