// Set:     02
// Task:    05
// Input:   double, double, double
// Output:  unsigned int, double, double

int sscanf(const char * string, const char * format, ...);
int printf(const char *, ...);
void solution(double, double, double, double *, double *, int *);
double sqrt(double);

int main(int argc, char *argv[]){
    unsigned int task = 5;
    int num = 0;
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    if(argc != 4){
        printf("Usage: %s <a> <b> <c>\n", argv[0]);
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
    solution(a, b, c, &x1, &x2, &num);
    if(num == -1){
        printf("Error: infinity number of solutions\n");
        return 3;
    }
    printf ("%s : Task = %d Num = %d X1 = %e X2 = %e\n",
            argv[0], task, num, x1, x2);
    return 0;
}

void solution(double a, double b, double c, 
              double *x1, double *x2, int *num){
    double d = 0, temp = 0, eps = 1.;
    while(1. + eps > 1.){
        eps /= 2.;
    }
    eps *= 2.;
    if(a < eps && a > -eps){
        if(b < eps && b > -eps){
            x1 = 0;
            x2 = 0;
            if(c < eps && c > -eps)
                *num = -1; // infinity number of solutions
            else{
                x1 = 0;
                x2 = 0;
                *num = 0; // no solutions because of 0 + c != 0
            }
        }
        else {
            *x1 = -c / b;
            *x2 = 0;
            *num = 1;
        }
        return ;
    }
    d = b*b - 4*a*c;
    if(d < 0){
        *x1 = 0;
        *x2 = 0;
        *num = 0;
    }
    else if(d > 0){
        *x1 = (-b + sqrt(d))/2*a;
        *x2 = (-b - sqrt(d))/2*a;
        if(*x2 > *x1){
            temp = *x1;
            *x1 = *x2;
            *x2 = temp;
        }
        if((d - b*b) < eps && (d - b*b) > -eps){
            if(*x1 < eps && *x1 > -eps){
                if(b > 0 || b < 0)
                    *x1 = -b - *x2;
                else
                    *x1 = c / *x2;
            }
            if(*x2 < eps && *x2 > -eps){
                if(b > 0 || b < 0)
                    *x2 = -b - *x1;
                else
                    *x2 = c / *x1;
            }
        }
        *num = 2;
    }
    else{
        *x1 = -b / 2*a;
        *x2 = 0;
        *num = 1;
    }
    return ;
}
