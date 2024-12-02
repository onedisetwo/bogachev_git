#include <stdio.h>
#include <time.h>
#include "errors.h"
#include "solve.h"

#define TASK 4

int main(int argc, char *argv[]){
	const char *nameIn, *nameOut, *s;
	int res, ret;
	double t;
	if(argc != 4){
		printf("Usage: <input file> <output file> <s>\n");
		return 1;
	}
	nameIn = argv[1];
	nameOut = argv[2];
	s = argv[3];
	t = clock();
	ret = solve1__4(nameIn, nameOut, s, &res);
	t = (clock() - t) / CLOCKS_PER_SEC;
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		return 2;
	}
	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, t);
	return 0;
}
