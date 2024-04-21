#include "main.h"

/**
 * #define MAX_LINE_LENGTH 80
 * #define MAX_ARGS 1
 */


int main(void)
{

	if (isatty(STDIN_FILENO))
	{
		return (interactive());
	}
	else
	{

	}
	return (0);
}
