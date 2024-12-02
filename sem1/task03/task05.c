// Set:     03
// Task:    05
// Input:   file name
// Output:  int

#include <stdio.h>
#define TASK 5

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
    double now = 0, pred = 0;
    int type = 4;
    FILE *fp;
    fp = fopen(name, "r");
    if(!fp)
        return -1;
    if(fscanf(fp, "%lf", &pred) != 1){
        if(!feof(fp)){
            fclose(fp);
            return -2;
        }
        fclose(fp);
        *ans = 4;
        return 0;
    }
    while(fscanf(fp, "%lf", &now) == 1){
        if(type == 0)
            continue;
        if(type == 4){
            if(pred < now)
                type = 1;
            else if(pred > now)
                type = 2;
            else
                type = 3;
        }
        else{
            if(type == 3){
                if(pred < now)
                    type = 1;
                if(pred > now)
                    type = 2;
            }
            else{
                if((type == 1 && pred > now) || (type == 2 && pred < now))
                    type = 0;
            }
        }
        pred = now;
    }
    if(!feof(fp)){
        fclose(fp);
        return -2;
    }
    fclose(fp);
    *ans = type;
    return 0;
}