enum char_type {
	EMPTY,
	LIT, //simple literal [task1]
	ANY1, //any symbol (dot) [task1]
//	REP, //symbol repeats for a to b times [task2-4]
};

int is_str_equal1(const char*, char*, enum char_type*);
int mark_str1(const char *, char*, enum char_type*);
int solve1(const char*, const char*, const char*, int*);

char get_special(int task);
void act_special(int task, int*, int*);
int mark_str2__4(const char *, char*, int*, int*, int);
int is_str_equal2__4(const char*, char*, int*, int*);
int solve2__4(const char*, const char*, const char*, int*, int);

int mark_str5(const char *, char*, char*);
int is_str_equal5(const char*, char*, char*);
int solve5(const char*, const char*, const char*, int*);
