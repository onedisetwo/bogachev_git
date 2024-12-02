# include <stdio.h>
# include <time.h>
# include "student.h"
# include "list_node.h"
# include "solve.h"

int main(int argc, char* argv[]){
	// Constant variables
	const int TASK = 2;
	const char *VAR_LIST = "r [filename]";

	// Input variables
	int r;
	char* filename = NULL;

	// Internal variables
	io_status ret;
	double t;
	int res;
	FILE *fp;
	list_node *head;

	// Input
	if( !( argc == 3 && sscanf(argv[1], "%d", &r) == 1 )) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	filename = argv[2];

	// Reading of file and memory allocations
	if(!(fp = fopen(filename, "r"))){
                printf("%s\n", get_error_message(io_status::open));
		return 2;
	}
	ret = read_list(fp, &head);
	if(ret != io_status::success){
		printf("%s\n", get_error_message(ret));
		delete_list(head);
		fclose(fp);
		return 2;
	}
	fclose(fp);

	// Solution and printing the result
	print_list(r, head);

	t = clock();
	res = solve2(head);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, t);

	// Freeing up memory
	delete_list(head);
	return 0;
}
