#include <stdio.h>
#include <time.h>
#include "test.h"
#include "m_string.h"

double test_1 (size_t count, size_t (*p)(const char *), const char *s, size_t *res){
	double t;
	size_t i, r = 0;
	t = clock();
	for(i = 0; i < count; i++)
		r = (*p)(s);
	t = (clock() - t)/CLOCKS_PER_SEC;
	*res = r;
	return t;
}

double test_2_5 (size_t count, char *(*p)(char *, const char *),
		 char *s1, const char *s2, char **res){
	double t;
	size_t i, len = strlen_(s1);
	char *r = 0;
	t = clock();
	for(i = 0; i < count; i++){
		s1[len] = 0;
		r = (*p)(s1, s2);
	}
	t = (clock() - t)/CLOCKS_PER_SEC;
	*res = r;
	return t;
}

double test_3_4 (size_t count, char *(*p)(const char *, int),
		 const char *s, int ch, char **res){
	double t;
	size_t i;
	char *r = 0;
	t = clock();
	for(i = 0; i < count; i++){
		r = (*p)(s, ch);
	}
	t = (clock() - t)/CLOCKS_PER_SEC;
	*res = r;
	return t;
}

double test_6 (size_t count, int (*p)(const char *, const char *),
	       const char *s1, const char *s2, int *res){
	double t;
	size_t i;
	int r = 0;
	t = clock();
	for(i = 0; i < count; i++){
		r = (*p)(s1, s2);
	}
	t = (clock() - t)/CLOCKS_PER_SEC;
	*res = r;
	return t;
}

double test_7_8 (size_t count, size_t (*p)(const char *, const char *),
	       const char *s1, const char *s2, size_t *res){
	double t;
	size_t i, r = 0;
	t = clock();
	for(i = 0; i < count; i++){
		r = (*p)(s1, s2);
	}
	t = (clock() - t)/CLOCKS_PER_SEC;
	*res = r;
	return t;
}

double test_9 (size_t count, char *(*p)(const char *, const char *),
	       const char *s1, const char *s2, char **res){
	double t;
	size_t i;
	char *r = 0;
	t = clock();
	for(i = 0; i < count; i++){
		r = (*p)(s1, s2);
	}
	t = (clock() - t)/CLOCKS_PER_SEC;
	*res = r;
	return t;
}

double test_10 (size_t count, char *(*p)(char *, const char *, char **),
		char *str, const char *delim, char **saveptr, char **res){
	double t;
	size_t i, len, len_orig;
	char *r = 0;
	len_orig = strlen_(str);
	t = clock();
	if(count != 0){
		r = (*p)(str, delim, saveptr);
		len = strlen_(str);
		if(len != len_orig) str[len] = delim[0];
		for(i = 0; i < count - 1; i++){
			r = (*p)(str, delim, saveptr);
			if(len != len_orig) str[len] = delim[0];
		}
	}
	*res = r;
	t = (clock() - t)/CLOCKS_PER_SEC;
	return t;
}
