#include <stdio.h>
#include "set04.h"
#define TASK 8

int solution(const char *name, int *ans);
double m_fabs(double x){
    return x >= 0 ? x : -x;
}
int isEqual(double x, double y){
    return m_fabs(x-y) <= EPS*(m_fabs(x) + m_fabs(y)) ? 1 : -1;
}

int main(int argc, const char *argv[]){
    int ans, ret;
    const char *name;
    if(argc != 2){
        printf("Usage: <file name> <x>\n");
        return -1;
    }
    name = argv[1];
    ret = solution(name, &ans);
    switch(ret){
        case SUCCESS:{
            printf ("%s : Task = %d Result = %d\n", 
                    argv[0], TASK, ans);
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

int solution(const char *name, int *ans){
    FILE *fp;
    double pred1, pred2, now;
    int type = 0;
    fp = fopen(name, "r");
    if(!fp)
        return ERROR_OPEN;
    if(fscanf(fp, "%lf", &pred1) != 1){
        if(!feof(fp)){
            fclose(fp);
            return ERROR_READ;
        }
        fclose(fp);
        *ans = 4;
        return SUCCESS;
    }
    if(fscanf(fp, "%lf", &pred2) != 1){
        if(!feof(fp)){
            fclose(fp);
            return ERROR_READ;
        }
        fclose(fp);
        *ans = 4;
        return SUCCESS;
    }
    if(fscanf(fp, "%lf", &now) != 1){
        if(!feof(fp)){
            fclose(fp);
            return ERROR_READ;
        }
        fclose(fp);
        if(isEqual(pred1, pred2) == 1){
            *ans = 3;
        }
        if(isEqual(pred1, 0) == 1 || isEqual(pred2, 0) == 1){
            *ans = 1;
        }
        return SUCCESS;
    }
    if(isEqual(now, pred2) == 1 && isEqual(pred2, pred1) == 1)
        type = 3;
    else if(isEqual(pred1, 0) != 1 && 
            isEqual(pred2, 0) != 1 && 
            isEqual(now, 0) != 1 && 
            isEqual(now / pred2, pred2 / pred1) == 1)
        type = 2;
    else if(isEqual(now - pred2, pred2 - pred1) == 1)
        type = 1;
    else {
        fclose(fp);
        *ans = 0;
        return SUCCESS;
    }
    while(fscanf(fp, "%lf", &now) == 1){
        if(isEqual(now, pred2) == 1 && isEqual(pred2, pred1) == 1)
            type = 3;
        else if(isEqual(pred1, 0) != 1 && 
                isEqual(pred2, 0) != 1 && 
                isEqual(now, 0) != 1 && 
                isEqual(now / pred2, pred2 / pred1) == 1)
            type = 2;
        else if(isEqual(now - pred2, pred2 - pred1) == 1)
            type = 1;
        else {
            fclose(fp);
            *ans = 0;
            return SUCCESS;
        }
        pred1 = pred2;
        pred2 = now;
    }
    if(!feof(fp)){
        fclose(fp);
        return ERROR_READ;
    }
    fclose(fp);
    *ans = type;
    return SUCCESS;
}