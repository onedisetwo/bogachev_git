#include <stdio.h>
#include <string.h>
#include <time.h>
#include "m_string.h"
#include "test.h"

#define TASK 1
#define print_usage printf("Usage: %s count string\n", argv[0])

int main(int argc, char *argv[]){
	size_t len, len_std, count;
	double t, t_std;
	char *s = 0;
	if(argc != 3 || sscanf(argv[1], "%zu", &count) != 1){
		print_usage;
		return 1;
	}
	s = argv[2];
	t = test_1(count, &strlen_, s, &len);
	t_std = test_1(count, &strlen, s, &len_std);
	printf("%s : Task = %d Res = %zu Elapsed = %.2f\n",
		argv[0], TASK, len, t);
	printf("%s : Task = %d Res = %zu Elapsed = %.2f\n",
		argv[0], TASK, len_std, t_std);
}
