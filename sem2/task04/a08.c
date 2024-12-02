#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "matrix_io.h"
#include "matrix.h"

#define TASK 8

int main(int argc, char *argv[]){
	int k, n, m, i, j, p, ret;
	double t, *a, g;
	char *filename;
	if(!((argc == 8 || argc == 9) && sscanf(argv[1], "%d", &i) == 1
		&& sscanf(argv[2], "%d", &j) == 1 && sscanf(argv[3], "%lf", &g) == 1
		&& sscanf(argv[4], "%d", &n) == 1 && sscanf(argv[5], "%d", &m) == 1
		&& sscanf(argv[6], "%d", &p) == 1 && sscanf(argv[7], "%d", &k) == 1)){
		printf("Usage: %s i j g n m p k (filename)\n", argv[0]);
		return 1;
	}
	if(k == 0 && argc == 9){
		filename = argv[8];
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
	ret = add_line(a, n, m, i - 1, j - 1, g);
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
