#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "matrix_io.h"
#include "matrix.h"

#define TASK 10

#define usage_error \
	printf("Usage: %s n m k p kA (nameA) kB (nameB)\n", argv[0]); \
	return 1; \

int main(int argc, char *argv[]){
	int kA, kB, retA, retB, n, m, k, p, pl = 0;
	double t, *a, *b, *c;
	char *nameA, *nameB;
	if(!((argc >= 7  || argc <= 9) && sscanf(argv[1], "%d", &n) == 1
		&& sscanf(argv[2], "%d", &m) == 1 && sscanf(argv[3], "%d", &k)
		&& sscanf(argv[4], "%d", &p) == 1 && sscanf(argv[5], "%d", &kA) == 1)){
			usage_error
	}
	if(kA == 0){
		pl = 1;
		nameA = argv[6];
	}
	if(!(argc >= 7 + pl && sscanf(argv[6 + pl], "%d", &kB) == 1)){
		usage_error
	}
	if(kB == 0)
		if(argc == 8 + pl)
			nameB = argv[7 + pl];
		else{
			usage_error
		}
	else
		if(argc == 8 + pl){
			usage_error
		}
	a = (double*) malloc (n * m * sizeof(double));
	if(!a){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	b = (double*) malloc (m * k * sizeof(double));
	if(!b){
		printf("%s\n", get_error_message(ERROR_MEM));
		free(a);
		return 2;
	}
	c = (double*) malloc (n * k * sizeof(double));
	if(!c){
		printf("%s\n", get_error_message(ERROR_MEM));
		free(a);
		free(b);
		return 2;
	}
	if(kA == 0)
		retA = read_matrix(a, n, m, nameA);
	else
		retA = init_matrix(a, n, m, kA);
	if(kB == 0)
		retB = read_matrix(b, m, k, nameB);
	else
		retB = init_matrix(b, m, k, kB);
	if(retA != SUCCESS || retB != SUCCESS){
		printf("%s\n", get_error_message(retA));
		printf("%s\n", get_error_message(retB));
		free(a);
		free(b);
		free(c);
		return 2;
	}
	print_matrix(a, n, m, p);
	print_matrix(b, m, k, p);
	t = clock();
	multiply_matrix(a, b, n, m, k, c);
	t = (clock() - t) / CLOCKS_PER_SEC;
	print_matrix(c, n, k, p);
	printf ("%s : Task = %d Elapsed = %.2f\n", argv[0], TASK, t);
	free(a);
	free(b);
	free(c);
	return 0;
}
