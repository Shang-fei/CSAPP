#include "csapp.h"
#define MAXARGS 128

/*Function prototypes*/
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

int main()
{
	char cmdline[MAXARGS];
	while(1)
	{
		printf(">");
		Fgets(cmdline, MAXLINE, stdin);
		if(feof(stdin))
		  exit(0);

		eval(cmdline);
	}
}
