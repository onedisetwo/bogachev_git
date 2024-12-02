#include <stdio.h>
#include "set04.h"
#define TASK 4

int solution(const char *name, int *ans, double *x, int *i, int *j);
double m_fabs(double x){
    return x >= 0 ? x : -x;
}
int isEqual(double x, double y){
    return 3 * m_fabs(x-y) <= EPS*(m_fabs(x) + m_fabs(y) + 1) ? 1 : -1;
}

int main(int argc, const char *argv[]){
    int ans, i = 0, j = 0, ret;
    const char *name;
    double x = 0;
    if(argc != 2){
        printf("Usage: <file name> <x>\n");
        return -1;
    }
    name = argv[1];
    ret = solution(name, &ans, &x, &i, &j);
    switch(ret){
        case SUCCESS:{
            printf ("%s : Task = %d Result = %d X = %f i = %d j = %d\n", 
                    argv[0], TASK, ans, x, i, j);
            return 0;
        }
        case EMPTY_FILE:{
            printf("File %s is empty\n", name);
            return -2;
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

int solution(const char *name, int *ans, double *x, int *i, int *j){
    FILE *fp;
    double now;
    int num = 1, max, fnum, lnum;
    fp = fopen(name, "r");
    if(!fp)
        return ERROR_OPEN;
    if(fscanf(fp, "%lf", &now) != 1){
        if(!feof(fp)){
            fclose(fp);
            return ERROR_READ;
        }
        fclose(fp);
        return EMPTY_FILE;
    }
    max = now;
    fnum = 1;
    lnum = 1;
    num++;
    while(fscanf(fp, "%lf", &now) == 1){
        if(isEqual(now, max) == 1)
            lnum = num;
        if(now > max){
            max = now;
            fnum = num;
            lnum = num;
        }
        num++;
    }
    if(!feof(fp)){
        fclose(fp);
        return ERROR_READ;
    }
    fclose(fp);
    *x = max;
    *i = fnum;
    *j = lnum;
    *ans = 0;
    return SUCCESS;
}