#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "errors.h"

int main(int argc, char *argv[]){
	const int TASK = 8, ARGC = 3;
	const char *VAR_LIST = "p filename";
	int arg;
	double time;

	int p, ret, len;
	char *filename;
	node head, *new_head;
	head.string = 0;
        head.next = 0;

	arg = 1;
	if( !( 	argc == ARGC
		&& sscanf(argv[arg++], "%d", &p) == 1) ){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	filename = argv[arg++];

	ret = read_file(&head, filename);
	if(ret != SUCCESS){
		printf("%s\n", get_error_message(ret));
		return 2;
	}

	print_list(&head, p);

//--------------------------------------------------
	time = clock();
	new_head = solve8(&head);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------

	len = get_list_len(new_head);

	printf("\nNew list:\n");
	print_list(new_head, p);
	printf ("%s : Task = %d Length = %d Elapsed = %.2f\n",
		argv[0], TASK, len, time);
	free_list(new_head);
	if(new_head != &head)
		free(new_head);
	return 0;
}
