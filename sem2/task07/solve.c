#include "solve.h"
#include "matrix.h"
#include "matrix_io.h"
#include "errors.h"
#include <stdio.h>

#define EPS 1e-16
#define ABS(a) ((a) < 0 ? -(a) : (a))
//#define EQUAL_D(a, b) (ABS(a - b) < EPS * ABS(a + b))
#define EQUAL_ZERO(a) (ABS((a)) < EPS)
#define SWAP(a, b, temp) \
	temp = a; \
	a = b; \
	b = temp; \

double get_scalar_product(double *a, double *b, int n){
        int i;
        double res;
        res = 0;
        for(i = 0; i < n; i++){
                res += a[i] * b[i];
        }
        return res;
}

int solve1(double *a, double *x0, double *x1, double **x_m, int n, int m, double *r1){
	int k;
	double res, temp;
	double *x, *x_new, *tempP;
	x = x0;
	x_new = x1;
	for(k = 0; k < m; k++){
		multiply_matrices(a, x, n, n, 1, x_new);
		SWAP(x, x_new, tempP)
	}
	multiply_matrices(a, x, n, n, 1, x_new);
	temp = get_scalar_product(x, x, n);
	if(EQUAL_ZERO(temp))
		return DIVISION_BY_ZERO;
	res = get_scalar_product(x_new, x, n) / temp;
	*x_m = x;
	*r1 = res;
	return SUCCESS;
}

void solve2(double *a, double *b, double *x0, double *m1, int n, int m, double t, double **x_m){
	int i;
	double *x, *r;
	r = m1;
	x = x0;
	for(i = 0; i < m; i++){
		multiply_matrices(a, x, n, n, 1, r);
		add_matrices(r, 1, b, -1, n, 1, r);
		add_matrices(x, 1, r, -t, n, 1, x);
	}
	*x_m = x;
}

int solve3(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double **x_m){
	// x ~ x0
	int k, i;
	double *r_prev, temp1, temp2, t, *u;
	r_prev = m1;
	// r0 = A*x0 -b
	multiply_matrices(a, x, n, n, 1, r_prev);
	add_matrices(r_prev, 1, b, -1, n, 1, r_prev);
	for(k = 0; k < m; k++){
		u = (r_prev == m1 ? m2 : m1);
		multiply_matrices(a, r_prev, n, n, 1, u);
		temp1 = get_scalar_product(u, r_prev, n);
		if(EQUAL_ZERO(temp1))
			return DIVISION_BY_ZERO;
		t = get_scalar_product(r_prev, r_prev, n) / temp1;
		//r_new = u;
		for(i = 0; i < n; i++){
			temp1 = x[i];
			temp2 = r_prev[i];
			u[i] = temp2 - t * u[i];
			x[i] = temp1 - t * temp2;
		}
		r_prev = u;
	}
	*x_m = x;
	return SUCCESS;
}

int solve4(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double **x_m){
	// x ~ x0
	int k, i;
	double *r_prev, temp1, temp2, *u, t;
	r_prev = m1;
	// r0 = A*x0 -b
	multiply_matrices(a, x, n, n, 1, r_prev);
	add_matrices(r_prev, 1, b, -1, n, 1, r_prev);
	for(k = 0; k < m; k++){
		u = (r_prev == m1 ? m2 : m1);
		multiply_matrices(a, r_prev, n, n, 1, u);
		temp1 = get_scalar_product(u, u, n);
		if(EQUAL_ZERO(temp1))
			return DIVISION_BY_ZERO;
		t = get_scalar_product(u, r_prev, n) / temp1;
		for(i = 0; i < n; i++){
			temp1 = x[i];
			temp2 = r_prev[i];
			u[i] = temp2 - t * u[i];
			x[i] = temp1 - t * temp2;
		}
		r_prev = u;
	}
	*x_m = x;
	return SUCCESS;
}

void multiply_diag(double *a, double *x, int n){
	// x -> diag(a) * x
	int i;
	for(i = 0; i < n; i++){
		x[i] = a[i*n + i] * x[i];
	}
}

int multiply_diag_inv(double *a, double *x, double *res, int n){
	// x -> diag(a)^-1 * x
	int i;
	double temp;
	for(i = 0; i < n; i++){
		temp = a[i*n + i];
		if(EQUAL_ZERO(temp))
			return DIVISION_BY_ZERO;
		res[i] = x[i] / temp;
	}
	return SUCCESS;
}

/*double get_scalar_product_spec5(double *a, double *u, int n){
	int i;
	double res = 0, temp;
	for(i = 0; i < n; i++){
		temp = u[i];
		res += temp * (temp * a[i*n + i]);
	}
	return res;
}*/

int solve5(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double **x_m){
	int k, ret;
	double *r, *u, *v, t, temp;
	r = m1;
	u = m2;
	v = b;
	multiply_matrices(a, x, n, n, 1, r);
	add_matrices(r, 1, b, -1, n, 1, r);
	for(k = 0; k < m; k++){
		if((ret = multiply_diag_inv(a, r, u, n)) != SUCCESS) // r -> u
			return ret;
		multiply_matrices(a, u, n, n, 1, v);
		temp = get_scalar_product(v, u, n);
		if(EQUAL_ZERO(temp))
			return DIVISION_BY_ZERO;
		t = get_scalar_product(u, r, n) / temp;
		add_matrices(x, 1, u, -t, n, 1, x);
		add_matrices(r, 1, v, -t, n, 1, r);
	}
	*x_m = x;
	return SUCCESS;
}

/*double get_scalar_product_spec6(double *v, double *a, double *u, int n){
	int i;
	double res = 0;
	for(i = 0; i < n; i++)
		res += v[i] * (u[i] * a[i*n + i]);
	return res;
}*/

int solve6(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double **x_m){
	int k, ret;
	double *r, *u, *v, t, temp;
	r = m1;
	u = m2;
	v = b;
	multiply_matrices(a, x, n, n, 1, r);
	add_matrices(r, 1, b, -1, n, 1, r);
	for(k = 0; k < m; k++){
		if((ret = multiply_diag_inv(a, r, u, n)) != SUCCESS) // r -> u
			return ret;
		multiply_matrices(a, u, n, n, 1, v);
		temp = get_scalar_product(v, v, n);
		if(EQUAL_ZERO(temp))
			return DIVISION_BY_ZERO;
		t = get_scalar_product(v, r, n) / temp;
		add_matrices(x, 1, u, -t, n, 1, x);
		add_matrices(r, 1, v, -t, n, 1, r);
	}
	*x_m = x;
	return SUCCESS;
}

int solve7(double *a, double *b, double *x, double *m1, double *m2, int n, int m, double t, double **x_m){
	int k, ret;
	double *r, *u, *v;
	r = m1;
	u = m2;
	v = b;
	multiply_matrices(a, x, n, n, 1, r);
	add_matrices(r, 1, b, -1, n, 1, r);
	for(k = 0; k < m; k++){
		if((ret = multiply_diag_inv(a, r, u, n)) != SUCCESS) // r -> u
			return ret;
		multiply_matrices(a, u, n, n, 1, v);
		add_matrices(x, 1, u, -t, n, 1, x);
		add_matrices(r, 1, v, -t, n, 1, r);
	}
	*x_m = x;
	return SUCCESS;
}

int solve_system_DL(double *a, double *x, double *b, double tb, int n){
	int i, j;
	double temp, tempS;
	for(i = 0; i < n; i++){
		tempS = tb * b[i];
		for(j = 0; j < i; j++){
			tempS -= x[j] * a[i*n + j];
		}
		temp = a[i*n + i];
		if(EQUAL_ZERO(temp))
			return DIVISION_BY_ZERO;
		x[i] = tempS / a[i*n + i];
	}
	return SUCCESS;
}

int solve8(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t){
	// x ~ x0
	int k, ret;
	double *r;
	(void)m2; (void)m3;
	r = m1;
	for(k = 0; k < m; k++){
		multiply_matrices(a, x, n, n, 1, r);
		add_matrices(r, 1, b, -1, n, 1, r);
		ret = solve_system_DL(a, r, r, -t, n);
		if(ret != SUCCESS)
			return ret;
		add_matrices(r, 1, x, 1, n, 1, x);
	}
	return SUCCESS;
}

int solve_system_DR(double *a, double *x, double *b, double tb, int n){
	int i, j;
	double temp, tempS;
	for(i = n - 1; i >= 0; i--){
		tempS = tb * b[i];
		for(j = n - 1; j > i; j--){
			tempS -= x[j] * a[i*n + j];
		}
		temp = a[i*n + i];
		if(EQUAL_ZERO(temp))
			return DIVISION_BY_ZERO;
		x[i] = tempS / a[i*n + i];
	}
	return SUCCESS;
}

int solve9(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t){
	// x ~ x0
	int k, ret;
	double *r;
	(void)m2; (void)m3;
	r = m1;
	for(k = 0; k < m; k++){
		multiply_matrices(a, x, n, n, 1, r);
		add_matrices(r, 1, b, -1, n, 1, r);
		ret = solve_system_DR(a, r, r, -t, n);
		if(ret != SUCCESS)
			return ret;
		add_matrices(r, 1, x, 1, n, 1, x);
	}
	return SUCCESS;
}

int solve10(double *a, double *b, double *x, double *m1, double *m2, double *m3, int n, int m, double t){
	// x ~ x0
	int k, ret;
	double *r;
	(void)m2; (void)m3;
	r = m1;
	for(k = 0; k < m; k++){
		multiply_matrices(a, x, n, n, 1, r);
		add_matrices(r, 1, b, -1, n, 1, r);
		ret = solve_system_DL(a, r, r, -t, n);
		if(ret != SUCCESS)
			return ret;
		multiply_diag(a, r, n);
		ret = solve_system_DR(a, r, r, 1, n);
		if(ret != SUCCESS)
			return ret;
		add_matrices(r, 1, x, 1, n, 1, x);
	}
	return SUCCESS;
}

