#include "matrix.h"
#include "errors.h"

#define abs(a) (a < 0 ? -a : a)
#define EPS 1e-16
#define equal_d(a, b) (abs(a - b) < EPS * abs(a + b))

#define swap(a, b, temp) \
	temp = a; \
	a = b; \
	b = temp; \

// TASK 1
int is_simm(double *a, int n){
	int i, j;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(!equal_d(a[i*n + j], a[j*n + i]))
				return 0;
	return 1;
}

// TASK 2
double get_trace(double *a, int n){
	int i;
	double tr = 0;
	for(i = 0; i < n; i++)
		tr += a[i * n + i];
	return tr;
}

// TASK 3
void transpose_sqr(double *a, int n){
	double temp;
	int i, j;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++){
			swap(a[i*n + j], a[j*n + i], temp)
		}
}

// TASK 6
int swap_lines(double *a, int n, int m, int s1, int s2){
	double temp;
	int i;
	// numbering from 0
	if(!(s1 >= 0 && s1 < n && s2 >= 0 && s2 < n))
		return ERROR_INPUT;
	for(i = 0; i < m; i++){
		swap(a[s1*m + i], a[s2*m + i], temp)
	}
	return SUCCESS;
}

// TASK 7
int swap_columns(double *a, int n, int m, int s1, int s2){
	double temp;
	int i;
	// numbering from 0
	if(!(s1 >= 0 && s1 < m && s2 >= 0 && s2 < m))
		return ERROR_INPUT;
	for(i = 0; i < n; i++){
		swap(a[i*m + s1], a[i*m + s2], temp)
	}
	return SUCCESS;
}

// TASK 8
int add_line(double *a, int n, int m, int s1, int s2, double g){
	int i;
	if(!(s1 >= 0 && s1 < n && s2 >= 0 && s2 < n))
		return ERROR_INPUT;
	for(i = 0; i < m; i++)
		a[s2*m + i] += g * a[s1*m + i];
	return SUCCESS;
}

// TASK 9, 10
void multiply_matrix(double *a, double *b, int n, int m, int k, double *c){
	// A * B = C
	int i, j, h;
	double sum;
	for(i = 0; i < n; i++){
		for(j = 0; j < k; j++){
			sum = 0;
			for(h = 0; h < m; h++)
				sum += a[i*m + h] * b[h*k + j];
			c[i*k + j] = sum;
		}
	}
}
