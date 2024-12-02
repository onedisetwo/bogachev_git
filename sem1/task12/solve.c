#include <stdlib.h>
//#include <string.h>
#include <stdio.h>
#include "solve.h"
#include "m_string.h"

int solve1(char **a, int n, char *s){
	int i, j, k;
	for(i = 0, j = 0; i < n; i++){
		if(strcmp_(a[i], s) >= 0){
			if(i != j){
				free(a[j]);
				a[j] = a[i];
				a[i] = 0;
			}
			j++;
		}
	}
	for(k = j; k < n; k++)
		if(a[k]){
			free(a[k]);
			a[k] = 0;
		}
	return j;
}

int solve2(char **a, int n, char *s){
	int i, j, k;
	for(i = 0, j = 0; i < n; i++){
		if(strstr_(s, a[i]) == NULL){
			if(i != j){
				free(a[j]);
				a[j] = a[i];
				a[i] = 0;
			}
			j++;
		}
	}
	for(k = j; k < n; k++)
		if(a[k]){
			free(a[k]);
			a[k] = 0;
		}
	return j;
}

int solve3(char **a, int n, char *s){
	int i, j, k;
	for(i = 0, j = 0; i < n; i++){
		if(a[i][strcspn_(a[i], s)] != 0){
			if(i != j){
				free(a[j]);
				a[j] = a[i];
				a[i] = 0;
			}
			j++;
		}
	}
	for(k = j; k < n; k++)
		if(a[k]){
			free(a[k]);
			a[k] = 0;
		}
	return j;
}

int solve4(char **a, int n, char *s){
	int i, j, k, len = strlen_(s), f = 0;
	for(i = 0, j = 0; i < n; i++){
		if((int)strlen_(a[i]) >= len){
			f = 0;
			if(i != j){
				free(a[j]);
				a[j] = a[i];
				a[i] = 0;
			}
			j++;
		}
		else
			if(!f){
				if(i != j){
					free(a[j]);
					a[j] = a[i];
					a[i] = 0;
				}
				j++;
				f = 1;
			}
	}
	for(k = j; k < n; k++)
		if(a[k]){
			free(a[k]);
			a[k] = 0;
		}
	return j;
}

int solve5(char **a, int n, char *s){
	int i, j, k, len = strlen_(s), len2, f = 0;
	for(i = 0, j = 0; i < n; i++){
		if((len2 = (int)strlen_(a[i])) < len
			|| strcmp_(a[i] + len2 - len, s)){
			f = 0;
			if(i != j){
				free(a[j]);
				a[j] = a[i];
				a[i] = 0;
			}
			j++;
		}
		else
			if(!f){
				if(i != j){
					free(a[j]);
					a[j] = a[i];
					a[i] = 0;
				}
				j++;
				f = 1;
			}
	}
	for(k = j; k < n; k++)
		if(a[k]){
			free(a[k]);
			a[k] = 0;
		}
	return j;
}

int solve6(char **a, int n, char *s){
	int i, j, k, f = 0, f2 = 1;
	for(i = 0, j = 0; i < n; i++){
		if(a[i][strcspn_(a[i], s)]){
			if(!f2){
				if(i != j){
					free(a[j]);
					a[j] = a[i - 1];
					a[i - 1] = 0;
				}
				j++;
			}
			if(i != j){
				free(a[j]);
				a[j] = a[i];
				a[i] = 0;
			}
			j++;
			f = 0;
			f2 = 1;
		}
		else{
			f2 = 0;
			if(!f){
				if(i != j){
					free(a[j]);
					a[j] = a[i];
					a[i] = 0;
				}
				j++;
				f = 1;
				f2 = 1;
			}
		}
	}
	if(f && !f2){
		if(i != j){
			free(a[j]);
			a[j] = a[i - 1];
			a[i - 1] = 0;
		}
		j++;
	}
	for(k = j; k < n; k++)
		if(a[k]){
			free(a[k]);
			a[k] = 0;
		}
	return j;
}

int solve7(char **a, int n, char *s){
	int i, j, k, wait = -1;
	for(i = 0, j = 0; i < n; i++){
		if((i == 0 && strcmp_(a[i + 1], s) >= 0)
			|| (i == n - 1 && strcmp_(a[i - 1], s) >= 0)
			|| (i > 0 && i < n - 1 && strcmp_(a[i - 1], s) >= 0
			&& strcmp_(a[i + 1], s) >= 0)){
			if(wait != -1){
				if(wait != j){
					free(a[j]);
					a[j] = a[wait];
					a[wait] = 0;
				}
				wait = i;
				j++;
			}
			else{
				wait = i;
			}
		}
		else
			if(wait != -1){
				if(wait != j){
					free(a[j]);
					a[j] = a[wait];
					a[wait] = 0;
				}
				wait = -1;
				j++;
			}
	}
	if(wait != -1){
		if(wait != j){
			free(a[j]);
			a[j] = a[wait];
			a[wait] = 0;
		}
		j++;
	}
	for(k = j; k < n; k++)
		if(a[k]){
			free(a[k]);
			a[k] = 0;
		}
	return j;
}

char *strstr_t_ (const char *s1, const char *s2, int t[256]){
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

int solve8(char **a, int n, char *s){
	int i, j, k, wait = -1, d = (int)'a' - (int)'A';
	int t[256];
        /* Строчные эквивалентны прописным, инициализация массива
                для модифицированной strstr_t_*/
        for(i = 0; i < (int)'a'; i++)
                t[i] = i;
        for(i = (int)'a'; i <= (int)'z'; i++)
                t[i] = i - d;
        for(i = (int)'z' + 1; i < 256; i++)
                t[i] = i;
	for(i = 0, j = 0; i < n; i++){
		if((i == 0 && strstr_t_(s, a[i + 1], t) == NULL)
			|| (i == n - 1 && strstr_t_(s, a[i - 1], t) == NULL)
			|| (i > 0 && i < n - 1 && strstr_t_(s, a[i - 1], t) == NULL
			&& strstr_t_(s, a[i + 1], t) == NULL)){
			if(wait != -1){
				if(wait != j){
					free(a[j]);
					a[j] = a[wait];
					a[wait] = 0;
				}
				wait = i;
				j++;
			}
			else{
				wait = i;
			}
		}
		else
			if(wait != -1){
				if(wait != j){
					free(a[j]);
					a[j] = a[wait];
					a[wait] = 0;
				}
				wait = -1;
				j++;
			}
	}
	if(wait != -1){
		if(wait != j){
			free(a[j]);
			a[j] = a[wait];
			a[wait] = 0;
		}
		j++;
	}
	for(k = j; k < n; k++)
		if(a[k]){
			free(a[k]);
			a[k] = 0;
		}
	return j;
}
