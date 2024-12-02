#include <stdio.h>
#include "io_status.h"

void print_error_message(int code, char* arg){
	switch(code){
		case ERROR_OPEN:
			printf("Error: cannot open %s\n", arg);
			break;
		case ERROR_READ:
			printf("Error: cannot read %s\n", arg);
			break;
		case EMPTY_FILE:
			printf("Error: %s is empty\n", arg);
			break;
		default:
			printf("Error: unknown error %d\n", code);
	}
}
