#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "errors.h"
#include "main.h"

int main(int argc, char *argv[]){
	const int TASK = 12, ARGC = 6;
	const char *VAR_LIST = "a b eps k1 k2";
	int arg;
	double time;
	double (*f[7])(double) = {f0, f1, f2, f3, f4, f5, f6};

	int k1, k2, count, ret, it;
	double a, b, eps, res;

	arg = 1;
	if( !( 	argc == ARGC
		&& sscanf(argv[arg++], "%lf", &a) == 1
		&& sscanf(argv[arg++], "%lf", &b) == 1
		&& sscanf(argv[arg++], "%lf", &eps) == 1
		&& sscanf(argv[arg++], "%d", &k1) == 1
		&& sscanf(argv[arg++], "%d", &k2) == 1
		&& k1 >= 0 && k1 <= 6 && k2 >= 0 && k2 <= 6) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}

//--------------------------------------------------
	time = clock();
	ret = solve12(a, b, eps, f[k1], f[k2], &res, &it);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		return 2;
	}
	count = get_count();

	printf ("%s : Task = %d Res = %e N = %d Count = %d T = %.2f\n",
		argv[0], TASK, res, it, count, time);
	return 0;
}