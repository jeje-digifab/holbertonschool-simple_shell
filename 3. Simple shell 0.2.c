#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Point d'entrée de l'interpréteur de ligne de commande
 *
 * Return: Toujours 0 (Succès)
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    char **args;
    int i;

    while (1)
    {
        printf("$ ");
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            printf("\n");
            free(line);
            exit(EXIT_SUCCESS);
        }
        else
        {
            /* Split the line into arguments */
            args = malloc(sizeof(char *) * 64);
            token = strtok(line, " \n");
            for (i = 0; token != NULL; i++)
            {
                args[i] = token;
                token = strtok(NULL, " \n");
            }
            args[i] = NULL;

            /* Execute the command */
            if (fork() == 0)
            {
                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            }
            else
            {
                wait(NULL);
            }

            free(args);
        }
    }
    return (0);
}
