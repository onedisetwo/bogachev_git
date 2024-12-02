int get_diff(char *a[], int n, int (*cmp)(const char*, const char*));

int up_strcmp(const char *a, const char *b);
int down_strcmp(const char *a, const char *b);
int up_len(const char *a, const char *b);
int down_len(const char *a, const char *b);

void swap(char **a, char **b);

int get_insert_pos_bin(char *a[], int n, char *x, int (*cmp)(const char*, const char*));
// for non-decreasing array

void merge_arrays(char *a[], int n, char *b[], int m, char *c[],
	int (*cmp)(const char*, const char*));
// for non-decreasing arrays

int split_array(char *a[], int n, char *x, int (*cmp)(const char*, const char*));

void bubble_sort(char *a[], int n, int (*cmp)(const char*, const char*));

void selection_sort(char *a[], int n, int (*cmp)(const char*, const char*));

void insertion_sort_lin(char *a[], int n, int (*cmp)(const char*, const char*));

void insertion_sort_bin(char *a[], int n, int (*cmp)(const char*, const char*));

void copy(char *a[], char *b[], int n);
// a -> b

void neumann_sort(char *a[], char *b[], int n, int (*cmp)(const char*, const char*));

void quick_sort(char *a[], int n, int (*cmp)(const char*, const char*));

void heap_sort(char *a[], int n, int (*cmp)(const char*, const char*));
