#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "matrix_io.h"
#include "solve.h"

#define TASK 10
#define USAGE_MES "Usage: %s n m p k (filename)\n"

int main(int argc, char *argv[]){
	int n, m, p, k, ret;
	char *filename;
	double time, res, *a;
	if(!((argc == 5 || argc == 6)
		&& sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &m)
		&& sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &k) == 1)){
		printf(USAGE_MES, argv[0]);
		return 1;
	}
	if(k == 0){
		if(argc == 6)
			filename = argv[5];
		else{
			printf(USAGE_MES, argv[0]);
			return 1;
		}
	}
	a = (double*) malloc (n * m * sizeof(double));
	if(!a){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	if(k == 0)
		ret = read_matrix(a, n, m, filename);
	else
		ret = init_matrix(a, n, m, k);
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		free(a);
		return 2;
	}
	print_matrix(a, n, m, p);
	time = clock();
	res = solve10(a, n, m);
	time = (clock() - time) / CLOCKS_PER_SEC;
	print_matrix(a, n, m, p);
	printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], TASK, res, time);
	free(a);
	return 0;
}
