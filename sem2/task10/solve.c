#include "solve.h"
#include "errors.h"
#include <stdio.h>
#include <math.h>

#define EPS 1e-16
//#define ABS(a) ((a) < 0 ? -(a) : (a))
#define EQUAL_D(a, b, eps) (fabs(a - b) <= eps * fabs(a + b))
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

int solve1(double a, double b, double eps, int MaxIt, double (*f)(double), double *x){
	double c, f_c, f_a = (*f)(a), f_b = (*f)(b);
	int it_count = 1;
	c = (a + b) / 2;
	f_c = (*f)(c);
	if(f_a * f_b > 0)
		return -1;
	while(!(fabs(f_c) < eps) && it_count < MaxIt){
		if(f_c * f_a < 0){
			b = c;
			f_b = f_c;
		}
		else if(f_c * f_b < 0){
			a = c;
			f_a = f_c;
		}
		c = (a + b) / 2;
		f_c = (*f)(c);
		it_count++;
	}
	if(it_count < MaxIt){
		*x = c;
		return it_count;
	}
	else
		return -2;
}

int solve2(double x0, double eps, int MaxIt, double (*f)(double), double (*d)(double), double *x_s){
	double f_x = (*f)(x0), d_x = (*d)(x0), comp_eps = get_eps(), x;
	int it_count = 0;
	x = x0;
	while(!(fabs(f_x) < eps) && it_count < MaxIt){
		if(fabs(d_x) < comp_eps)
			return -3;
		x = x - f_x / d_x;
		f_x = (*f)(x);
		d_x = (*d)(x);
		it_count++;
	}

	if(it_count < MaxIt){
		*x_s = x;
		return it_count;
	}
	else
		return -2;
}

int solve3(double a, double b, double eps, int MaxIt, double (*f)(double), double *x){
	double c, f_a = (*f)(a), f_b = (*f)(b), f_c;
	int it_count = 0;
	if(f_a * f_b > 0)
		return -1;
	c = a - (b-a) * f(a) / (f(b)-f(a));
	f_c = (*f)(c);
	while(!(fabs(f_c) < eps) && it_count < MaxIt){
		if(f_c * f_a < 0){
			b = c;
			f_b = f_c;
		}
		else if(f_c * f_b < 0){
			a = c;
			f_a = f_c;
		}
		c = a - (b-a) * f_a / (f_b-f_a);
		f_c = (*f)(c);
		it_count++;
	}
	if(it_count < MaxIt){
		*x = c;
		return it_count;
	}
	else
		return -2;
}

int solve4(double a, double b, double eps, int MaxIt, double (*f)(double), double *x){
	double c, f_a = (*f)(a), f_b = (*f)(b), f_c;
	int it_count = 0;
	c = a - (b-a) * f(a) / (f(b)-f(a));
	f_c = (*f)(c);
	while(!(fabs(f_c) < eps) && it_count < MaxIt){
		//if(!(fabs(f_c) < fabs(f_a) || fabs(f_c) < fabs(f_b)))
		//	return -1;
		if(fabs(f_a) > fabs(f_b)){
			a = c;
			f_a = f_c;
		}
		else{
			b = c;
			f_b = f_c;
		}
		if(fabs(f_b - f_a) <= EPS)
			return DIVISION_BY_ZERO;
		c = a - (b-a) * f_a / (f_b - f_a);
		f_c = (*f)(c);
		it_count++;
	}
	if(it_count < MaxIt){
		*x = c;
		return it_count;
	}
	else
		return -2;
}

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

int solve5(double a, double b, double eps, int MaxIt, double (*f)(double), double *x_s){
	int it_count = 0;
	double fx[3], x2_copy, x[3], temp, ftemp;
	x[0] = a;
	x[2] = b;
	fx[0] = f(x[0]);
	fx[2] = f(x[2]);
	temp = (a + b) / 2.;
	ftemp = f(temp);
	while(fabs(ftemp) >= eps && it_count < MaxIt){
		x[1] = (x[0] + x[2]) / 2;
		fx[1] = f(x[1]);
		x2_copy = x[2];
		if(lagrange_interpolation(0, fx, x, 3, &temp) != SUCCESS)
			return -1;
		x[2] = x2_copy;
		ftemp = f(temp);
		if(fabs(ftemp) > fabs(fx[0]) && fabs(ftemp) > fabs(fx[2]))
			return -1;
		if(fabs(fx[0]) > fabs(fx[2]) && fabs(fx[0]) > fabs(ftemp)){
			fx[0] = ftemp;
			x[0] = temp;
			continue;
		}
		else{
			fx[2] = ftemp;
			x[2] = temp;
		}
		it_count++;
	}
	if(it_count < MaxIt){
		*x_s = temp;
		return it_count;
	}
	else
		return -2;
}

int solve6(double a, double b, double eps, int MaxIt, int m, double *d, double (*f)(double), double *x_s){
	int it_count = 0, k;
	double temp, ftemp;
	double h;
	d[0] = a;
	d[m + 1] = a;
	d[2*(m + 1)] = f(a);
	d[m] = b;
	d[m + m+1] = b;
	d[m + 2*(m+1)] = f(b);
	temp = (a + b) / 2;
	ftemp = f(temp);
	while(fabs(ftemp) >= eps && it_count < MaxIt){
		h = fabs(d[m] - d[0]) / m;
		for(k = 1; k < m; k++){
			d[k] = d[0] + h * k;
			d[k + m+1] = d[0] + h * k;
			d[k + 2 * (m+1)] = f(d[0] + h * k);
		}
		if(lagrange_interpolation(0, d + 2*(m+1), d + m+1, m + 1, &temp) != SUCCESS)
			return -1;
		ftemp = f(temp);
		if(fabs(ftemp) > fabs(d[2*(m+1)]) && fabs(ftemp) > fabs(d[2*(m+1) + m]))
			return -1;
		if(fabs(d[2*(m+1)]) > fabs(d[2*(m+1) + m]) && fabs(d[2*(m+1)]) > fabs(ftemp)){
			d[2*(m+1)] = ftemp;
			d[0] = temp;
			d[m + 1] = temp;
			continue;
		}
		else{
			d[2*(m+1) + m] = ftemp;
			d[m] = temp;
			d[m + 1 + m] = temp;
		}
		it_count++;
	}
	if(it_count < MaxIt){
		*x_s = temp;
		return it_count;
	}
	else
		return -2;
}

int solve7(double x0, double eps, int MaxIt, double (*f)(double), double *x_s){
	double x;
	int it_count = 0;
	x = (*f)(x0);
	while(!(fabs(x0 - x) < eps) && it_count < MaxIt){
		x0 = x;
		x = (*f)(x0);
		it_count++;
	}

	if(it_count < MaxIt){
		*x_s = x0 - x;
		return it_count;
	}
	else
		return -2;
}

int solve8(double a, double b, double eps, int MaxIt, double (*f)(double), double *x_max){
	double x, h, f_prev, f_new; //comp_eps = get_eps();
	int it_count = 1;
	const double CONST_DIVISOR = 10;
	f_prev = (*f)(a);
	h = (b - a) / CONST_DIVISOR;
	x = a + h;
	f_new = (*f)(x);
	while(!(fabs(h) < eps) && it_count < MaxIt){
		if(f_new < f_prev/* || fabs(f_new - f_prev) < comp_eps*/)
			h /= -CONST_DIVISOR;
		f_prev = f_new;
		if(x + h > b || x + h < a)
			break;
		//while(x + h > b)
		//	h /= CONST_DIVISOR;
		x += h;
		f_new = (*f)(x);
		it_count++;
	}
	if(it_count < MaxIt){
		if((*f)(b) > f_new)
			*x_max = b;
		else
			*x_max = x;
		return it_count;
	}
	else
		return -2;
}

int solve9(double a, double b, double eps, int MaxIt, double (*f)(double), double *x_max){
	double x1, x2, f_1, f_2, f_a, f_b, bc = b;
	int it_count = 1, flag = 0;
	const double GOLDEN_RATIO = (1 + sqrt(5)) / 2;
	f_a = (*f)(a);
	f_b = (*f)(b);
	(void)f_a; (void)f_b;
	x1 = b - (b-a) / GOLDEN_RATIO;
	x2 = a + (b-a) / GOLDEN_RATIO;
	f_1 = (*f)(x1);
	f_2 = (*f)(x2);
	while(!(fabs(a - b) < eps) && it_count < MaxIt){
		if(f_1 < f_2){
			flag = 1;
			a = x1;
			f_a = f_1;
		}
		else if(f_2 < f_1){
			flag = 2;
			b = x2;
			f_b = f_2;
		}
		else
			break;
		if(flag == 1){
			f_1 = f_2;
			x1 = x2;
			x2 = a + (b - a) / GOLDEN_RATIO;
			f_2 = (*f)(x2);
		}
		else{
			f_2 = f_1;
			x2 = x1;
			x1 = b - (b - a) / GOLDEN_RATIO;
			f_1 = (*f)(x1);
		}
		it_count++;
	}
	if(it_count < MaxIt){
		if((*f)(bc) > (*f)((b+a)*0.5))
			*x_max = bc;
		else
			*x_max = (b + a)*0.5;
		return it_count;
	}
	else
		return -2;
}

// can divide by zero
double get_lagr2(double fx[2], double x[2]){
        return (fx[1] - fx[0]) / (x[1] - x[0]);
}

// can divide by zero
// x1 - x0 = x2 - x1
double get_lagr3(double fx[3], double x[3]){
        return (get_lagr2(fx+1, x+1) - get_lagr2(fx, x)) / (x[2] - x[0]);
}

int solve10(double a, double b, double eps, int MaxIt, double (*f)(double), double *x_max){
	int it_count = 0;
	double fx[3], x[3], v, fv, temp, fa, fb;
	x[0] = a;
	x[2] = b;
	fa = f(a);
	fx[0] = fa;
	fb = f(b);
	fx[2] = fb;
	while((fabs(x[0] - x[2]) >= eps && it_count < MaxIt) || it_count == 0){
		x[1] = (x[0] + x[2]) / 2;
		fx[1] = f(x[1]);
		temp = get_lagr3(fx, x);
		if(fabs(temp) < EPS){
			*x_max = (fa > fb ? a : b);
			return it_count;
		}
		v = -0.5 * get_lagr2(fx, x) / temp + 0.5 * (x[0] + x[1]);
		fv = f(v);
		if(v < a || v > b){
			*x_max = (fa > fb ? a : b);
			return it_count;
		}
		if(fv < fx[0] && fv < fx[2])
			return -1;
		if(fx[0] < fx[2] && fx[0] < fv){
			fx[0] = fv;
			x[0] = v;
		}
		else{
			fx[2] = fv;
			x[2] = v;
		}
		it_count++;
	}
	if(it_count < MaxIt){
		if(fa > fv && fa > fb)
			*x_max = a;
		else if(fb > fv && fb > fa)
			*x_max = b;
		else
			*x_max = v;
		return it_count;
	}
	else
		return -2;
}
/*#define MIN2(a, b) (a < b ? a : b)
#define MIN3(a, b, c) (MIN2(a, b) < c ? MIN2(a, b) : c)
#define MIN4(a, b, c, d) (MIN2(a, b) < MIN2(c, d) ? MIN2(a, b) : MIN2(c, d))
#define MAX2(a, b) (a > b ? a : b)
#define MAX3(a, b, c) (MAX2(a, b) > c ? MAX2(a, b) : c)

int solve10(double a, double b, double eps, int MaxIt, double (*f)(double), double *x_max){
 	double x1 = a, x2 = (a+b)/2, x3 = b, ak, bk, x = (a+b)/2, fx, b_const = b;
	double f1 = (*f)(x1), f2 = (*f)(x2), f3 = (*f)(x3), mimin, mamax, xmamax;
	int it_count = 0;
	fx = f3;
	mamax = fx;
	xmamax = x3;
	while(!(fabs(MAX3(x1, x2, x3) - MIN3(x1, x2, x3)) < eps) && it_count < MaxIt){
		ak = (f2*x3 - f3*x2) - (f1*x3 - f3*x1) + (f1*x2 - f2*x1);
		bk = (x2*x2*f3 - x3*x3*f2) - (x1*x1*f3 - x3*x3*f1) + (x1*x1*f2 - x2*x2*f1);
		temp = (x2*x2*x3 - x3*x3*x2) - (x1*x1*x3 - x1*x3*x3) + (x1*x1*x2 - x1*x2*x2);
		if(fabs(temp) < eps)
			return -3;
		if(fabs(ak) < eps)
			return -3;
		x = -0.5*bk/ak;
//		if(x <= MIN3(x1, x2, x3) || x >= MAX3(x1, x2, x3))
//			return -1;
		fx = (*f)(x);
		if(mamax < fx){
			mamax = fx;
			xmamax = x;
		}
		mimin = MIN4(f1, f2, f3, fx);
		if(mimin <= fx && mimin >= fx){
			*x_max = xmamax;
			return it_count;
		} else if(mimin <= f1 && mimin >= f1){
			f1 = fx;
			x1 = x;
		} else if(mimin <= f2 && mimin >= f2){
			f2 = fx;
			x2 = x;
		} else if(mimin <= f3 && mimin >= f3){
			f3 = fx;
			x3 = x;
		}
		it_count++;
	}
	if(it_count < MaxIt){
		if((*f)(b_const) > (*f)(x))
			*x_max = b_const;
		else
			*x_max = x;
		return it_count;
	}
	else{
		*x_max = xmamax;
		return it_count;
	}
}*/

/*int solve10(double a, double b, double eps, int MaxIt, double (*f)(double), double *x_s){
	double f_a = (*f)(a), f_b = (*f)(b), c, f_c, x, f_x;
	double x_l[3], y_l[3], c;
	int it_count = 0;
	c = (a+b)/2;
	f_c = (*f)(c);
	x_l[0] = f_a;
	x_l[1] = f_c;
	x_l[2] = f_b;
	y_l[0] = a;
	y_l[1] = c;
	y_l[2] = b;
	while(!(fabs(????????) < eps) && it_count < MaxIt){
		if(lagrange_interpolation(0, x_l, y_l, 3, &x) != SUCCESS)
			return -3;
		f_x = (*f)(x);
		if(fabs(f_x) < fabs(f_a) && fabs(f_x) < fabs(f_b) && fabs(f_x) < fabs(f_c)){
			return -1;
		}
		c = x;
		f_c = f_x;
		it_count++;
	}
	if(it_count < MaxIt){
		*x_s = c;
		return it_count;
	}
	else
		return -2;
}*/
