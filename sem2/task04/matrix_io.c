#include <stdio.h>
#include "matrix_io.h"
#include "errors.h"

int read_matrix(double *a, int n, int m, const char *filename){
	FILE *fp;
	int i, j;
	if(!(fp = fopen(filename, "r")))
		return ERROR_OPEN;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(fscanf(fp, "%lf", a + i*m + j) != 1){
				fclose(fp);
				return ERROR_READ;
			}
	fclose(fp);
	return SUCCESS;
}

void print_matrix(double *a, int n, int m, int p){
	int np = (n > p ? p : n);
	int mp = (m > p ? p : m);
	int i, j;
	for(i = 0; i < np; i++){
		for(j = 0; j < mp; j++)
			printf(" %10.3e", a[i*m + j]);
		printf("\n");
	}
}

double f1(int n, int m, int i, int j){
	return (n > m ? n : m) - (i > j ? i : j) + 1;
}

double f2(int n, int m, int i, int j){
	(void)n; (void)m;
	return (i > j ? i : j);
}

double f3(int n, int m, int i, int j){
	(void)n; (void)m;
	return (i > j ? i - j : j - i);
}

double f4(int n, int m, int i, int j){
	(void)n; (void)m;
	return (i + j != 1 ? 1./(i + j - 1) : 1);
}

int init_matrix(double *a, int n, int m, int k){
	double (*f[])(int, int, int, int) = {f1, f2, f3,f4};
	int len = sizeof(f) / sizeof(f[0]);
	double (*p)(int, int, int, int);
	int i, j;
	if(k < 1 || k > len)
		return ERROR_INIT;
	p = f[k - 1];
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			a[i * m + j] = p(n, m, i + 1, j + 1);
	return SUCCESS;
}
