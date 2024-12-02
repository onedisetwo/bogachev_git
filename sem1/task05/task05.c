#include <stdio.h>
#include "io_status.h"
#include "print_bits.h"

#define TASK 5

int main(int argc, const char *argv[]){
	int ret, res = 0, i = 0, j = 0;
	if(argc != 2){
		printf("Usage: <filename>");
		return  WRONG_INPUT;
	}
	ret = solution(argv[1], &res, &i, &j);
	if(ret == SUCCESS){
		ret = print_bits(argv[1]);
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
	unsigned int now, predBit, nowBit, sizeUI, counterMain = 0, fNotZero;
	int maxLen = 0, currLen = 1, currFirst = -1, first = -1, last = -1;
	fp = fopen(filename, "r");
	if(!fp)
		return ERROR_OPEN;
	predBit = 0;
	while(fscanf(fp, "%u", &now) == 1){
		fNotZero = 0;
		sizeUI = 8 * sizeof(unsigned int);
		while(sizeUI != 0){
			nowBit = (now>>(sizeUI - 1))&1;
			sizeUI--;
			if(nowBit == 1)
				fNotZero = 1;
			if(fNotZero == 0)
				continue;
			if(nowBit == 1 && maxLen < 2){
				last = counterMain;
				if(maxLen == 0){
					first = counterMain;
					maxLen = 1;
				}
			}
			if(predBit == 1 && nowBit == 1){
				if(currLen == 1)
					currFirst = counterMain - 1;
				currLen++;
				if(currLen == maxLen)
					last = currFirst;
				if(currLen > maxLen){
					maxLen = currLen;
					first = currFirst;
					last = currFirst;
				}
			}
			else
				currLen = 1;
			predBit = nowBit;
			counterMain++;
		}
	}
	if(!feof(fp)){
		fclose(fp);
		return ERROR_READ;
	}
	if(maxLen != 0){
		*res = maxLen;
		*i = first;
		*j = last;
	}
	fclose(fp);
	return SUCCESS;
}

