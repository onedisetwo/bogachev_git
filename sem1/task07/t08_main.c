#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "io_status.h"
#include "io_array.h"
#include "m_func.h"

#define TASK 8

int solve(char* filename, double* a, int n, int* res);

int main(int argc, char *argv[]){
	int n, p, s, res, ret;
	char* name = 0;
	char *b = 0;
	double* a;
	double t;
	if( !((argc == 5 || argc == 6) && sscanf(argv[2], "%d", &n) == 1 &&
	    sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1) ) {
		printf("Usage: %s [name B] n p s [name]\n", argv[0]);
		return 1;
	}
	b = argv[1];
	if(argc == 6){
		if(s == 0)
			name = argv[5];
		else{
			printf("Usage: %s [name B] n p s [name]\n", argv[0]);
			return 1;
		}
	}
	else
                if(s < 1 || s > 6){
                        printf("Usage: %s [name B] n p s [name]\n", argv[0]);
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
        ret = solve(b, a, n, &res);
	if(ret != SUCCESS){
		print_error_message(ret, b);
		free(a);
		return 4;
	}
        t = (clock() - t) / CLOCKS_PER_SEC;
        printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
                argv[0], TASK,  res, t);
        free(a);
        return 0;
}

int solve(char* filename, double* a, int n, int* res){
	FILE *fp;
	double now;
	int i, c = 0, num = 0, ans = 0, k = 1, f1 = 0;
	if( !(fp = fopen(filename, "r")) )
		return ERROR_OPEN;
	while(fscanf(fp, "%lf", &now) == 1){
//		printf("%lf:\n", now);
		if(is_equal(now,a[c])){
//			printf("now == a[%d]\n", c);
			c++;
		}
		else{
			if(c == 0)
				continue;
//			printf("now != a[%d]\n",c);
			k = 1;
			for(i = 0; i + k <= c; i++){
				if(i+k == c){
//					printf("compare a[%d] and %lf\n",i,now);
					if(!is_equal(a[i],now)){
						f1 = 1;
//						printf("4\n");
						k++;
						i = -1;
						continue;
					}
					else
						break;
				}
//				printf("compare a[%d] and a[%d]\n",i,i+k);
				if(!is_equal(a[i], a[i + k])){
					f1 = 1;
//					printf("3\n");
					k++;
					i = -1;
				}
			}
			c = i;
			if(f1 == 0)
				c++;
			f1 = 0;
//			printf("c = %d\n", c);
		}
		if(c == n){
//			printf("c == n, ans++\n");
			ans++;
			k = 1;
			for(i = 0; i + k < c; i++){
//				printf("compare a[%d] and a[%d]\n",i,i+k);
				if(!is_equal(a[i], a[i + k])){
//					printf("2\n");
					k++;
					i = -1;
				}
			}
			c = i;
//			printf("c = %d\n", c);
		}
		num++;
//		printf("\n");
	}
	if(!feof(fp)){
		fclose(fp);
		return ERROR_READ;
	}
	*res = ans;
	fclose(fp);
	return SUCCESS;
}
