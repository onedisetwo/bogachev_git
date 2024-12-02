# include "main.h"

int get_diff (data *a, int n);

int get_insert_pos_bin(data* a, int n, data x);
int get_insert_pos_bin_old(data* a, int n, data x);
// for non-decreasing array

void merge_arrays(data *a, int n, data *b, int m, data *c);
// for non-decreasing arrays

int split_array(data *a, int n, int m);
int split_array_old(data *a, int n, data x);

void bubble_sort (data *a, int n);

void selection_sort(data *a, int n);

void insertion_sort_lin(data *a, int n);

void insertion_sort_bin(data *a, int n);

void copy(data *a, data *b, int n);
// a -> b

void neumann_sort(data *a, data *b, int n);

void quick_sort(data *a, int n);

void heap_sort(data *a, int n);
