#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"
#include "m_sort.h"

#define TASK 5

int main(int argc, char *argv[]){
	int n, p, s, ret, diff;
	char* name = 0;
	double* a;
	double t;
	if( !((argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1 &&
	    sscanf(argv[2], "%d", &p) == 1 && sscanf(argv[3], "%d", &s) == 1) ) {
		printf("Usage: %s n p s [name]\n", argv[0]);
		return 1;
	}
	if(argc == 5){
		if(s == 0)
			name = argv[4];
		else{
			printf("Usage: %s n p s [name]\n", argv[0]);
			return 1;
		}
	}
	else
                if(s < 1 || s > 6){
                        printf("Usage: %s n p s [name]\n", argv[0]);
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
        selection_sort(a, n);
        t = (clock() - t) / CLOCKS_PER_SEC;
	printf("New array:\n");
	print_array(a, n, p);
	diff = get_diff(a, n);
        printf("%s : Task = %d Diff = %d Elapsed = %.2f\n",
                argv[0], TASK, diff, t);
        free(a);
        return 0;
}
