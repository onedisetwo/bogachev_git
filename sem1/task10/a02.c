#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "m_string.h"
#include "test.h"

#define TASK 2
#define print_usage printf("Usage: %s count string\n", argv[0])

int main(int argc, char *argv[]){
	size_t count, len;
	double t, t_std;
	char *s1 = 0, *s2 = 0, *res = 0;
	if(argc != 3 || sscanf(argv[1], "%zu", &count) != 1){
		print_usage;
		return 1;
	}
	s2 = argv[2];
	len = strlen_(s2);
	s1 = (char *)malloc((len + 1)*sizeof(char));
	if(!s1){
		printf("%s : Not enough memory\n", argv[0]);
		return 2;
	}
	t = test_2_5(count, strcpy_, s1, s2, &res);
	t_std = test_2_5(count, strcpy, s1, s2, &res);
	printf("%s : Task = %d Res = %s Elapsed = %.2f\n",
		argv[0], TASK, s1, t);
	printf("%s : Task = %d Res = %s Elapsed = %.2f\n",
		argv[0], TASK, s1, t_std);
	free(s1);
}
