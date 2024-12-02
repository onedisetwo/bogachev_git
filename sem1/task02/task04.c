// Set:     02
// Task:    04
// Input:   double, double, double
// Output:  double, double

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
void solution(double, double, double, double *, double *);

int main(int argc, char *argv[]){
    unsigned int task = 4;
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    if (argc != 4){
        printf ("Usage: %s <a> <b> <c>\n",argv[0]);
        return 1;
    }
    if(sscanf(argv[1], "%le", &a) != 1){
        printf ("Usage: %s <a> <b> <c>\n",argv[0]);
        return 2;
    }
    if(sscanf(argv[2], "%le", &b) != 1){
        printf ("Usage: %s <a> <b> <c>\n",argv[0]);
        return 2;
    }
    if(sscanf(argv[3], "%le", &c) != 1){
        printf ("Usage: %s <a> <b> <c>\n",argv[0]);
        return 2;
    }
    solution(a, b, c, &x1, &x2);
    printf ("%s : Task = %d X1 = %e X2 = %e\n",
            argv[0], task, x1, x2);
    return 0;
}

void solution(double a, double b, double c, 
              double *max, double *min){
    if(a > b && a > c)
        *max = a;
    else
        if(b > c)
            *max = b;
        else
            *max = c;
    if(a < b && a < c)
        *min = a;
    else
        if(b < c)
            *min = b;
        else
            *min = c;
}