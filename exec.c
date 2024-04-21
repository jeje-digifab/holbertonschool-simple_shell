#include "main.h"

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int execute_command(void)
{
	char *argv[] = {"/bin/ls", "-l", NULL};
   int val = execv(argv[0], argv);

   if (val == -1)
         perror("Error");

	printf("Before execve\n");

	return (0);
}
