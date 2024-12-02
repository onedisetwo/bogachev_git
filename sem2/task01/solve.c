#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "solve.h"

#define BUF_LEN 1234

char* strstr_end(char*, char*, int, int);

char* strstr_end(char *haystack, char *needle, int h_len, int n_len){
	int h = n_len - 1, j = h_len - 1;
	for(; h >= 0; h--, j--)
		if(needle[h] != haystack[j])
			break;
	if(h < 0)
		return needle;
	else
		return NULL;
}

int split_str(char *, int *, char**);

int split_str(char *str, int *t, char **words){
	int i, j = 0;
	for(i = 0; str[i]; ){
		for(; str[i] && t[(int)str[i]] != 0; i++)
			str[i] = 0;
		if(!str[i])
			break;
		words[j++] = str + i;
		for(; str[i] && t[(int)str[i]] == 0; i++) ;
	}
	return j;
}

int solve1(const char *nameIn, const char *nameOut, const char *s_orig, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN], s[BUF_LEN], *strPos;
	enum search_type { DEFAULT, STR_BEG } s_type = DEFAULT;
	int i, j, count = 0;
	if(s_orig[0] == '^'){
		s_type = STR_BEG;
		i = 1;
	}
	else
		i = 0;
	for(j = 0; s_orig[i]; i++){
		if(s_orig[i] == '\\')
			if(s_orig[++i] != 0)
				s[j++] = s_orig[i];
			else
				return ERROR_INPUT;
		else
			s[j++] = s_orig[i];
	}
	s[j] = 0;
	if(!(fin = fopen(nameIn, "r")))
		return ERROR_OPEN;
	if(!(fout = fopen(nameOut, "w"))){
		fclose(fin);
		return ERROR_OPEN;
	}
	while(fgets(buf, BUF_LEN, fin)){
		strPos = strstr(buf, s);
		if((s_type == DEFAULT && strPos != NULL) ||
			(s_type == STR_BEG && strPos == buf)){
			if(fprintf(fout, "%s", buf) < 0){
				fclose(fin);
				fclose(fout);
				return ERROR_WRITE;
			}
			count++;
		}
	}
	fclose(fout);
	if(!feof(fin)){
		fclose(fin);
		return ERROR_READ;
	}
	fclose(fin);
	*res = count;
	return SUCCESS;
}

int solve2(const char *nameIn, const char *nameOut, const char *s_orig, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN], s[BUF_LEN], *strPos;
	enum search_type { DEFAULT, STR_END } s_type = DEFAULT;
	int i, j = 0, count = 0;
	for(i = 0; s_orig[i]; i++){
		if(s_orig[i] == '\\')
			if(s_orig[++i] != 0)
				s[j++] = s_orig[i];
			else
				return ERROR_INPUT;
		else
			if(s_orig[i + 1] == 0 && s_orig[i] == '$'){
				s_type = STR_END;
			}
			else
				s[j++] = s_orig[i];
	}
	s[j] = 0;
	if(!(fin = fopen(nameIn, "r")))
		return ERROR_OPEN;
	if(!(fout = fopen(nameOut, "w"))){
		fclose(fin);
		return ERROR_OPEN;
	}
	while(fgets(buf, BUF_LEN, fin)){
		strPos = NULL;
		if(s_type == DEFAULT)
			strPos = strstr(buf, s);
		else
			strPos = strstr_end(buf, s, strlen(buf) - 1, j);
		if(strPos != NULL){
			if(fprintf(fout, "%s", buf) < 0){
				fclose(fin);
				fclose(fout);
				return ERROR_WRITE;
			}
			count++;
		}
	}
	fclose(fout);
	if(!feof(fin)){
		fclose(fin);
		return ERROR_READ;
	}
	fclose(fin);
	*res = count;
	return SUCCESS;
}

int solve3(const char *nameIn, const char *nameOut, const char *s_orig, const char *t, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN], buf2[BUF_LEN], s[BUF_LEN];
	char* words[BUF_LEN/2];
	enum search_type { DEFAULT, WORD_BEG } s_type = DEFAULT;
	int i, j, count = 0, table[256];
	if(s_orig[0] == '\\' && s_orig[1] == '<'){
		s_type = WORD_BEG;
		i = 2;
	}
	else
		i = 0;
	for(j = 0; s_orig[i]; i++){
		if(s_orig[i] == '\\')
			if(s_orig[++i] != 0 && s_orig[i] != '<')
				s[j++] = s_orig[i];
			else
				return ERROR_INPUT;
		else
			s[j++] = s_orig[i];
	}
	s[j] = 0;
	if(!(fin = fopen(nameIn, "r")))
		return ERROR_OPEN;
	if(!(fout = fopen(nameOut, "w"))){
		fclose(fin);
		return ERROR_OPEN;
	}
	for(i = 0; i < 256; i++)
		table[i] = 0;
	for(i = 0; t[i]; i++){
		table[(int)t[i]] = 1;
	}
	table[(int)'\n'] = 1;
	for(i = 0; i < BUF_LEN/2; i++)
		words[i] = 0;
	if(s_type == DEFAULT)
		while(fgets(buf, BUF_LEN, fin)){
			if(strstr(buf, s) != NULL){
				if(fprintf(fout, "%s", buf) < 0){
					fclose(fin);
					fclose(fout);
					return ERROR_WRITE;
				}
				count++;
			}
		}
	else
		while(fgets(buf, BUF_LEN, fin)){
			strcpy(buf2, buf);
			split_str(buf2, table, words);
			for(i = 0; words[i]; i++){
				if(strstr(words[i], s) == words[i]){
					if(fprintf(fout, "%s", buf) < 0){
						fclose(fin);
						fclose(fout);
						return ERROR_WRITE;
					}
					count++;
					break;
				}
				words[i] = 0;
			}
			for(; words[i]; i++)
				words[i] = 0;
		}
	fclose(fout);
	if(!feof(fin)){
		fclose(fin);
		return ERROR_READ;
	}
	fclose(fin);
	*res = count;
	return SUCCESS;
}

int solve4(const char *nameIn, const char *nameOut, const char *s_orig, const char *t, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN], buf2[BUF_LEN], s[BUF_LEN];
	char* words[BUF_LEN/2];
	enum search_type { DEFAULT, WORD_END } s_type = DEFAULT;
	int i, j, count = 0, table[256];
	for(i = 0, j = 0; s_orig[i]; i++){
		if(s_orig[i] == '\\')
			if(s_orig[i + 1] == '>'){
				if(s_orig[i + 2] == 0){
					s_type = WORD_END;
					break;
				}
				else
					return ERROR_INPUT;
			}
			else
				if(s_orig[++i] != 0)
					s[j++] = s_orig[i];
				else
					return ERROR_INPUT;
		else
			s[j++] = s_orig[i];
	}
	s[j] = 0;
	if(!(fin = fopen(nameIn, "r")))
		return ERROR_OPEN;
	if(!(fout = fopen(nameOut, "w"))){
		fclose(fin);
		return ERROR_OPEN;
	}
	for(i = 0; i < 256; i++)
		table[i] = 0;
	for(i = 0; t[i]; i++){
		table[(int)t[i]] = 1;
	}
	table[(int)'\n'] = 1;
	for(i = 0; i < BUF_LEN/2; i++)
		words[i] = 0;
	if(s_type == DEFAULT)
		while(fgets(buf, BUF_LEN, fin)){
			if(strstr(buf, s) != NULL){
				if(fprintf(fout, "%s", buf) < 0){
					fclose(fin);
					fclose(fout);
					return ERROR_WRITE;
				}
				count++;
			}
		}
	else
		while(fgets(buf, BUF_LEN, fin)){
			strcpy(buf2, buf);
			split_str(buf2, table, words);
			for(i = 0; words[i]; i++){
				if(strstr_end(words[i], s, strlen(words[i]), j) != NULL){
					if(fprintf(fout, "%s", buf) < 0){
						fclose(fin);
						fclose(fout);
						return ERROR_WRITE;
					}
					count++;
					break;
				}
				words[i] = 0;
			}
			for(; words[i]; i++)
				words[i] = 0;
		}
	fclose(fout);
	if(!feof(fin)){
		fclose(fin);
		return ERROR_READ;
	}
	fclose(fin);
	*res = count;
	return SUCCESS;
}

int solve5(const char *nameIn, const char *nameOut, const char *s_orig, const char *t, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN], buf2[BUF_LEN], s[BUF_LEN];
	char* words_buf[BUF_LEN/2];
	char*  words_s[BUF_LEN/2];
	int i, j, count = 0, table[256];
	if(!(fin = fopen(nameIn, "r")))
		return ERROR_OPEN;
	if(!(fout = fopen(nameOut, "w"))){
		fclose(fin);
		return ERROR_OPEN;
	}
	for(i = 0; i < 256; i++)
		table[i] = 0;
	for(i = 0; t[i]; i++){
		table[(int)t[i]] = 1;
	}
	table[(int)'\n'] = 1;
	for(i = 0; i < BUF_LEN/2; i++){
		words_buf[i] = 0;
		words_s[i] = 0;
	}
	strcpy(s, s_orig);
	split_str(s, table, words_s);
	while(fgets(buf, BUF_LEN, fin)){
		strcpy(buf2, buf);
		split_str(buf2, table, words_buf);
		for(i = 0; words_buf[i]; i++){
			for(j = 0; words_s[j]; j++){
				if(strcmp(words_buf[i], words_s[j]) == 0){
					if(fprintf(fout, "%s", buf) < 0){
						fclose(fin);
						fclose(fout);
						return ERROR_WRITE;
					}
					count++;
					for(; words_buf[i]; i++)
						words_buf[i] = 0;
					break;
				}
			}
			words_buf[i] = 0;
		}
	}
	fclose(fout);
	if(!feof(fin)){
		fclose(fin);
		return ERROR_READ;
	}
	fclose(fin);
	*res = count;
	return SUCCESS;
}
