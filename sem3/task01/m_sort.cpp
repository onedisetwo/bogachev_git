#include "m_sort.h"
#include "main.h"
#include <stdio.h>

int get_diff (data* a, int n){
	int i, diff = 0;
	for(i = 1; i < n; i++){
		if(a[i] < a[i-1])
			diff++;
	}
	return diff;
}

#define swap(a, b, tmp) tmp = a; a = b; b = tmp;

// TASK 1
int get_insert_pos_bin (data *a, int n, data x){
	int l = 0, r = n, s = n;
	while(l != r){
		s = (l + r) / 2;
		if(a[s] < x)
			l = s + 1;
		else
			r = s;
	}
	return (l == 0) ? 0 : l - 1;
}

int get_insert_pos_bin_old (data *a, int n, data x){
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
void merge_arrays (data *a, int n, data *b, int m, data *c){
	int i = 0, j = 0, k = 0;
	while(i < n && j < m){
		if(!(a[i] > b[j])){
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
int split_array (data *a, int n, int m){
	int i = 0, j = n - 1;
	data temp;
	data x = a[m];
	while(i <= j){
		while(a[i] < x)
			i++;
		while(a[j] > x)
			j--;
		if(i <= j){
			swap(a[i], a[j], temp)
			if(i == m){
				m = j;
				i++;
			}
			else {
				if(j == m){
					m = i;
					j--;
				}
				else{
					i++;
					j--;
				}
			}
		}
	}
	return m; // Insert pos
}

int split_array_old (data *a, int n, data x){
	int i = 0, j = n - 1;
	data temp;
	while(i <= j){
		if(a[i] < x)
			i++;
		else {
			if(!(a[j] < x))
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
void bubble_sort (data *a, int n){
	int i, j;
	data temp;
	for(i = n - 1; i > 0; i--){
		for(j = 0; j < i; j++){
			if(a[j] > a[j+1]){
				swap(a[j], a[j+1], temp);
			}
		}
	}
}

// TASK 5
void selection_sort(data *a, int n){
	int startPos, i, minPos;
	data temp;
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
void insertion_sort_lin(data *a, int n){
	int k, i, insPos;
	data temp;
	for(k = 0; k < n; k++){
		temp = a[k];
		for(i = 0; i < k; i++)
			if(!(a[i] < a[k])){
				insPos = i;
				for(i = k; i > insPos; i--)
					a[i] = a[i-1];
				a[insPos] = temp;
				break;
			}
	}
}

// TASK 7
void insertion_sort_bin(data *a, int n){
	int k, i, insPos;
	data temp;
	for(k = 0; k < n; k++){
		temp = a[k];
		insPos = get_insert_pos_bin_old(a, k, a[k]);
		for(i = k; i > insPos; i--)
			a[i] = a[i-1];
		a[insPos] = temp;
	}
}

// TASK 8
void copy(data *a, data *b, int n){
	for(int i = 0; i < n; i++){
		b[i] = a[i];
	}
}

void neumann_sort(data *a, data *b, int n){
	int k, i;
	data *a_orig = a, *c;
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
void quick_sort(data *a, int n){
	int split_pos;
	data temp;
	while(n > 1){
		split_pos = split_array_old(a, n, a[n/2]);
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
void heap_sort(data *a, int n){
	data temp, x;
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
				if(!(a[k*2 + 2] > x)){
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
				if(!(a[k*2 + 1] > x)){
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

