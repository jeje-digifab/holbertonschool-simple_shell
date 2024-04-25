#include "shell.h"

int custom_execlp(const char *file, const char *arg0, ...) {
    int i = 1;
    va_list args;
    const char *argv[10];
    char *full_path = realpath(file, NULL);

    argv[0] = arg0;
    va_start(args, arg0);

    while ((argv[i] = va_arg(args, const char *)) != NULL && i < 9) {
        i++;
    }
    va_end(args);
    argv[i] = NULL;

    if (full_path == NULL) {
        perror("realpath");
        return -1;
    }

    if (execve(full_path, (char *const *)argv, NULL) == -1) {
        perror(argv[0]);
        free(full_path);
        return -1;
    }

    free(full_path);
    return 0;
}

void execute_command(char **args) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
}
