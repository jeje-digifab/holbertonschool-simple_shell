#include "shell.h"
/**
 * handle_command - execute the provided command if all condition
 *
 * @command: the command to execute
 * @program_name: the name of the program to passed on argument
 *
 * Return: 0 on success, 1 on error
*/
int handle_command(char *command, char *program_name)
{
	char *path = get_path();
	pid_t process_id;
	char **args = parse_user_input(command);
	path_list *directories = create_path_list(path);
	int status = 0;

	if (args == NULL || directories == NULL || path == NULL)
	{
		free_path_list(directories);
		free_tokens(args);
		free(path);
		return (1);
	}

	process_id = fork();
	if (process_id == 0)
	{
		execute_command(args, program_name);
		free_path_list(directories);
		free_tokens(args);
		free(path);
		exit(EXIT_SUCCESS);
	}
	else if (process_id > 0)
		wait(&status);
	else
	{
		perror("error");
		status = 1;
	}

	free_path_list(directories);
	free_tokens(args);
	free(path);
	return (status);
}
