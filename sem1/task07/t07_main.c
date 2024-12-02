#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"

#define TASK 7

int solve(double* a, int n, char* name, int* res);

int main(int argc, char *argv[]){
	int n, p, res, ret;
	char* name = 0;
	double* a;
	double t;
	if( !(argc == 4 && sscanf(argv[1], "%d", &n) == 1 &&
	    sscanf(argv[2], "%d", &p) == 1) ) {
		printf("Usage: %s n p [name]\n", argv[0]);
		return 1;
	}
	name = argv[3];
        a = (double *)malloc(n * sizeof(double));
        if(!a){
                printf("Error: not enough memory\n");
                return 2;
        }
        t = clock();
        ret = solve(a, n, name, &res);
	if(ret != SUCCESS){
		print_error_message(ret, name);
		free(a);
		return 3;
	}
        t = (clock() - t) / CLOCKS_PER_SEC;
	printf("New array:\n");
	print_array(a, res, p);
        printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
                argv[0], TASK,  res, t);
        free(a);
        return 0;
}

int solve(double* a, int n, char* filename, int *res){
	FILE *fp;
	int ans = 0, i, j;
	double now, pred1, pred2;
	if( !(fp = fopen(filename, "r")) )
		return ERROR_OPEN;
	if(fscanf(fp, "%lf", &pred1) != 1)
		if(!feof(fp)){
			fclose(fp);
			return ERROR_READ;
		}
	if(fscanf(fp, "%lf", &pred2) != 1)
		if(!feof(fp)){
			fclose(fp);
			return ERROR_READ;
		}
	while(fscanf(fp, "%lf", &now) == 1){
		if(pred1 < pred2 && now < pred2){
			if(ans > n)
				ans = n;
			for(i = 0; i < n; i++){
				if(i >= ans){
					a[i] = pred2;
					ans++;
					break;
				}
				if(a[i] < pred2){
					if(ans >= n)
						ans = n - 1;
					for(j = ans; j > i; j--){
						a[j] = a[j - 1];
					}
					a[i] = pred2;
					ans++;
					break;
				}
				if(is_equal(a[i], pred2))
					break;
			}
		}
		pred1 = pred2;
		pred2 = now;
	}
	if(!feof(fp)){
		fclose(fp);
		return ERROR_READ;
	}
	*res = ans;
	fclose(fp);
	return SUCCESS;
}
