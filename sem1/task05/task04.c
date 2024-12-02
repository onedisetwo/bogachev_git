#include <stdio.h>
#include "io_status.h"
#include "print_bits.h"

#define TASK 4

int main(int argc, const char *argv[]){
	int ret, res = 0, i = 0, j = 0;
	if(argc != 2){
		printf("Usage: <filename>");
		return  WRONG_INPUT;
	}
	ret = solution(argv[1], &res, &i, &j);
	if(ret == SUCCESS){
		ret = print_bits0(argv[1]);
		if(ret != SUCCESS){
			switch(ret){
				case ERROR_OPEN:
					printf("Error: cannot open %s second time for print_bits\n", argv[1]);
					break;
				case ERROR_READ:
					printf("Error: cannot read %s second time for print_bits\n", argv[1]);
					break;
				default:
					printf("Unknown error with file %s during second opening\n", argv[1]);
			}
		}
		printf("%s : Task = %d Result = %d i = %d j = %d\n",
			argv[0], TASK, res, i, j);
		return SUCCESS;
	}
	switch(ret){
		case ERROR_OPEN:
			printf("Error: cannot open %s\n", argv[1]);
			break;
		case ERROR_READ:
			printf("Error: cannot read %s\n", argv[1]);
			break;
		default:
			printf("Unknown error with file %s\n", argv[1]);
	}
	return -2;
}

int solution(const char *filename, int *res, int *i, int *j){
	FILE *fp;
	unsigned int now, nowBits[3] = {0}, sizeUI, counterMain = 0;
	int counterAns = 0, first = -1, last = -1;
	fp = fopen(filename, "r");
	if(!fp)
		return ERROR_OPEN;
	while(fscanf(fp, "%u", &now) == 1){
		sizeUI = 8 * sizeof(unsigned int);
		while(sizeUI != 0){
			nowBits[2] = (now>>(sizeUI - 1))&1;
			sizeUI--;
			if(counterMain > 1 && nowBits[0] < nowBits[1] && nowBits[2] < nowBits[1]){
				if(counterAns == 0)
					first = counterMain - 1;
				last = counterMain - 1;
				counterAns++;
			}
			nowBits[0] = nowBits[1];
			nowBits[1] = nowBits[2];
			counterMain++;
		}
	}
	if(!feof(fp)){
		fclose(fp);
		return ERROR_READ;
	}
	if(counterAns != 0){
		*res = counterAns;
		*i = first;
		*j = last;
	}
	fclose(fp);
	return SUCCESS;
}
