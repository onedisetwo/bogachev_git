#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
#include "solve.h"

#define TASK 3

int main(int argc, char *argv[]){
	int n, p, i, res, ret;
	double t;
	const char *filename;
	char *s;
	char **a;
	if(!(argc == 5 && sscanf(argv[1], "%d", &n) == 1
		&& sscanf(argv[2], "%d", &p) == 1)){
		printf("Usage: %s <size> <max print> <filename> <string>\n", argv[0]);
		return 1;
	}
	filename = argv[3];
	s = argv[4];
	a = (char **)malloc(n * sizeof(char *));
	if(!a){
		printf("Error: cannot allocate array a\n");
		return 2;
	}
	for(i = 0; i < n; i++)
		a[i] = 0;
	ret = read_array(a, n, filename);
	if(ret != SUCCESS){
		switch(ret){
			case ERROR_OPEN:
				printf("Error: cannot open file %s\n", filename);
				break;
			case ERROR_READ:
				printf("Error: cannot read file %s\n", filename);
				break;
			case ERROR_MEM:
				printf("Error: cannot allocate string\n");
				break;
			default:
				printf("Error: unknown %d\n", ret);
		}
		free(a);
		return 3;
	}
	print_array(a, n, p);
	t = clock();
	res = solve3(a, n, s);
	t = (clock() - t) / CLOCKS_PER_SEC;
	printf ("New array:\n");
	print_array (a, res, p);
	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, t);
	free_array (a, res);
	free(a);
	return 0;
}

