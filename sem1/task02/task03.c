// Set:     02
// Task:    03
// Input:   double
// Output:  double

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
double solution(double);

int main(int argc, char *argv[]){
    unsigned int task = 3;
    double res = 0, arg = 0;
    if (argc != 2){
        printf ("Usage: %s <n>\n",argv[0]);
        return 1;
    }
    if(sscanf(argv[1], "%le", &arg) != 1){
        printf ("Usage: %s <n>\n", argv[0]);
        return 2;
    }
    res = solution(arg);
    if(!(res < -1) && !(res > -1)){
        printf("Error: division by 0\n");
        return 3;
    }
    printf ("%s : Task = %d Result = %e\n",
            argv[0], task, res);
    return 0;
}

double solution(double x){
    double res = 0, eps = 1.;
    while(1. + eps > 1.){
        eps /= 2.;
    }
    eps *= 2.;
    if((x - 3) < eps && (x - 3) > -eps){
        // Error: division by 0
        return -1;
    }
    if(x - 1 >= 0)
        res = x - 1;
    else
        res = -(x - 1);
    res -= 2;
    res /= x - 3;
    if(res < 0)
        res = -res;
    return res;
}