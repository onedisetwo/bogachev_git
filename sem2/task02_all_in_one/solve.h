enum char_type {
	EMPTY,
	ANY1, //any symbol (dot)
	REP, //symbol repeats for a to b times
};

int mark_str1__4(const char *, char*, enum char_type*, int*, int*);
int mark_str5(const char *, char*, char*);
int is_str_equal1__4(const char*, char*, enum char_type*, int*, int*);
int is_str_equal5(const char*, char*, char*);
int solve1__4(const char*, const char*, const char*, int*);
int solve5(const char*, const char*, const char*, int*);
