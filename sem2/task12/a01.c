#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "errors.h"

int main(int argc, char *argv[]){
	const int TASK = 1, ARGC = 3;
	const char *VAR_LIST = "p filename";
	int arg;
	double time;

	int p, res, ret;
	char *filename;
	node head;
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
	res = solve1(&head);
	time = (clock() - time) / CLOCKS_PER_SEC;
//--------------------------------------------------

	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, time);
	free_list(&head);
	return 0;
}
