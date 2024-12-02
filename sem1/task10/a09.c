#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "m_string.h"
#include "test.h"

#define TASK 9
#define print_usage printf("Usage: %s count s1 s2\n", argv[0])

int main(int argc, char *argv[]){
	size_t count;
	double t, t_std;
	char *s1 = 0, *s2 = 0, *res, *res_std;
	if(argc != 4 || sscanf(argv[1], "%zu", &count) != 1){
		print_usage;
		return 1;
	}
	s1 = argv[2];
	s2 = argv[3];
	t = test_9(count, strstr_, s1, s2, &res);
	t_std = test_9(count, strstr, s1, s2, &res_std);
	printf("%s : Task = %d Res = %s Elapsed = %.2f\n",
		argv[0], TASK, res == NULL ? "Not found" : res, t);
	printf("%s : Task = %d Res = %s Elapsed = %.2f\n",
		argv[0], TASK, res_std == NULL ? "Not found" : res_std, t_std);
}
