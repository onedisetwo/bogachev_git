#include <stdio.h>
#include "io_status.h"
#include "io_array.h"

int read_array(double* a, int n, const char* name){
	FILE *fp;
	int i;
	if( !(fp = fopen(name, "r")) )
		return ERROR_OPEN;
	for(i = 0; i < n; i++){
		if(fscanf(fp, "%lf", a + i) != 1){
			fclose(fp);
			return ERROR_READ;
		}
	}
	fclose(fp);
	return SUCCESS;
}

void init_array(double *a, int n, int s){
	int i;
	switch(s){
		case 1:
			for(i = 1; i <= n; i++)
				a[i - 1] = i;
			break;
		case 2:
			for(i = 1; i <= n; i++)
				a[i - 1] = n - i;
			break;
		case 3:
			for(i = 1; i <= n; i++)
				a[i - 1] = (double)(i) / 2.0;
			break;
		case 4:
			for(i = 1; i <= n; i++)
				a[i - 1] = n - (double)(i) / 2.0;
			break;
		case 5:
			for(i = 1; i <= n; i++)
				a[i - 1] = (double)(i) * 2.0;
			break;
		case 6:
			for(i = 1; i <= n; i++)
				a[i - 1] = n - (double)(i) * 2.0;
			break;
	}
}

void print_array(double *a, int n, int p){
	int i;
	for(i = 0; i < p && i < n; i++)
		printf("%lf ", *(a+i));
	printf("\n");
}
