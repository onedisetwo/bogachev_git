// Set:     02
// Task:    10
// Input:   int
// Output:  double

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
double solution(int);

int main(int argc, char *argv[]){
    unsigned int task = 10;
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
    if(n < 0){
        printf("Error: quantity cannot be negative\n");
        return 3;
    }
    res = solution(n);
    printf ("%s : Task = %d Result = %e\n",
            argv[0], task, res);
    return 0;
}

double solution(int n){
    int amount = 0, d = 0;
    double sum = 0;
    if(n == 0)
        return 0;
    if(n == 1)
        return 2;
    sum = 2;
    amount = 1;
    for(int x = 3; amount < n; x += 2){
        for(d = 3; x%d != 0 && d*d < x; d += 2){ }
        if(x%d != 0 || x == 3){
            sum += x;
            amount++;
        }
    }
    return sum;
}