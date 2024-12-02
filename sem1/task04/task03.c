#include <stdio.h>
#include "set04.h"
#define TASK 3

int solution(const char *name, double x, int *ans, int *i, int *j);
double m_fabs(double x){
    return x >= 0 ? x : -x;
}
int isEqual(double x, double y){
    return 3 * m_fabs(x-y) <= EPS*(m_fabs(x) + m_fabs(y) + 1) ? 1 : -1;
}

int main(int argc, const char *argv[]){
    int ans, i = 0, j = 0, ret;
    const char *name;
    double x;
    if(argc != 3 || sscanf(argv[2], "%lf", &x) != 1){
        printf("Usage: <file name> <x>\n");
        return -1;
    }
    name = argv[1];
    ret = solution(name, x, &ans, &i, &j);
    switch(ret){
        case SUCCESS:{
            printf ("%s : Task = %d Result = %d i = %d j = %d\n", 
                    argv[0], TASK, ans, i, j);
            return 0;
        }
        case ERROR_OPEN:{
            printf("Cannot open %s\n", name);
            return -2;
        }
        case ERROR_READ:{
            printf("Cannot read %s\n", name);
            return -2;
        }
        default:{
            printf("Unknown error with %s\n", name);
            return -2;
        }
    }
}

int solution(const char *name, double x, int *ans, int *i, int *j){
    FILE *fp;
    double now;
    int num = 1, res = 0, res1 = 0, res2 = 0;
    fp = fopen(name, "r");
    if(!fp)
        return ERROR_OPEN;
    while(fscanf(fp, "%lf", &now) == 1){
        if(isEqual(now, x) == 1){
            if(res1 == 0)
                res1 = num;
            res2 = num;
            res = 1;
        }
        num++;
    }
    if(!feof(fp)){
        fclose(fp);
        return ERROR_READ;
    }
    fclose(fp);
    if(res == 1){
        *i = res1;
        *j = res2;
    }
    *ans = res;
    return SUCCESS;
}