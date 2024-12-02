#include <stdio.h>
#include <time.h>
#include "io_status.h"
#include "solve.h"

#define TASK 2

int main(int argc, char *argv[]){
	const char *nameIn, *nameOut;
	char *s;
	double t = 0;
	int ret, res = 0;
	if(argc != 4){
		printf("Usage: <name input> <name output> <string>\n");
		return 1;
	}
	nameIn = argv[1];
	nameOut = argv[2];
	s = (char *)argv[3];
	t = clock();
	ret = solve2(nameIn, nameOut, s, &res);
	t = (clock() - t) / CLOCKS_PER_SEC;
	if(ret != SUCCESS){
		print_error_message(ret, (char*)"input or ouptut file");
		return 2;
	}
	printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, t);
	return 0;
}
