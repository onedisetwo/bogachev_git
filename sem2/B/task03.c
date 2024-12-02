#include "double_comparison.h"
#include "norm.h"
#include "initial.h"
#include "constants.h"

int LU_factorization(double *a, int n);
int solve03(double *a, double *b, double *x, int n);

/*int LU_factorization(double *a, int n){
    int i, j, k;
    int in, ij, ik, jj, kj;
    int m;
    double cur;
    ij = 0;
    m = n + 1;
    for (i = 0; i < n; i++){
        in = ij;
        jj = 0;
        for (j = 0; j < i; j++){
            cur = a[ij];
            ik = in;
            kj = j;
            for (k = 0; k < j; k++){
                cur -= a[ik] * a[kj];
                ik++;
                kj += n;
            }
            a[ij] = cur / a[jj];
            ij++;
            jj += m;
        }
        for (; j < n; j++){
            cur = a[ij];
            ik = in;
            kj = j;
            for (k = 0; k < i; k++){
                cur -= a[ik] * a[kj];
                ik++;
                kj += n;
            }
            a[ij] = cur;
            ij++;
        }
    }
    return SUCCESS;
}*/

/*int LU_factorization(double *a, int n){
    int i;
    int in, ij, ik, jj, kj;
    int m;
    double cur;
    ij = 0;
    m = n + 1;
    for (i = 0; i < n; i++){
        in = ij;
        for (jj = 0;; jj += m){
            cur = a[ij];
            ik = in;
            kj = ij - in;
            if (kj >= i){
                break;
            }
            for (;kj < jj;){
                cur -= a[ik] * a[kj];
                ik++;
                kj += n;
            }
            a[ij] = cur / a[jj];
            ij++;
        }
        for (;;){
            cur = a[ij];
            ik = in;
            kj = ij - in;
            if (kj >= n){
                break;
            }
            for (;kj < ij;){
                cur -= a[ik] * a[kj];
                ik++;
                kj += n;
            }
            a[ij] = cur;
            ij++;
        }
    }
    return SUCCESS;
}*/

int LU_factorization(double *a, int n){
    int i, j, k;
    double cur;
    for (i = 0; i < n; i++){
        for (j = 0; j < i; j++){
            cur = a[i * n + j];
            for (k = 0; k < j;  k++){
                cur -= a[i * n + k] * a[k * n + j];
            }
            a[i * n + j] = cur / a[j * n + j];
        }
        for (; j < n; j++){
            cur = a[i * n + j];
            for (k = 0; k < i; k++){
                cur -= a[i * n + k] * a[k * n + j];
            }
            a[i * n + j] = cur;
        }
    }
    return SUCCESS;
}

int solve03(double *a, double *b, double *x, int n){
    int j, k, ret;
    double cur;
    ret = LU_factorization(a, n);
    if (ret != SUCCESS){
        switch (ret){
            case ERROR_DIVISION:
                return ERROR_DIVISION;
            case ERROR_ALG:
                return ERROR_ALG;
            default:
                return ERROR_UNKNOWN;
        }
    }
    for (j = 0; j < n; j++){
        cur = b[j];
        for(k = 0; k < j; k++){
            cur -= a[j * n + k] * x[k];
        }
        x[j] = cur;
    }
    for (j = n - 1; j >= 0; j--){
        cur = x[j];
        for(k = j + 1; k < n; k++){
            cur -= a[j * n + k] * x[k];
        }
        x[j] = cur / a[j * n + j];
    }
    return SUCCESS;
}

int main(int argc, char **argv){
    main_0(argc, argv, 3, solve03);
}