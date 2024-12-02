#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "matrix_io.h"
#include "matrix.h"

#define TASK 5

int main(int argc, char *argv[]){
	int k, n, p, ret;
	double t, *a;
	char *filename;
	if(!((argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1
		&& sscanf(argv[2], "%d", &p) == 1 && sscanf(argv[3], "%d", &k) == 1)){
		printf("Usage: %s n p k (filename)\n", argv[0]);
		return 1;
	}
	if(k == 0 && argc == 5){
		filename = argv[4];
	}
	a = (double*) malloc (n * n * sizeof(double));
	if(!a){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	if(k == 0)
		ret = read_matrix(a, n, n, filename);
	else
		ret = init_matrix(a, n, n, k);
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		free(a);
		return 2;
	}
	print_matrix(a, n, n, p);
	t = clock();
	solve5(a, n);
	t = (clock() - t) / CLOCKS_PER_SEC;
	print_matrix(a, n, n, p);
	printf ("%s : Task = %d Elapsed = %.2f\n", argv[0], TASK, t);
	free(a);
	return 0;
}
