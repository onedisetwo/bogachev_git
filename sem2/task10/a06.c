#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "errors.h"
#include "main.h"

int main(int argc, char *argv[]){
	const int TASK = 6, ARGC = 7;
	const char *VAR_LIST = "m a b eps M k";
	int arg;
	double time;
	double (*f[7])(double) = {f0, f1, f2, f3, f4, f5, f6};

	int k, it, count, MaxIt, m;
	double a, b, eps, x, fx;
	double *d;

	arg = 1;
	if( !( 	argc == ARGC
		&& sscanf(argv[arg++], "%d", &m) == 1
		&& sscanf(argv[arg++], "%lf", &a) == 1
		&& sscanf(argv[arg++], "%lf", &b) == 1
		&& sscanf(argv[arg++], "%lf", &eps) == 1
		&& sscanf(argv[arg++], "%d", &MaxIt) == 1
		&& sscanf(argv[arg++], "%d", &k) == 1
		&& k >= 0 && k <= 6) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}

	d = (double*) malloc (3 * (m + 1) * sizeof(double));
	if(!d){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
//--------------------------------------------------
	time = clock();
	it = solve6(a, b, eps, MaxIt, m, d, f[k], &x);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------
	count = get_count();
        if(it < 0){
                if(it == -1 || it == -2)
                        printf ("%s : Task = %d X = NOT FOUND Count = %d T = %.2f\n",
                                argv[0], TASK, count, time);
                else
                        printf("Program is killed due to unknown error in \"solve\" function\n");
		free(d);
                return 2;
        }
        fx = (f[k])(x);
        printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n",
                argv[0], TASK, x, fx, it, count, time);
	free(d);
        return 0;
}
