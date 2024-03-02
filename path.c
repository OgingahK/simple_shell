#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

void parse_input(char *user_input, char **user_command, char **arguments)
{
    int argument_index = 0;
    *user_command = strtok(user_input, DELIMITERS);
    if (*user_command == NULL)
    {
        return;
    }
    
    while ((arguments[argument_index] = strtok(NULL, DELIMITERS)) != NULL)
    {
         argument_index++;
    }
}


int command_exists(char *potential_command)
{
     char *environment_path = getenv("PATH");
    char *path_copy = strdup(environment_path);
    char *path_segment = strtok(path_copy, ":");
    char full_path[MAX_INPUT_LENGTH];
    
    while (path_segment != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", path_segment, potential_command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return 1;
        }
        path_segment = strtok(NULL, ":");
    }
    free(path_copy);
    return 0;
}

int input_exists(char *user_input)
{
    char *user_command;
    char *arguments[MAX_ARGUMENTS];
    size_t input_size = MAX_INPUT_LENGTH;
    char *error_message = "Command not found";

    user_input = (char *)malloc(input_size * sizeof(char));
    if (user_input == NULL)
    {
         perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (1) {
        write(STDOUT_FILENO, "$ ", strlen("$ "));
        if (getline(&user_input, &input_size, stdin) == -1)
        {
             perror("getline");
            exit(EXIT_FAILURE);
        }

        parse_input(user_input, &user_command, arguments);

        if (user_command != NULL) {
            if (command_exists(user_command))
        {
                pid_t child_process_id = fork();
                if (child_process_id < 0)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                else if (child_process_id == 0)
                {
                    execvp(user_command, arguments);
                    perror("execvp"); 
                    exit(EXIT_FAILURE);
                }
                else
                {
                    wait(NULL);
                }
            }
            else
            {
                perror(error_message);
            }
        }
    }

    free(user_input);
    return 0;
}
