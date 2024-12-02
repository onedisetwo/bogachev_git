// Set:     03
// Task:    04
// Input:   file name
// Output:  int

#include <stdio.h>
#define TASK 4

int solution(const char *name, int *ans);

int main(int argc, char *argv[]){
    int res = 0, ans = 0;
    char *name;
    if(argc != 2){
        printf("Usage: <file name>\n");
        return -1;
    }
    name = argv[1];
    res = solution(name, &ans);
    if(res != 0){
        switch(res){
            case -1:
                printf("Error: cannot open %s\n", name);
                break;
            case -2:
                printf("Error: cannot read %s\n", name);
                break;
            default:
                printf("Error: unknown error %d in file %s\n", res, name);
        }
        return -2;
    }
    printf("%s : Task = %d Result = %d\n", argv[0], TASK, ans);
}

int solution(const char *name, int *ans){
    double now = 0, pred2 = 0, pred1 = 0;
    int num = 0;
    FILE *fp;
    fp = fopen(name, "r");
    if(!fp)
        return -1;
    if(fscanf(fp, "%lf", &pred2) != 1){
        if(!feof(fp)){
            fclose(fp);
            return -2;
        }
        fclose(fp);
        *ans = 0;
        return 0;
    }
    if(fscanf(fp, "%lf", &pred1) != 1){
        if(!feof(fp)){
            fclose(fp);
            return -2;
        }
        fclose(fp);
        *ans = 0;
        return 0;
    }
    while(fscanf(fp, "%lf", &now) == 1){
        if(pred1 >= pred2 && pred1 >= now)
            num++;
        pred2 = pred1;
        pred1 = now;
    }
    if(!feof(fp)){
        fclose(fp);
        return -2;
    }
    fclose(fp);
    *ans = num;
    return 0;
}