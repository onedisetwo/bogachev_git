enum error_codes
{
	SUCCESS,
	ERROR_OPEN,
	ERROR_READ,
	ERROR_WRITE,
	EMPTY_FILE,
	ERROR_MEM,
	ERROR_INPUT,
	ERROR_INIT,
	DIVISION_BY_ZERO,
	DIVERGENT_INTEGRAL,
};

const char* get_error_message(int code);
