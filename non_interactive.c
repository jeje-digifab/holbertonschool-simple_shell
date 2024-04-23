#include "main.h"

/**
 * non_interactive - reads input from stdin and processes it in non-interactive
 *                   mode
 *
 * Return: 0 on success, -1 on error
 */

int non_interactive(void)
{
	char buffer[MAX_LINE_LENGTH];

	while (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL)
	{
		if (strlen(buffer) == 0)
		{
			continue;
		}

		if (parse_input(buffer) == -1)
		{
			perror("Error:");
			return (-1);
		}
	}

	return (0);
}


/**
 * parse_input - parses the input string into an array of arguments
 *
 * @input: the input string to be parsed
 *
 * Return: 0 on success, -1 on error
 */

int parse_input(char *input) {
    char *args[MAX_ARGS];
    char *token;
    int i = 0;

    token = strtok(input, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        token = strtok(NULL, " \t\n");
        i++;
    }
    args[i] = NULL;

    if (args[0] != NULL) {
        if (access(args[0], F_OK) == 0) { /* Check if command exists*/
            return create_fork(args); /* Call create_fork only if the command exists */
        } else {
            printf("Command not found: %s\n", args[0]); /* Print error message */
            return -1;
        }
    }

    return 0;
}

/**
 * create_path_list - creates a linked list of directories from the PATH
 *                    environment variable
 *
 * @path: the PATH environment variable string
 *
 * Return: a pointer to the head of the linked list
 */
struct node *create_path_list(char *path) {
    struct node *head = NULL;
    struct node *tail = NULL;

    char *dir = strtok(path, ":");

    while (dir != NULL) {
        struct node *new_node = (struct node *) malloc(sizeof(struct node));

        new_node->dir = strdup(dir);
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        dir = strtok(NULL, ":");
    }

    return head;
}
