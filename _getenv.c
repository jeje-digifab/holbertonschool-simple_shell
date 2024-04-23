#include "shell.h"
/**
 * _getenv - function that finds a specific environment variable
 *
 * @name: pointer to the name of the env variable to find
 *
 * Return: the value of env variable or NUL if not found
*/
char *_getenv(const char *name)
{
	int index;

	for (index = 0; environ[index]; index++)
	{
		if (strncmp(name, environ[index], strlen(name)) == 0
					&& environ[index][strlen(name)] == '=')
		{
			return (environ[index]);
		}
	}
	return (NULL);
}
