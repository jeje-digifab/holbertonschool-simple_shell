#include "shell.h"
/**
 * print_environnement - function that print the 'env' of the PATH
 *
 * Return: 0 on success
*/
int print_environnement(void)
{
	int index = 0;

	for (index = 0; environ[index] != NULL; index++)
	{
		printf("%s\n", environ[index]);
	}

	return (0);
}
