#include "m_func.h"

double m_fabs(double x){
	return x < 0 ? -x : x;
}

int is_equal(double a, double b){
	return m_fabs(a - b) <= EPS*(m_fabs(a) + m_fabs(b)) ? 1 : 0;
}

int m_gcd(int a, int b){
	int temp;
	while(a != 0 && b != 0){
		if(a < b){
			temp = a;
			a = b;
			b = temp;
		}
		a = a % b;
	}
	return a != 0 ? a : b;
}
