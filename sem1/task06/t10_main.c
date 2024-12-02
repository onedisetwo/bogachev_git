#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"

#define TASK 10

int solve(double* a, int n, double* b, int m);

int main(int argc, char *argv[]){
	int n, m, p1, p2, s1, s2, ret, res, plusEl = 0;
	char* name1 = 0;
	char* name2 = 0;
	double* a;
	double* b;
	double t;
	printf("%d\n",argc);
	if( !((argc == 7 || argc == 8 || argc == 9) && sscanf(argv[1], "%d", &n) == 1 &&
	    sscanf(argv[2], "%d", &p1) == 1 && sscanf(argv[3], "%d", &s1) == 1) ) {
		printf("Usage: %s n p1 s1 [name] m p2 s2 [name]\n", argv[0]);
		return 1;
	}
	if(s1 == 0){
		name1 = argv[4];
		plusEl = 1;
	}
	if( !(sscanf(argv[4 + plusEl], "%d", &m) == 1 &&
	      sscanf(argv[5 + plusEl], "%d", &p2) == 1 &&
	       sscanf(argv[6 + plusEl], "%d", &s2) == 1) ) {
		printf("Usage: %s n p1 s1 [name] m p2 s2 [name]\n", argv[0]);
		return 1;
	}
	if(s2 == 0){
		name2 = argv[7 + plusEl];
	}
        if(s1 < 0 || s1 > 6 || s2 < 0 || s2 > 6){
                printf("Usage: %s n p1 s1 [name] m p2 s2 [name]\n", argv[0]);
                return 1;
        }
	a = (double *)malloc(n * sizeof(double));
	if(!a){
		printf("Error: not enough memory\n");
		return 2;
	}
	b = (double *)malloc(m * sizeof(double));
	if(!b){
		printf("Error: not enough memory\n");
		free(a);
		return 2;
	}
	if(s1 == 0){
		ret = read_array(a, n, name1);
		if(ret != SUCCESS){
			print_error_message(ret, name1);
			free(a);
			free(b);
			return 3;
		}
	}
	else
		init_array(a, n, s1);
	if(s2 == 0){
		ret = read_array(b, m, name2);
		if(ret != SUCCESS){
			print_error_message(ret, name2);
			free(a);
			free(b);
			return 3;
		}
	}
	else
		init_array(b, n, s2);
	print_array(a, n, p1);
	print_array(b, m, p2);
	t = clock();
	res = solve(a, n, b, m);
	t = (clock() - t) / CLOCKS_PER_SEC;
	printf("New array:\n");
	print_array(a, res, p1);
	printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK,  res, t);
	free(a);
	free(b);
	return 0;
}

int solve(double* a, int n, double* b, int m){
	int i = 0, j = 0, del = 0;
	for(i = 0; i < n; i++){
		a[i - del] = a[i];
		for(j = 0; j < m; j++)
			if(is_equal(a[i], b[j])){
				del++;
				break;
			}
	}
	return n - del;
}
