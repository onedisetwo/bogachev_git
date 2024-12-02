int get_diff(double *a, int n);

int get_insert_pos_bin(double* a, int n, double x);
// for non-decreasing array

void merge_arrays(double *a, int n, double *b, int m, double *c);
// for non-decreasing arrays

int split_array(double *a, int n, double x);

void bubble_sort(double *a, int n);

void selection_sort(double *a, int n);

void insertion_sort_lin(double *a, int n);

void insertion_sort_bin(double *a, int n);

void copy(double *a, double *b, int n);
// a -> b

void neumann_sort(double *a, double *b, int n);

void quick_sort(double *a, int n);

void heap_sort(double *a, int n);
