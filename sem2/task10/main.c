#include <stdio.h>
#include "main.h"
#include "errors.h"
#include <math.h>

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

static int count = 0;

int get_count(void){
	return count;
}

double f0(double x){
	count++;
	(void)x;
	return 1;
}

double f1(double x){
	count++;
	return x - 1e100;
}

double f2(double x){
	count++;
	return 4 - x*x;
}

double f3(double x){
	count++;
	return x*x*x + 3*x*x + 16;
}

double f4(double x){
	count++;
	return 3 - 2*x*x - x*x*x*x;
}

double f5(double x){
	count++;
	return sqrt(fabs(x) + 1) - 2;
}

double f6(double x){
	count++;
	return sqrt(sqrt(fabs(x) + 1) + 1) - 2;
}

double d0(double x){
	count++;
	(void)x;
	return 0;
}

double d1(double x){
	count++;
	(void)x;
	return 1;
}

double d2(double x){
	count++;
	return -2 * x;
}

double d3(double x){
	count++;
	return 3*x*x + 6*x;
}

double d4(double x){
	count++;
	return -4*x - 4*x*x*x;
}

double d5(double x){
	count++;
	return (x < 0 ? -0.5/sqrt(-x+1) : 0.5/sqrt(x+1));
}

double d6(double x){
	count++;
	return (1/sqrt(sqrt(fabs(x)+1)+1)) * d5(x);
}

