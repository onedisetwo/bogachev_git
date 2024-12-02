#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "matrix_io.h"
#include "matrix.h"

#define TASK 7

int main(int argc, char *argv[]){
	int k, n, m, i, j, p, ret;
	double t, *a;
	char *filename;
	if(!((argc == 7 || argc == 8) && sscanf(argv[1], "%d", &i) == 1
		&& sscanf(argv[2], "%d", &j) == 1 && sscanf(argv[3], "%d", &n) == 1
		&& sscanf(argv[4], "%d", &m) == 1 && sscanf(argv[5], "%d", &p) == 1
		&& sscanf(argv[6], "%d", &k) == 1)){
		printf("Usage: %s i j n m p k (filename)\n", argv[0]);
		return 1;
	}
	if(k == 0 && argc == 8){
		filename = argv[7];
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
	t = clock();
	ret = swap_columns(a, n, m, i - 1, j - 1);
	t = (clock() - t) / CLOCKS_PER_SEC;
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		free(a);
		return 2;
	}
	print_matrix(a, n, m, p);
	printf ("%s : Task = %d Elapsed = %.2f\n", argv[0], TASK, t);
	free(a);
	return 0;
}
