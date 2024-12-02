# include <stdio.h>
# include <time.h>
# include "student.h"
# include "tree.h"

int main(int argc, char* argv[]){
	// Constant variables
	const char *VAR_LIST = "r filename k";

	// Input variables
	int r, k;
	char* filename = nullptr;

	// Internal variables
	io_status ret;
	double t;
	int res;
	FILE *fp;
	tree a;

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
	ret = a.read(fp);
	if(ret != io_status::success){
		printf("%s\n", get_error_message(ret));
		fclose(fp);
		return 2;
	}
	fclose(fp);

	// Solution and printing the result
	printf("Input tree:\n");
	a.print(r);
	for(int task = 1; task <= 6; task++){
		t = clock ();
		res = a.tasks1_6 (k, task);
		t = (clock() - t) / CLOCKS_PER_SEC;
		printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n",
			argv[0], task, k, res, t);
	}
	return 0;
}
