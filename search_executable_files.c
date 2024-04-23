#include "shell.h"
/**
 * check_access - function that check the accessibility of a file to be execute
 *
 * @path: the path of the file to be checked for access
 *
 * Return: 1 if the file is accessible for execution, 0 otherwise
*/
int check_access(const char *path)
{
	if (access(path, X_OK) == 0)
	{
		return (1);
	}
	return (0);
}
/**
 * search_executable_files - function that take 2 inputs, just see below
 * It search the path of executable files
 *
 * @head: the head of the simply linked llist
 * @command: the command to search on the PATH
 *
 * Return: NULL if any executable file match with 'command'
*/
char *search_executable_files(path_list *head, const char *command)
{
	char *pathname, *result = NULL;

	if (head == NULL || head->directory == NULL)
	{
		fprintf(stderr, "Invalid path\n");
		return (NULL);
	}

	while (head != NULL)
	{
		pathname = malloc(strlen(head->directory) + strlen(command) + 2);
		if (pathname == NULL)
		{
			perror("Memory allocation failed");
			return (NULL);
		}

		sprintf(pathname, "%s/%s", head->directory, command);
		if ((command[0] == '/' || command[0] == '.') && check_access(command))
		{
			result = strdup(command);
		}
		else if (check_access(pathname))
		{
			result = strdup(pathname);
		}

		if (result != NULL)
		{
			free(pathname);
			return (result);
		}

		free(pathname);
		head = head->next;
	}

	return (NULL);
}
