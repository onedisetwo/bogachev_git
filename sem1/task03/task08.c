// Set:     03
// Task:    08
// Input:   file name, file name
// Output:  int

#include <stdio.h>
#define TASK 8
#define EPS 1e-16

int solution(const char *nameA, const char *nameB, int *ans);
double m_fabs(double x){
    return x >= 0 ? x : -x;
}

int main(int argc, char *argv[]){
    int res = 0, ans = 0;
    char *nameA, *nameB;
    if(argc != 3){
        printf("Usage: <file name> <file name>\n");
        return -1;
    }
    nameA = argv[1];
    nameB = argv[2];
    res = solution(nameA, nameB, &ans);
    if(res != 0){
        switch(res){
            case -1:
                printf("Error: cannot open %s\n", nameB);
                break;
            case -2:
                printf("Error: cannot read %s\n", nameB);
                break;
            case 1:
                printf("Error: cannot open %s\n", nameA);
                break;
            case 2:
                printf("Error: cannot read %s\n", nameA);
                break;
            case 3:
                printf("Error: not enough elements in %s to evaluate answer\n", nameA);
                break;
            default:
                printf("Error: unknown error %d in file %s or %s\n", res, nameA, nameB);
        }
        return -2;
    }
    printf("%s : Task = %d Result = %d\n", argv[0], TASK, ans);
}

int solution(const char *nameA, const char *nameB, int *ans){
    double a[3] = {0}, b = 0;
    int type = 1, num = 0, i;
    FILE *fa, *fb;
    fb = fopen(nameB, "r");
    fa = fopen(nameA, "r");
    if(!fb)
        return -1;
    while(1 == 1){
        if(fscanf(fb, "%lf", &b) != 1){
            if(fa)
                fclose(fa);
            fclose(fb);
            return -2;
        }
        else{
            if(feof(fb)){
                break;
            }
            num++;
        }
        if(num < 2)
            continue;
        if(num == 2){
            if(!fa){
                fclose(fb);
                return 1;
            }
            for(i = 0; i < 3; i++){
                if(fscanf(fa, "%lf", &a[i]) != 1){
                    fclose(fb);
                    if(feof(fa)){
                    fclose(fa);
                        return 3;
                    }
                    fclose(fa);
                    return 2;
                }
            }
        }
        if(num > 2){
            a[0] = a[1];
            a[1] = a[2];
            if(fscanf(fa, "%lf", &a[2]) != 1){
                fclose(fb);
                if(feof(fa)){
                    fclose(fa);
                    return 3;
                }
                fclose(fa);
                return 2;
            }
        }
        if( !(m_fabs(b - (a[0]+a[2])/2) < EPS) ){
            type = 0;
        }
    }
    fclose(fa);
    fclose(fb);
    *ans = type;
    return 0;
}