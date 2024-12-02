#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "errors.h"
#include "main.h"

int main(int argc, char *argv[]){
	const int TASK = 7, ARGC = 5;
	const char *VAR_LIST = "x0 eps M k";
	int arg;
	double time;
	double (*f[7])(double) = {f0, f1, f2, f3, f4, f5, f6};

	int k, it, count, MaxIt;
	double eps, x0, fx, x;

	arg = 1;
	if( !( 	argc == ARGC
		&& sscanf(argv[arg++], "%lf", &x0) == 1
		&& sscanf(argv[arg++], "%lf", &eps) == 1
		&& sscanf(argv[arg++], "%d", &MaxIt) == 1
		&& sscanf(argv[arg++], "%d", &k) == 1
		&& k >= 0 && k <= 6) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}

//--------------------------------------------------
	time = clock();
	it = solve7(x0, eps, MaxIt, f[k], &x);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------
	if(it < 0){
		switch(it){
			case -1:
				printf("Algorithm is not applicable (f(a) * f(b) > 0)\n");
				break;
			case -2:
				printf("Maximum number of iterations exceeded\n");
				break;
			case -3:
				printf("Program was forcibly interrupted to prevent division by 0\n");
				break;
			default:
				printf("Program is killed due to unknown error in \"solve\" function\n");
		}
		return 4;
	}
	count = get_count();
	fx = (f[k])(x);

	printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n",
		argv[0], TASK, x, fx, it, count, time);
	return 0;
}
