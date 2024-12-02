#include "solve.h"
#include "matrix.h"

#define abs(a) (a < 0 ? -a : a)
#define max(a, b) (a < b ? b : a)

double solve1(double *a, int n, int m){
	int i, j;
	double res = 0, sum;
	for(i = 0; i < n; i++){
		sum = 0;
		for(j = 0; j < m; j++)
			sum += abs(a[i*m + j]);
		res = (sum > res ? sum : res);
	}
	return res;
}

double solve2(double *a, int n, int m){
	int i, j;
	double res = 0, sum;
	for(j = 0; j < m; j++){
		sum = 0;
		for(i = 0; i < n; i++)
			sum += abs(a[i*m + j]);
		if(res < sum)
			res = sum;
	}
	return res;
}

double solve3(double *a, double *x, double *b, int n, int m){
	int i, j;
	double res = 0, sum;
	for(i = 0; i < n; i++){
		sum = 0;
		for(j = 0; j < m; j++)
			sum += a[i*m + j] * x[j];
		sum -= b[i];
		res += abs(sum);
	}
	return res;
}

double solve4(double *a, double *x, double *b, int n, int m){
	int i, j;
	double res = 0, sum;
	for(i = 0; i < n; i++){
		sum = 0;
		for(j = 0; j < m; j++)
			sum += a[i*m + j] * x[j];
		sum -= b[i];
		if(sum < 0)
			sum = -sum;
		if(res < sum)
			res = sum;
	}
	return res;
}

double solve5(double *a, double *b, int n, int m){
	int i, j;
	double res = 0, sum;
	for(i = 0; i < n; i++){
		sum = 0;
		for(j = 0; j < m; j++)
			sum += a[i*m + j] * b[j*n + i];
		sum -= 1;
		res += abs(sum);
	}
	return res;
}

double solve6(double *a, double *b, int n, int m){
	int i, j;
	double res = 0, sum;
	for(i = 0; i < n; i++){
		sum = 0;
		for(j = 0; j < m; j++)
			sum += a[i*m + j] * b[j*n + i];
		sum -= 1;
		if(sum < 0)
			sum = -sum;
		if(res < sum)
			res = sum;
	}
	return res;
}

double solve7(double *a, int n, int m){
	int i, j;
	double temp, res = 0;
	for(j = 0; j < m; j++){
		temp = a[j];
		res = max(res, abs(temp));
	}
	for(i = 1; i < n - 1; i++){
		temp = a[i*m];
		res = max(res, abs(temp));
		for(j = 1; j < m - 1; j++){
			temp = a[i*m + j] = 0.2 * (a[(i-1)*m + j] +
				a[(i+1)*m + j] + temp + a[i*m + j+1]);
			res = max(res, abs(temp));
		}
		temp = a[i*m + j];
		res = max(res, abs(temp));
	}
	for(j = 0; j < m; j++){
		temp = a[i*m + j];
		res = max(res, abs(temp));
	}
	return res;
}

double solve8(double *a, int n, int m){
	int i, j;
	double temp, res = 0;
	for(j = 0; j < m; j++){
		temp = a[(n-1)*m + j];
		res = max(res, abs(temp));
	}
	for(i = n - 2; i > 0; i--){
		temp = a[i*m + m - 1];
		res = max(res, abs(temp));
		for(j = m - 2; j > 0; j--){
			temp = a[i*m + j] = 0.2 * (a[(i-1)*m + j] +
				a[(i+1)*m + j] + a[i*m + j-1] + temp);
			res = max(res, abs(temp));
		}
		temp = a[i*m + j];
		res = max(res, abs(temp));
	}
	for(j = 0; j < m; j++){
		temp = a[j];
		res = max(res, abs(temp));
	}
	return res;
}

double solve9(double *a, int n, int m){
	int i, j;
	double temp, res = 0;
	for(j = 0; j < m; j++){
		temp = a[j];
		res = max(res, abs(temp));
	}
	for(i = 1; i < n - 1; i++){
		temp = a[i*m + m-1];
		res = max(res, abs(temp));
		for(j = m - 2; j > 0; j--){
			temp = a[i*m + j] = 0.2 * (a[(i-1)*m + j] +
				a[(i+1)*m + j] + a[i*m + j-1] + temp);
			res = max(res, abs(temp));
		}
		temp = a[i*m + j];
		res = max(res, abs(temp));
	}
	for(j = 0; j < m; j++){
		temp = a[i*m + j];
		res = max(res, abs(temp));
	}
	return res;
}

double solve10(double *a, int n, int m){
	int i, j;
	double temp, res = 0;
	for(j = 0; j < m; j++){
		temp = a[(n-1)*m + j];
		res = max(res, abs(temp));
	}
	for(i = n - 2; i > 0; i--){
		temp = a[i*m];
		res = max(res, abs(temp));
		for(j = 1; j < m - 1; j++){
			temp = a[i*m + j] = 0.2 * (a[(i-1)*m + j] +
				a[(i+1)*m + j] + temp + a[i*m + j+1]);
			res = max(res, abs(temp));
		}
		temp = a[i*m + j];
		res = max(res, abs(temp));
	}
	for(j = 0; j < m; j++){
		temp = a[j];
		res = max(res, abs(temp));
	}
	return res;
}

double solve11(double *a, int n, int m){
	int i, rPos = 0;
	double temp, res = 0;
	for(i = 0; i < n * m; i++){
		temp = a[i];
		if(temp < 0)
			temp = -temp;
		if(temp > res){
			res = max(res, temp);
			rPos = i;
		}
	}
	swap_lines(a, n, m, 0, i = rPos/m);
	swap_columns(a, n, m, 0, rPos - i*m);
	return res;
}
