#include "csapp.h"

int mysystem(char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if(pid == 0)
	{
		if(execl("/bin/sh", "-c", command, NULL) == -1)
		{
			perror("execl error");
			exit(-1);
		}
		exit(0);
	}
	if(waitpid(pid, &status, 0) > 0)
	{
		if(WIFEXITED(status))
		{
			return WIFEXITED(status);
		}
		else if(WIFSIGNALED(status))
		{
			printf("chlid %d teminated normally with exit status = %d", pid, WIFSIGNALED(status));
			return WIFSIGNALED(status);
		}
		else
		{
			printf("chlid %d teminated abnormally\n");
		}
	}
	else
	{
		perror("waitpid error");
		return EXIT_FAILURE;
	}
}

