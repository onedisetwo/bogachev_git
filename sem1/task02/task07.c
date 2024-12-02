// Set:     02
// Task:    07
// Input:   int
// Output:  double

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
double solution(int);

int main(int argc, char *argv[]){
    unsigned int task = 7;
    int n = 0;
    double res = 0;
    if (argc != 2){
        printf ("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    if(sscanf(argv[1], "%d", &n) != 1){
        printf ("Usage: %s <n>\n", argv[0]);
        return 2;
    }
    res = solution(n);
    printf ("%s : Task = %d Result = %e\n",
            argv[0], task, res);
    return 0;
}

double solution(int n){
    double x0 = 2, x1 = 9, res = 0, pow2 = 0;
    if(n == 0){
        return x0;
    }
    if(n == 1){
        return x1;
    }
    if(n > 1){
        pow2 = 4;
        for(int i = 2; i <= n; i++){
            res = 5*x1 - 6*x0 + pow2;
            x0 = x1;
            x1 = res;
            pow2 *= 4;
        }
    }
    if(n < 0){
        pow2 = 1;
        for(int i = -1; i >= n; i--){
            res = (5*x0 - x1 + pow2);
            x0 = x1;
            x1 = res;
            pow2 /= 4;
        }
    }
    return res;
}