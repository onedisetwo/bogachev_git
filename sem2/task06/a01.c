#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_io.h"
#include "solve.h"
#include "errors.h"
#include "main.h"

int main(int argc, char *argv[]){
	const int TASK = 1, MIN_ARGC = 5, MAX_ARGC = 6;
	const char *VAR_LIST = "n m p k (filename)";

	int m, n, p, k, arg, ret, res;
	double *a, time;
	char *filename;

	arg = 1;
	if( !( 	argc >= MIN_ARGC && argc <= MAX_ARGC
		&& sscanf(argv[arg++], "%d", &m) == 1
		&& sscanf(argv[arg++], "%d", &n) == 1
		&& sscanf(argv[arg++], "%d", &p) == 1
		&& get_k_name(&k, &filename, &arg, argc, argv) == SUCCESS ) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	a = (double*) malloc (m * n * sizeof(double));
	if(!a){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	ret = (k == 0 ? read_matrix(a, m, n, filename) : init_matrix(a, m, n, k));
	if(ret != SUCCESS){
		free(a);
		printf("%s\n", get_error_message(ret));
		return 3;
	}

	print_matrix(a, m, n, p);
	time = clock();
	res = solve1(a, m, n);
	time = (clock() - time) / CLOCKS_PER_SEC;
	print_matrix(a, m, n - 1, p);
	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, time);
	free(a);
	return 0;
}
