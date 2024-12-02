int get_k_name(int*, char**, int*, int, char**);

int get_r1_linear_system(double *a, double *x, double *b, int n, double *r1, double normA);
	// May happen division by zero
void get_r2_linear_system(double *x, int n, double *r2);
void init_b(double *a, double *b, int n);
