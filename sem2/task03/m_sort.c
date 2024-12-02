#include "m_sort.h"
#include "array_io.h"
#include <stdio.h>
#include <string.h>

// Other functions
int get_diff(char *a[], int n, int (*cmp)(const char*, const char*)){
	int i, diff = 0;
	for(i = 1; i < n; i++)
		if(cmp(a[i], a[i-1]) == 1)
			diff++;
	return diff;
}

void swap(char **a, char **b){
	char *temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// Comparators
int up_strcmp(const char *a, const char *b){
	return strcmp(a, b) < 0 ? 1 : 0;
}

int down_strcmp(const char *a, const char *b){
	return strcmp(a, b) > 0 ? 1 : 0;
}

int up_len(const char *a, const char *b){
	return strlen(a) < strlen(b) ? 1 : 0;
}

int down_len(const char *a, const char *b){
	return strlen(a) > strlen(b) ? 1 : 0;
}

// TASK 1
int get_insert_pos_bin(char *a[], int n, char *x, int (*cmp)(const char*, const char*)){
	int l = 0, r = n, s = n;
	while(l != r){
		s = (l + r) / 2;
		if(cmp(a[s], x) == 1)
			l = s + 1;
		else
			r = s;
	}
	return l;
}

// TASK 2
void merge_arrays(char *a[], int n, char *b[], int m, char *c[],
			int (*cmp)(const char*, const char*)){
	int i = 0, j = 0, k = 0;
	while(i < n && j < m){
		if(cmp(a[i], b[j]) == 1){
			c[k] = a[i];
			i++;
			k++;
			continue;
		}
		else{
			c[k] = b[j];
			j++;
			k++;
			continue;
		}
	}
	for( ; i < n; i++){
		c[k] = a[i];
		k++;
	}
	for( ; j < m; j++){
		c[k] = b[j];
		k++;
	}
}

// TASK 3
int split_array(char *a[], int n, char *x, int (*cmp)(const char*, const char*)){
	int i = 0, j = n - 1;
	while(i <= j){
		if(cmp(a[i], x) == 1)
			i++;
		else {
			if(cmp(a[j], x) != 1)
				j--;
			else{
				swap(&a[i], &a[j]);
				i++; 	j--;
			}
		}
	}
	return i; // Insert pos
}

// TASK 4
void bubble_sort(char *a[], int n, int (*cmp)(const char*, const char*)){
	int i, j;
	for(i = n - 1; i > 0; i--){
		for(j = 0; j < i; j++){
			if(cmp(a[j], a[j+1]) == 0){
				swap(&a[j], &a[j+1]);
			}
		}
	}
}

// TASK 5
void selection_sort(char *a[], int n, int (*cmp)(const char*, const char*)){
	int startPos, i, minPos;
	for(startPos = 0; startPos < n; startPos++){
		minPos = startPos;
		for(i = startPos + 1; i < n; i++){
			if(cmp(a[minPos], a[i]) == 0)
				minPos = i;
		}
		swap(&a[startPos], &a[minPos]);
	}
}

// TASK 6
void insertion_sort_lin(char *a[], int n, int (*cmp)(const char*, const char*)){
	int k, i, insPos;
	char *temp;
	for(k = 0; k < n; k++){
		temp = a[k];
		for(i = 0; i < k; i++)
			if(cmp(a[i], a[k]) == 0){
				insPos = i;
				for(i = k; i > insPos; i--)
					a[i] = a[i-1];
				a[insPos] = temp;
				break;
			}
	}
}

// TASK 7
void insertion_sort_bin(char *a[], int n, int (*cmp)(const char*, const char*)){
	int k, i, insPos;
	char *temp;
	for(k = 0; k < n; k++){
		temp = a[k];
		insPos = get_insert_pos_bin(a, k, a[k], cmp);
		for(i = k; i > insPos; i--)
			a[i] = a[i-1];
		a[insPos] = temp;
	}
}

// TASK 8
void copy(char *a[], char *b[], int n){
	for(int i = 0; i < n; i++){
		b[i] = a[i];
	}
}

void neumann_sort(char *a[], char *b[], int n, int (*cmp)(const char*, const char*)){
	int k, i;
	char **a_orig = a, **c;
	for(k = 1; k <= n; k *= 2){
		for(i = 0; i < n; i += 2*k){
			if(i + k < n)
				merge_arrays(a+i, k, a+i+k, (i+2*k < n ? k : n-(i+k)), b+i, cmp);
			else
				copy(a + i, b + i, n - i);
		}
		c = a;
		a = b;
		b = c;
	}
	if(a != a_orig)
		copy(a, a_orig, n);
}

// TASK 9
void quick_sort(char *a[], int n, int (*cmp)(const char*, const char*)){
	int split_pos;
	while(n > 1){
		split_pos = split_array(a, n, a[n/2], cmp);
		if(split_pos == 0){
			swap(&a[0], &a[n/2]);
			a++;
			n--;
			continue;
		}
		if(split_pos < n - split_pos){
			quick_sort(a, split_pos, cmp);
			a = a + split_pos;
			n = n - split_pos;
		}
		else{
			quick_sort(a + split_pos, n - split_pos, cmp);
			n = split_pos;
		}
	}
}

// TASK 10
void heap_sort(char *a[], int n, int (*cmp)(const char*, const char*)){
	char *x, *temp;
	int k, i, insPos;
	if(n == 0)
		return ;
	for(k = 1; k < n; k++){
		insPos = 0;
		for(i = k; i - 1 >= 0; i = (i - 1)/2){
			if(cmp(a[(i - 1)/2], a[k]) == 0){
				insPos = i;
				break;
			}
		}
		temp = a[k];
		for(i = k; i > insPos; i = (i - 1)/2){
			a[i] = a[(i - 1)/2];
		}
		a[insPos] = temp;
	}
	swap(&a[n - 1], &a[0]);
	for(n = n - 1; n > 1; n--){
		k = 0;
		x = a[0];
		while(k*2 + 1 < n){
			if(k*2 + 2 == n){
				if(cmp(x, a[k*2 + 1]) == 1){
					a[k] = a[k*2 + 1];
					a[k*2 + 1] = x;
				}
				else
					a[k] = x;
				break;
			}
			if(cmp(a[k*2 + 1], a[k*2 + 2]) == 1){
				if(cmp(a[k*2 + 2], x) == 1){
					a[k] = x;
					break;
				}
				else{
					a[k] = a[k*2 + 2];
					k = k*2 + 2;
					continue;
				}
			}
			else{
				if(cmp(a[k*2 + 1], x) == 1){
					a[k] = x;
					break;
				}
				else{
					a[k] = a[k*2 + 1];
					k = k*2 + 1;
					continue;
				}
			}
		}
		if(k*2 + 1 >= n)
			a[k] = x;
		swap(&a[n - 1], &a[0]);
	}
}
