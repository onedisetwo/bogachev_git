#include "help_funcs.h"

int max(int x, int y){
    if (x > y){
        return x;
    }
    return y;
}

int abs(int x){
    if (x > 0){
        return x;
    }
    return -x;
}

double f1(int n, int m, int i, int j){
    return max(n, m) - max(i, j);
}

double f2(int n, int m, int i, int j){
    (void) n;
    (void) m;
    return 1 + max(i, j);
}

double f3(int n, int m, int i, int j){
    (void) n;
    (void) m;
    return abs(i - j);
}

double f4(int n, int m, int i, int j){
    (void) n;
    (void) m;
    return 1. / (i + j + 1);
}