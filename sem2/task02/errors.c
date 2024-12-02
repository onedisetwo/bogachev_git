#include "errors.h"

const char* get_error_message(int code){
	switch(code){
		case ERROR_OPEN:
			return "Failed to open file";
		case ERROR_READ:
			return "Failed to read file";
		case ERROR_WRITE:
			return "Failed to write to file";
		case ERROR_MEM:
			return "Failed to allocate memory";
		case EMPTY_FILE:
			return "File is empty";
		case ERROR_INPUT:
			return "Incorrect input";
		default:
			return "Unknown error";
	}
}
