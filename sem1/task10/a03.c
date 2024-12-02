#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "m_string.h"
#include "test.h"

#define TASK 3
#define print_usage printf("Usage: %s count string char\n", argv[0])

int main(int argc, char *argv[]){
	size_t count;
	double t, t_std;
	char *s = 0, *res = 0, *res_std = 0, ch;
	if(argc != 4 || sscanf(argv[1], "%zu", &count) != 1 ||
	   sscanf(argv[3], "%c", &ch) != 1){
		print_usage;
		return 1;
	}
	s = argv[2];
	t = test_3_4(count, strchr_, s, ch, &res);
	t_std = test_3_4(count, strchr, s, ch, &res_std);
	printf("%s : Task = %d Res = %s Elapsed = %.2f\n",
		argv[0], TASK, res == NULL ? "Not found" : res, t);
	printf("%s : Task = %d Res = %s Elapsed = %.2f\n",
		argv[0], TASK, res_std == NULL ? "Not found" : res_std, t_std);
}
