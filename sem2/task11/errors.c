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
			return "Input file is empty";
		case ERROR_INPUT:
			return "Incorrect input";
		case ERROR_INIT:
			return "Cannot initialize matrix, check your input";
		case DIVISION_BY_ZERO:
			return "Program execution was forcibly interrupted to prevent division by zero";
		case DIVERGENT_INTEGRAL:
			return "Integral of this function is divegrent";
		case SUCCESS:
			return "";
		default:
			return "Unknown error";
	}
}
