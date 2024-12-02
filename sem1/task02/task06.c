// Set:     02
// Task:    06
// Input:   int
// Output:  double

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
double solution(int);

int main(int argc, char *argv[]){
    unsigned int task = 6;
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
    double pow3 = 1, pow2 = 0, res = 1;
    if(n > 0){
        pow2 = 8;
        for(int i = 0; i < n; pow3 *= 3, i++){ }
        res = pow3;
        pow3 /= 3;
        for(int i = 0; i < n; pow3 /= 3, pow2 *= 2, i++){
            res += pow3 * pow2;
        }
    }
    if(n < 0){
        pow2 = 2;
        for(int i = n; i < 0; pow3 /= 3, i++){ }
        res = pow3;
        for(int i = n; i < 0; pow3 *= 3, pow2 /= 2, i++){
            res -= pow3 * pow2;
        }
    }
    return res;
}