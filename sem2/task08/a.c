#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_io.h"
#include "matrix.h"
#include "solve.h"
#include "errors.h"
#include "main.h"

#define init_or_read_matrix(a, n, m, k, filename) \
	(k == 0 ? read_matrix(a, n, m, filename) : init_matrix(a, n, m, k))

int main(int argc, char *argv[]){
	const int TASK = 3, MIN_ARGC = 4, MAX_ARGC = 5;
	const char *VAR_LIST = "n p k (name)";

	int n, p, kA;
	char *nameA;
	int  arg, retA, ret1, ret2 = SUCCESS;
	double *a, *b, *solution, time, r1, r2, normA;
	arg = 1;
	if( !( 	argc >= MIN_ARGC && argc <= MAX_ARGC
		&& sscanf(argv[arg++], "%d", &n) == 1
		&& sscanf(argv[arg++], "%d", &p) == 1
		&& get_k_name(&kA, &nameA, &arg, argc, argv) == SUCCESS ) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	a = (double*) malloc (n * n * sizeof(double));
	b = (double*) malloc (n * 1 * sizeof(double));
	solution = (double*) malloc (n * 1 * sizeof(double));
	if(!a || !b || !solution){
		if(a)	free(a);
		if(b) 	free(b);
		if(solution) 	free(solution);
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	retA = init_or_read_matrix(a, n, n, kA, nameA);
	if(retA != SUCCESS){
		free(a);
		free(b);
		free(solution);
		printf("%s\n", get_error_message(retA));
		return 3;
	}
	init_b(a, b, n);

	printf("Matrix A:\n");
	print_matrix(a, n, n, p);
	printf("Matrix b:\n");
	print_matrix(b, 1, n, p);

	normA = get_norm_inf(a, n, n);
//--------------------------------------------------
	time = clock();
	ret1 = solve(a, n, b, solution, normA);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------
	if(ret1 != SUCCESS){
		printf("%s\n", get_error_message(ret1));
		free(a);
		free(b);
		free(solution);
		return 4;
	}
	printf("New matrix A:\n");
	print_matrix(a, n, n, p);
	retA = init_or_read_matrix(a, n, n, kA, nameA);
	if(retA != SUCCESS){
		printf("%s\n", get_error_message(retA));
		free(a);
		free(b);
		free(solution);
		return 3;
	}
	init_b(a, b, n);
	ret2 = get_r1_linear_system(a, solution, b, n, &r1, normA);
	if(ret2 != SUCCESS){
		printf("%s\n", get_error_message(ret2));
		free(a);
		free(b);
		free(solution);
		return 4;
	}
	printf("Vector x:\n");
	print_matrix(solution, 1, n, p);
	get_r2_linear_system(solution, n, &r2);
	printf ("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f K = %d N = %d\n",
		argv[0], TASK, r1, r2, time, kA, n);
	free(a);
	free(b);
	free(solution);
	return 0;
}
