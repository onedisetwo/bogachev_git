#include <stdio.h>
#include "m_sort.h"
#include "student.h"

int get_diff (student* a, int n){
	int i, diff = 0;
	for(i = 1; i < n; i++){
		if(a[i] < a[i-1])
			diff++;
	}
	return diff;
}

void swap(student*, student*);
void swap(student *a, student *b){
	student temp;
	temp = (student&&)(*a);
	*a = (student&&)(*b);
	*b = (student&&)(temp);
}

// TASK 1
int get_insert_pos_bin (student *a, int n, student *x){
	int l = 0, r = n, s = n;
	while(l != r){
		s = (l + r) / 2;
		if(a[s] < *x)
			l = s + 1;
		else
			r = s;
	}
	return (l == 0) ? 0 : l - 1;
}

// TASK 2
void merge_arrays (student *a, int n, student *b, int m, student *c){
	int i = 0, j = 0, k = 0;
	while(i < n && j < m){
		if(!(a[i] > b[j])){
			c[k] = (student&&)a[i];
			i++;
			k++;
			continue;
		}
		else{
			c[k] = (student&&)b[j];
			j++;
			k++;
			continue;
		}
	}
	for( ; i < n; i++){
		c[k] = (student&&)a[i];
		k++;
	}
	for( ; j < m; j++){
		c[k] = (student&&)b[j];
		k++;
	}
}

// TASK 3
int split_array (student *a, int n, int m){
	int i = 0, j = n - 1;
	student x = a[m];// = (student&&)a[m];
	while(i <= j){
		while(a[i] < x)
			i++;
		while(a[j] > x)
			j--;
		if(i <= j){
			swap(a+i, a+j);
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
//	a[m] = (student&&)x;
	return m; // Insert pos
}

int split_array_old (student *a, int n, student *x){
	int i = 0, j = n - 1;
	while(i <= j){
		if(a[i] < *x)
			i++;
		else {
			if(!(a[j] < *x))
				j--;
			else{
				swap(a+i, a+j);
				i++; 	j--;
			}
		}
	}
	return i; // Insert pos
}

// TASK 4
void bubble_sort (student *a, int n){
	int i, j;
	for(i = n - 1; i > 0; i--){
		for(j = 0; j < i; j++){
			if(a[j] > a[j+1]){
				swap(a+j, a+(j+1));
			}
		}
	}
}

// TASK 5
void selection_sort(student *a, int n){
	int startPos, i, minPos;
	student temp;
	for(startPos = 0; startPos < n; startPos++){
		minPos = startPos;
		for(i = startPos + 1; i < n; i++){
			if(a[minPos] > a[i])
				minPos = i;
		}
		swap(a + startPos, a + minPos);
	}
}

// TASK 6
void insertion_sort_lin(student *a, int n){
	int k, i, insPos;
	student temp;
	for(k = 0; k < n; k++){
		for(i = 0; i < k; i++)
			if(!(a[i] < a[k])){
				insPos = i;
				temp = (student&&)a[k];
				for(i = k; i > insPos; i--)
					a[i] = (student&&)a[i-1];
				a[insPos] = (student&&)temp;
				break;
			}
	}
}

// TASK 7
void insertion_sort_bin(student *a, int n){
	int k, i;
	int insPos, s, r;
	student temp;
	for(k = 0; k < n; k++){
		insPos = 0;
		s = k;
		r = k;
		while(insPos != r){
			s = (insPos + r) / 2;
			if(a[s] < a[k])
				insPos = s + 1;
			else
				r = s;
		}
		temp = (student&&)a[k];
		for(i = k; i > insPos; i--)
			a[i] = (student&&)a[i-1];
		a[insPos] = (student&&)temp;
	}
}

// TASK 8
void move(student *a, student *b, int n){
	for(int i = 0; i < n; i++){
		b[i] = (student&&)a[i];
	}
}

void neumann_sort(student *a, student *b, int n){
	int k, i;
	student *a_orig = a, *c;
	for(k = 1; k <= n; k *= 2){
		for(i = 0; i < n; i += 2*k){
			if(i + k < n)
				merge_arrays(a+i, k, a+i+k, (i+2*k < n ? k : n-(i+k)), b+i);
			else
				move(a + i, b + i, n - i);
		}
		c = a;
		a = b;
		b = c;
	}
	if(a != a_orig)
		move(a, a_orig, n);
}

// TASK 9
void quick_sort(student *a, int n){
	int split_pos;
	while(n > 1){
		split_pos = split_array_old(a, n, a + n/2);
		if(split_pos == 0){
			swap(a, a+(n/2));
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
void heap_sort(student *a, int n){
	student temp, x;
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
		temp = (student&&)a[k];
		for(i = k; i > insPos; i = (i - 1)/2){
			a[i] = (student&&)a[(i - 1)/2];
		}
		a[insPos] = (student&&)temp;
	}
	swap(a+(n-1), a);
	for(n = n - 1; n > 1; n--){
		k = 0;
		x = (student&&)a[0];
		while(k*2 + 1 < n){
			if(k*2 + 2 == n){
				if(x < a[k*2 + 1]){
					a[k] = (student&&)a[k*2 + 1];
					a[k*2 + 1] = (student&&)x;
				}
				else
					a[k] = (student&&)x;
				break;
			}
			if(a[k*2 + 1] < a[k*2 + 2]){
				if(!(a[k*2 + 2] > x)){
					a[k] = (student&&)x;
					break;
				}
				else{
					a[k] = (student&&)a[k*2 + 2];
					k = k*2 + 2;
					continue;
				}
			}
			else{
				if(!(a[k*2 + 1] > x)){
					a[k] = (student&&)x;
					break;
				}
				else{
					a[k] = (student&&)a[k*2 + 1];
					k = k*2 + 1;
					continue;
				}
			}
		}
		if(k*2 + 1 >= n)
			a[k] = (student&&)x;
		swap(a+(n-1), a);
	}
}

