#include "main.h"



#define MAX_LINE_LENGTH 80

/**
 * #define MAX_LINE_LENGTH 80
 * #define MAX_ARGS 1
 */


char *read_input(char **input, size_t *len)
{
	ssize_t read;


	printf("$ ");
	read = getline(input, len, stdin);
	if (read == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	return (*input);
}

void process_input(char *input)
{
	if (strcmp(input, "exit\n") == 0)
	{
		exit(EXIT_SUCCESS);
	}

	else if (strcmp(input, "env\n") == 0)
	{
		print_env();
	}

	else if (strcmp(input, "\n") != 0)
	{
		input[strcspn(input, "\n")] = '\0';
		printf("%s: No such file or directory\n", input);
	}
}


void print_env(void)
{
	char **env;

	for (env =  environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}

int interactive(void)
{
	char *input = NULL;
	size_t len = 0;

	while (1)
	{
		input =  read_input(&input, &len);
		process_input(input);
	}
	free(input);
	return (0);

}

