#include "shell.h"

#define MAX_ARGS 20

/**
 * custom_execlp - Executes a file with given arguments
 * @file: The file to be executed
 * @arg0: The first argument to pass to the file
 *        (usually the name of the file)
 * @...: The rest of the arguments to pass to the file
 *
 * Description: This function is a custom version of execlp.
 *              It takes a file and a variable number of arguments,
 *              and executes the file with those arguments.
 *              The function uses execvp to execute the file,
 *              and perror to print an error message if the file
 *              is not found.
 *
 * Return: If the function succeeds, it does not return.
 *         If the function fails (and errno is set to ENOENT),
 *         it returns -1.
 */
int custom_execlp(const char *file, const char *arg0, ...)
{
    int i;

    va_list args;
    const char *argv[MAX_ARGS + 1];
    char *full_path = realpath(file, NULL);

    if (full_path == NULL)
    {
        perror("realpath");
        return -1;
    }

    argv[0] = arg0;
    va_start(args, arg0);

   
    for (i = 1; i < MAX_ARGS && (argv[i] = va_arg(args, const char *)) != NULL; i++)
    {
        
    }
    va_end(args);
    argv[i] = NULL;

    if (execve(full_path, (char *const *)argv, NULL) == -1)
    {
        perror(argv[0]);
        free(full_path);
        return -1;
    }

    free(full_path);
    return 0;
}

/**
 * execute_command - Executes a command passed as a string
 * @command: The command to be executed
 *
 * Description: This function forks the current process and executes the
 * command
 * passed as a string. It first tokens the command string into arguments using
 * spaces and tabs as delimiters. If the command is "exit", it exits the child
 * process. If the command is empty, it displays the prompt and exits the child
 * process. If the command is not "exit" and not empty, it uses execvp to
 * replace the child process with the command. If execvp fails, it prints an
 * error message and exits the child process. The parent process waits for the
 * child process to finish executing the command.
 *
 * Return: This function does not return a value
 */
void execute_command(const char *command)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    else if (child_pid == 0)
    {
        char *args[MAX_ARGS + 1]; 
        char *token = strtok((char *)command, " ");
        int i = 0;

        while (token != NULL && i < MAX_ARGS)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (i == 0)
        {
            display_prompt();
            exit(EXIT_SUCCESS);
        }
        if (strcmp(args[0], "exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        if (execvp(args[0], args) == -1)
        {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL);
    }
}
