#include "m_sort.h"
#include "m_func.h"
#include "io_array.h"
#include <stdio.h>

int get_diff(double* a, int n){
	int i, diff = 0;
	for(i = 1; i < n; i++){
		if(a[i] < a[i-1])
			diff++;
	}
	return diff;
}

// TASK 1
int get_insert_pos_bin(double *a, int n, double x){
	int l = 0, r = n, s = n;
	while(l != r){
		s = (l + r) / 2;
		if(a[s] < x)
			l = s + 1;
		else
			r = s;
	}
	return l;
}

// TASK 2
void merge_arrays(double *a, int n, double *b, int m, double *c){
	int i = 0, j = 0, k = 0;
	while(i < n && j < m){
		if(a[i] < b[j] || is_equal(a[i], b[j])){
			c[k] = a[i];
			i++;
			k++;
			continue;
		}
		if(a[i] > b[j] || is_equal(a[i], b[j])){
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
int split_array(double *a, int n, double x){
	int i = 0, j = n - 1;
	double temp;
	while(i <= j){
		if(a[i] < x)
			i++;
		else {
			if(a[j] > x || is_equal(a[j],x))
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
void bubble_sort(double *a, int n){
	int i, j;
	double temp;
	for(i = n - 1; i > 0; i--){
		for(j = 0; j < i; j++){
			if(a[j] > a[j+1]){
				swap(a[j], a[j+1], temp);
			}
		}
	}
}

// TASK 5
void selection_sort(double *a, int n){
	int startPos, i, minPos;
	double temp;
	for(startPos = 0; startPos < n; startPos++){
		minPos = startPos;
		for(i = startPos + 1; i < n; i++){
			if(a[minPos] > a[i])
				minPos = i;
		}
		swap(a[startPos], a[minPos], temp);
	}
}

// TASK 6
void insertion_sort_lin(double *a, int n){
	int k, i, insPos;
	double temp;
	for(k = 0; k < n; k++){
		temp = a[k];
		for(i = 0; i < k; i++)
			if(a[i] > a[k] || is_equal(a[i], a[k])){
				insPos = i;
				for(i = k; i > insPos; i--)
					a[i] = a[i-1];
				a[insPos] = temp;
				break;
			}
	}
}

// TASK 7
void insertion_sort_bin(double *a, int n){
	int k, i, insPos;
	double temp;
	for(k = 0; k < n; k++){
		temp = a[k];
		insPos = get_insert_pos_bin(a, k, a[k]);
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

void neumann_sort(double *a, double *b, int n){
	int k, i;
	double *a_orig = a, *c;
	for(k = 1; k <= n; k *= 2){
		for(i = 0; i < n; i += 2*k){
			if(i + k < n)
				merge_arrays(a+i, k, a+i+k, (i+2*k < n ? k : n-(i+k)), b+i);
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
void quick_sort(double *a, int n){
	int split_pos;
	double temp;
	while(n > 1){
		split_pos = split_array(a, n, a[n/2]);
		if(split_pos == 0){
			swap(a[0], a[n/2], temp);
			a++;
			n--;
			continue;
		}
		if(split_pos < n - split_pos){
			quick_sort(a, split_pos);
			a = a + split_pos;
			n = n - split_pos;
		}
		else{
			quick_sort(a + split_pos, n - split_pos);
			n = split_pos;
		}
	}
}

// TASK 10
void heap_sort(double *a, int n){
	double temp, x;
	int k, i, insPos;
	if(n == 0)
		return ;
	for(k = 1; k < n; k++){
		insPos = 0;
		for(i = k; i - 1 >= 0; i = (i - 1)/2){
			if(a[(i - 1)/2] > a[k]){
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
				if(x < a[k*2 + 1]){
					a[k] = a[k*2 + 1];
					a[k*2 + 1] = x;
				}
				else
					a[k] = x;
				break;
			}
			if(a[k*2 + 1] < a[k*2 + 2]){
				if(a[k*2 + 2] < x || is_equal(a[k*2 + 2], x)){
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
				if(a[k*2 + 1] < x || is_equal(a[k*2 + 1], x)){
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
