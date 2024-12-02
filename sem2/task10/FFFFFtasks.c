//#include <stdio.h>
#include <math.h>

#include "tasks.h"

#define SIGN(x) ((x) < (0) ? (1) : (0)) 

#define MAXIT1 720

#define MAXIT2 100

#define MAXIT3 25000

#define MAXIT4 10000

#define MAXIT5 10000

#define MAXIT6 10000

#define MAXIT7 10000

#define MAXIT8 10000

#define MAXIT9 10000

#define MAXIT10 10000

int task1(double (*op)(double), double a, double b, double ep, double *x)
{
	double c = 0.0, f_a = (*op)(a), f_b = (*op)(b), f_c = 0.0;
	int i = 0;
	
	if(fabs(f_a) < ep)
	{
		*x = a;
		return 0;
	}

	if(fabs(f_b) < ep)
	{
		*x = b;
		return 0;
	}

	if(SIGN(f_a) == SIGN(f_b))
	{
		return -1;
	}

	for(i = 0; i < MAXIT1; i++)
	{
		c = (a + b) * 0.5;

		if((b - a < ep) || ((c <= a) && (c >= a)) || ((c >= b) && (c <= b)))
		{
			*x = c;
			return i;
		}

		f_c = (*op)(c);
		if(fabs(f_c) < ep)
		{
			*x = c;
			return i; 
		}

		if(SIGN(f_a) != SIGN(f_c))
		{
			b = c;
			f_b = f_c;
		}else
		{
			a = c;
			f_a = f_c;
		}

	}
	return -1;
}


int task2(double (*op)(double), double (*d)(double), double x0, double ep, double *x)
{
	int i = 0;
	double zn = 0.0, pr = 0.0;
	for(i = 0; i < MAXIT2; i++)
	{
		zn = (*op)(x0);
		if(fabs(zn) < ep)
		{
			*x = x0;
			return i;
		}

		pr = (*d)(x0);

		if(fabs(pr) < ep)
		{
			return -1;
		}
		x0 -= zn/pr;
	}
	return -1;
}


int task3(double (*op)(double), double a, double b, double ep, double *x)
{
	double c = a, f_a = (*op)(a), f_b = (*op)(b), f_c = 0.0;
	int i;

	if(fabs(f_a) < ep)
	{
		*x = a;
		return 0;
	}

	if(fabs(f_b) < ep)
	{
		*x = b;
		return 0;
	}

	if(fabs(f_b - f_a) < ep)
	{
		return -1;
	}
	c = a - f_a * (b - a) / (f_b - f_a);

	f_c = (*op)(c);

	//
	if(SIGN(f_a) == SIGN(f_b))
	{
		return -1;
	}
	//

	if(fabs(f_c) < ep)
	{
		*x = c;
		return 0; 
	}

	for(i = 0; i < MAXIT3; i++)
	{
		if(fabs(f_b - f_a) < ep)
		{
			return -1;
		}

		c = a - f_a * (b - a) / (f_b - f_a);
		///
		if(c < a || c > b)
		{
			return -1;
		}
		///
		if((b - a < ep) || ((c <= a) && (c >= a)) || ((c >= b) && (c <= b)))
		{
			return -1;
		}

		f_c = (*op)(c);

		if(fabs(f_c) < ep)
		{
			*x = c;
			return i; 
		}

		if(SIGN(f_a) != SIGN(f_c))
		{
			b = c;
			f_b = f_c;
		}else
		{
			a = c;
			f_a = f_c;
		}

	}
	return -1;
}


int task4(double (*op)(double), double a, double b, double ep, double *x)
{
	double c = a, f_a = (*op)(a), f_b = (*op)(b), f_c = 0.0, aaa = 0.0, bbb = 0.0;
	int i = 0;


	if(fabs(f_a) < ep)
	{
		*x = a;
		return 0;
	}

	if(fabs(f_b) < ep)
	{
		*x = b;
		return 0;
	}

	if(fabs(f_b - f_a) < ep)
	{
		return -1;
	}

	c = a - f_a * (b - a) / (f_b - f_a);

	f_c = (*op)(c);

	for(i = 1; i < MAXIT4; i++)
	{
		if(fabs(f_b - f_a) < ep)
		{
			if(fabs(f_c) < ep)
			{
				*x = c;
				return i;
			}
			return -1;
		}
		c = a - f_a * (b - a) / (f_b - f_a);

		f_c = (*op)(c);

		if(fabs(f_c) < ep)
		{
			*x = c;
			return i; 
		}
		if((aaa = fabs(f_a)) < (bbb = fabs(f_b)))
		{
			if(fabs(f_c) > bbb)
			{
				return -1;
			}
			b = c;
			f_b = f_c;
			
			
		}else
		{
			if(fabs(f_c) > aaa)
			{
				return -1;
			}
			a = c;
			f_a = f_c;
		}
	}
	return -1;
}


int task5(double (*op)(double), double a, double b, double ep, double *x)
{
	int i, e = 1;//e = 1 - a; 2 - b; 3 - c; 
	double c = (a + b) * 0.5, d = 0.0, f_a = (*op)(a), f_b = (*op)(b);
	double f_c = 0.0, f_d = 0.0, f_e = 0.0, he1 = 0.0, he2 = 0.0, aaa = 0.0, bbb = 0.0, ccc = 0.0;

	if(fabs(f_a) < ep)
	{
		*x = a;
		return 0;
	}
	if(fabs(f_b) < ep)
	{
		*x = b;
		return 0;
	}

	if(fabs(f_a) < ep)
	{
		*x = a;
		return 0;
	}

	if(fabs(f_b) < ep)
	{
		*x = b;
		return 0;
	}

	c = (a + b) * 0.5;
	f_c = (*op)(c);

	if(fabs(f_c) < ep)
	{
		*x = c;
		return 0;
	}

	for(i = 0; i < MAXIT5; i++)
	{
	//	if((aaa = fabs(f_a)) <= (bbb = fabs(f_b)) && (aaa >= bbb))
		if(fabs(f_b - f_a) < ep)
		{
			return -1;
		}
	//	if(aaa <= (ccc = fabs(f_c)) && (aaa >= ccc))
		if(fabs(f_c - f_b) < ep)
		{
			return -1;
		}
	//	if(bbb <= ccc && (bbb >= ccc))
		if(fabs(f_c - f_a) < ep)
		{
			return -1;
		}

		he1 = (b - a) / (f_b - f_a);
		he2 = (c - b) / (f_c - f_b);

		d = a - he1 * f_a + f_a * f_b * (he2 - he1) / (f_c - f_a);
		f_d = (*op)(d);

		if(fabs(f_d) < ep)
		{
			*x = d;
			return i;
		}
		
		e = 1;
		f_e = aaa;
		if(f_e < bbb)
		{
			f_e = bbb;
			e = 2;
		}

		if(f_e < ccc)
		{
			f_e = ccc;
			e = 3;
		}

		if(fabs(f_d) > f_e)
		{
			return -1;
		}

		switch(e)
		{
			case 1:
				a = d;
				f_a = f_d;
				break;
			case 2:
				b = d;
				f_b = f_d;
				break;
			default:
				c = d;
				f_c = f_d;
		}

	}
	return -1;
}


int task6(double (*op)(double), int m, double *d, double a, double b, double ep, double *x)
{
	int i = 0, j = 0;
	double c = 0.0, f_c = 0.0;
	double *xx = d, *yy = d + m + 1, *zz = yy + m + 1;
	double aaa, ccc = (b - a) / m;

	for(i = 0; i < m + 1 ; i++)
	{
		xx[i] = a + i * ccc;

		yy[i] = (*op)(xx[i]);
		aaa = fabs(yy[i]);

		if(aaa < ep)
		{
			*x = xx[i];
			return 0;
		} 
	}

	quicksort_array(yy, xx, m + 1);
	c = xx[m];
	f_c = yy[m];

	for(i = 0; i < MAXIT6; i++)
	{
		//sort new val
		for (j = m-1; (j >= 0) && (f_c < yy[j]); j--)
		{
			yy[j + 1] = yy[j]; 
			xx[j + 1] = xx[j]; 
		}
		j++;
		xx[j] = c;
		yy[j] = f_c;

		//save xx
		for(j = 1; j < m + 1; j++)
		{
			zz[j] = xx[j];
			if(fabs(yy[j] - yy[j - 1]) < ep)
			{
				return -1;
			}
		}

		//found new point
		c = funk2(yy, zz, m + 1, 0);

		f_c = (*op)(c);

		if(fabs(f_c) < ep)
		{
			*x = c;
			return i;
		}

	//	if (fabs(xx[m] - c) < ep)
	//	{
	//		*x = c;
	//		return i;
	//	}
		if(fabs(fabs(f_c) - fabs(yy[m])) < ep)
		{
			return -1;
		}

		xx[m] = c;
		yy[m] = f_c;
	}

	return -1;
}


int task7(double (*op)(double), double x0, double ep, double *x)
{
	int i;
	double zn = 0.0;

	for(i = 0; i < MAXIT7; i++)
	{
		zn = (*op)(x0);
		if(fabs(zn - x0) < ep)
		{
			*x = zn;
			return i;
		}
		x0 = zn;
	}
	return -1;
}


int task8(double (*op)(double), double a, double b, double ep, double *x)
{
	double shag = (b - a) * 0.0001;
	int i;
	double xx = a, f_x = 0.0, f_a = (*op)(a), f_b = (*op)(b), max, OT = a;
	f_x = f_a;
	max = f_a;
	if(max < f_a)
	{
		max = f_a;
		OT = a;
	}
	if(max < f_b)
	{
		OT = b;
	}

	for(i = 0; (shag > ep) && (xx >= a) && (xx <= b) && (i < MAXIT8); i++)
	{
		xx += shag;

		f_x = (*op)(xx);

		if(f_x < max)
		{
			shag *= -0.1;
		}

		if(max < f_x)
		{
			max = f_x;
			OT = xx;
		}	
	}

	

	*x = OT;
	return i;	
}


int task9(double (*op)(double), double a, double b, double ep, double *x)
{
	int i;
	double x1, x2, f_1 = (*op)(a), f_2 = (*op)(b), al = (sqrt(5) - 1) * 0.5, max, OT = a;

	max = f_1;

	if(max < f_2)
	{
		OT = b;
		max = f_2;
	}

	x1 = a + al*(b - a);
	f_1 = (*op)(x1);
	x2 = b - al*(b - a);
	f_2 = (*op)(x2);

	for(i = 0; (b - a) > ep && i < MAXIT9; i++)
	{
		if(f_2 > f_1)
		{
			if(f_2 > max)
			{
				max = f_2;
				OT = x2;
			}
			a = x1;
			x1 = x2;
			f_1 = f_2;
			x2 = b - al*(b - a);
			f_2 = (*op)(x2);
		}else
		{
			if(f_1 > max)
			{
				max = f_1;
				OT = x1;
			}
			b = x2;
			x2 = x1;
			f_2 = f_1;
			x1 = a + al*(b - a);
			f_1 = (*op)(x1);
		}
	}
	*x = OT;
	return i;
}


int task10(double (*op)(double), double a, double b, double ep, double *x)
{
	double he1, he2, c = (a + b) * 0.5, f_a = (*op)(a), f_b = (*op)(b), f_c = (*op)(c), f123, d, f_d, aaa, bbb, ccc;
	double min = f_a, f_e, OT = a;
	int i, e = 1;

	for(i = 0; i < MAXIT10 && !(fabs(a - b) < ep && fabs(a - c) < ep && fabs(b - c) < ep); i++)
	{
		aaa = fabs(a);
		bbb = fabs(b);
		ccc = fabs(c);
		if(fabs(bbb - aaa) < ep)
		{
			return -1;
		}
		if(fabs(aaa - ccc) < ep)
		{
			return -1;
		}
		if(fabs(bbb - ccc) < ep)
		{
			return -1;
		}
		he1 = (f_b - f_a) / (b - a);
		he2 = (f_c - f_b) / (c - b);
		f123 = 0.5 * (he2 - he1) / (c - a);

		if(fabs(f123) <= ep)
		{
			return -1;
		}
		d = a - he1/f123 + b;
		f_d = (*op)(d);
		e = 1;
		f_e = aaa;
		if(f_e > bbb)
		{
			f_e = bbb;
			e = 2;
		}

		if(f_e > ccc)
		{
			f_e = ccc;
			e = 3;
		}

		if(fabs(f_d) < f_e)
		{
			return -1;
		}

		switch(e)
		{
			case 1:
				a = d;
				f_a = f_d;
				break;
			case 2:
				b = d;
				f_b = f_d;
				break;
			default:
				c = d;
				f_c = f_d;
		}
	}

	min = fabs(f_a);
	if(fabs(f_b) > min)
	{
		OT = b;
		min = fabs(f_b);
	}

	if(fabs(f_c) > min)
	{
		OT = c;
		min = fabs(f_c);
	}


	*x = OT;
	return i;
}



double funk2(double* x, double* y, int n, double x0)
{
	int i = 0, j = 0;
	double res = 0;

	for(i = 0; i < n; i++)
	{
		for(j = n-1; j > i; j--)
		{
			y[j] = (y[j] - y[j-1]) / (x[j] - x[j-i-1]);
		}
	}

	for(i = n-1; i >= 0; i--)
	{
		res *= (x0 - x[i]);
		res += y[i];
	}

	return res;
}


void quicksort_array(double *aa, double *bb, int lena)
{
	int res = 0;

	while(lena > 1)
	{
		res = task3func(aa, bb, lena, aa[lena / 2]);

		if(res == 0)
		{
			lena -= 1;
			aa += 1;
			bb += 1;
			continue;
		}
		if(res >= lena - 1)
		{
			lena -= 1;
			continue;
		}
		if((lena / 2) > res)
		{
			quicksort_array(aa, bb, res);
			aa += (res + 1);
			bb += (res + 1);
			lena = lena - (res + 1);
		}else
		{
			quicksort_array(aa + res + 1, bb + res + 1, lena - (res + 1));
			lena = res;
		}
		
	}
}

int task3func(double *ma, double *bb, int len, double va)
{
	int i, j;
	double tmp = 0;
	i = 0;
	j = len - 1;
	while(i < j)
	{
		while((i <= j) && (ma[i] - va < 0))
		{
			i++;
		}
		while((i < j) && ( ma[j] - va > 0))
		{
			j--;
		}

		if (i < j)
		{
			if ((ma[j] <= ma[i]) && (ma[j] >= ma[i]))//((ma[i] >= ma[j]) && (ma[i] <= ma[j]))
			{
				j--;
				continue;
			}
			//swap_values(&ma[i], &ma[j]);
			tmp = ma[i];
			ma[i] = ma[j];
			ma[j] = tmp;

			tmp = bb[i];
			bb[i] = bb[j];
			bb[j] = tmp;
		}
	}
	return i;
}

