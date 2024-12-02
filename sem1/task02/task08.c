// Set:     02
// Task:    08
// Input:   double, int
// Output:  double

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
double solution(double, int);

int main(int argc, char *argv[]){
    unsigned int task = 8;
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
    if(n < 0){
        printf("Error: factorial of a negative number is undefined\n");
        return 3;
    }
    res = solution(x, n);
    printf ("%s : Task = %d Result = %e\n",
            argv[0], task, res);
    return 0;
}

double solution(double x, int n){
    double res = 0, fact = 1, x0 = x, eps = 1.;
    while(1. + eps > 1.){
        eps /= 2.;
    }
    eps *= 2;
    if(n == 0)
        return x + 1;
    for(int i = 1; i <= n; i++){
        fact *= i;
        if(x/fact < eps && x/fact > -eps)
            break;
        res += x/fact;
        x *= x0;
    }
    return res;
}