# include <stdio.h>
# include <time.h>
# include "main.h"
# include "errors.h"
# include "m_sort.h"

int data::p;

int main(int argc, char* argv[]){
	const int TASK = 3;
	const char *VAR_LIST = "m n p s [filename_m]";

	int m, n, p, s;
	char* filename_m = NULL;

	data* data_m;
	int ret, res;
	double t;

	if( !( (argc == 5 || argc == 6)
		&& sscanf(argv[1], "%d", &m) && sscanf(argv[2], "%d", &n) == 1
		&& sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &s) == 1 )) {
		printf("Usage: %s %s\n", argv[0], VAR_LIST);
		return 1;
	}
	if(argc == 6){
		if(s == 0)
			filename_m = argv[5];
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

	data_m = new data[n];
	if(!data_m){
		printf("%s\n", get_error_message(ERROR_MEM));
		return 2;
	}
	data::set_p(p);

	if(s == 0){
		ret = read_array(data_m, n, filename_m);
		if(ret != SUCCESS){
			printf("%s\n", get_error_message(ret));
			delete[] data_m;
			return 2;
		}
	}
	else
		init_array(data_m, n, s);
	print_array(data_m, n, data::get_p());

	t = clock();
	res = split_array(data_m, n, m);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("\nNew array:\n");
	print_array(data_m, n, data::get_p());
	printf ("%s : Task = %d Res = %d Elapsed = %.2f\n",
		argv[0], TASK, res, t);

	delete[] data_m;
	return 0;
}
