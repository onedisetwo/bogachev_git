#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "m_string.h"
#include "test.h"

#define TASK 5
#define print_usage printf("Usage: %s count s1 s2\n", argv[0])

int main(int argc, char *argv[]){
	size_t count, len;
	double t, t_std;
	char *s = 0, *s1 = 0, *s2 = 0, *res = 0, *res_std = 0;
	if(argc != 4 || sscanf(argv[1], "%zu", &count) != 1){
		print_usage;
		return 1;
	}
	s = argv[2];
	s2 = argv[3];
	len = strlen_(s) + strlen_(s2);
	s1 = (char *)malloc((len + 1)*sizeof(char));
	if(!s1){
		printf("%s : Not enough memory\n", argv[0]);
		return 2;
	}
	strcpy_(s1, s);
	t = test_2_5(count, strcat_, s1, s2, &res);
	strcpy_(s1, s);
	t_std = test_2_5(count, strcat, s1, s2, &res_std);
	printf("%s : Task = %d Res = %s Elapsed = %.2f\n",
		argv[0], TASK, res, t);
	printf("%s : Task = %d Res = %s Elapsed = %.2f\n",
		argv[0], TASK, res_std, t_std);
	free(s1);
}
