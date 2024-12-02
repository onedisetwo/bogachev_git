#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"
#include "m_sort.h"

#define TASK 5
#define print_usage_error printf("Usage: %s c n p s [name]\n", argv[0])

int main(int argc, char *argv[]){
	int c, n, p, s, ret, diff;
	char* name = 0;
	double* a;
	double t;
	if( !((argc == 5 || argc == 6) &&
 	    sscanf(argv[1], "%d", &c) && sscanf(argv[2], "%d", &n) == 1 &&
	    sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1) ) {
		print_usage_error;
		return 1;
	}
	if(argc == 6){
		if(s == 0)
			name = argv[5];
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
        selection_sort(a, n, (c == 1 ? compare1 : compare2));
        t = (clock() - t) / CLOCKS_PER_SEC;
	printf("New array:\n");
	print_array(a, n, p);
	diff = get_diff(a, n, (c == 1 ? compare1 : compare2));
        printf("%s : Task = %d Diff = %d Elapsed = %.2f\n",
                argv[0], TASK, diff, t);
        free(a);
        return 0;
}
