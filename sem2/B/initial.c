#include "initial.h"
#include "constants.h"

int set_r1(double *a, double *b, double *x, int n, double *r1, double Eps){
    double norm_b;
    norm_b = sum_norm(b, n, 1);
    if (is_equal(norm_b, 0, Eps) == 1){
        return ERROR_DIVISION;
    }
    *r1 = sum_norm_deviation(a, x, b, n) / norm_b;
    return SUCCESS;
}

void set_r2(double *x, int n, double *r2){
    int i;
    *r2 = 0;
    for (i = 0; i < n; i++){
        *r2 += abs_value(x[i] - ((i + 1) % 2));
    }
}

int calculate_r(double *a, double *x, double *b, int n, double *r1, double *r2, double Eps){
    int ret;
    set_r2(x, n, r2);
    ret = set_r1(a, b, x, n, r1, Eps);
    if (ret != SUCCESS){
        switch(ret){
            case ERROR_DIVISION:
                return ERROR_DIVISION;
            default:
                return ERROR_UNKNOWN;
        }
    }
    return SUCCESS;
}

int check(double *a, int n, double Eps_norm){
    int i;
    for (i = 0; i < n; i++){
        if (is_equal(a[i * n + i], 0, Eps_norm) == 1){
            return ERROR_ALG;
        }
    }
    return SUCCESS;
}

int main_0(int argc, char **argv, int task, int (*solve)(double *, double *, double *, int)){
    double *a, *b, *x;
    int n, p, k;
    char *name = 0;
    int ret;
    double t;
    double Eps, Eps_norm;
    double r1, r2;
    Eps = get_eps();
    if (!((argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1 && n > 0 && sscanf(argv[2], "%d", &p) == 1 && p >= 0 && sscanf(argv[3], "%d", &k) == 1 && k >= 0)){
        printf("Usage: %s n p k [name]\n", argv[0]);
        return 1;
    }
    if (argc == 5){
        name = argv[4];
        if (k != 0){
            printf("Improper value of k!\n");
            return 1;
        }
        if (!(name)){
            printf("Improper name of file!\n");
            return 1;
        }
    }
    else{
        if (k == 0){
            printf("Improper value of k!\n");
            return 1;
        }
    }

    a = (double *) malloc(n * n * sizeof(double));
    if (!a){
        printf("Not enougth memory!\n");
        return 2;
    }
    b = (double *) malloc(n * sizeof(double));
    if (!b){
        printf("Not enougth memory!\n");
        free(a);
        return 2;
    }
    x = (double *) malloc(n * sizeof(double));
    if (!x){
        printf("Not enougth memory!\n");
        free(a);
        free(b);
        return 2;
    }
    if (name){
        ret = read_matrix(a, n, n, name);
    }
    else{
        ret = init_matrix(a, n, n, k);
    }
    if (ret != SUCCESS){
        switch(ret){
            case ERROR_OPEN:
                printf("Cannot open %s\n", name);
                break;
            case ERROR_READ:
                printf("Cannot read %s\n", name);
                break;
            case ERROR_INIT:
                printf("Cannot initialize array!\n");
                break;
            default:
                printf("Unknown error %d in %s %s\n", ret, name? "file": "init", name? name: " ");
        }
        free(a);
        free(b);
        free(x);
        return 3;
    }
    init_b_vector(a, b, n);

    printf("Init:\n");
    print_matrix(a, n, n, p);
    print_matrix(b, 1, n, p);

    Eps_norm = Eps * max_norm(a, n, n);
    ret = check(a, n, Eps_norm);
    if (ret != SUCCESS){
        switch(ret){
            case ERROR_ALG:
                printf("The algorithm is not applicable. The matrix is probably singular.\n");
                break;
            default:
                printf("Unknown error!\n");
        }
        free(a);
        free(b);
        free(x);
        return 3;
    }

    t = clock();
    ret = solve(a, b, x, n);
    t = (clock() - t) / CLOCKS_PER_SEC;

    if (ret != SUCCESS){
        switch(ret){
            case ERROR_DIVISION:
                printf("Zero division error in solve-function.\n");
                break;
            case ERROR_ALG:
                printf("The algorithm is not applicable.\n");
                break;
            default:
                printf("Unknown error in solve-function.\n");
        }
        free(a);
        free(b);
        free(x);
        return 3;
    }
    printf("Result:\n");
    print_matrix(x, 1, n, p);
    calculate_r(a, x, b, n, &r1, &r2, Eps);
    printf("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f K = %d N = %d\n", argv[0], task, r1, r2, t, k, n);
    free(a);
    free(b);
    free(x);
    return 0;
}