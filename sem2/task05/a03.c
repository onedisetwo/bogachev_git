#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "matrix_io.h"
#include "solve.h"
#include "main.h"

#define TASK 3
#define make_matrix(matrix, n, m, k, filename) \
	(k == 0 ? read_matrix(matrix, n, m, filename) : init_matrix(matrix, n, m, k))

int main(int argc, char *argv[]){
	int n, m, p, kA, kB, kX, arg = 1;
	char *nameA, *nameB, *nameX;
	double time, res, *a, *b, *x;
	const char *VAR_LIST = "n m p kA (nameA) kB (nameB) kX (nameX)";
	if(!((argc >= 7 && argc <= 10)
		&& sscanf(argv[arg++], "%d", &n) == 1
		&& sscanf(argv[arg++], "%d", &m) == 1
		&& sscanf(argv[arg++], "%d", &p) == 1)){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	if( get_k_name(&kA, &nameA, &arg, argc, argv) != SUCCESS ||
		get_k_name(&kB, &nameB, &arg, argc, argv) != SUCCESS ||
		get_k_name(&kX, &nameX, &arg, argc, argv) != SUCCESS){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	a = (double*) malloc (n * m * sizeof(double));
	b = (double*) malloc (n * sizeof(double));
	x = (double*) malloc (m * sizeof(double));
	if(!a || !b || !x){
		printf("%s\n", get_error_message(ERROR_MEM));
		if(a)	free(a);
		if(b)	free(b);
		if(x)	free(x);
		return 2;
	}
	{
		int retA, retB, retX;
		retA = make_matrix(a, n, m, kA, nameA);
		retB = make_matrix(b, n, 1, kB, nameB);
		retX = make_matrix(x, m, 1, kX, nameX);
		if(!(retA == SUCCESS && retB == SUCCESS && retX == SUCCESS)){
			free(a); free(b); free(x);
			if(retA != SUCCESS)	printf("%s\n", get_error_message(retA));
			if(retB != SUCCESS)	printf("%s\n", get_error_message(retB));
			if(retX != SUCCESS)	printf("%s\n", get_error_message(retX));
			return 2;
		}
	}
	print_matrix(a, n, m, p);
	print_matrix(b, n, 1, p);
	print_matrix(x, m, 1, p);
	time = clock();
	res = solve3(a, x, b, n, m);
	time = (clock() - time) / CLOCKS_PER_SEC;
	printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], TASK, res, time);
	free(a); free(b); free(x);
	return 0;
}
