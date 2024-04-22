#include "main.h"

/**
 * create_fork - creates a new process using fork() and executes the command
 *               using execvp()
 *
 * @args: array of arguments for the command to be executed
 *
 * Return: 0 on success, 1 on error
 */
int create_fork(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		status = my_execvp(args);
		if (status == -1)
		{
			perror(args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
		return (-1);
	}

	return (0);
}

/**
 * my_execvp - executes the command with the given arguments by searching
 *             for the executable file in the directories specified in
 *             the PATH environment variable
 *
 * @args: array of arguments for the command to be executed
 *
 * Return: 0 on success, -1 on error
 */

int my_execvp(char **args)
{
	char *token, *file_path, *path;
	int status;
	struct stat st;

	if (stat(args[0], &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
	{
		pid_t pid = fork();

		if (pid == 0)
		{
			execv(args[0], args);
			perror("execv");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			return (WEXITSTATUS(status));
		}
		else
		{
			perror("fork");
			return (-1);
		}
	}
	path = getenv("PATH");
	if (!path)
	{
		perror("Path not found");
		return (-1);
	}
	token = strtok(path, DELIM);
	while (token != NULL)
	{
		file_path = malloc(strlen(token) + strlen(args[0]) + 2);
		sprintf(file_path, "%s/%s", token, args[0]);

		if (stat(file_path, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
		{
			pid_t pid = fork();

			if (pid == 0)
			{
				execv(file_path, args);
				perror("execv");
				exit(EXIT_FAILURE);
			}
			else if (pid > 0)
			{
				waitpid(pid, &status, 0);
				free(file_path);
				return (WEXITSTATUS(status));
			}
			else
			{
				perror("fork");
				free(file_path);
				return (-1);
			}
		}
		free(file_path);
		token = strtok(NULL, DELIM);
	}
	errno = ENOENT;
	perror("Command not found");
	return (-1);
}


/**
 * my_wait - waits for the child process to terminate and prints the status
 *
 * @status: pointer to the status variable
 *
 * Return: the status of the child process
 */
int my_wait(int *status)
{
	pid_t pid;

	pid = wait(status);
	if (pid == -1)
	{
		perror("wait");
		return (-1);
	}
	if (WIFEXITED(*status))
	{
		printf("Child process exited with status %d\n", WEXITSTATUS(*status));
		return (WEXITSTATUS(*status));
	}
	else if (WIFSIGNALED(*status))
	{
		printf("Child process terminated by signal %d\n", WTERMSIG(*status));
		return (WTERMSIG(*status) + 128);
	}
	else if (WIFSTOPPED(*status))
	{
		printf("Child process stopped by signal %d\n", WSTOPSIG(*status));
		return (WSTOPSIG(*status) + 128);
	}
	else
	{
		fprintf(stderr, "Child process terminated abnormally\n");
		return (-1);
	}
	return (0);
}

/**
 * shell_loop - runs the shell loop
 */

void shell_loop(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t len;
	int status;
	char **args = calloc(MAX_ARGS, sizeof(char *));

	while ((len = getline(&line, &n, stdin)) != -1)
	{
		parse_input(line, args);
		status = create_fork(args);
		free_args(args);
		if (status == 0)
		{
			break;
		}
	}

	free(line);
	free(args);
}

/**
 * free_args - frees the memory allocated for the arguments
 *
 * @args: array of arguments
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}
