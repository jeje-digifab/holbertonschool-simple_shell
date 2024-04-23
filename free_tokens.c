#include "shell.h"
/**
 * free_tokens - function that free the stored token
 *
 * @tokens: token which are stored on the function parse_user_input
 *
 * Return: nothing
*/
void free_tokens(char **tokens)
{
	int index;

	if (tokens == NULL)
	{
		free(tokens);
		return;
	}

	for (index = 0; tokens[index] != NULL; index++)
	{
		free(tokens[index]);
	}

	free(tokens);
}
