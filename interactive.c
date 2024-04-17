#include "main.h"

/**
 * interactive - Runs a simple interactive shell
 *
 * This function reads lines of input from the user in an infinite loop,
 * processes the input, and performs the appropriate action.
 *
 * Return: Always returns 0
 */

int interactive(void)
{
	char *input = NULL;
	size_t len = 0;

	signal(SIGINT, sigint_handler);

	while (1)
	{
		input =  read_input(&input, &len);
		process_input(input);
	}
	free(input);
	return (0);

}

/**
 * read_input - reads a line of input from stdin and stores it in a buffer
 * @input: a double pointer to a buffer to store the input
 * @len: a pointer to a size_t variable containing the size of the buffer
 *
 * Return: a pointer to the buffer containing the input
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

/**
 * process_input - processes a line of input from the user
 * @input: a pointer to a buffer containing the input
 *
 * Return: void
 */

void process_input(char *input)
{
	if (strcmp(input, "exit\n") == 0)
	{
		free(input);
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


/**
 * print_env - prints the environment variables
 *
 * Return: void
 */

void print_env(void)
{
	char **env;

	for (env =  environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}

/**
 * sigint_handler - Handles the SIGINT signal
 * @signum: The signal number (unused in this function)
 *
 * Description: This function is called when the SIGINT signal is received.
 *		It prints a newline character and resets the signal handler to
 *		its default behavior.
 */

void sigint_handler(int signum)
{
	static int sigint_received;
	(void) signum;

	if (!sigint_received)
	{
		sigint_received = 1;
		signal(SIGINT, SIG_IGN);
		printf("\n");
		printf("$ ");
		fflush(stdout);
		signal(SIGINT, sigint_handler);
		sigint_received = 0;
	}
}
