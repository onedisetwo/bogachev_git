#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"
#include "m_sort.h"

#define TASK 2

int main(int argc, char *argv[]){
	int n, m, p1, p2, s1, s2, diff, ret, plusArg = 0;
	char *name1 = 0, *name2 = 0;
	double *a, *b, *c;
	double t;
	if( !((argc == 7 || argc == 8 || argc == 9) && sscanf(argv[1], "%d", &n) == 1 &&
	    sscanf(argv[2], "%d", &p1) == 1 && sscanf(argv[3], "%d", &s1) == 1) ) {
		printf("Usage: %s n p1 s1 [name1] m p2 s2 [name2]\n", argv[0]);
		return 1;
	}
	if(s1 == 0){
		plusArg = 1;
		name1 = argv[4];
	}
	if(s1 < 0 && s1 > 6){
		printf("Usage: %s n p1 s1 [name1] m p2 s2 [name2]\n", argv[0]);
		return 1;
	}
	if( !(sscanf(argv[4 + plusArg], "%d", &m) == 1 && sscanf(argv[5 + plusArg], "%d", &p2) == 1 &&
	    sscanf(argv[6 + plusArg], "%d", &s2) == 1) ) {
		printf("Usage: %s n p1 s1 [name1] m p2 s2 [name2]\n", argv[0]);
		return 1;
	}
	if(s2 == 0)
		name2 = argv[7 + plusArg];
	if(s2 < 0 && s2 > 6){
		printf("Usage: %s n p1 s1 [name1] m p2 s2 [name2]\n", argv[0]);
		return 1;
	}
        a = (double *)malloc(n * sizeof(double));
	b = (double *)malloc(m * sizeof(double));
	c = (double *)malloc((n+m) * sizeof(double));
	if(!a || !b || !c){
		printf("Error: not enough memory\n");
		if(a) 	free(a);
		if(b) 	free(b);
		if(c) 	free(c);
		return 2;
	}
        if(s1 == 0){
                ret = read_array(a, n, name1);
                if(ret != SUCCESS){
                        print_error_message(ret, name1);
                        free(a); free(b); free(c);
                        return 3;
                }
        }
        else
                init_array(a, n, s1);
	if(s2 == 0){
                ret = read_array(b, m, name2);
                if(ret != SUCCESS){
                        print_error_message(ret, name2);
                        free(a); free(b); free(c);
                        return 3;
                }
        }
        else
                init_array(b, m, s2);
        print_array(a, n, p1);
	print_array(b, m, p2);
        t = clock();
        merge_arrays(a, n, b, m, c);
        t = (clock() - t) / CLOCKS_PER_SEC;
	printf("New array:\n");
	print_array(c, n + m, (p1 > p2 ? p1 : p2));
	diff = get_diff(c, n + m);
        printf("%s : Task = %d Diff = %d Elapsed = %.2f\n",
                argv[0], TASK,  diff, t);
        free(a); free(b); free(c);
        return 0;
}
