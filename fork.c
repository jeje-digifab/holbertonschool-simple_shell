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
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}

	if (pid == 0)
	{
		/*Code pour le processus fils*/
		if (execvp(args[0], args) == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
	}

	else
	{
		/*Code pour le processus parent*/
		wait(&status);
	}
	return (0);
}

/**
  * get_file_path - Get's the full path of the file
  * @file_name: Argument name
  *
  * Return: The full path argument to the file
  */

char *get_file_path(void)
{
		char *path = getenv("PATH");

		if (!path)
		{
			perror("Path not found");
			return (NULL);
		}

		return (path);
}

/*int my_execvp(char **args)*/
int my_execvp(void)
{
/*appeler execvp et renvoyer -1 en cas d'erreur*/

	const char * path = getenv( "PATH" );
	printf( "PATH environment variable == %s\n", path );

	return 0;
/*
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	printf("Before execve\n");
	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error:");
	}
	printf("After execve\n");
	return (0);
*/
}




/*
int my_wait(int *status)
{
	*/
	/*appeler wait et renvoyer le statut de sortie du processus enfant*/

/*
}
*/
