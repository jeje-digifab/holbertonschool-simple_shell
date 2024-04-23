#include "shell.h"
/**
 * main - function as a basic UNIX shell interpreter, parsing user input
 *		executing commands & managing built-in operations like 'exit' and 'env'
 *
 * @argc: number of arguments passed to the program
 * @argv: array of strings representing the arguments
 *
 * Return: 0 if success , 1 if error
*/
int main(__attribute__((unused)) int argc, char *argv[])
{
	char *input = NULL, *path;
	int result;

	path = _getenv("PATH");
	if (path == NULL)
		return (-1);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		result = read_user_input(&input);
		if (result == 0)
		{
			if (feof(stdin))
			{
				free(input);
				exit(EXIT_SUCCESS);
			}
		}
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(input, "env\n") == 0)
		{
			print_environnement();
			free(input);
			continue;
		}
		if (handle_command(input, argv[0]) != 0)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], input);
			free(input);
		}
	}
	free(input);
	return (0);
}
