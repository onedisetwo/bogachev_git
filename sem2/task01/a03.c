#include <stdio.h>
#include <time.h>
#include "errors.h"
#include "solve.h"

#define TASK 3

int main(int argc, char *argv[]){
	const char *nameIn, *nameOut, *s, *t;
	int res, ret;
	double time;
	if(argc != 5){
		printf("Usage: <input file> <output file> <s> <t>\n");
		return 1;
	}
	nameIn = argv[1];
	nameOut = argv[2];
	s = argv[3];
	t = argv[4];
	time = clock();
	ret = solve3(nameIn, nameOut, s, t, &res);
	time = (clock() - time) / CLOCKS_PER_SEC;
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		return 2;
	}
	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, time);
	return 0;
}
