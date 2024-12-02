# include <stdio.h>
# include <time.h>
# include "student.h"
# include "list1.h"

int main(int argc, char* argv[]){
	// Constant variables
	const int TASK = 1;
	const char *VAR_LIST = "r [filename] k";

	// Input variables
	int r;
	char* filename = NULL;

	// Internal variables
	io_status ret;
	double t;
	FILE *fp;
	list1 curr_list;

	// Input
	if( !( argc == 3 && sscanf(argv[1], "%d", &r) == 1 ) ) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	filename = argv[2];

	// Reading of file and memory allocations
	if(!(fp = fopen(filename, "r"))){
                printf("%s\n", get_error_message(io_status::open));
		return 2;
	}
	ret = curr_list.read(fp);
	if(ret != io_status::success){
		printf("%s\n", get_error_message(ret));
		fclose(fp);
		return 2;
	}
	fclose(fp);

	// Solution and printing the result
	curr_list.print(r);

	t = clock();
	curr_list.bubble_sort();
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf ("New list:\n");
	curr_list.print(r);
	printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n",
		argv[0], TASK, curr_list.get_less_than_previous(), t);

	return 0;
}
