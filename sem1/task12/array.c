#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

#define BUF_LEN 1234

void print_array (char **a, int n, int max_print){
	int i, m = (n > max_print ? max_print : n);
	for(i = 0; i < m; i++)
		if(a[i])
			printf("%s\n", a[i]);
}

void free_array (char **a, int n){
	int i;
	for(i = 0; i < n; i++)
		if(a[i]){
			free(a[i]);
			a[i] = 0;
		}
}

int read_array (char **a, int n, const char *name){
	char buf[BUF_LEN];
	FILE *fp;
	int i, j;
	if(!(fp = fopen(name, "r")))
		return ERROR_OPEN;
	for(i = 0; i < n; i++){
		if(!fgets(buf, BUF_LEN, fp)){
			fclose(fp);
			free_array(a, i);
			return ERROR_READ;
		}
		for(j = 0; buf[j]; j++)
			if(buf[j] == '\n'){
				buf[j] = 0;
				break;
			}
		a[i] = (char *)malloc((j+1)*sizeof(char));
		if(!a[i]){
			fclose(fp);
			free_array(a, i);
			return ERROR_MEM;
		}
		strcpy(a[i], buf);
	}
	fclose(fp);
	return SUCCESS;
}
