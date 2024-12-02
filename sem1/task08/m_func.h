#define EPS 1e-16

#define swap(a, b, temp) \
	temp = a; \
	a = b; \
	b = temp; \

double m_fabs(double x);
int is_equal(double a, double b);
int m_gcd(int a, int b);
double m_fmin(double *a, double *b);
double m_fmax(double *a, double *b);
