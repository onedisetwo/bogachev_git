#include "norm.h"

double max_norm(double *a, int n, int m){
    int i, j;
    double max, cur;
    max = -1;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            cur = abs_value(a[i * m + j]);
            if (cur > max){
                max = cur;
            }
        }
    }
    return max;
}

double sum_norm(double *a, int n, int m){
    int i, j;
    double sum;
    sum = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            sum += abs_value(a[i * m + j]);
        }
    }
    return sum;
}

double sum_norm_deviation(double *a, double *x, double *b, int n){
    int j, k;
    double cur;
    for (j = 0; j < n; j++){
        cur = 0;
        for(k = j; k < n; k++){
            cur += a[j * n + k] * x[k];
        }
        x[j] = cur;
    }
    for (j = n - 1; j >= 0; j--){
        cur = x[j];
        for(k = j - 1; k >= 0; k--){
            cur += a[j * n + k] * x[k];
        }
        x[j] = cur - b[j];
    }
    return sum_norm(x, n, 1);
}