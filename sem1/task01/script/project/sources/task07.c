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
    printf ("Task = %d Result = %u\n", 7, res);
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
    const unsigned int len = 8 * sizeof (unsigned int);
    unsigned int bits[8 * sizeof (unsigned int)] = { 0 },
                 res = n,
                 counter = len;
    while (n != 0){
        counter--;
        bits[counter] = n%2;
        n /= 2;
    }
    for(unsigned int i = counter + 1 ; i < len - 1; i++){
        if(bits[i-1] == 0 && bits[i+1] == 0 && bits[i] == 0)
            res += (1 << (len - i - 1));
    }
    return res;
}