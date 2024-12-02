#include <stdio.h>
#include "m_string.h"

size_t strlen_ (const char *s){
	size_t i = 0;
	while(s[i])
		i++;
	return i;
}

char *strcpy_ (char *s1, const char *s2){
	size_t i;
	for(i = 0; (s1[i] = s2[i]); i++);
	return s1;
}

char *strchr_ (const char *s, int ch){
	size_t i = 0;
	while(s[i] != ch && s[i] != 0){
		i++;
	}
	if(s[i] == ch)
		return (char *)s + i;
	else
		return NULL;
}

char *strrchr_ (const char *s, int ch){
	size_t i = 0, pos = 0;
	while(s[i] != 0){
		if(s[i] == ch)
			pos = i;
		i++;
	}
	if(s[pos] == ch)
		return (char *)s + pos;
	else
		return NULL;
}

char *strcat_ (char *s1, const char *s2){
	size_t i = 0;
	while(s1[i])
		i++;
	strcpy_(s1 + i, s2);
	return s1;
}

int strcmp_ (const char *s1, const char *s2){
	size_t i = 0;
	for(i = 0; s1[i] != 0 && s1[i] == s2[i]; i++);
	return s1[i] - s2[i];
}

size_t strcspn_ (const char *s1, const char *s2){
	char a[256];
	size_t i;
	for(i = 0; i < 256; i++)
		a[i] = 0;
	for(i = 0; s2[i]; i++)
		a[(unsigned char)s2[i]] = 1;
	for(i = 0; s1[i]; i++)
		if(a[(unsigned char)s1[i]] == 1)
			break;
	return i;
}

size_t strspn_ (const char *s1, const char *s2){
	char a[256];
	size_t i;
	for(i = 0; i < 256; i++)
		a[i] = 0;
	for(i = 0; s2[i]; i++)
		a[(unsigned char)s2[i]] = 1;
	for(i = 0; s1[i]; i++)
		if(a[(unsigned char)s1[i]] == 0)
			break;
	return i;
}

char *strstr_ (const char *s1, const char *s2){
	size_t i, c = 0, k, f1 = 0, j;
	for(i = 0; s1[i] && s2[c]; i++){
		if(s1[i] == s2[c])
			c++;
		else{
			if(c == 0)
				continue;
			k = 1;
			for(j = 0; j + k <= c; j++){
				if(j + k == c){
					if(s1[i] != s2[j]){
						f1 = 1;
						k++;
						j = -1;
						continue;
					}
					else
						break;
				}
				if(s2[j] != s2[j + k]){
					f1 = 1;
					k++;
					j = -1;
				}
			}
			c = j;
			if(f1 == 0)
				c++;
			f1 = 0;
		}
	}
	if(s2[c])
		return (NULL);
	else
		return (char *)s1 + i - c;
}

char *strstr_table_ (const char *s1, const char *s2, int t[256]){
	size_t i, c = 0, k, f1 = 0, j;
	for(i = 0; s1[i] && s2[c]; i++){
		if(t[(int)s1[i]] == t[(int)s2[c]])
			c++;
		else{
			if(c == 0)
				continue;
			k = 1;
			for(j = 0; j + k <= c; j++){
				if(j + k == c){
					if(t[(int)s1[i]] != t[(int)s2[j]]){
						f1 = 1;
						k++;
						j = -1;
						continue;
					}
					else
						break;
				}
				if(t[(int)s2[j]] != t[(int)s2[j + k]]){
					f1 = 1;
					k++;
					j = -1;
				}
			}
			c = j;
			if(f1 == 0)
				c++;
			f1 = 0;
		}
	}
	if(s2[c])
		return (NULL);
	else
		return (char *)s1 + i - c;
}

char *strtok_r_ (char *str, const char *delim, char **saveptr){
	size_t i;
	char d[256], *word = 0;
	for(i = 0; i < 256; i++)
		d[i] = 0;
	for(i = 0; delim[i]; i++)
		d[(int)delim[i]] = 1;
	for(i = 0; str[i]; i++){
		if(d[(int)str[i]] == 0){
			if(word == 0){
				word = str + i;
			}
		}
		else
			if(word != 0){
				str[i] = 0;
				*saveptr = str + i + 1;
				return word;
			}
	}
	*saveptr = (char *)"";
	return word == 0 ? (NULL) : word;
}
