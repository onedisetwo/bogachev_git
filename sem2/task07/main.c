#include <stdio.h>
#include "main.h"
#include "errors.h"

#define EPS 1e-16
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define EQUAL_D(a, b) (ABS(a - b) < EPS * ABS(a + b))
#define EQUAL_ZERO(a) (ABS((a)) < EPS)

int get_k_name(int *k, char **name, int *arg, int argc, char *argv[]){
        if(sscanf(argv[*arg], "%d", k) != 1 || *arg >= argc)
                return ERROR_INPUT;
        (*arg)++;
        if(*k != 0)
                return SUCCESS;
        if(*arg >= argc)
                return ERROR_INPUT;
        else
                *name = argv[(*arg)++];
        return SUCCESS;
}

int get_r2_task1(double *a, double *x, int n, double r1, double *r2){
	int i, j;
	double res, rxS, tempS, temp;
	rxS = 0;
	for(i = 0; i < n; i++){
		temp = x[i];
		rxS += ABS(r1 * temp);
	}
	res = 0;
	for(i = 0; i < n; i++){
		tempS = 0;
		for(j = 0; j < n; j++){
			tempS += a[i*n + j] * x[j];
		}
		tempS -= r1 * x[i];
		if(EQUAL_ZERO(rxS)){
			return DIVISION_BY_ZERO;
		}
		res += ABS(tempS) / rxS;
	}
	*r2 = res;
	return SUCCESS;
}

int get_r1_task2_10(double *a, double *x, double *b, int n, double *r1){
	int i, j;
	double res, bS, tempS, temp;
	bS = 0;
	for(i = 0; i < n; i++){
		temp = b[i];
		bS += ABS(temp);
	}
	res = 0;
	for(i = 0; i < n; i++){
		tempS = 0;
		for(j = 0; j < n; j++){
			tempS += a[i*n + j] * x[j];
		}
		tempS -= b[i];
		res += ABS(tempS);
	}
	if(EQUAL_ZERO(bS))
		return DIVISION_BY_ZERO;
	res /= bS;
	*r1 = res;
	return SUCCESS;
}

void get_r2_task2_10(double *x, int n, double *r2){
	int k, i;
	double res, temp;
	res = 0;
	k = 1;
	for(i = 0; i < n; i++){
		temp = x[i];
		res += ABS(temp - k);
		k = (k == 0 ? 1 : 0);
	}
	*r2 = res;
}

void init_b(double *a, double *b, int n){
	int i, k;
	double tempS;
	for(i = 0; i < n; i++){
		tempS = 0;
		for(k = 0; k <= (n - 1) / 2; k++){
			tempS += a[i*n + (2*k+1) - 1];
		}
		b[i] = tempS;
	}
}
