#include "shell.h"
/**
 * create_path_list - create a path list that contains all directories of PATH
 *					each directory are separate by ":" and store on a new directory.
 *					It creates a simply linked list which has those directories
 *
 * @path: the path of all executable files
 *
 * Return: the head of the struct
*/
path_list *create_path_list (char *path)
{
	path_list *head = NULL;
	path_list *tail = NULL;
	path_list *new_node = NULL;

	char *directory = strtok(path, ":");

	while (directory != NULL)
	{
		new_node = malloc(sizeof(path_list));
		if (new_node == NULL)
		{
			perror("Memory allocation error");
			return (NULL);
		}

		new_node->directory = strdup(directory);
		new_node->next = NULL;

		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		directory = strtok(NULL, ":");
	}
	return (head);
}
