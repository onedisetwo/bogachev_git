# include <stdio.h>
# include <time.h>
# include "student.h"
# include "m_sort.h"

int main(int argc, char* argv[]){
	const int TASK = 1;
	const char *VAR_LIST = "student_x n p s [filename_m]";

	int n, p, s;
	char* filename_m = nullptr;

	student* student_m;
	student student_x;
	int res;
	io_status ret;
	double t;
	char x_name[LEN];
	int x_value;

	if( !( (argc == 6 || argc == 7) && sscanf(argv[1], "%s", x_name)
	 	&& sscanf(argv[2], "%d", &x_value) == 1 && sscanf(argv[3], "%d", &n) == 1
		&& sscanf(argv[4], "%d", &p) == 1 && sscanf(argv[5], "%d", &s) == 1 )) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	if(argc == 7){
		if(s == 0)
			filename_m = argv[6];
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
	if(student_x.init_public(x_name, x_value) != io_status::success){
		printf("%s\n", get_error_message(io_status::memory));
		return 2;
	}

	student_m = new student[n];
	if(!student_m){
		printf("%s\n", get_error_message(io_status::memory));
		return 2;
	}

	if(s == 0){
		ret = read_array(student_m, n, filename_m);
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
	res = get_insert_pos_bin(student_m, n, &student_x);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf ("%s : Task = %d Res = %d Elapsed = %.2f\n",
		argv[0], TASK, res, t);

	delete[] student_m;
	return 0;
}
