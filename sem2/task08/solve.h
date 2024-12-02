double get_scalar_product(double *a, double *b, int n);
        // returns scalar product of vectors (a, b) with length n

int solve_system_L(double *a, double *x, double *b, int n, double specEps);
int solve_system_U(double *a, double *x, double *b, int n, double specEps);
int solve(double *a, int n, double *b, double *x, double normA);
