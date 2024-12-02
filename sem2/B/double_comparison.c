#include "double_comparison.h"

double get_eps(void){
    double res;
    res = 1;
    while (res + 1 > 1){
        res /= 2;
    }
    return res;
}

double abs_value(double num){
    if (num > 0){
        return num;
    }
    return -num;
}

int is_equal(double num_1, double num_2, double Eps){
    if (abs_value(num_1 - num_2) < Eps){
        return 1;
    }
    return 0;
}