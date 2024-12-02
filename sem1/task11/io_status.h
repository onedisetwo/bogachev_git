#define SUCCESS 0
#define ERROR_OPEN (-101)
#define ERROR_READ (-102)
#define EMPTY_FILE (-103)
#define ERROR_WRITE (-104)

void print_error_message(int code, char *error_file_name);
