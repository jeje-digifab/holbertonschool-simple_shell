#include "main.h"

/**
 * main - entry point of the shell program
 * @argc: number of command line arguments
 * @argv: array of command line argument strings
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	if (argc > 1)
	{
		non_interactive(argv[1]);
	}
	else if (isatty(STDIN_FILENO))
	{
		interactive();
	}
	else
	{
		non_interactive(NULL);
	}
	return (0);
}

/**
 * hsh_export - modifies the PATH environment variable to include a new
 *  directory
 *
 * @args: an array of arguments passed to the function
 */
void hsh_export(char **args)
{
	if (args[1] == NULL)
	{
		print_env();
	}
	else
	{
		char *path = getenv("PATH");

		char *new_path = malloc(strlen(args[1]) + strlen(path) + 2);

		sprintf(new_path, "%s:%s", args[1], path);

		setenv("PATH", new_path, 1);

		free(new_path);
	}
}



/**
 * create_path_list - creates a linked list of directories from the PATH
 *                    environment variable
 *
 * @path: the PATH environment variable string
 *
 * Return: a pointer to the head of the linked list
 */
struct node *create_path_list(char *path)
{
	struct node *head = NULL;
	struct node *tail = NULL;

	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		struct node *new_node = (struct node *) malloc(sizeof(struct node));

		new_node->dir = strdup(dir);
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

		dir = strtok(NULL, ":");
	}

	return (head);
}

/**
 * read_commands_from_file - reads commands from a file and executes them
 * @filename: name of the file to read commands from
 *
 * Return: void
 */
void read_commands_from_file(char *filename)
{
	size_t n = 0;
	ssize_t len;
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *line = NULL;
	FILE *fp = fopen(filename, "r");

	if (!fp)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((len = getline(&line, &n, fp)) != -1)
	{
		parse_input(line, args);
		execute_command(args);
	}

	free(line);
	free(args);
	fclose(fp);
}
