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
 * execute_command - executes the arguments passed to the child process
 *
 * @command: string of arguments passed to it
 *
 * Return: 0
 */

void execute_commands(char *command)
{
	char *args[2];
	args[0] = command;
	args[1] = NULL;

	execvp(command, args);
	perror("execvp");
	exit(EXIT_FAILURE);
}

int main(void)
{
	char *lineptr;
	size_t buf_size = 0;
	ssize_t nread;
	pid_t pid;
	bool is_pipe = false;
	char *sign = "$ ";

	while (1 && !is_pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
		{
			is_pipe = true;
		}

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
			execute_commands(lineptr);
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
