#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
            system(line);
        }
    }
    return (0);
}
