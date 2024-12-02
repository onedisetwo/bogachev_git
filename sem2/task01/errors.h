enum error_codes
{
	SUCCESS,
	ERROR_OPEN,
	ERROR_READ,
	ERROR_WRITE,
	EMPTY_FILE,
	ERROR_MEM,
	ERROR_INPUT,
};

const char* get_error_message(int code);
