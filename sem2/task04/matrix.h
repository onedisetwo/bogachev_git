int is_simm(double *a, int n);
double get_trace(double *a, int n);
void transpose_sqr(double *a, int n);
void solve4(double *a, int n);
void solve5(double *a, int n);

int swap_lines(double *a, int n, int m, int i, int j);
// swap i-th and j-th lines. numbering starts from 0

int swap_columns(double *a, int n, int m, int i, int j);
// swap i-th and j-th columns. numbering starts from 0

int add_line(double *a, int n, int m , int i, int j, double g);
// add to the j-th line the i-th line multiplied by g

void multiply_matrix(double *a, double *b, int n, int m, int k, double *c);
