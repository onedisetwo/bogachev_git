# include <stdio.h>
# include "main.h"
# include "errors.h"

void data::print (FILE* fp) const{
	int len = get_M(), i = 0;
	fprintf(fp, "%d ", m);
	for(i = 0; i < len; i++){
		fprintf(fp, "%le ", a[i]);
	}
	fprintf(fp, "\n");
}

int data::read (FILE* fp){
	int i = 0;
	char buf[LEN];
	char *tmp, *buf2;
	const char delim[2] = " ";
	if(!fgets(buf, LEN, fp))
		return ERROR_READ;
	buf2 = buf;
	if(sscanf(buf, "%d", &m) != 1)
		return ERROR_READ;
	m = (m > M) ? M : m;
	tmp = buf2;
	tmp = strtok(tmp, delim);
	for(i = 0;(tmp = strtok(NULL, delim)) && i < m; i++){
		if(sscanf(tmp, "%lf", a + i) != 1)
			return ERROR_READ;
	}
	if(i < m)
		return ERROR_READ;
	return SUCCESS;
}

int f (int s, int n, int i){
	switch(s){
		case 1:	return i;
		case 2:	return n - i;
		case 3: return i/2;
		case 4: return n - i/2;
		default: return 0; // can't happen
	}
}

void data::init (int s, int n, int i){
	int j = 0;
	m = f(s, n, i);
	for(j = 0; j < ((m > M) ? M : m); j++){
		a[j] = 0;
	}
}

int read_array (data* data_m, int n, char* filename){
	FILE *fp;
	int i = 0;
	if(!(fp = fopen(filename, "r"))){
		return ERROR_READ;
	}
	for(i = 0; i < n; i++){
		if(data_m[i].read(fp) != SUCCESS){
			fclose(fp);
			return ERROR_READ;
		}
	}
	fclose(fp);
	return SUCCESS;
}

// print to the screen
void print_array (data* data_m, int n, int p){
	int i = 0;
	for(i = 0; i < ((n > p) ? p : n); i++)
		(data_m[i]).print();
}

void init_array (data* data_m, int n, int s){
	int i = 0;
	for(i = 1; i <= n; i++){
		data_m[i-1].init(s, n, i);
	}
}
