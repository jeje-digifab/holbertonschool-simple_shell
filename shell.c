#include "shell.h"

int main(void) {
    char command[COMMAND_SIZE];

    signal(SIGINT, sigint_handler);

    while (1) {
        display_prompt();
        read_command(command, sizeof(command));

        if (strcmp(command, "exit") == 0) {
            break;
        }

        execute_command(parse_args(command));

        fflush(stdin);
    }

    return EXIT_SUCCESS;
}
