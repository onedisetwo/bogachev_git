#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "m_string.h"
#include "test.h"

#define TASK 10
#define print_usage printf("Usage: %s count s1 s2\n", argv[0])

int main(int argc, char *argv[]){
	size_t count;
	double t, t_std;
	char *s = 0, *delim = 0, *res, *res_std, *next = 0, *next_std = 0;
	if(argc != 4 || sscanf(argv[1], "%zu", &count) != 1){
		print_usage;
		return 1;
	}
	s = argv[2];
	delim = argv[3];
	t = test_10(count, strtok_r_, s, delim, &next, &res);
	t_std = test_10(count, strtok_r, s, delim, &next_std, &res_std);
	printf("%s : Task = %d Res = %s Saveptr = %s Elapsed = %.2f\n",
		argv[0], TASK, res == NULL ? "Not found" : res,
		next == NULL ? "Not found" : next, t);
	printf("%s : Task = %d Res = %s Saveptr = %s Elapsed = %.2f\n",
		argv[0], TASK, res_std == NULL ? "Not found" : res_std,
		next_std == NULL ? "Not found" : next_std, t_std);
}
