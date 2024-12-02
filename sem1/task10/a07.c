#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "m_string.h"
#include "test.h"

#define TASK 7
#define print_usage printf("Usage: %s count s1 s2\n", argv[0])

int main(int argc, char *argv[]){
	size_t count, res, res_std;
	double t, t_std;
	char *s1 = 0, *s2 = 0;
	if(argc != 4 || sscanf(argv[1], "%zu", &count) != 1){
		print_usage;
		return 1;
	}
	s1 = argv[2];
	s2 = argv[3];
	t = test_7_8(count, strcspn_, s1, s2, &res);
	t_std = test_7_8(count, strcspn, s1, s2, &res_std);
	printf("%s : Task = %d Res = %zu Elapsed = %.2f\n",
		argv[0], TASK, res, t);
	printf("%s : Task = %d Res = %zu Elapsed = %.2f\n",
		argv[0], TASK, res_std, t_std);
}
