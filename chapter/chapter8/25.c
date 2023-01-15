#include "csapp.h"

#define MAXSIZE 1024
#define TIME 5

jmp_buf buf;

void handle(int signum)
{
	siglongjmp(buf, 1);
}

char *tfgets(char *s, int size, FILE *stream)
{
	if(signal(SIGALRM, handle) == SIG_ERR)
	{
		perror("signal error");
		return NULL;
	}
	else
	{
		alarm(TIME);
	}
	if(!sigsetjmp(buf, 1))
	{
		return fgets(s, size, stream);
	}
	else
	{
		return NULL;
	}
}

int main()
{
	char str[MAXSIZE];
	char *c = tfgets(str, MAXSIZE, stdin);
	if(c)
	{
		printf("Input : %s", c);
	}
	else
	{
		fprintf(stderr, "Time out\n");
	}
	return 0;
}












