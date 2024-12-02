#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"

#define TASK 7

int solve(double* a, int n, char* nameB, int* res);

int main(int argc, char *argv[]){
	int n, p, s, res, ret;
	char* name = 0, *nameB = 0;
	double* a;
	double t;
	if( !((argc == 5 || argc == 6) && sscanf(argv[2], "%d", &n) == 1 &&
	    sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1) ) {
		printf("Usage: %s n p s [name]\n", argv[0]);
		return 1;
	}
	nameB = argv[1];
	if(argc == 6){
		if(s == 0)
			name = argv[5];
		else{
			printf("Usage: %s n p s [name]\n", argv[0]);
			return 1;
		}
	}
	else
                if(s < 1 || s > 6){
                        printf("Usage: %s n p s [name]\n", argv[0]);
                        return 1;
                }
        a = (double *)malloc(n * sizeof(double));
        if(!a){
                printf("Error: not enough memory\n");
                return 2;
        }
        if(s == 0){
                ret = read_array(a, n, name);
                if(ret != SUCCESS){
                        print_error_message(ret, name);
                        free(a);
                        return 3;
                }
        }
        else
                init_array(a, n, s);
        print_array(a, n, p);
        t = clock();
        ret = solve(a, n, nameB, &res);
        if(ret != SUCCESS){
                print_error_message(ret, nameB);
                free(a);
                return 3;
        }
	t = (clock() - t) / CLOCKS_PER_SEC;
        printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
                argv[0], TASK,  res, t);
	free(a);
	return 0;
}

int solve(double* a, int n, char *filename, int* res){
	int i, ans = 0;
	double now;
	FILE *fp;
	if( !(fp = fopen(filename, "r")) ){
		return ERROR_OPEN;
	}
	while(fscanf(fp, "%lf", &now) == 1){
		for(i = 0; i < n; i++)
			if(is_equal(a[i], now)){
				ans++;
				break;
			}
	}
	if(!feof(fp)){
		fclose(fp);
		return ERROR_READ;
	}
 	*res = ans;
	return SUCCESS;
}
