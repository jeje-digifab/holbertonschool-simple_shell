#include "shell.h"

/**
 * main - Entry point of the program
 *
 * Description: This function serves as the entry point of the program.
 * It contains the main loop that repeatedly prompts the user for input,
 * reads the input command, and executes it until the user enters the
 * "exit" command.
 * Signals are also handled within this function.
 *
 * Return: Always returns EXIT_SUCCESS upon successful completion.
 */

int main(void)
{
	char command[128];

	signal(SIGINT, sigint_handler);

	while (1)
	{
		display_prompt();
		read_command(command, sizeof(command));

		if (strcmp(command, "exit") == 0)
		{
			break;
		}

		execute_command(command);

		fflush(stdin);
	}

	return (EXIT_SUCCESS);
}

