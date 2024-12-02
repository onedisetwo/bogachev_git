# include <stdio.h>
# include <time.h>
# include "student.h"
# include "m_sort.h"

int main(int argc, char* argv[]){
	const int TASK = 2;
	const char *VAR_LIST = "n1 p1 s1 [filename1] n2 p2 s2 [filename2]";

	int n1, n2, p1, p2, s1, s2, plusArg = 0;
	char* filename1 = NULL;
	char* filename2 = NULL;

	student* student_m1;
	student* student_m2;
	student* student_mc;
	io_status ret;
	double t;

	if( !((argc == 7 || argc == 8 || argc == 9) && sscanf(argv[1], "%d", &n1) == 1 &&
            sscanf(argv[2], "%d", &p1) == 1 && sscanf(argv[3], "%d", &s1) == 1) ) {
                printf("Usage: %s %s\n", argv[0], VAR_LIST);
                return 1;
        }
        if(s1 == 0){
                plusArg = 1;
                filename1 = argv[4];
        }
        if(s1 < 0 && s1 > 6){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
                return 1;
        }
        if( !(sscanf(argv[4 + plusArg], "%d", &n2) == 1 && sscanf(argv[5 + plusArg], "%d", &p2) == 1 &&
            sscanf(argv[6 + plusArg], "%d", &s2) == 1) ) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
                return 1;
        }
        if(s2 == 0)
                filename2 = argv[7 + plusArg];
        if(s2 < 0 && s2 > 6){
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
                return 1;
        }

	student_m1 = new student[n1];
	student_m2 = new student[n2];
	student_mc = new student[n1 + n2];
	if(!student_m1 || !student_m2 || !student_mc){
		printf("%s\n", get_error_message(io_status::memory));
		if(student_m1)	delete[] student_m1;
		if(student_m2)	delete[] student_m2;
		if(student_mc) 	delete[] student_mc;
		return 2;
	}

	if(s1 == 0){
		ret = read_array(student_m1, n1, filename1);
		if(ret != io_status::success){
			printf("%s\n", get_error_message(ret));
			delete[] student_m1;
			delete[] student_m2;
			delete[] student_mc;
			return 2;
		}
	}
	else{
		ret = init_array(student_m1, n1, s1);
		if(ret != io_status::success){
			printf("%s\n", get_error_message(ret));
			delete[] student_m1;
			delete[] student_m2;
			delete[] student_mc;
			return 2;
		}
	}
	if(s2 == 0){
		ret = read_array(student_m2, n2, filename2);
		if(ret != io_status::success){
			printf("%s\n", get_error_message(ret));
			delete[] student_m1;
			delete[] student_m2;
			delete[] student_mc;
			return 2;
		}
	}
	else{
		ret = init_array(student_m2, n2, s2);
		if(ret != io_status::success){
			printf("%s\n", get_error_message(ret));
			delete[] student_m1;
			delete[] student_m2;
			delete[] student_mc;
			return 2;
		}
	}
	printf("Array 1:\n");
	print_array(student_m1, n1, p1);
	printf("Array 2:\n");
	print_array(student_m2, n2, p1);

	t = clock();
	merge_arrays (student_m1, n1, student_m2, n2, student_mc);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("\nNew array:\n");
	print_array(student_mc, n1 + n2, p1 + p2);
	printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n",
		argv[0], TASK, get_diff(student_mc, n1 + n2), t);

	delete[] student_m1;
	delete[] student_m2;
	delete[] student_mc;
	return 0;
}
