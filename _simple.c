#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int main(void)
{
	char *lineptr = NULL;
	size_t buf_size = 0;
	ssize_t nread;
	pid_t pid;
	char *token;
	char *sign = "$ ";
	char *args[100];
	int i = 0;
	int status;

	while (1)
	{
		write("$ ");

		nread = getline(&lineptr, &buf_size, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
			{
				write("\n");
				break;
			}
			else
			{
				perror("Getline Error");
				exit(EXIT_FAILURE);
			}

			lineptr[strcspn(lineptr, "\n")] = '\0';

			token = strtok(lineptr, " ");
			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;

			pid = fork();
			if (pid == -1)
			{
				perror("Fork Error");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				if(execvp(args[0], args) == -1)
				{
					perror(args[0]);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				waitpid(pid, &status, 0);
			}

			if (WIFEXITED(status))
			{
				write("%d\n", WEXITSTATUS(status));
			}
			else
			{
				perror("Waitpid Error");
				exit(EXIT_FAILURE);
			}
		}
	}
	free(lineptr);
	return (0);
}
