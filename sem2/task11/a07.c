#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "errors.h"
#include "main.h"

int main(int argc, char *argv[]){
	const int TASK = 7, ARGC = 5;
	const char *VAR_LIST = "a b n k";
	int arg;
	double time;
	double (*f[7])(double) = {f0, f1, f2, f3, f4, f5, f6};

	int n, k, count, ret;
	double a, b, res;

	arg = 1;
	if( !( 	argc == ARGC
		&& sscanf(argv[arg++], "%lf", &a) == 1
		&& sscanf(argv[arg++], "%lf", &b) == 1
		&& sscanf(argv[arg++], "%d", &n) == 1
		&& sscanf(argv[arg++], "%d", &k) == 1
		&& k >= 0 && k <= 6) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}

//--------------------------------------------------
	time = clock();
	ret = solve7(a, b, n, f[k], &res);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		return 2;
	}
	count = get_count();

	printf ("%s : Task = %d Res = %e Count = %d T = %.2f\n",
		argv[0], TASK, res, count, time);
	return 0;
}
