void psum1(float a[], float p[], long n)
{
	long i;
	long temp, temp1, temp2, temp3;
	long val_last = p[0];
	for(i=0 ; i<n-3 ; i+=4){
		temp = val_last + a[i];
		temp1 = temp + a[i+1];
		temp2 = temp1 + a[i+2};
		temp3 = temp2 + a[i+3];

		p[i] = temp;
		p[i+1] = temp1;
		p[i+2] = temp2;
		p[i+3] = temp3;

		last_val = last_val + (a[i]+a[i+1]+a[i+2]+a[i+3]);
	}
	for(i ; i<n ; i++){
		val_last += a[i];
		p[i] = val_last;
	}
