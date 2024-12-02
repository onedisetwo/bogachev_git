# include <stdio.h>
# include <time.h>
# include "main.h"
# include "errors.h"
# include "m_sort.h"

int data::p;

int main(int argc, char* argv[]){
	const int TASK = 2;
	const char *VAR_LIST = "n1 p1 s1 [filename1] n2 p2 s2 [filename2]";

	int n1, n2, p1, p2, s1, s2, plusArg = 0;
	char* filename1 = NULL;
	char* filename2 = NULL;

	data* data_m1;
	data* data_m2;
	data* data_mc;
	int ret;
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

	data_m1 = new data[n1];
	data_m2 = new data[n2];
	data_mc = new data[n1 + n2];
	if(!data_m1 || !data_m2 || !data_mc){
		printf("%s\n", get_error_message(ERROR_MEM));
		if(data_m1)	delete[] data_m1;
		if(data_m2)	delete[] data_m2;
		if(data_mc) 	delete[] data_mc;
		return 2;
	}

	if(s1 == 0){
		ret = read_array(data_m1, n1, filename1);
		if(ret != SUCCESS){
			printf("%s\n", get_error_message(ret));
			delete[] data_m1;
			delete[] data_m2;
			delete[] data_mc;
			return 2;
		}
	}
	else
		init_array(data_m1, n1, s1);
	if(s2 == 0){
		ret = read_array(data_m2, n2, filename2);
		if(ret != SUCCESS){
			printf("%s\n", get_error_message(ret));
			delete[] data_m1;
			delete[] data_m2;
			delete[] data_mc;
			return 2;
		}
	}
	else
		init_array(data_m2, n2, s2);

	printf("Array 1:\n");
	data::set_p(p1);
	print_array(data_m1, n1, data::get_p());
	printf("Array 2:\n");
	data::set_p(p2);
	print_array(data_m2, n2, data::get_p());

	t = clock();
	merge_arrays (data_m1, n1, data_m2, n2, data_mc);
	t = (clock() - t) / CLOCKS_PER_SEC;

	data::set_p(p1 + p2);
	printf("\nNew array:\n");
	print_array(data_mc, n1 + n2, data::get_p());
	printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n",
		argv[0], TASK, get_diff(data_mc, n1 + n2), t);

	delete[] data_m1;
	delete[] data_m2;
	delete[] data_mc;
	return 0;
}
