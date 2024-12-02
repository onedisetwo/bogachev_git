#include <stdio.h>
#include "set04.h"
#define TASK 6

int solution(const char *name, int *ans, double *x);
double m_fabs(double x){
    return x >= 0 ? x : -x;
}
int isEqual(double x, double y){
    return 3 * m_fabs(x-y) <= EPS*(m_fabs(x) + m_fabs(y) + 1) ? 1 : -1;
}

int main(int argc, const char *argv[]){
    int ans, ret;
    const char *name;
    double x = 0;
    if(argc != 2){
        printf("Usage: <file name> <x>\n");
        return -1;
    }
    name = argv[1];
    ret = solution(name, &ans, &x);
    switch(ret){
        case SUCCESS:{
            printf ("%s : Task = %d Result = %d X = %f\n", 
                    argv[0], TASK, ans, x);
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

int solution(const char *name, int *ans, double *x){
    FILE *fp;
    double now, avg = 0, pred, num = 0, del = 0;
    int len = 1, suml = 0;
    fp = fopen(name, "r");
    if(!fp)
        return ERROR_OPEN;
    if(fscanf(fp, "%lf", &pred) != 1){
        if(!feof(fp)){
            fclose(fp);
            return ERROR_READ;
        }
        fclose(fp);
        *ans = 0;
        return SUCCESS;
    }
    while(fscanf(fp, "%lf", &now) == 1){
        if(isEqual(now, pred) == 1){
            len++;
        }
        else{
            if(len > 1){
                del = suml + len;
                avg = (avg * suml + pred * len) / del;
                suml += len;
            }
            len = 1;
        }
        if(len == 2)
            num++;
        pred = now;
    }
    if(len > 1){
        del = suml + len;
        avg = (avg * suml + pred * len) / del;
        suml += len;
    }
    if(!feof(fp)){
        fclose(fp);
        return ERROR_READ;
    }
    fclose(fp);
    if(suml == 0){
        *ans = 0;
    }
    else{
        *ans = num;
        *x = avg;
    }
    return SUCCESS;
}