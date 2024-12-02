#include <stdio.h>
#include "main.h"
#include "errors.h"

int get_k_name(int *k, char **name, int *arg, int argc, char *argv[]){
        if(sscanf(argv[*arg], "%d", k) != 1 || *arg >= argc)
                return ERROR_INPUT;
        (*arg)++;
        if(*k != 0)
                return SUCCESS;
        if(*arg >= argc)
                return ERROR_INPUT;
        else
                *name = argv[(*arg)++];
        return SUCCESS;
}

int read_data1_3(const char *filename, double *x, double *y, int n){
	FILE *fp;
	int i;
	if(!(fp = fopen(filename, "r")))
		return ERROR_OPEN;
	for(i = 0; i < n; i++){
		if(!( fscanf(fp, "%lf", x + i) == 1
		&& fscanf(fp, "%lf", y + i) == 1 )){
			fclose(fp);
			return ERROR_READ;
		}
	}
	fclose(fp);
	return SUCCESS;
}

int read_data4(const char *filename, double *x, double *y, double *d, int n){
	FILE *fp;
	int i;
	if(!(fp = fopen(filename, "r")))
		return ERROR_OPEN;
	for(i = 0; i < n; i++){
		if(!( fscanf(fp, "%lf", x + i) == 1
		&& fscanf(fp, "%lf", y + i) == 1
		&& fscanf(fp, "%lf", d + i) == 1 )){
			fclose(fp);
			return ERROR_READ;
		}
	}
	fclose(fp);
	return SUCCESS;
}
