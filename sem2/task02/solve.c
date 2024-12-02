#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "solve.h"

#define BUF_LEN 1234

#define open_files \
	if(!(fin = fopen(nameIn, "r"))) \
		return ERROR_OPEN; \
	if(!(fout = fopen(nameOut, "w"))){ \
		fclose(fin); \
		return ERROR_OPEN; \
	}

// ============== TASK 1 =============== //

int mark_str1(const char *s_orig, char *s, enum char_type *mk){
	int i, j = 0;
	for(i = 0; s_orig[i]; i++){
		if(s_orig[i] == '\\')
			if(s_orig[i + 1] == 0)
				return ERROR_INPUT;
			else{
				i++;
				mk[j] = LIT;
				s[j] = s_orig[i];
				j++;
			}
		else
			if(s_orig[i] == '.'){
				mk[j] = ANY1;
				s[j] = '@';
				j++;
			}
			else{
				mk[j] = LIT;
				s[j] = s_orig[i];
				j++;
			}
	}
	return SUCCESS;
}

int is_str_equal1(const char *s, char *sm /*marked*/, enum char_type *mk){
	int i;
	for(i = 0; s[i] != 0 && s[i] != '\n'; i++){
		switch(mk[i]){
			case EMPTY:
				return 0;
			case LIT:
				if(s[i] != sm[i])
					return 0;
			case ANY1:
				break;
		}
	}
	if(mk[i] != EMPTY)
		return 0;
	return 1;
}

int solve1(const char *nameIn, const char *nameOut, const char *s_orig, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN], s[BUF_LEN];
	enum char_type mk[BUF_LEN] /*markers*/;
	int  i, count;
	open_files;
	// files fin and fout now is open
	for(i = 0; i < BUF_LEN; i++){
		s[i] = 0;
		mk[i] = EMPTY;
	}
	if(mark_str1(s_orig, s, mk) != SUCCESS){
		fclose(fin); fclose(fout);
		return ERROR_INPUT;
	}
	count = 0;
	while(fgets(buf, BUF_LEN, fin)){
		if(is_str_equal1(buf, s, mk)){
			if(fprintf(fout, "%s", buf) < 0){
				fclose(fin); fclose(fout);
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


// ============== TASK 2-4 =============== //

char get_special(int task){
	switch(task){
		case 2:
			return '?';
		case 3:
			return '+';
		case 4:
			return '*';
	}
	return 0;
}

void act_special(int task, int* min_rep, int* max_rep){
	switch(task){
		case 2:
			*min_rep = *min_rep - 1;
			break;
		case 3:
			*max_rep = BUF_LEN;
			break;
		case 4:
			*min_rep = *min_rep - 1;
			*max_rep = BUF_LEN;
			break;
	}
}

int mark_str2__4(const char *s_orig, char *s, int* min_rep, int* max_rep, int task_num){
	int i, j = 0, count = 0;
	for(i = 0; s_orig[i]; i++){
		if(s_orig[i] == '\\')
			if(s_orig[i + 1] == 0)
				return ERROR_INPUT;
			else{
				count = 0;
				i++;
				if(s[j - 1] == s_orig[i]){
					min_rep[j - 1]++;
					max_rep[j - 1]++;
				}
				else{
					s[j] = s_orig[i];
					min_rep[j] = 1;
					max_rep[j] = 1;
					j++;
				}
			}
		else{
			if(i == 0){
				s[j] = s_orig[i];
				min_rep[j] = 1;
				max_rep[j] = 1;
				j++;
			}
			else{
				if(s_orig[i] == get_special(task_num)){
					if(count == 0){
						act_special(task_num, &min_rep[j - 1], &max_rep[j - 1]);
						count++;
					}
				}
				else{
					count = 0;
					if(s[j - 1] == s_orig[i]){
						min_rep[j - 1]++;
						max_rep[j - 1]++;
					}
					else{
						s[j] = s_orig[i];
						min_rep[j] = 1;
						max_rep[j] = 1;
						j++;
					}
				}
			}
		}
	}
	return SUCCESS;
}

int is_str_equal2__4(const char *s, char *sm /*marked*/, int *min_rep, int *max_rep){
	int i, j, count = 0;
	for(i = 0, j = 0; s[i] != 0 && s[i] != '\n'; i++, j++){
		if(max_rep[j] == 0)
			return 0;
		else{
			while(s[i] == sm[j]){
				count++;
				i++;
			}
			if(count >= min_rep[j] && count <= max_rep[j]){
				i--;
				count = 0;
			}
			else
				return 0;
		}
	}
	for(; max_rep[j] != 0; j++)
		if(min_rep[j] > 0)
			return 0;
	return 1;
}

int solve2__4(const char *nameIn, const char *nameOut, const char *s_orig, int *res, int task_num){
	FILE *fin, *fout;
	char buf[BUF_LEN], s[BUF_LEN];
	int  i, count, min_rep[BUF_LEN], max_rep[BUF_LEN];
	open_files;
	// files fin and fout now is open
	for(i = 0; i < BUF_LEN; i++){
		s[i] = 0;
		min_rep[i] = 0;
		max_rep[i] = 0;
	}
	if(mark_str2__4(s_orig, s, min_rep, max_rep, task_num) != SUCCESS){
		fclose(fin); fclose(fout);
		return ERROR_INPUT;
	}
	count = 0;
	while(fgets(buf, BUF_LEN, fin)){
		if(is_str_equal2__4(buf, s, min_rep, max_rep)){
			if(fprintf(fout, "%s", buf) < 0){
				fclose(fin); fclose(fout);
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


// ============== TASK 5 =============== //

int mark_str5(const char *s_orig, char *s_low, char *s_high){
	int i, j = 0;
	for(i = 0; s_orig[i]; i++, j++){
		if(s_orig[i] == '\\'){
			if(s_orig[i + 1] != 0){
				i++;
				s_low[j] = s_orig[i];
				s_high[j] = s_orig[i];
			}
			else
				return ERROR_INPUT;
		}
		else{
			if(s_orig[i] == '['){
				if(s_orig[i + 4] == ']' && s_orig[i + 2] == '-'){
					s_low[j] = s_orig[i + 1];
					s_high[j] = s_orig[i + 3];
					i += 4;
				}
				else
					return ERROR_INPUT;
			}
			else{
				if(s_orig[i] == ']')
					return ERROR_INPUT;
				s_low[j] = s_orig[i];
				s_high[j] = s_orig[i];
			}
		}
	}
	return SUCCESS;
}

int is_str_equal5(const char *buf, char *s_low, char *s_high){
	int i;
	for(i = 0; buf[i] != 0 && buf[i] != '\n'; i++){
		if(buf[i] < s_low[i] || buf[i] > s_high[i])
			return 0;
	}
	if(s_low[i] != 0 && s_high[i] != 0)
		return 0;
	return 1;
}

int solve5(const char *nameIn, const char *nameOut, const char *s_orig, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN], s_low[BUF_LEN], s_high[BUF_LEN];
	int i, count;
	open_files;
	// files fin and fout now is open
	for(i = 0; i < BUF_LEN; i++){
		s_low[i] = 0;
		s_high[i] = 0;
	}
	if(mark_str5(s_orig, s_low, s_high) != SUCCESS){
		fclose(fin);
		fclose(fout);
		return ERROR_INPUT;
	}
	count = 0;
	while(fgets(buf, BUF_LEN, fin)){
		if(is_str_equal5(buf, s_low, s_high)){
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
