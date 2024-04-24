#include "shell.h"

#define BUFFER_SIZE 1024

extern char **environ;

char *read_input(char **input, size_t *len) {
    int read;

    printf("#cisfun$ ");
    read = getline(input, len, stdin);
    if (read == -1) {
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        }
        perror("getline");
        exit(EXIT_FAILURE);
    }
    return (*input);
}

void process_input(char *input) 
{
    int i = 0;
    char *args[10]; 

    char *token = strtok(input, " ");

    if (strcmp(input, "exit\n") == 0) {
        free(input);
        exit(EXIT_SUCCESS);
    } else if (strcmp(input, "\n") == 0) {
      
    } else {
        input[strcspn(input, "\n")] = '\0'; 
        
        while (token != NULL && i < 9) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            exitt(args);
        } else {
            execute_command(input);
        }
    }
}

void print_env(void) {
    char **env;
    for (env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void sigint_handler(int signum) {
    (void) signum;
    printf("\n#cisfun$ ");
    fflush(stdout);
}

int custom_execlp(const char *file, const char *arg0, ...) {
    int i = 1;
    va_list args;
    const char *argv[10];

    argv[0] = arg0;
    va_start(args, arg0);

    while ((argv[i] = va_arg(args, const char *)) != NULL && i < 9) {
        i++;
    }
    va_end(args);
    argv[i] = NULL;

    execvp(file, (char *const *)argv);

    return -1;
}

void execute_command(const char *command) {
    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        custom_execlp(command, command, (char *)NULL);
        perror("custom_execlp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

int process_sig(void) 
{
    char *input = NULL;
    size_t len = 0;
    signal(SIGINT, sigint_handler);
    while (1) {
        input = read_input(&input, &len);
        process_input(input);
    }

    return 0;
}
