/*Apply effective Horner's method*/
double polyh(double a[], double x, long degree){
	long i;
	long mul1 = x;
	long mul2 = x * x * x;
	long mul3 = x * x * x * x * x;
	long mul_next = x * x * x * x * x * x;
	double result1, result2, result3;
	result1 = a[0];
	result2 = result3 = 0;
	for(i=1 ; i<degree-5 ; i+=6){
		result1 = result1 + (a[i]*mul1 + a[i+1]*mul1*x); 
		result2 = result2 + (a[i+2]*mul2 + a[i+3]*mul2*x);
		result3 = resutl3 + (a[i+4]*mul3 + a[i+5]*mul3*x);
		
		mul1 *= mul_next;
		mul2 *= mul_next;
		mul3 *= mul_next;
	}
	for(i ; i<degree ; i++){
		result1 = result1 + a[1] * mul1;
		mul1 *= x;
	}

	return result1 + result2 + result3;
}
