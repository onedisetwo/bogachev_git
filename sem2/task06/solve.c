#include "solve.h"

#define ABS(a) (a < 0 ? -a : a)
#define SQ(a) a * a

void delete_col(double *a, int m, int n, int col){
	int i, j, k;
	k = 1;
	// col numeration starts from 0
	for(i = col + 1; i < m * n; i++, k++){
		for(j = 1; j < n; j++, i++)
			a[i - k] = a[i];
	}
}

void delete_col_line(double *a, int m, int n, int col, int line){
	int i, j, k;
	k = 1;
	i = col + 1;
	if(line != 0){
		for( ; ; i++, k++){
			for(j = 1; j < n; j++, i++){
				if(i >= line * n)
					break;
				a[i - k] = a[i];
			}
			if(i >= line * n)
				break;
		}
		i += n;
	}
	else{
		for(i = n; i < n + col; i++){
			a[i - n] = a[i];
		}
		i++;
		j = 1;
	}
	k += n;
	for(; i < m * n; i++, k++){
		for(; j < n && i < m * n; j++, i++)
			a[i - k] = a[i];
		j = 1;
	}
}

int search1_2(double *a, int m, int n){
	int i, res = 0;
	double k = a[0], temp;
	for(i = 1; i < n*m; i++){
		temp = a[i];
		temp = ABS(temp);
		if(temp < k){
			k = temp;
			res = i;
		}
	}
	return res;
}

int solve1(double *a, int m, int n){
	int col, num;
	num = search1_2(a, n, m);
	col = num - (num / n) * n;
	delete_col(a, m, n, col);
	return col + 1;
}

int solve2(double *a, int m, int n){
	int col, line, num;
	num = search1_2(a, n, m);
	line = num / n;
	col = num - line * n;
	delete_col_line(a, m, n, col, line);
	return num;
}

double get_col_abs_summ(double *a, int m, int n, int col){
	int i;
	double temp, tempS;
	tempS = 0;
	for(i = 0; i < m; i++){
		temp = a[i*n + col];
		tempS += ABS(temp);
	}
	return tempS;
}

double get_line_abs_summ(double *a, int m, int n, int line){
	int j;
	double temp, tempS;
	(void)m;
	tempS = 0;
	for(j = 0; j < n; j++){
		temp = a[line*n + j];
		tempS += ABS(temp);
	}
	return tempS;
}

int search3(double *a, int m, int n){
	int j, res;
	double k, tempS;
	k = get_col_abs_summ(a, m, n, 0);
	res = 0;
	for(j = 1; j < n; j++){
		tempS = get_col_abs_summ(a, m, n, j);
		if(tempS < k){
			res = j;
			k = tempS;
		}
	}
	return res;
}

int solve3(double *a, int m, int n){
	int col, num;
	num = search3(a, m, n);
	col = num - (num / n) * n;
	delete_col(a, m, n, col);
	return col + 1;
}

int search4(double *a, int m, int n){
	int i, j, nLine, nCol;
	double tempS, sLine, sCol;
	sCol = get_col_abs_summ(a, m, n, 0);
	nCol = 0;
	for(j = 1; j < m; j++){
		tempS = get_col_abs_summ(a, m, n, j);
		if(tempS < sCol){
			sCol = tempS;
			nCol = j;
		}
	}
	sLine = get_line_abs_summ(a, m, n, 0);
	nLine = 0;
	for(i = 1; i < m; i++){
		tempS = get_line_abs_summ(a, m, n, i);
		if(tempS < sLine){
			sLine = tempS;
			nLine = i;
		}
	}
	return nLine * n + nCol;
}

int solve4(double *a, int m, int n){
	int col, line, num;
	num = search4(a, m, n);
	line = num / n;
	col = num - line * n;
	delete_col_line(a, m, n, col, line);
	return num;
}

int search5(double *a, int m, int n){
	int i, j, res;
	double maxS, minEl, temp, tempS;
	maxS = 0;
	res = 0;
	for(j = 0; j < n; j++){
		minEl = a[j];
		minEl = ABS(minEl);
		tempS = minEl;
		for(i = 1; i < m; i++){
			temp = a[i*n + j];
			temp = ABS(temp);
			if(temp < minEl)
				minEl = temp;
			tempS += temp;
		}
		tempS -= minEl;
		if(tempS > maxS){
			res = j;
			maxS = tempS;
		}
	}
	return res;
}

int solve5(double *a, int m, int n){
	int col, num;
	num = search5(a, m, n);
	col = num - (num / n) * n;
	delete_col(a, m, n, col);
	return col + 1;
}

int search6(double *a, int m, int n){
	int i, j, res, size;
	double diagTemp, temp, tempS, maxS;
	size = (n > m ? m : n);
	maxS = 0;
	res = 0;
	for(j = 0; j < size; j++){
		diagTemp = a[j*n + j];
		tempS = 0;
		for(i = 0; i < m; i++){
			temp = a[i*n + j] - diagTemp;
			tempS += ABS(temp);
		}
		if(tempS > maxS){
			maxS = tempS;
			res = j;
		}
	}
	return res;
}

int solve6(double *a, int m, int n){
	int col, num;
	num = search6(a, m, n);
	col = num - (num / n) * n;
	delete_col(a, m, n, col);
	return col + 1;
}

double get_col_norm7_10(double *a, int m, int n, int col){
	int i;
	double temp, colS = 0, tempS = 0;
	for(i = 0; i < m; i++)
		colS += a[i*n + col];
	colS /= (double)m;
	for(i = 0; i < m; i++){
		temp = a[i*n + col];
		tempS += SQ(temp - colS);
	}
	return tempS;
}

int search7(double *a, int m, int n){
	int j, res;
	double tempS, minS;
	res = 0;
	minS = get_col_norm7_10(a, m, n, 0);
	for(j = 1; j < n; j++){
		tempS = get_col_norm7_10(a, m, n, j);
		if(tempS < minS || minS < 0){
			minS = tempS;
			res = j;
		}
	}
	return res;
}

int solve7(double *a, int m, int n){
	int col, num;
	num = search7(a, m, n);
	col = num - (num / n) * n;
	delete_col(a, m, n, col);
	return col + 1;
}

int search8(double *a, int m, int n){
	int i, j, res;
	double maxS, lineS, colS, tempS, veryBadEl;
	maxS = 0;
	res = 0;
	for(j = 0; j < n; j++){
		colS = get_col_abs_summ(a, m, n, j);
		for(i = 0; i < m; i++){
			veryBadEl = a[i*n + j];
			lineS = get_line_abs_summ(a, m, n, i);
			tempS = colS + lineS - 2 * ABS(veryBadEl);
			if(tempS > maxS){
				maxS = tempS;
				res = i*n + j;
			}
		}
	}
	return res;
}

int solve8(double *a, int m, int n){
	int col, line, num;
	num = search8(a, m, n);
	line = num / n;
	col = num - line * n;
	delete_col_line(a, m, n, col, line);
	return num;
}

int search9(double *a, int m, int n){
	int i, j, h, res;
	double temp, maxS, lineS, colS, tempS, veryBadEl;
	maxS = 0;
	res = 0;
	for(j = 0; j < n; j++){
		for(i = 0; i < m; i++){
			veryBadEl = a[i*n + j];
			colS = 0;
			for(h = 0; h < m; h++){
				temp = a[h*n + j];
				colS += ABS(temp - veryBadEl);
			}
			lineS = 0;
			for(h = 0; h < n; h++){
				temp = a[i*n + j];
				lineS += ABS(temp - veryBadEl);
			}
			tempS = colS + lineS;
			if(tempS > maxS){
				maxS = tempS;
				res = i*n + j;
			}
		}
	}
	return res;
}

int solve9(double *a, int m, int n){
	int col, line, num;
	num = search9(a, m, n);
	line = num / n;
	col = num - line * n;
	delete_col_line(a, m, n, col, line);
	return num;
}

double get_line_norm7_10(double *a, int m, int n, int line){
	int j;
	double temp, lineS = 0, tempS = 0;
	(void)m;
	for(j = 0; j < n; j++)
		lineS += a[line*n + j];
	lineS /= (double)n;
	for(j = 0; j < n; j++){
		temp = a[line*n + j];
		tempS += SQ(temp - lineS);
	}
	return tempS;
}

int search10(double *a, int m, int n){
	int i, j, res;
	double minS, tempS;
	res = 0;
	minS = get_col_norm7_10(a, m, n, 0) + get_line_norm7_10(a, m, n, 0);
	for(i = 0; i < m; i++)
		for(j = 0; j < n; j++){
			tempS = get_col_norm7_10(a, m, n, j) + get_line_norm7_10(a, m, n, i);
			if(tempS < minS){
				minS = tempS;
				res = i*n + j;
			}
		}
	return res;
}

int solve10(double *a, int m, int n){
	int col, line, num;
	num = search10(a, m, n);
	line = num / n;
	col = num - line * n;
	delete_col_line(a, m, n, col, line);
	return num;
}
