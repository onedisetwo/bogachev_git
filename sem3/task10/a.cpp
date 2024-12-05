# include <stdio.h>
# include <time.h>
# include "student.h"
# include "list2.h"
# include "tree.h"

int list2::m = 0;
int list2::r = 0;

const char* get_error_message (io_status) ;

int main(int argc, char* argv[]){
	// Constant variables
	const char *VAR_LIST = "r filename m";

	// Input variables
	int r, m;
	char* filename = nullptr;

	// Internal variables
	io_status ret;
	double t;
	int res;
	FILE *fp;
	tree<student> *a;
	tree<list2> *b;

	// Input
	if( !( argc == 4 && sscanf(argv[1], "%d", &r) == 1 &&
			sscanf(argv[3], "%d", &m) == 1 ) ) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	filename = argv[2];
	list2::set_m (m);
	list2::set_r (r);

// ===== TREE<STUDENT>
	a = new tree<student>;
	// Reading of file and memory allocations
	if(!(fp = fopen(filename, "r"))){
                printf("%s\n", get_error_message(io_status::open));
		delete a;
		return 2;
	}
	ret = a->read(fp);
	if(ret != io_status::success){
		printf("%s\n", get_error_message(ret));
		fclose(fp);
		delete a;
		return 2;
	}
	// fclose(fp);

	// Solution and printing the result
	printf("Input tree:\n");
	a->print(r);
	for(int task = 1; task <= 5; task++){
		t = clock ();
		res = a->tasks1_5 (task);
		t = (clock() - t) / CLOCKS_PER_SEC;
		printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n",
			argv[0], task, m, res, t);
	}
	delete a;

// ===== TREE<LIST2>
	b = new tree<list2>;
	// Reading of file and memory allocations
/*  	if(!(fp = fopen(filename, "r"))){
                printf("%s\n", get_error_message(io_status::open));
		return 2;
	} */
	rewind(fp);
//	fp.fseek(start);
	ret = b->read(fp);
	if(ret != io_status::success){
		printf("%s\n", get_error_message(ret));
		fclose(fp);
		delete b;
		return 2;
	}
	fclose(fp);

	// Solution and printing the result
	printf("Input tree:\n");
	b->print(r);
	for(int task = 1; task <= 5; task++){
		t = clock ();
		res = b->tasks1_5 (task);
		t = (clock() - t) / CLOCKS_PER_SEC;
		printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n",
			argv[0], task, m, res, t);
	}
	delete b;
	return 0;
}

const char* get_error_message(io_status err){
        switch(err){
                case io_status::open:
                        return "Failed to open file";
                case io_status::format:
                        return "Wrong input format in file";
                case io_status::eof:
                        return "Not enough data in file";
                case io_status::memory:
                        return "Failed to allocate memory";
                case io_status::success:
                        return "";
                default:
                        return "Unknown error";
        }
}

