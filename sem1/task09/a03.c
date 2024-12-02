#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"
#include "m_sort.h"

#define TASK 3
#define print_usage_error printf("Usage: %s x c n p s [name]\n", argv[0]);

int main(int argc, char *argv[]){
	int c, n, p, s, res, ret;
	char* name = 0;
	double* a;
	double t, x;
	if( !((argc == 6 || argc == 7) && sscanf(argv[1], "%lf", &x) == 1 &&
	    sscanf(argv[2], "%d", &c) == 1 && sscanf(argv[3], "%d", &n) == 1 &&
	    sscanf(argv[4], "%d", &p) == 1 && sscanf(argv[5], "%d", &s) == 1) ) {
		print_usage_error;
		return 1;
	}
	if(argc == 7){
		if(s == 0)
			name = argv[6];
		else{
			print_usage_error;
			return 1;
		}
	}
	else
                if(s < 1 || s > 6){
			print_usage_error;
                        return 1;
                }
        a = (double *)malloc(n * sizeof(double));
        if(!a){
                printf("Error: not enough memory\n");
                return 2;
        }
        if(s == 0){
                ret = read_array(a, n, name);
                if(ret != SUCCESS){
                        print_error_message(ret, name);
                        free(a);
                        return 3;
                }
        }
        else
                init_array(a, n, s);
        print_array(a, n, p);
        t = clock();
        res = split_array(a, n, x, (c == 1 ? compare1 : compare2));
        t = (clock() - t) / CLOCKS_PER_SEC;
	printf("New array:\n");
	print_array(a, n, p);
        printf("%s : Task = %d Res = %d Elapsed = %.2f\n",
                argv[0], TASK,  res, t);
        free(a);
        return 0;
}
