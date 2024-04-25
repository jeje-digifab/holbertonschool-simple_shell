#include "shell.h"

int read_command(char *command, size_t size) {
    if (fgets(command, size, stdin) == NULL) {
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }
    }
    command[strcspn(command, "\n")] = '\0';
    return 1;
}

void sigint_handler(int signum) {
    static int sigint_received;
    (void)signum;

    if (!sigint_received) {
        sigint_received = 1;
        signal(SIGINT, SIG_IGN);
        printf("\n");
        display_prompt();
        fflush(stdout);
        signal(SIGINT, sigint_handler);
        sigint_received = 0;
    }
}
