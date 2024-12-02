// Set:     02
// Task:    02
// Input:   double (>0)
// Output:  int

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
int solution(double);

int main(int argc, char *argv[]){
    unsigned int task = 2;
    int res = 0;
    double arg = 0;
    if (argc != 2){
        printf ("Usage: %s <n>\n",argv[0]);
        return 1;
    }
    if(sscanf(argv[1], "%le", &arg) != 1){
        printf ("Usage: %s <n>\n",argv[0]);
        return 2;
    }
    if(arg <= 0){
        printf("Error: number must be positive\n");
        return 3;
    }
    res = solution(arg);
    printf ("%s : Task = %d Result = %d\n",
            argv[0], task, res);
    return 0;
}

int solution(double x){
    int k = 0;
    double pow2 = 1;
    if(x > 1)
        for( ; !(pow2 <= x && x < pow2*2); pow2 *= 2){
            k++;
        }
    else
        for( ; !(pow2 <= x && x < pow2*2); pow2 /= 2){
            k--;
        }
    return k;
}