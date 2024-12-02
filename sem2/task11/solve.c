#include "solve.h"
#include "errors.h"
#include <stdio.h>
#include <math.h>

#define EPS 1e-16
#define EQUAL_D(a, b, eps) (fabs(a - b) <= eps * fabs(a + b))

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

int solve1(double x, double h, double (*f)(double), double *res){
	double der;
	const double eps = get_eps();
	if(fabs(h) < eps)
		return DIVISION_BY_ZERO;
	der = (f(x + h) - f(x)) / h;
	*res = der;
	return SUCCESS;
}

int solve2(double x, double h, double (*f)(double), double *res){
	double der;
	const double eps = get_eps();
	if(fabs(h) < eps)
		return DIVISION_BY_ZERO;
	der = 0.5 * (f(x + h) - f(x - h)) / h;
	*res = der;
	return SUCCESS;
}

int solve3(double x, double h, double (*f)(double), double *res){
	double der2;
	const double eps = get_eps();
	if(fabs(h * h) < eps)
		return DIVISION_BY_ZERO;
	der2 = (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
	*res = der2;
	return SUCCESS;
}

int solve4(double a, double b, int n, double (*f)(double), double *res){
	const double h = (b - a) / (double)n;
	double riem_sum;
	int k;
	riem_sum = 0.5 * h * (f(a) + f(b));
	for(k = 1; k < n; k++){
		riem_sum += h * f(a + k * h);
	}
	*res = riem_sum;
	return SUCCESS;
}

int solve5(double a, double b, int n, double (*f)(double), double *res){
	const double h = 0.5 * (b - a) / (double)n;
	double riem_sum;
	int k;
	riem_sum = h * (f(a) + f(b) + 4 * f(a + h)) / 3.;
	for(k = 1; k < n; k++){
		riem_sum += (2./3.) * h * (f(a + 2*k*h) + 2 * f(a + (2*k+1)*h));
	}
	*res = riem_sum;
	return SUCCESS;
}

double sign(double x){
	return (x < 0 ? -1 : 1);
}

int solve6(double a, double b, int n, double (*f)(double), double *res){
	const double h = (b - a) / (double)n;
	double sum, fx_curr, fx_next, tmp_curr, tmp_next, x, c1, c2, diff1, diff2;
	int k;
	x = a;
	sum = 0;
	tmp_curr = sqrt(fabs(x)) * sign(x);
	fx_curr = f(x);
	for(k = 0; k < n; k++, x += h){
		fx_next = f(x + h);
		tmp_next = sqrt(fabs(x+h)) * sign(x+h);

		c2 = (fx_next - fx_curr) / h;
		c1 = fx_curr - c2 * x;
		diff1 = 2 * tmp_next - 2 * tmp_curr;
		diff2 = (2./3.) * (sqrt(fabs(x+h)) * fabs(x+h) - sqrt(fabs(x)) * fabs(x));
		sum += c1 * diff1 + c2 * diff2;

		fx_curr = fx_next;
		tmp_curr = tmp_next;
	}
	*res = sum;
	return SUCCESS;
}

// can divide by zero
double get_lagr2(double fx[2], double diff){
	return (fx[1] - fx[0]) / diff;
}

// can divide by zero
// x1 - x0 = x2 - x1
double get_lagr3(double fx[3], double diff){
	return 0.5 * (fx[2] - 2*fx[1] + fx[0]) / (diff * diff);
}

int solve7(double a, double b, int n, double (*f)(double), double *res){
	const double h = 0.5 * fabs(b - a) / (double)n;
	double sum, l1, l2, l3, c1, c2, c3, x, x1_tmp, x2_tmp, diff1, diff2, diff3;
	double fx[3];
	int k;
	x = a;
	sum = 0;
	fx[0] = f(x);
	for(k = 0; k < n - 1; k++){
		fx[1] = f(x + h);
		fx[2] = f(x + 2*h);
		l1 = fx[0];
		l2 = get_lagr2(fx, h);
		l3 = get_lagr3(fx, h);
		c1 = l3;
		c2 = l2 - l3 * (2*x + h);
		c3 = l1 - l2 * x + l3 * x * (x + h);
		x1_tmp = sqrt(fabs(x)) * sign(x);
		x2_tmp = sqrt(fabs(x + 2*h)) * sign(x + 2*h);
		diff3 = 2. * (x2_tmp - x1_tmp);
		diff2 = (2. / 3.) * (x2_tmp * (x + 2*h) - x1_tmp * x);
		diff1 = (2. / 5.) * (x2_tmp * (x + 2*h) * (x + 2*h) - x1_tmp * x * x);
		sum += c1 * diff1 + c2 * diff2 + c3 * diff3;

		fx[0] = fx[2];
		x += 2*h;
	}
	*res = sum;
	return SUCCESS;
}

int solve8(double a, double b, const double eps, double (*f)(double), double *res, int *it){
	double sum_curr, sum_next, h;
	int k, n = 4, count = 2;
	h = fabs(b - a) / n;
	sum_curr = 0.5 * h * (f(a) + f(b));
	for(k = 1; k < n; k++){
		sum_curr += h * f(a + (double)(k) * h);
	}
	sum_next = 0.5 * sum_curr;
	for(k = 0; k < n; k++){
		sum_next += 0.5 * h * f(a + 0.5 * (double)(2*k + 1) * h);
	}
	while(fabs(sum_next - sum_curr) >= eps){
		if(count >= 31){
			*it = -1;
			*res = 0;
			return SUCCESS;
		}
		n *= 2;
		h /= 2;
		sum_curr = sum_next;
		sum_next = 0.5 * sum_curr;
		for(k = 0; k < n; k++){
			sum_next += 0.5 * h * f(a + 0.5 * (double)(2*k + 1) * h);
		}
		count++;
	}
	*it = 2*n;
	*res = sum_next;
	return SUCCESS;
}

int solve9(double a, double b, const double eps, double (*f)(double), double *res, int *it){
	double sum_curr1, sum_curr2, sum_next1, sum_next2, h;
	int k, n = 4, count = 2;
	h = 0.5 * fabs(b - a) / (double)(n);
	sum_curr1 = h * (f(a) + f(b)) / 3.;
	sum_curr2 = 2./3. * h * f(a + h);
	for(k = 1; k < n; k++){
		sum_curr1 += 2./3. * h * f(a + 2*k * h);
		sum_curr2 += 2./3. * h * f(a + (2*k + 1) * h);
	}
	sum_next1 = 0.5 * (sum_curr1 + sum_curr2);
	sum_next2 = 0;
	for(k = 0; k < 2*n; k++){
		sum_next2 += 1./3. * h * f(a + (2*k + 1) * 0.5 * h);
	}
	while(fabs(sum_next1 + 2*sum_next2 - sum_curr1 - 2*sum_curr2) >= eps){
		n *= 2;
		if(count >= 31){
			*it = -1;
			*res = 0;
			return SUCCESS;
		}
		h /= 2;
		sum_curr1 = sum_next1;
		sum_curr2 = sum_next2;
		sum_next1 = 0.5 * (sum_curr1 + sum_curr2);
		sum_next2 = 0;
		for(k = 0; k < 2*n; k++){
			sum_next2 += 1./3. * h * f(a + (2*k + 1) * 0.5 * h);
		}
		count++;
	}
	*it = 2*n;
	*res = sum_next1 + 2 * sum_next2;
	return SUCCESS;
}

int solve10(double a, const double eps, double (*f)(double), double *res, double *b){
	double val_curr, val_next, sum, h;
	int temp, ret, count = 1;
	h = 1;
	ret = solve8(a, a + h, eps, f, &val_curr, &temp);
	if(ret != SUCCESS)
		return ret;
	a += h;
	h *= 2;
	ret = solve8(a, a + h, eps, f, &val_next, &temp);
	if(ret != SUCCESS)
		return ret;
	sum = val_curr + val_next;
	while(fabs(val_next) >= eps){
		val_curr = val_next;
		a += h;
		h *= 2;
		ret = solve8(a, a + h, eps, f, &val_next, &temp);
		if(ret != SUCCESS)
			return ret;
		sum += val_next;
		count++;
		if(count >= 31){
			*b = -1;
			*res = 0;
			return SUCCESS;
		}
	}
	*b = a + h;
	*res = sum;
	return SUCCESS;
}

int solve11(double a, const double eps, double (*f)(double), double *res, double *b){
	double val_curr, val_next, sum, h;
	int temp, ret, count = 1;
	h = 1;
	ret = solve9(a, a + h, eps, f, &val_curr, &temp);
	if(ret != SUCCESS)
		return ret;
	a += h;
	h *= 2;
	ret = solve9(a, a + h, eps, f, &val_next, &temp);
	if(ret != SUCCESS)
		return ret;
	sum = val_curr + val_next;
	while(fabs(val_next) >= eps){
		val_curr = val_next;
		a += h;
		h *= 2;
		ret = solve9(a, a + h, eps, f, &val_next, &temp);
		if(ret != SUCCESS)
			return ret;
		sum += val_next;
		count++;
		if(count >= 31){
			*b = -1;
			*res = 0;
			return SUCCESS;
		}
	}
	*b = a + h;
	*res = sum;
	return SUCCESS;
}

double get_length(double x1, double y1, double x2, double y2){
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int solve12(double a, double b, const double eps, double (*fx)(double), double (*fy)(double),
		double *res, int *it){
	double sum_curr, sum_next, x1, y1, x2, y2, h;
	int k, n = 2;
	h = fabs(b - a) / (double)(n);
	x1 = fx(a);
	y1 = fy(a);
	x2 = fx(b);
	y2 = fy(b);
	sum_curr = get_length(x1, y1, x2, y2);
	n *= 2;
	h /= 2;
	sum_next = 0;
	x1 = fx(a);
	y1 = fy(a);
	for(k = 1; k <= n; k++){
		x2 = fx(a + k*h);
		y2 = fy(a + k*h);
		sum_next += get_length(x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
	}
	while(fabs(sum_next - sum_curr) >= eps){
		sum_curr = sum_next;
		n *= 2;
		h /= 2;
		sum_next = 0;
		x1 = fx(a);
		y1 = fy(a);
		for(k = 1; k <= n; k++){
			x2 = fx(a + k*h);
			y2 = fy(a + k*h);
			sum_next += get_length(x1, y1, x2, y2);
			x1 = x2;
			y1 = y2;
		}
	}
	*it = 2*n;
	*res = sum_next;
	return SUCCESS;
}

// problem 2 in task09
int lagrange_interpolation(const double x0, double *x, double *y, int n, double *res){
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
