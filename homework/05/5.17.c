#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define K sizeof(unsigned long)

void *effective_memset(void* s, int c, size_t n)
{
	size_t num = 0;
	unsigned long long_char;
	unsigned char *w = (unsigned char *) &long_char;
	while(num < K)
	{
		*w++ = (unsigned char)c;
		num++;
	}
	size_t cnt = 0;
	unsigned char *schar = s;
	while(cnt < n)
	{
		if((size_t)schar % K == 0){
			break;
		}
		*schar++ = (unsigned char)c;
		cnt++;
	}
	unsigned long *str = (unsigned long *)schar;
	size_t rest = n - cnt;
	size_t loop = rest / K;
	size_t tail = rest % K;
	for(int i=0 ; i<loop ; i++)
	{
		*str++ = long_char;
	}
	schar = (unsigned char *)str;
	for(int i=0 ; i<tail ; i++)
	{
		*schar++ = (unsigned char)c;
	}
	return s;
}









