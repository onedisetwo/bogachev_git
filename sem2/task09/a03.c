#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "errors.h"
#include "main.h"

int main(int argc, char *argv[]){
	const int TASK = 3, ARGC = 4;
	const char *VAR_LIST = "x0 n filename";

	int n, ret, arg;
	char *filename;
	double x0, *x, *y, time, res;
	arg = 1;
	if( !( 	argc == ARGC
		&& sscanf(argv[arg++], "%lf", &x0) == 1
		&& sscanf(argv[arg++], "%d", &n) == 1 ) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	filename = argv[arg];
	x = (double*) malloc (n * sizeof(double));
	y = (double*) malloc (n * sizeof(double));
	if(!x || !y){
		if(x)	free(x);
		if(y) 	free(y);
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	ret = read_data1_3(filename, x, y, n);
	if(ret != SUCCESS){
		free(x);
		free(y);
		printf("%s\n", get_error_message(ret));
		return 3;
	}

//--------------------------------------------------
	time = clock();
	ret = solve3(x0, x, y, n, &res);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		free(x);
		free(y);
		return 4;
	}

	printf ("%s : Task = %d Result = %e Elapsed = %.2f\n",
		argv[0], TASK, res, time);
	free(x);
	free(y);
	return 0;
}
