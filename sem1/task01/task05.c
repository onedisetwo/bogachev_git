int printf(const char *,...);
int scanf(const char *,...);
void print_bits(unsigned int);
unsigned int f1(unsigned int);

int main(void){
    unsigned int n, res;
    printf ("Input:\t");
    if (scanf ("%u", &n) != 1){
        printf ("Usage: number\n");
        return 1;
    }
    print_bits (n);
    res = f1 (n);
    printf("Result:\t");
    print_bits (res);
    printf ("Task = %d Result = %u\n", 5, res);
    return 0;
}

void print_bits(unsigned int n){
    const unsigned int len = 8 * sizeof (unsigned int);
    unsigned int bits[8 * sizeof (unsigned int)] = { 0 };
    for (unsigned int counter = len - 1; n != 0; counter--){
        bits[counter] = n%2;
        n /= 2;
    }
    for(unsigned int i = 0; i < len; i++)
        printf("%u",bits[i]);
    printf("\n");
}

unsigned int f1(unsigned int n){
    unsigned int counter = 0, res = 0, is0 = 0;
    while (n != 0){
        if(is0 == 1){
            counter++;
            if(n%2 == 0)
                res = counter;
        }
        if(n%2 == 0 && is0 == 0)
            is0 = 1;
        n /= 2;
    }
    return res-1;
}