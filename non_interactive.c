#include "main.h"

/**
 * non_interactive - runs the shell in non-interactive mode
 * @filename: the name of the file containing commands to execute
 *
 * This function reads commands from the specified file and executes them
 * in a child process. It continues reading and executing commands until
 * it reaches the end of the file.
 */
void non_interactive(char *filename)
{
	size_t n = 0;
	ssize_t len;
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *line = NULL;
	FILE *fp;

	if (filename == NULL)
	{
		fp = stdin;
	}
	else
	{
		fp = fopen(filename, "r");
		if (!fp)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
	}

	while ((len = getline(&line, &n, fp)) != -1)
	{
		parse_input(line, args);
		execute_command(args);
	}

	if (filename != NULL)
	{
		fclose(fp);
	}
}


/**
 * parse_input - parses a line of input into an array of arguments
 * @line: a pointer to a buffer containing the input
 * @args: a pointer to an array of arguments
 *
 * This function uses strtok() to split the input string into an array of
 * arguments, using whitespace as the delimiter. It stores the arguments
 * in the array pointed to by args, and sets the last element of the array
 * to NULL.
 */
void parse_input(char *line, char **args)
{
	char *token;
	int i = 0;

	token = strtok(line, DELIMITER);
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, DELIMITER);
	}
	args[i] = NULL;
}

/**
 * execute_command - executes a command in a child process
 * @args: an array of arguments for the command
 *
 * This function creates a child process using fork() and executes the
 * specified command in the child process using execvp(). It waits for
 * the child process to terminate and then returns control to the parent
 * process.
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		wait(&status);
	}
}
