#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * execute_command - executes the arguments passed to the child process
 *
 * @args: string of argument passed to it
 *
 * Return: 0
 */

void execute_command(char **args)
{
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
}

int main(void)
{
        char *lineptr = NULL;
        char **args = NULL;
        size_t buf_size = 0;
        ssize_t nread;
        pid_t pid;
        char *prompt = "$ ";
        bool is_pipe = false;
        int argcount = 0;
        char *token;

        while (1 && !is_pipe)
        {
                if (isatty(STDIN_FILENO) == 0)
                {
                        is_pipe = true;
                }

                write(STDOUT_FILENO, prompt, 2);

                nread = getline(&lineptr, &buf_size, stdin);
                if (nread == -1)
                {
                        if (errno == 4)
                        {
                                break;
                        }
                        perror("Getline Error");
                        free(lineptr);
                        exit(EXIT_FAILURE);
                }
                lineptr[strcspn(lineptr, "\n")] = '\0';

		if (lineptr[0] == '\0')
		{
			continue;
		}

		token = strtok(lineptr, " ");
                while (token != NULL)
                {
                        args = realloc(args, (argcount + 1) * sizeof(char*));
                        args[argcount++] = token;
                        token = strtok(NULL, " ");
                }
                args = realloc(args, (argcount + 1) * sizeof(char*));
                args[argcount] = NULL;

                if (strcmp(args[0], "ls") == 0)
                {
                       perror("No such file or directory");
                }
		else if (strcmp(args[0], "/bin/ls") == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execute_command(args);
			}
			else if (pid == -1)
			{
				perror("Fork Error");
				exit(EXIT_FAILURE);
			}
			else
			{
				wait(NULL);
			}
		}
		if (strcmp(args[0], "exit") == 0)
		{
			break;
		}

		free(args);
	}
        return (0);
}
