# include <stdio.h>
# include <time.h>
# include "student.h"
# include "list2.h"

int main(int argc, char* argv[]){
	// Constant variables
	const int TASK = 7;
	const char *VAR_LIST = "r [filename] k";

	// Input variables
	int r, k;
	char* filename = NULL;

	// Internal variables
	io_status ret;
	double t;
	FILE *fp;
	list2 curr_list;
	unsigned int len1, len2;

	// Input
	if( !( argc == 4 && sscanf(argv[1], "%d", &r) == 1 &&
		sscanf(argv[3], "%d", &k) == 1 ) ) {
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
	len1 = curr_list.get_length();

	t = clock();
	curr_list.solve7(k);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf ("New list:\n");
	curr_list.print(r);
	len2 = curr_list.get_length();
	printf ("%s : Task = %d Len Old = %u Len New = %u Elapsed = %.2f\n",
		argv[0], TASK, len1, len2, t);

	return 0;
}
