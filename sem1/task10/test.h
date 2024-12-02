double test_1 (size_t count, size_t (*p)(const char *), const char *s, size_t *res);

double test_2_5 (size_t count, char *(*p)(char *, const char *),
                 char *s1, const char *s2, char **res);

double test_3_4 (size_t count, char *(*p)(const char *, int),
		 const char *s, int ch, char **res);

double test_6 (size_t count, int (*p)(const char *, const char *),
	       const char *s1, const char *s2, int *res);

double test_7_8 (size_t count, size_t (*p)(const char *, const char *),
		 const char *s1, const char *s2, size_t *res);

double test_9 (size_t count, char *(*p)(const char *, const char *),
	       const char *s1, const char *s2, char **res);

double test_10 (size_t count, char *(*p)(char *, const char *, char **),
	       char *str, const char *delim, char **saveptr, char **res);
