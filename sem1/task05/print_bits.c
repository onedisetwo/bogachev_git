#include <stdio.h>
#include "io_status.h"
#include "print_bits.h"

int print_bits (const char* filename){
	FILE *file;
	unsigned int now, sizeUI, flag;
	file = fopen(filename, "r");
	if(!file)
		return ERROR_OPEN;
	while(fscanf(file, "%u", &now) == 1){
		flag = 0;
		sizeUI = 8 * sizeof(unsigned int);
		while(sizeUI != 0){
			if(((now>>(sizeUI - 1))&1) != 0)
				flag = 1;
			if(flag == 1)
				printf("%u", (now>>(sizeUI - 1))&1);
			sizeUI--;
		}
	}
	printf("\n");
	if(!feof(file)){
		fclose(file);
		return ERROR_READ;
	}
	fclose(file);
	return SUCCESS;
}

int print_bits0 (const char* filename){
	FILE *file;
	unsigned int now, sizeUI = sizeof(unsigned int);
	file = fopen(filename, "r");
	if(!file)
		return ERROR_OPEN;
	while(fscanf(file, "%u", &now) == 1){
		sizeUI = 8 * sizeof(unsigned int);
		while(sizeUI != 0){
			printf("%u", (now>>(sizeUI - 1))&1);
			sizeUI--;
		}
	}
	printf("\n");
	if(!feof(file)){
		fclose(file);
		return ERROR_READ;
	}
	fclose(file);
	return SUCCESS;
}
