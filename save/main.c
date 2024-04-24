#include "shell.h"

#include "shell.h"

int main(void)
{
    return process_sig();
}

void _isatty(void)
{
	if (isatty(STDIN_FILENO))
		printf("#cisfun$ ");
}
