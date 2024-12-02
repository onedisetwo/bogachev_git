#include <stdio.h>
#include <time.h>
#include "io_status.h"
#include "solve.h"
#include "m_string.h"

#define TASK 7

int main(int argc, char *argv[]){
	const char *nameIn, *nameOut, *s2;
	char *s1;
	double t = 0;
	int ret, res = 0;
	if(argc != 5){
		printf("Usage: <name input> <name output> <string1> <string2>\n");
		return 1;
	}
	nameIn = argv[1];
	nameOut = argv[2];
	s1 = argv[3];
	s2 = argv[4];
	t = clock();
	ret = solve7(nameIn, nameOut, s1, s2, &res);
	t = (clock() - t) / CLOCKS_PER_SEC;
	if(ret != SUCCESS){
		print_error_message(ret, (char*)"input or ouptut file");
		return 2;
	}
	printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, t);
	return 0;
}
