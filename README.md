Shell  Group Project
A group project to build a simple shell that is able to do the following;

Task 1 - Betty would be proud
Write a beautiful code that passes the Betty checks

Task 2 - Simple_shell
Write a UNIX command line interpreter.
Usage: simple_shell
Your Shell should:
Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)

You don’t have to:
use the PATH
implement built-ins
handle special characters : ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments
execve will be the core part of your Shell, don’t forget to pass the environ to it…

Task 3
Handle command lines with arguments

Task 4
Handle the PATH
fork must not be called if the command doesn’t exist

Task 5
Implement the env built-in, that prints the current environment

Task 6
Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit

Task 7
Implement the env built-in, that prints the current environment

Task 8
Write your own getline function
Use a buffer to read many chars at once and call the least possible the read system call
You will need to use static variables
You are not allowed to use getline
You don’t have to:
be able to move the cursor
You are not allowed to use strtok
handle arguments for the built-in exit
Usage: exit status, where status is an integer used to exit the shell

Task 9
Implement the setenv and unsetenv builtin commands
setenv
Initialize a new environment variable, or modify an existing one
Command syntax: setenv VARIABLE VALUE
Should print something on stderr on failure
unsetenv
Remove an environment variable
Command syntax: unsetenv VARIABLE
Should print something on stderr on failure

Task 10
Implement the builtin command cd:
Changes the current directory of the process.
Command syntax: cd [DIRECTORY]
If no argument is given to cd the command must be interpreted like cd $HOME
You have to handle the command cd -
You have to update the environment variable PWD when you change directory

Task 11
Handle the commands separator ;

Task 12
Handle the && and || shell logical operators

Task 13
Implement the alias builtin command
Usage: alias [name[='value'] ...]
alias: Prints a list of all aliases, one per line, in the form name='value'
alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value

Task 14
Handle variables replacement
Handle the $? variable
Handle the $$ variable

Task 15
Handle comments (#)

Task 16 - File as Input
Usage: simple_shell [filename]
Your shell can take a file as a command line argument
The file contains all the commands that your shell should run before exiting
The file should contain one command per line
In this mode, the shell should not print a prompt and should not read from stdin
