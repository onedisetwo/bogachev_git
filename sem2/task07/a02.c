#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_io.h"
#include "solve.h"
#include "errors.h"
#include "main.h"

#define init_or_read_matrix(a, n, m, k, filename) \
	(k == 0 ? read_matrix(a, n, m, filename) : init_matrix(a, n, m, k))

int main(int argc, char *argv[]){
	const int TASK = 2, MIN_ARGC = 7, MAX_ARGC = 9;
	const char *VAR_LIST = "t m n p kA (nameA) kX0 (nameX0)";

	int m, n, p, kA, kX0;
	char *nameA, *nameX0;
	int  arg, retA, retX0, ret;
	double *a, *x0, *x1, *b, *x_m, time, r1, r2, tau;

	arg = 1;
	if( !( 	argc >= MIN_ARGC && argc <= MAX_ARGC
		&& sscanf(argv[arg++], "%lf", &tau) == 1
		&& sscanf(argv[arg++], "%d", &m) == 1
		&& sscanf(argv[arg++], "%d", &n) == 1
		&& sscanf(argv[arg++], "%d", &p) == 1
		&& get_k_name(&kA, &nameA, &arg, argc, argv) == SUCCESS
		&& get_k_name(&kX0, &nameX0, &arg, argc, argv) == SUCCESS ) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	a = (double*) malloc (n * n * sizeof(double));
	x0 = (double *) malloc (n * 1 * sizeof(double));
	x1 = (double *) malloc (n * 1 * sizeof(double));
	b = (double *) malloc (n * 1 * sizeof(double));
	if(!a || !x0 || !x1 || !b){
		if(a)	free(a);
		if(x0)	free(x0);
		if(x1)	free(x1);
		if(b)	free(b);
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	retA = init_or_read_matrix(a, n, n, kA, nameA);
	retX0 = init_or_read_matrix(x0, n, 1, kX0, nameX0);
	if(retA != SUCCESS || retX0 != SUCCESS){
		free(a);
		free(x0);
		free(x1);
		free(b);
		printf("%s\n", get_error_message(retA));
		printf("%s\n", get_error_message(retX0));
		return 3;
	}
	init_b(a, b, n);
	printf("Matrix A:\n");
	print_matrix(a, n, n, p);
	printf("Vector x0:\n");
	print_matrix(x0, n, 1, p);
	printf("Matrix B:\n");
	print_matrix(b, n, 1, p);

	time = clock();
	solve2(a, b, x0, x1, n, m, tau, &x_m);
	time = (clock() - time) / CLOCKS_PER_SEC;
	printf("Vector x_m:\n");
	print_matrix(x_m, 1, n, p);
	ret = get_r1_task2_10(a, x_m, b, n, &r1);
	if(ret == SUCCESS){
		get_r2_task2_10(x_m, n, &r2);
		printf ("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f\n",
			argv[0], TASK, r1, r2, time);
	}
	else
		printf("%s\n", get_error_message(ret));
	free(a);
	free(x0);
	free(x1);
	free(b);
	if(ret == SUCCESS)
		return 0;
	else
		return 4;
}