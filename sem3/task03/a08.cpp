# include <stdio.h>
# include <time.h>
# include "student.h"
# include "solve.h"

int main(int argc, char* argv[]){
	// Constant variables
	const int TASK = 8;
	const char *VAR_LIST = "Name Value n p s [filename]";

	// Input variables
	int n, p, s;
	char* filename = NULL;

	// Internal variables
	student* student_m;
	student student_x;
	io_status ret;
	double t;
	int res, x_value;
	char x_name[LEN];

	// Input
	if( !( (argc == 6 || argc == 7) && sscanf(argv[1], "%s", x_name)
		&& sscanf(argv[2], "%d", &x_value) && sscanf(argv[3], "%d", &n) == 1
		&& sscanf(argv[4], "%d", &p) == 1 && sscanf(argv[5], "%d", &s) == 1 )) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	if(argc == 7){
		if(s == 0)
			filename = argv[6];
		else{
			printf("Usage: %s %s\n", argv[0], VAR_LIST);
			return 1;
		}
	}
	else
		if(s < 1 || s > 4){
			printf("Usage: %s %s\n", argv[0], VAR_LIST);
			return 1;
		}

	// Memory operations
	student_x.init_public(x_name, x_value);
	student_m = new student[n];
	if(!student_m){
		printf("%s\n", get_error_message(io_status::memory));
		return 2;
	}

	if(s == 0){
		ret = read_array(student_m, n, filename);
		if(ret != io_status::success){
			printf("%s\n", get_error_message(ret));
			delete[] student_m;
			return 2;
		}
	}
	else{
                ret = init_array(student_m, n, s);
                if(ret != io_status::success){
                        printf("%s\n", get_error_message(ret));
                        delete[] student_m;
                        return 2;
                }
        }

	// Solution and printing the result
	print_array(student_m, n, p);

	t = clock();
	res = solve8(student_m, n, &student_x);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("\nNew array:\n");
	print_array(student_m, res, p);
	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n",
		argv[0], TASK, res, t);

	// Freeing up memory
	delete[] student_m;
	return 0;
}
