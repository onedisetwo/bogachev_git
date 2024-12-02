#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "solve.h"
#include "errors.h"
#include "main.h"

int main(int argc, char *argv[]){
	const int TASK = 7, ARGC = 3;
	const char *VAR_LIST = "x eps";

	int arg;
	double x, eps, time, res, resid;
	arg = 1;
	if( !( 	argc == ARGC
		&& sscanf(argv[arg++], "%lf", &x) == 1
		&& sscanf(argv[arg++], "%lf", &eps) == 1 ) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}

//--------------------------------------------------
	time = clock();
	res = m_exp(x, eps);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------

	resid = fabs(exp(x) - res);
	printf ("%s : Task = %d Result = %e Residual = %e Elapsed = %.2f\n",
		argv[0], TASK, res, resid, time);
	return 0;
}
