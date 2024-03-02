#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGUMENTS 64
#define DELIMITERS " \a\t\r\n"

void parse_input(char *user_input, char **user_command, char **arguments);
int command_exists(char *potential_command);
int input_exists(char *user_input);
void execute_command(char **args);
int main(void);

#endif
