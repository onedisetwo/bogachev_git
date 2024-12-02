# include <stdio.h>
# include <time.h>
# include "student.h"
# include "m_sort.h"

int main(int argc, char* argv[]){
	const int TASK = 5;
	const char *VAR_LIST = "n p s [filename]";

	int n, p, s;
	char* filename = NULL;

	student* student_m;
	io_status ret;
	double t;

	if( !( (argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1
		&& sscanf(argv[2], "%d", &p) == 1 && sscanf(argv[3], "%d", &s) == 1 )) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	if(argc == 5){
		if(s == 0)
			filename = argv[4];
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
	print_array(student_m, n, p);

	t = clock();
	selection_sort(student_m, n);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("\nNew array:\n");
	print_array(student_m, n, p);
	printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n",
		argv[0], TASK, get_diff(student_m, n), t);

	delete[] student_m;
	return 0;
}
