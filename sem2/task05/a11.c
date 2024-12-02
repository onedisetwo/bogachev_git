#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "matrix_io.h"
#include "solve.h"
#include "main.h"

#define TASK 11
#define USAGE_MES "Usage: %s n m p k (filename)\n"
#define make_matrix(matrix, n, m, k, filename) \
        (k == 0 ? read_matrix(matrix, n, m, filename) : init_matrix(matrix, n, m, k))

int main(int argc, char *argv[]){
	int n, m, p, k, ret, arg = 1;
	char *filename;
	double time, res, *a;
	if(!((argc == 5 || argc == 6)
		&& sscanf(argv[arg++], "%d", &n) == 1
		&& sscanf(argv[arg++], "%d", &m) == 1
		&& sscanf(argv[arg++], "%d", &p) == 1)){
		printf(USAGE_MES, argv[0]);
		return 1;
	}
	if(get_k_name(&k, &filename, &arg, argc, argv) != SUCCESS){
		printf(USAGE_MES, argv[0]);
		return 1;
	}
	a = (double*) malloc (n * m * sizeof(double));
	if(!a){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	ret = make_matrix(a, n, m, k, filename);
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		free(a);
		return 2;
	}
	print_matrix(a, n, m, p);
	time = clock();
	res = solve11(a, n, m);
	time = (clock() - time) / CLOCKS_PER_SEC;
	print_matrix(a, n, m, p);
	printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], TASK, res, time);
	free(a);
	return 0;
}
