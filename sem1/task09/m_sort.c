#include "m_sort.h"
#include "m_func.h"
#include "io_array.h"
#include <stdio.h>

int get_diff(double* a, int n, int (*cmp)(double, double)){
	int i, diff = 0;
	for(i = 1; i < n; i++){
		if(cmp(a[i], a[i-1]) == 1)
			diff++;
	}
	return diff;
}

// Comparators
int compare1(double x, double y){
	if(x < y) return 1;
	if(x > y) return -1;
	return 0;
}

int compare2(double x, double y){
	if(x > y) return 1;
	if(x < y) return -1;
	return 0;
}

// TASK 1
int get_insert_pos_bin(double *a, int n, double x, int (*cmp)(double, double)){
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
void merge_arrays(double *a, int n, double *b, int m, double *c, int (*cmp)(double, double)){
	int i = 0, j = 0, k = 0;
	while(i < n && j < m){
		if(cmp(a[i], b[j]) != -1){
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
int split_array(double *a, int n, double x, int (*cmp)(double, double)){
	int i = 0, j = n - 1;
	double temp;
	while(i <= j){
		if(cmp(a[i], x) == 1)
			i++;
		else {
			if(cmp(a[j], x) != 1)
				j--;
			else{
				swap(a[i], a[j], temp);
				i++; 	j--;
			}
		}
	}
	return i; // Insert pos
}

// TASK 4
void bubble_sort(double *a, int n, int (*cmp)(double, double)){
	int i, j;
	double temp;
	for(i = n - 1; i > 0; i--){
		for(j = 0; j < i; j++){
			if(cmp(a[j], a[j+1]) == -1){
				swap(a[j], a[j+1], temp);
			}
		}
	}
}

// TASK 5
void selection_sort(double *a, int n, int (*cmp)(double, double)){
	int startPos, i, minPos;
	double temp;
	for(startPos = 0; startPos < n; startPos++){
		minPos = startPos;
		for(i = startPos + 1; i < n; i++){
			if(cmp(a[minPos], a[i]) == -1)
				minPos = i;
		}
		swap(a[startPos], a[minPos], temp);
	}
}

// TASK 6
void insertion_sort_lin(double *a, int n, int (*cmp)(double, double)){
	int k, i, insPos;
	double temp;
	for(k = 0; k < n; k++){
		temp = a[k];
		for(i = 0; i < k; i++)
			if(cmp(a[i], a[k]) != 1){
				insPos = i;
				for(i = k; i > insPos; i--)
					a[i] = a[i-1];
				a[insPos] = temp;
				break;
			}
	}
}

// TASK 7
void insertion_sort_bin(double *a, int n, int (*cmp)(double, double)){
	int k, i, insPos;
	double temp;
	for(k = 0; k < n; k++){
		temp = a[k];
		insPos = get_insert_pos_bin(a, k, a[k], cmp);
		for(i = k; i > insPos; i--)
			a[i] = a[i-1];
		a[insPos] = temp;
	}
}

// TASK 8
void copy(double *a, double *b, int n){
	for(int i = 0; i < n; i++){
		b[i] = a[i];
	}
}

void neumann_sort(double *a, double *b, int n, int (*cmp)(double, double)){
	int k, i;
	double *a_orig = a, *c;
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
void quick_sort(double *a, int n, int (*cmp)(double, double)){
	int split_pos;
	double temp;
	while(n > 1){
		split_pos = split_array(a, n, a[n/2], cmp);
		if(split_pos == 0){
			swap(a[0], a[n/2], temp);
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
void heap_sort(double *a, int n, int (*cmp)(double, double)){
	double temp, x;
	int k, i, insPos;
	if(n == 0)
		return ;
	for(k = 1; k < n; k++){
		insPos = 0;
		for(i = k; i - 1 >= 0; i = (i - 1)/2){
			if(cmp(a[(i - 1)/2], a[k]) == -1){
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
	swap(a[n - 1], a[0], temp);
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
				if(cmp(a[k*2 + 2], x) != -1){
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
				if(cmp(a[k*2 + 1], x) != -1){
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
		swap(a[n - 1], a[0], temp);
	}
}
