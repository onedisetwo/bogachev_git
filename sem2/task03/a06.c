#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"
#include "m_sort.h"
#include "array_io.h"

#define TASK 6

int main(int argc, char *argv[]){
	int (*f[])(const char*, const char*) =
		{up_strcmp, down_strcmp, up_len, down_len};
	const int len = sizeof(f) / sizeof(f[0]);
	int (*cmp)(const char*, const char*);
	int c, n, p, ret;
	double t;
	char *filename, **a;
	if(!((argc == 5) && sscanf(argv[1], "%d", &c) == 1 && c > 0 && c <= len
		&& sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1)){
		printf("Usage: %s c n p name\n", argv[0]);
		return 1;
	}
	filename = argv[4];
	cmp = f[c - 1];
	a = (char**) malloc (n * sizeof(char*));
	if(!a){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	ret = read_array(a, n, filename);
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		free(a);
		return 2;
	}
	print_array(a, n, p);
	t = clock();
	insertion_sort_lin(a, n, cmp);
	t = (clock() - t) / CLOCKS_PER_SEC;
	printf ("New array:\n");
	print_array (a, n, p);
	printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n",
		argv[0], TASK, get_diff(a, n, cmp), t);
	delete_array(a, n);
	free(a);
	return 0;
}

