# include <stdio.h>
# include <time.h>
# include "student.h"
# include "tree.h"

int main(int argc, char* argv[]){
	// Constant variables
	const int TASK = 7;
	const char *VAR_LIST = "r filename name value";

	// Input variables
	int r, value;
	char* filename = nullptr;
	char* name = nullptr;

	// Internal variables
	io_status ret;
	double t;
	FILE *fp;
	int T, L, C1, C2, H, W, B;
	tree a;
	student s;

	// Input
	if( !( argc == 5 && sscanf(argv[1], "%d", &r) == 1 &&
		sscanf(argv[4], "%d", &value) ) ) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	filename = argv[2];
	name = argv[3];

	// Reading of file and memory allocations
	if( s.init(name, value) != io_status::success)
		return 2;
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
	printf("Original tree:\n");
	a.print(r);
	T = a.get_count_total ();
	L = a.get_count_leaf ();
	C1 = a.get_count_1 ();
	C2 = a.get_count_2 ();
	H = a.get_height ();
	W = a.get_width ();
	B = a.get_balance ();
	printf ("%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d\n",
		argv[0], TASK, T, L, C1, C2, H, W, B);
	t = clock ();
	a.task7 (s);
	t = (clock() - t) / CLOCKS_PER_SEC;
	printf ("Modified tree:\n");
	a.print (r);
	T = a.get_count_total ();
	L = a.get_count_leaf ();
	C1 = a.get_count_1 ();
	C2 = a.get_count_2 ();
	H = a.get_height ();
	W = a.get_width ();
	B = a.get_balance ();
	printf ("%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d Elapsed = %.2f\n",
		argv[0], TASK, T, L, C1, C2, H, W, B, t);
	return 0;
}
