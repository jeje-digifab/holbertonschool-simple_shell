/*
#include "main.h"
*/
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <string.h> 

/*
#define MAX_LINE_LENGTH 80
#define MAX_ARGS 1
*/

extern char **environ;
int main (void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;
	char **env;
	while (1)
	{
		printf("$ ");
		read = getline(&input, &len, stdin);

		if (read == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}

		if (strcmp(input, "exit\n") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
			if (strcmp(input, "env\n") == 0)
		{
			
			for(env = environ; *env != NULL; env++)
			{
				printf("%s", *env);
		}
		}
		/*
		Execute commands based on 'input' here 
		Remember to fork a new process and use execve 
		*/
	}
	free(input);
	return (0);

}