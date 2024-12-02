#include "array_io.h"
#include "constants.h"

int read_matrix(double *a, int n, int m, const char * name){
    FILE *fp;
    int i, j;
    if (!(fp = fopen(name, "r"))){
        return ERROR_OPEN;
    }
    for (i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            if (fscanf(fp, "%lf", a + i * m + j) != 1){
                fclose(fp);
                return ERROR_READ;
            }
        }
    }
    fclose(fp);
    return SUCCESS;
}

void print_matrix(double *a, int n, int m, int p){
    int np = (n > p? p: n);
    int mp = (m > p? p: m);
    int i, j;
    for (i = 0; i < np; i++){
        for (j = 0; j < mp; j++){
            printf(" %10.3e", a[i * m + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int init_matrix(double *a, int n, int m, int k){
    int i, j;
    double (*f[])(int, int, int, int) = {f1, f2, f3, f4};
    int len = sizeof(f) / sizeof(f[0]);
    double (*p)(int, int, int, int);
    if (k < 1 || k > len){
        return ERROR_INIT;
    }
    p = f[k - 1];
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            a[i * m + j] = p(n, m, i, j);
        }
    }
    return SUCCESS;
}

void init_b_vector(double *a, double *b, int n){
    int i, k;
    double sum;
    for (i = 0; i < n; i++){
        sum = 0;
        for (k = 0; k <= n - 1; k += 2){
            sum += a[i * n + k];
        }
        b[i] = sum;
    }
}