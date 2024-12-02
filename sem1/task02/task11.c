// Set:     02
// Task:    11
// Input:   int
// Output:  int

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
int solution(int);

int main(int argc, char *argv[]){
    unsigned int task = 11;
    int n = 0, res = 0;
    if (argc != 2){
        printf ("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    if(sscanf(argv[1], "%d", &n) != 1){
        printf ("Usage: %s <n>\n", argv[0]);
        return 2;
    }
    if(n <= 0){
        printf("Error: number must be positive\n");
        return 3;
    }
    res = solution(n);
    printf ("%s : Task = %d Result = %d\n",
            argv[0], task, res);
    return 0;
}

int solution(int n){
    int num = 0, d = 0, x = 0;
    if(n == 1)
        return 2;
    num = 1;
    for(x = 1; num != n;){
        x += 2;
        for(d = 3; x%d != 0 && d*d < x; d += 2){ }
        if(x%d != 0 || x == 3){
            num++;
        }
    }
    return x;
}