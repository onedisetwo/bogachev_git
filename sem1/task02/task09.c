// Set:     02
// Task:    09
// Input:   double, int
// Output:  double

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
double solution(double, int);

int main(int argc, char *argv[]){
    unsigned int task = 9;
    int n = 0;
    double x = 0, res = 0;
    if (argc != 3){
        printf ("Usage: %s <x> <n>\n", argv[0]);
        return 1;
    }
    if(sscanf(argv[1], "%le", &x) != 1){
        printf ("Usage: %s <x> <n>\n", argv[0]);
        return 2;
    }
    if(sscanf(argv[2], "%d", &n) != 1){
        printf ("Usage: %s <x> <n>\n", argv[0]);
        return 2;
    }
    if(n <= 0){
        printf("Error: expected division by 0\n");
        return 3;
    }
    res = solution(x, n);
    printf ("%s : Task = %d Result = %e\n",
            argv[0], task, res);
    return 0;
}

double solution(double x, int n){
    double res = 0, x0 = x, eps = 1.;
    while(1. + eps > 1.){
        eps /= 2.;
    }
    eps *= 2.;
    for(int i = 1; i <= n; i++){
        if(x/i < eps && x/i > -eps)
            break;
        if(i%2 == 0)
            res += x/i;
        else
            res -= x/i;
        x *= x0;
    }
    return res;
}