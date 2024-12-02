#include <stdio.h>
#include "io_status.h"
#include "m_string.h"
#include "solve.h"
#include <stdlib.h>

#define BUF_LEN 1500

#define default_file_open(nameIn, fin, nameOut, fout) 	\
	if( !(fin = fopen(nameIn, "r")) ){ 	\
		return ERROR_OPEN; 		\
	} 					\
	if( !(fout = fopen(nameOut, "w")) ){ 	\
		fclose(fin); 			\
		return ERROR_OPEN;		\
	}


int solve1(const char *nameIn, const char *nameOut, const char *s, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN];
	int t[256];
	int d = (int)'a' - (int)'A', i, count = 0;
	default_file_open(nameIn, fin, nameOut, fout)
	/* Строчные эквивалентны прописным, инициализация массива
		для модифицированной strstr_table_*/
	for(i = 0; i < (int)'a'; i++)
		t[i] = i;
	for(i = (int)'a'; i <= (int)'z'; i++)
		t[i] = i - d;
	for(i = (int)'z' + 1; i < 256; i++)
		t[i] = i;
	while( fgets(buf, BUF_LEN, fin) ){
		if(strstr_table_ (buf, s, t)){
			if(fprintf(fout, "%s", buf) < 0){
				fclose(fin); fclose(fout);
				return ERROR_WRITE;
			}
			count++;
		}
	}
	if(!feof(fin)){
		fclose(fin); fclose(fout);
		return ERROR_READ;
	}
	fclose(fin); fclose(fout);
	*res = count;
	return SUCCESS;
}

int solve2(const char *nameIn, const char *nameOut, char *s, int *res){
	FILE *fin, *fout;
	char buf[BUF_LEN];
	int count = 0, slen, buflen;
	default_file_open(nameIn, fin, nameOut, fout)
	strcat_ ((char *)s, "\n");
	slen = strlen_(s);
	while( fgets(buf, BUF_LEN, fin) ){
		buflen = strlen_(buf);
		if(slen <= buflen && strcmp_(s, buf + buflen - slen) == 0){
			if(fprintf(fout, "%s", buf) < 0){
				fclose(fin); fclose(fout);
				return ERROR_WRITE;
			}
			count++;
		}
	}
	if(!feof(fin)){
		fclose(fin); fclose(fout);
		return ERROR_READ;
	}
	s[slen - 1] = 0;
	fclose(fin); fclose(fout);
	*res = count;
	return SUCCESS;
}

int solve3(const char *nameIn, const char *nameOut, const char *s1,
		const char *s2, int *res){
	FILE *fin, *fout;
	char buf_orig[BUF_LEN], *buf1, *buf2;
	int count = 0, s1len = strlen_(s1), f1;
	default_file_open(nameIn, fin, nameOut, fout)
	while( fgets(buf_orig, BUF_LEN, fin) ){
		buf1 = buf_orig;
		f1 = 0;
		while( (buf2 = strstr_(buf1, s1)) != NULL){
			buf2[0] = 0;
			if( fprintf(fout, "%s%s", buf1, s2) < 0){
				fclose(fin); fclose(fout);
				return ERROR_WRITE;
			}
			f1 = 1;
			buf1 = buf2 + s1len;
		}
		if(f1)
			count++;
		if(fprintf(fout, "%s", buf1) < 0){
			fclose(fin); fclose(fout);
			return ERROR_WRITE;
		}
	}
	if(!feof(fin)){
		fclose(fin); fclose(fout);
		return ERROR_READ;
	}
	fclose(fin); fclose(fout);
	*res = count;
	return SUCCESS;
}

int delete_spaces_r (const char *s1, char *s2, const char *t){
	int i, j = 0;
	for(i = 0; s1[i]; i++){
		if(!strchr_(t, s1[i]))
			s2[j++] = s1[i];
	}
	s2[j] = 0;
	return j;
}

int delete_spaces (char *s, const char *t){
	char *s2 = s;
	return delete_spaces_r ((const char *)s, s2, t);
}

int solve4(const char *nameIn, const char *nameOut, char *s,
		const char *t, int *res){
	FILE *fin, *fout;
	char buf1[BUF_LEN], buf2[BUF_LEN];
	int buflen, count = 0;
	default_file_open (nameIn, fin, nameOut, fout)
	delete_spaces (s, t);
	while( fgets(buf1, BUF_LEN, fin) ){
		buflen = delete_spaces_r (buf1, buf2, t);
		if(buf2[buflen - 1] == '\n')
			buf2[buflen - 1] = 0;
		if(strcmp_(buf2, s) != 0){
			count++;
			if(fprintf(fout, "%s", buf1) < 0){
				fclose(fin); fclose(fout);
				return ERROR_WRITE;
			}
		}
	}
	if(!feof(fin)){
		fclose(fin); fclose(fout);
		return ERROR_READ;
	}
	fclose(fin); fclose(fout);
	*res = count;
	return SUCCESS;
}

int solve5(const char *nameIn, const char *nameOut, char *s,
		const char *t, int *res){
	FILE *fin, *fout;
	char buf1[BUF_LEN], buf2[BUF_LEN];
	int buflen, count = 0;
	default_file_open (nameIn, fin, nameOut, fout)
	delete_spaces (s, t);
	while( fgets(buf1, BUF_LEN, fin) ){
		buflen = delete_spaces_r (buf1, buf2, t);
		if((int)strspn_(buf2, s) == buflen - 1){
			count++;
			if(fprintf(fout, "%s", buf1) < 0){
				fclose(fin); fclose(fout);
				return ERROR_WRITE;
			}
		}
	}
	if(!feof(fin)){
		fclose(fin); fclose(fout);
		return ERROR_READ;
	}
	fclose(fin); fclose(fout);
	*res = count;
	return SUCCESS;
}

int solve6(const char *nameIn, const char *nameOut, char *s,
		const char *t, int *res){
	FILE *fin, *fout;
	char buf1[BUF_LEN], buf2[BUF_LEN];
	int count = 0;
	default_file_open (nameIn, fin, nameOut, fout)
	delete_spaces (s, t);
	while( fgets(buf1, BUF_LEN, fin) ){
		delete_spaces_r (buf1, buf2, t);
		if(strstr_(buf2, s) != NULL){
			count++;
			if(fprintf(fout, "%s", buf1) < 0){
				fclose(fin); fclose(fout);
				return ERROR_WRITE;
			}
		}
	}
	if(!feof(fin)){
		fclose(fin); fclose(fout);
		return ERROR_READ;
	}
	fclose(fin); fclose(fout);
	*res = count;
	return SUCCESS;
}

int solve7(const char *nameIn, const char *nameOut, char *s,
		const char *t, int *res){
	FILE *fin, *fout;
	char buf1[BUF_LEN], buf2[BUF_LEN];
	int count = 0, slen;
	default_file_open (nameIn, fin, nameOut, fout)
	delete_spaces (s, t);
	slen = strlen_(s);
	while( fgets(buf1, BUF_LEN, fin) ){
		delete_spaces_r (buf1, buf2, t);
		buf2[slen] = 0;
		if(strcmp_(buf2, s) == 0){
			count++;
			if(fprintf(fout, "%s", buf1) < 0){
				fclose(fin); fclose(fout);
				return ERROR_WRITE;
			}
		}
	}
	if(!feof(fin)){
		fclose(fin); fclose(fout);
		return ERROR_READ;
	}
	fclose(fin); fclose(fout);
	*res = count;
	return SUCCESS;
}

int solve8 (const char *nameIn, const char *nameOut, const char *s1,
                const char *s2, const char *s3, int *res){
	FILE *fin, *fout;
	char buf_orig[BUF_LEN], *buf1, *buf2;
	int count = 0, s2len = strlen_(s2), f1 = 0;
	default_file_open (nameIn, fin, nameOut, fout);
	while( fgets(buf_orig, BUF_LEN, fin) ){
		f1 = 0;
		buf1 = buf_orig;
		while( (buf2 = strstr_(buf1, s1)) != NULL){
			f1 = 1;
			buf2[0] = 0;
			if(fprintf(fout, "%s%s%s%s", buf1, s2, s1, s3) < 0){
				fclose(fin); fclose(fout);
				return ERROR_WRITE;
			}
			buf1 = buf2 + s2len;
		}
		if(f1)
			count++;
		if(fprintf(fout, "%s", buf1) < 0){
			fclose(fin); fclose(fout);
			return ERROR_WRITE;
		}
	}
	if(!feof(fin)){
		fclose(fin); fclose(fout);
		return ERROR_READ;
	}
	fclose(fin); fclose(fout);
	*res = count;
	return SUCCESS;
}
