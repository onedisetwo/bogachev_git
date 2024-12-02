int solve1 (const char *nameIn, const char *nameOut, const char *s, int *res);
int solve2 (const char *nameIn, const char *nameOut, char *s, int *res);
int solve3 (const char *nameIn, const char *nameOut, const char *s1,
			const char *s2, int *res);

#define ARGS_4__7 const char *nameIn, const char *nameOut, char *s1, \
			const char *s2, int *res
int solve4 (ARGS_4__7);
int solve5 (ARGS_4__7);
int solve6 (ARGS_4__7);
int solve7 (ARGS_4__7);

int solve8 (const char *nameIn, const char *nameOut, const char *s1,
		const char *s2, const char *s3, int *res);

int delete_spaces_r (const char *s1, char *s2, const char *t);
int delete_spaces (char *s, const char *t);
