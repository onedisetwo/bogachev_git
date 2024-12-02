#include "solve.h"
#include "errors.h"
#include <stdio.h>
#include <math.h>

#define EPS 1e-16
//#define ABS(a) ((a) < 0 ? -(a) : (a))
#define EQUAL_D(a, b) (fabs(a - b) < EPS * fabs(a + b))
//#define EQUAL_ZERO(a) (ABS((a)) < EPS)

#define SWAP(a, b, temp) \
	temp = a; \
	a = b; \
	b = temp; \

double get_eps(void){
	double eps = 1.;
	while(eps + 1. > 1.)
		eps /= 2.;
	return eps;
}

int solve1(const double x0, double *x, double *y, int n, double *res){
	int i, j;
	double br, sum, tmp1, tmp2;
	const double eps = get_eps();
	sum = 0;
	for(i = 0; i < n; i++){
		br = 1;
		tmp1 = x[i];
		for(j = 0; j != i; j++){
			tmp2 = x[j];
			if(fabs(tmp1 - tmp2) < eps)
				return ERROR_INPUT;
			br *= (x0 - tmp2) / (tmp1 - tmp2);
		}
		for(j = i + 1; j < n; j++){
			tmp2 = x[j];
			if(fabs(tmp1 - tmp2) < eps)
				return ERROR_INPUT;
			br *= (x0 - tmp2) / (tmp1 - tmp2);
		}
		br *= y[i];
		sum += br;
	}
	*res = sum;
	return SUCCESS;
}

int solve2(const double x0, double *x, double *y, int n, double *res){
	int i, j, k;
	double br, sum, tmp1, num, den;
	const double eps = get_eps();
	sum = 0;
	for(i = 0; i < n; i++){
		tmp1 = y[n - 1];
		for(j = n - 1; j > i; j--){
			num = tmp1;
			tmp1 = y[j - 1];
			num -= tmp1;
			den = x[j] - x[j - i - 1];
			if(fabs(den) < eps)
				return ERROR_INPUT;
			y[j] = num / den;
		}
	}
	br = 1;
	sum = y[0];
	for(k = 1; k < n; k++){
		br *= (x0 - x[k - 1]);
		sum += br * y[k];
	}
	*res = sum;
	return SUCCESS;
}


int solve3(const double x0, double *x, double *y, int n, double *res){
	int i, j;
	double tmp1, num, den;
	const double eps = get_eps();
	for(i = 0; i < n; i++){
		tmp1 = y[0];
		for(j = 1; j < n - i; j++){
			num = -tmp1 * (x0 - x[j + i]);
			tmp1 = y[j];
			num += tmp1 * (x0 - x[j - 1]);
			den = x[j + i] - x[j - 1];
			if(fabs(den) < eps)
				return ERROR_INPUT;
			y[j - 1] = num / den;
		}
	}
	*res = y[0];
	return SUCCESS;
}


#define YD_EL(l) ((l)%2 == 0 ? y[(l)/2] : d[(l)/2])

int solve4(const double x0, double *x, double *y, double *d, int n, double *res){
	int i, j, k;
	double tmp1, num, den, br, sum;
	const double eps = get_eps();
	tmp1 = y[0];
	for(i = 1; i < n; i++){
		num = -tmp1;
		tmp1 = y[i];
		num += tmp1;
		den = x[i] - x[i - 1];
		if(fabs(den) < eps)
			return ERROR_INPUT;
		y[i] = num / den;
	}
	for(i = 2; i < 2*n; i++){
		tmp1 = YD_EL(i - 1);
		for(j = i; j < 2*n; j++){
			num = -tmp1;
			tmp1 = YD_EL(j);
			num += tmp1;
			den = x[j/2] - x[j/2 - (i%2 == 0 ? i/2 : i/2 + (j+1)%2)];
			if(fabs(den) < eps)
				return ERROR_INPUT;
			if(j%2 == 0)
				y[j/2] = num / den;
			else
				d[j/2] = num / den;
		}
	}
	br = 1;
	sum = YD_EL(0);
	for(k = 1; k < 2*n; k++){
		br *= (x0 - x[(k-1)/2]);
		sum += br * YD_EL(k);
	}
	*res = sum;
	return SUCCESS;
}


double m_sin(double x, double eps){
	int k;
	double coef = 1, a, res;
	if(x < 0){
		x = -x;
		coef *= (-1);
	}
	x = fmod(x, 2 * M_PI);
	if(x > M_PI){
		x -= M_PI;
		coef *= (-1);
	}
	if(x > M_PI/2){
		x -= M_PI/2;
		return coef * m_cos(x, eps);
	}
	if(x > 1){
		x *= 0.5;
		a = x;
		res = x;
		for(k = 1; fabs(a) > eps; k++){
			a *= -x * x / ((double)(2*k) * (double)(2*k + 1));
			res += a;
		}
		return 2. * coef * res * m_cos(x, eps);
	}
	else{
		a = x;
		res = x;
		for(k = 1; fabs(a) > eps; k++){
			a *= -x * x / ((double)(2*k) * (double)(2*k + 1));
			res += a;
		}
		return coef * res;
	}
}

double m_cos(double x, double eps){
	int k;
	double coef = 1, a, res;
	x = fmod(fabs(x), 2 * M_PI);
	if(x > M_PI){
		x -= M_PI;
		coef *= (-1);
	}
	if(x > M_PI/2){
		x -= M_PI/2;
		coef *= (-1);
		return coef * m_sin(x, eps);
	}
	a = 1;
	res = 1;
	if(x > 1){
		x *= 0.5;
		for(k = 1; fabs(a) > eps; k++){
			a *= -x * x / ((double)(2*k - 1)*(double)(2*k));
			res += a;
		}
		return coef * (2 * res * res - 1.);
	}
	else{
		for(k = 1; fabs(a) > eps; k++){
			a *= -x * x / ((double)(2*k - 1)*(double)(2*k));
			res += a;
		}
		return coef * res;
	}
}

double m_exp(double x, double eps){
	double a, res, mult;
	int k, is_negative;
	res = 1;
	if(x < 0){
		x = -x;
		is_negative = 1;
	}
	else
		is_negative = 0;
	mult = 1;
	for(k = 1; k < x || EQUAL_D(k, x); k++){
		mult *= M_E;
	}
	x = fmod(x, 1);
	res = 1;
	a = 1;
	for(k = 1; a > eps; k++){
		a *= (x / (double)k);
		res += a;
	}
	res *= mult;
	if(is_negative == 0)
		return res;
	else
		return 1. / res;
}

int m_log(double x, double eps, double *ans){
	double a, res;
	int k, p;
	if(x < 0 || !isfinite(x) || fabs(x) < EPS)
		return ERROR_INPUT;
	p = 0;
	while(x >= 2){
		x /= (double)2;
		p++;
	}
	x -= 1;
	res = x;
	a = x;
	for(k = 2; a/k > eps; k++){
		a *= -x;
		res += a / k;
	}
	*ans = res + p * M_LN2;
	return SUCCESS;
}
