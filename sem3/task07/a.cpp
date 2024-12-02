# include <stdio.h>
# include <time.h>
# include "student.h"
# include "tree.h"

int main(int argc, char* argv[]){
	// Constant variables
	const char *VAR_LIST = "r [filename] k";

	// Input variables
	int r;
	char* filename = NULL;

	// Internal variables
	io_status ret;
	double t;
	FILE *fp;
	int res, task;
	tree curr_tree;

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
	ret = curr_tree.read(fp);
	if(ret != io_status::success){
		printf("%s\n", get_error_message(ret));
		fclose(fp);
		return 2;
	}
	fclose(fp);

	// Solution and printing the result
	printf("Tree:\n");
	curr_tree.print(r);

	for(task = 1; task <= 5; task++){
		t = clock();
		switch(task){
			case 1:
				res = curr_tree.num_end_elements(); break;
			case 2:
				res = curr_tree.get_depth(); break;
			case 3:
				res = curr_tree.get_max_width(); break;
			case 4:
				res = curr_tree.task4(); break;
			case 5:
				res = curr_tree.num_having_one_child(); break;
		}
		t = (clock() - t) / CLOCKS_PER_SEC;
		printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",
			argv[0], task, res, t);
	}
	return 0;
}
