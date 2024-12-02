#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"

#define TASK 5

int solve(int k, double* a, int n);

int main(int argc, char *argv[]){
	int n, p, s, res, ret, k;
	char* name = 0;
	double* a;
	double t;
	if( !((argc == 5 || argc == 6) && sscanf(argv[1], "%d", &k) == 1 &&
	    sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 &&
	    sscanf(argv[4], "%d", &s) == 1) ) {
		printf("Usage: %s k n p s [name]\n", argv[0]);
		return 1;
	}
	if(argc == 6){
		if(s == 0)
			name = argv[5];
		else{
			printf("Usage: %s k n p s [name]\n", argv[0]);
			return 1;
		}
	}
	else
                if(s < 1 || s > 6){
                        printf("Usage: %s k n p s [name]\n", argv[0]);
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
        res = solve(k, a, n);
        t = (clock() - t) / CLOCKS_PER_SEC;
	printf("New array:\n");
	print_array(a, res, p);
        printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
                argv[0], TASK,  res, t);
        free(a);
        return 0;
}

int solve(int k, double* a, int n){
	int i, nCAvg = 0, nFAvg = 0,  del = 0, isFirst = 1;
	double finAvg = 0, currAvg = 0;
	for(i = 1; i < n; i++){
		if( !(a[i-1] < a[i]) ){
			if(isFirst){
				currAvg = a[i-1];
				nCAvg++;
				isFirst = 0;
			}
			currAvg = (currAvg * nCAvg + a[i]) / (nCAvg + 1);
			nCAvg++;
		}
		else{
			if((nCAvg + nFAvg) != 0 && nCAvg >= k){
				finAvg = (finAvg * nFAvg + currAvg * nCAvg) / (nCAvg + nFAvg);
				nFAvg += nCAvg;
			}
			isFirst = 1;
			currAvg = 0;
			nCAvg = 0;
		}
	}
	if((nFAvg + nCAvg) != 0 && nCAvg >= k){
		finAvg = (finAvg * nFAvg + currAvg * nCAvg) / (nCAvg + nFAvg);
		nFAvg += nCAvg;
	}
	if(nFAvg != 0)
		for(i = 0; i < n; i++){
			a[i - del] = a[i];
			if(a[i] < finAvg)
				del++;
		}
	return n - del;
}
