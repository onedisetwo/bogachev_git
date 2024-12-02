#include "student.h"

int get_diff (student *a, int n);

int get_insert_pos_bin(student* a, int n, student *x);
// for non-decreasing array

void merge_arrays(student *a, int n, student *b, int m, student *c);
// for non-decreasing arrays

int split_array(student *a, int n, int m);
int split_array_old(student *a, int n, student *x);

void bubble_sort (student *a, int n);

void selection_sort(student *a, int n);

void insertion_sort_lin(student *a, int n);

void insertion_sort_bin(student *a, int n);

//void copy(student *a, student *b, int n);
void move(student *a, student *b, int n);
// a -> b

void neumann_sort(student *a, student *b, int n);

void quick_sort(student *a, int n);

void heap_sort(student *a, int n);
