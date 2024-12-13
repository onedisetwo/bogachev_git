# include <stdio.h>
# include <time.h>

# include "io_status.h"
# include "student.h"
# include "b_tree.h"

int list2::m = 0;
int list2::r = 0;

int main(int argc, char* argv[]){
	/// Constant variables
	const char *VAR_LIST = "m r k filename";

	/// Input variables
	int m, r, k;
	char* filename = nullptr;

	/// Internal variables
	io_status ret;
	double t;
	//double t_total = clock();
	int res;
	FILE *fp;
	//b_tree<student> *a;

	/// Input
	if( !( argc == 5 && sscanf(argv[1], "%d", &m) == 1 &&
			sscanf(argv[2], "%d", &r) == 1 && sscanf(argv[3], "%d", &k) == 1 ) ) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	filename = argv[4];

	b_tree<student> *a = new b_tree<student>(m);
	/// Reading of file and memory allocations
	if(!(fp = fopen(filename, "r"))){
                printf("%s\n", get_error_message(io_status::open));
		delete a;
		return 2;
	}
	//t = clock();
	ret = a->read(fp);
	//t = (clock() - t) / CLOCKS_PER_SEC;
	//t_total += t;
	//printf("Student read: %.2f\n", t);
	if(ret != io_status::success){
		printf("%s\n", get_error_message(ret));
		fclose(fp);
		delete a;
		return 2;
	}
	fclose(fp);

	/// Solution and printing the result
	printf("Input tree:\n");
	a->print(r);
	for(int task = 1; task <= 6; task++){
		t = clock ();
		res = a->tasks1_6 (task, k);
		t = (clock() - t) / CLOCKS_PER_SEC;
		//t_total += t;
		printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n",
			argv[0], task, m, res, t);
	}
	delete a;
	//printf("Student total time: %.2f\n", t_total);*/
	//t_total = (clock() - t_total) / CLOCKS_PER_SEC;
	//printf("Program total time: %.2f\n", t_total);
	return 0;
}
