#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - simple shell project
 *
 * commandlineargs - executes the arguments passed to the child process
 *
 * @commandline: string of arguments passed to it
 *
 * Return: 0
 */

void commandlineargs(char *commandline)
{
	int argcount = 0;
	char *argvector[11];
	char *separator = " ";
	char *token;

	token = strtok(commandline, separator);
	while (token != NULL && argcount < 10)
	{
		argvector[argcount++] = strdup(token);
		token = strtok(NULL, separator);
	}

	if (argcount == 0)
	{
		perror("No command, No Argument");
		exit(EXIT_FAILURE);
	}

	argvector[argcount] = NULL;

	execvp(argvector[0], argvector);
	perror("excevp Failed");
	exit(EXIT_FAILURE);
}

int main(void)
{
	char *lineptr = NULL;
	size_t buf_size = 0;
	ssize_t nread;
	pid_t pid;
	char *sign = "$ ";

	while (1)
	{
		write(STDOUT_FILENO, sign, 2);

		nread = getline(&lineptr, &buf_size, stdin);
		if (nread == -1)
		{
			perror("Getline Error");
			free(lineptr);
			exit(EXIT_FAILURE);
		}

		lineptr[strcspn(lineptr, "\n")] = '\0';

		pid = fork();
		if (pid == 0)
		{
			commandlineargs(lineptr);
		}

		if (pid == -1)
		{
			perror("Fork Error");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}

	}

	free(lineptr);
	return (0);
}
