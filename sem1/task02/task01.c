// Set:     02
// Task:    01
// Input:   void
// Output:  double

int printf(const char *, ...);
double solution(void);

int main(int argc, char *argv[]){
    unsigned int task = 1;
    double res = 0;
    if (argc != 1){
        printf ("Usage: %s\n",argv[0]);
        return 1;
    }
    res = solution();
    printf ("%s : Task = %d Result = %e\n",
            argv[0], task, res);
    return 0;
}

double solution(void){
    double eps = 1.;
    while(1. + eps > 1.){
        eps /= 2.;
    }
    return eps * 2.;
}