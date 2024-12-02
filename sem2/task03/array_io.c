#include <stdio.h>
#include <stdlib.h>
#include "array_io.h"
#include "errors.h"

void delete_array(char *a[], int n){
	int i;
	for(i = 0; i < n; i++)
		free(a[i]);
}

void print_array(char *a[], int n, int p){
	int i, m = (n < p ? n : p);
	for(i = 0; i < m; i++)
		printf("%s\n", a[i]);
}

#define BUF_LEN 1234

int read_array(char *a[], int n, const char *filename){
	char buf[BUF_LEN];
	FILE *fp;
	int i, j, k;
	fp = fopen(filename, "r");
	if(!fp)
		return ERROR_OPEN;
	for(i = 0; i < n; i++){
		if(!fgets(buf, BUF_LEN, fp)){
			delete_array(a, i);
			fclose(fp);
			return ERROR_READ;
		}
		for(j = 0; buf[j]; j++)
			if(buf[j] == '\n'){
				buf[j] = 0;
				break;
			}
		a[i] = (char*) malloc ((j + 1)*sizeof(char));
		if(!a[i]){
			delete_array(a, i);
			fclose(fp);
			return ERROR_MEM;
		}
		for(k = 0; k <= j; k++)
			a[i][k] = buf[k];
	}
	fclose(fp);
	return SUCCESS;
}
