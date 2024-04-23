#include "shell.h"

/**
 * get_path - function that get the original PATH and all his variable.
 *
 * Return: the path name on a variable that contains a copy of PATH
*/
char *get_path()
{
	char **variable_in_environ = environ;
	char *path = NULL;
	char *path_copy;

	while (*variable_in_environ != NULL)
	{
		if (strncmp(*variable_in_environ, "PATH=", 5) == 0)
		{
			path = *variable_in_environ + 5;
			break;
		}
		variable_in_environ++;
	}
	if (path == NULL)
	{
		fprintf(stderr, "PATH variable not found\n");
		exit(EXIT_FAILURE);
	}

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("Error duplicating PATH");
		free(path_copy);
		exit(EXIT_FAILURE);
	}
	return (path_copy);
}
