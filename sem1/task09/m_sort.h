int get_diff(double *a, int n, int (*cmp)(double, double));

int compare1(double x, double y);

int compare2(double x, double y);

int get_insert_pos_bin(double* a, int n, double x, int (*cmp)(double, double));
// for non-decreasing array

void merge_arrays(double *a, int n, double *b, int m, double *c, int (*cmp)(double, double));
// for non-decreasing arrays

int split_array(double *a, int n, double x, int (*cmp)(double, double));

void bubble_sort(double *a, int n, int (*cmp)(double, double));

void selection_sort(double *a, int n, int (*cmp)(double, double));

void insertion_sort_lin(double *a, int n, int (*cmp)(double, double));

void insertion_sort_bin(double *a, int n, int (*cmp)(double, double));

void copy(double *a, double *b, int n);
// a -> b

void neumann_sort(double *a, double *b, int n, int (*cmp)(double, double));

void quick_sort(double *a, int n, int (*cmp)(double, double));

void heap_sort(double *a, int n, int (*cmp)(double, double));
