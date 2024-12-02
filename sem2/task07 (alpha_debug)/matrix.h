int is_simm(double *a, int n);
	// returns 1 if matrix is symmetrical, 0 otherwise

double get_trace(double *a, int n);
	// returns trace of square matrix

void transpose_sqr(double *a, int n);
	// transposes square matrix

int swap_lines(double *a, int n, int m, int i, int j);
	// swap i-th and j-th lines. numbering starts from 0

int swap_columns(double *a, int n, int m, int i, int j);
	// swap i-th and j-th columns. numbering starts from 0

int add_line(double *a, int n, int m , int i, int j, double g);
	// add to the j-th line the i-th line multiplied by g

void multiply_matrices(double *a, double *b, int n, int m, int k, double *c);
	// A*B = C

void add_matrices(double *a, double a_k, double *b, double b_k ,int n, int m, double *c);
	// A*a_k + B*b_k = C
        // C can be equal with A or B

double get_scalar_product(double *a, double *b, int n);
	// returns scalar product of vectors (a, b) with length n
