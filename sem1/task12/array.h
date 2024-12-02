void print_array (char **, int n, int max_print);

// Особождение ячеек 0..n-1 массива
void free_array (char **, int n);

int read_array (char **, int n, const char *name);

enum error_codes{
	SUCCESS, ERROR_OPEN, ERROR_READ, ERROR_MEM
};
