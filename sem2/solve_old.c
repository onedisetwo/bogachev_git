#include "solve.h"
#include "matrix.h"
#include "matrix_io.h"
#include "errors.h"
#include <stdio.h>

#define EPS 1e-16
#define ABS(a) ((a) < 0 ? -(a) : (a))
//#define EQUAL_D(a, b) (ABS(a - b) < EPS * ABS(a + b))
//#define EQUAL_ZERO(a) (ABS((a)) < EPS)
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

int solve_system_L(double *a, double *x, double *b, int n, double specEps){
	int i, j;
	double temp, tempS;
	for(i = 0; i < n; i++){
		tempS = b[i];
		for(j = 0; j < i; j++){
			tempS -= x[j] * a[i*n + j];
		}
		temp = a[i*n + i];
		if(ABS(temp) < specEps)
			return DIVISION_BY_ZERO;
		x[i] = tempS / temp;
	}
	return SUCCESS;
}

// function was changed for this certain task!
int solve_system_U(double *a, double *x, double *b, int n, double specEps){
	int i, j;
	double /*temp,*/ tempS;
	(void)specEps;
	for(i = n - 1; i >= 0; i--){
		tempS = b[i];
		for(j = n - 1; j > i; j--){
			tempS -= x[j] * a[i*n + j];
		}
		// MUST be uncommented but in the context of LU - solving its a[i*n + i] = 1
		/*temp = a[i*n + i];
		if(EQUAL_ZERO(temp))
			return DIVISION_BY_ZERO;
		x[i] = tempS / temp;*/
		x[i] = tempS;
	}
	return SUCCESS;
}

int solve(double *a, int n, double *b, double *x, double normA){
	int i, j, k, ret = SUCCESS;
	double diag, tempS;
	const double specEps = normA * EPS;

	for(k = 0; k < n; k++){
		// calc k-th column of l
		for(i = k; i < n; i++){
			tempS = 0;
			for(j = 0; j < k; j++){
				tempS += a[i*n + j] * a[j*n + k];
			}
			a[i*n + k] -= tempS;
		}
		diag = a[k*n + k];
		if(ABS(diag) < specEps)
			return DIVISION_BY_ZERO;
		// calc k-th line of u, u[i,i] := 1
		for(i = k + 1; i < n; i++){
			tempS = 0;
			for(j = 0; j < k; j++){
				tempS += a[k*n + j] * a[j*n + i];
			}
			a[k*n + i] = (a[k*n + i] - tempS) / diag;
		}
	}

	ret = solve_system_L(a, b, b, n, specEps);
	if(ret != SUCCESS)
		return ret;
	// modified solve_system_U is safe and always returns SUCCESS
	solve_system_U(a, x, b, n, specEps);
	return SUCCESS;
}
