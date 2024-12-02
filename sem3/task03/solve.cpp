#include "student.h"

int solve1(student* student_m, int n){
	int i, k;
	for(i = n - 1; i > 0; i--){
		if(student_m[i] < student_m[i - 1])
			student_m[i].erase_p();
	}
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve2(student* student_m, int n){
	int i, k;
	for(i = n - 1; i > 1; i--){
		if(student_m[i] > student_m[i - 1] && student_m[i] > student_m[i - 2])
			student_m[i].erase_p();
	}
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve3(student* student_m, int n){
	int i, k, del1 = 0;
	for(i = 1; i < n - 1; i++){
		if(student_m[i] < student_m[i - 1] && student_m[i] < student_m[i + 1]){
			if(del1 == 1)
				student_m[i - 1].erase_p();
			del1 = 1;
		}
		else{
			if(del1 == 1)
				student_m[i - 1].erase_p();
			del1 = 0;
		}
	}
	if(del1 == 1)
			student_m[n - 1].erase_p();
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve4(student* student_m, int n){
	int i, k, del2 = 0, del1 = 0;
	for(i = 2; i < n - 2; i++){
		if(student_m[i] > student_m[i - 2] && student_m[i] > student_m[i - 1] &&
			student_m[i] > student_m[i + 1] && student_m[i] > student_m[i + 2]){
			if(del2 == 1)
				student_m[i - 2].erase_p();
			del2 = del1;
			del1 = 1;
		}
		else{
			if(del2 == 1)
				student_m[i - 2].erase_p();
			del2 = del1;
			del1 = 0;
		}
	}
	if(del1 == 1)
		student_m[n - 3].erase_p();
	if(del2 == 1)
		student_m[n - 4].erase_p();
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve5(student* student_m, int n){
	int i, j, k, startPos = -1;
	for(i = 1; i < n; i++){
		if(student_m[i] < student_m[i - 1]){
			if(startPos == -1)
				startPos = i - 1;
		}
		else if(startPos != -1){
			for(j = startPos; j < i; j++)
				student_m[j].erase_p();
			startPos = -1;
		}
	}
	if(startPos != -1){
		for(j = startPos; j < i; j++)
			student_m[j].erase_p();
		startPos = -1;
	}
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve6(student* student_m, int n, student* x){
	int i, k;
	for(i = 0; i < n; i++){
		if(student_m[i] < *x)
			student_m[i].erase_p();
	}
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve7(student* student_m, int n, student* x){
	int i, k, startPos = -1;
	for(i = 0; i < n; i++){
		if(student_m[i] < *x){
			if(startPos == -1)
				startPos = i;
			else
				student_m[i].erase_p();
		}
		else
			startPos = -1;
	}
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve8(student* student_m, int n, student* x){
	int i, k, startPos = n + 1;
	for(i = 0; i < n; i++){
		if(student_m[i] > *x){
			if(startPos == n + 1)
				startPos = i;
		}
		else
			startPos = n + 1;
		if(i - 1 > startPos)
			student_m[i - 1].erase_p();
	}
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve9(student* student_m, int n, student* x){
	int i, k, delNext = 0;
	for(i = 0; i < n - 1; i++){
		if(delNext == 1 || student_m[i + 1] < *x){
			if(student_m[i] < *x)
				delNext = 1;
			else
				delNext = 0;
			student_m[i].erase_p();
		}
		else{
			if(student_m[i] < *x)
				delNext = 1;
			else
				delNext = 0;
		}
	}
	if(delNext == 1)
		student_m[n - 1].erase_p();
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}

int solve10(student* student_m, int n, student* x){
	int i, j, k, startPos = -1;
	for(i = 1; i < n; i++){
		if(startPos == -1){
			if(student_m[i - 1] < student_m[i] && student_m[i] < *x)
				startPos = i - 1;
		}
		else
			if(!(student_m[i - 1] < student_m[i] && student_m[i] < *x)){
				if(student_m[i] < *x)
					for(j = startPos; j < i; j++)
						student_m[j].erase_p();
				startPos = -1;
			}
	}
	if(startPos != -1)
		for(j = startPos; j < n; j++)
			student_m[j].erase_p();
	k = 0;
	for(i = 0; i < n; i++){
		if(student_m[i].is_empty())
			k++;
		else
			student_m[i - k] = (student&&)student_m[i];
	}
	return n - k;
}
