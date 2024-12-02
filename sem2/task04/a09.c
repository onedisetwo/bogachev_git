#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "matrix_io.h"
#include "matrix.h"

#define TASK 9

#define usage_error \
	printf("Usage: %s n m p kA (nameA) kB (nameB)\n", argv[0]); \
	return 1; \

int main(int argc, char *argv[]){
	int kA, kB, retA, retB, n, m, p, pl = 0;
	double t, *a, *b, *c;
	char *nameA, *nameB;
	if(!((argc >= 6  || argc <= 8)
		&& sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &m) == 1
		&& sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &kA) == 1)){
			usage_error
	}
	if(kA == 0){
		pl = 1;
		nameA = argv[5];
	}
	if(!(argc >= 6 + pl && sscanf(argv[5 + pl], "%d", &kB) == 1)){
		usage_error
	}
	if(kB == 0){
		if(argc == 7 + pl)
			nameB = argv[6 + pl];
		else{
			usage_error
		}
	}
	else
		if(argc == 7 + pl){
			usage_error
		}
	a = (double*) malloc (n * m * sizeof(double));
	if(!a){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	b = (double*) malloc (m * sizeof(double));
	if(!b){
		printf("%s\n", get_error_message(ERROR_MEM));
		free(a);
		return 2;
	}
	c = (double*) malloc (n * sizeof(double));
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
		retB = read_matrix(b, m, 1, nameB);
	else
		retB = init_matrix(b, m, 1, kB);
	if(retA != SUCCESS || retB != SUCCESS){
		printf("%s\n", get_error_message(retA));
		printf("%s\n", get_error_message(retB));
		free(a);
		free(b);
		free(c);
		return 2;
	}
	print_matrix(a, n, m, p);
	print_matrix(b, m, 1, p);
	t = clock();
	multiply_matrix(a, b, n, m, 1, c);
	t = (clock() - t) / CLOCKS_PER_SEC;
	print_matrix(c, n, 1, p);
	printf ("%s : Task = %d Elapsed = %.2f\n", argv[0], TASK, t);
	free(a);
	free(b);
	free(c);
	return 0;
}
