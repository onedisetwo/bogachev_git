#include "matrix.h"
#include "errors.h"

#define abs(a) ((a) < 0 ? -(a) : (a))
#define EPS 1e-16
#define equal_d(a, b) (abs(a - b) < EPS * abs(a + b))

#define swap(a, b, temp) \
	temp = a; \
	a = b; \
	b = temp; \

int is_simm(double *a, int n){
	int i, j;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(!equal_d(a[i*n + j], a[j*n + i]))
				return 0;
	return 1;
}

double get_trace(double *a, int n){
	int i;
	double tr = 0;
	for(i = 0; i < n; i++)
		tr += a[i * n + i];
	return tr;
}

void transpose_sqr(double *a, int n){
	double temp;
	int i, j;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++){
			swap(a[i*n + j], a[j*n + i], temp)
		}
}

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

int add_line(double *a, int n, int m, int s1, int s2, double g){
	int i;
	if(!(s1 >= 0 && s1 < n && s2 >= 0 && s2 < n))
		return ERROR_INPUT;
	for(i = 0; i < m; i++)
		a[s2*m + i] += g * a[s1*m + i];
	return SUCCESS;
}

void multiply_matrices(double *a, double *b, int n, int m, int k, double *c){
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

void add_matrices(double *a, double a_k, double *b, double b_k, int n, int m, double *c){
	// A*a_k + B*b_k = C
	// C can be equal with A or B
	int i;
	double tempA, tempB;
	for(i = 0; i < n * m; i++){
		tempA = a[i];
		tempB = b[i];
		c[i] = a_k * tempA + b_k * tempB;
	}
}

/*double get_scalar_product(double *a, double *b, int n){
        int i;
        double res;
        res = 0;
        for(i = 0; i < n; i++){
                res += a[i] * b[i];
        }
        return res;
}*/
