#include "shell.h"

/**
 * _getenv - gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_getenv(const char *name)
{
    int i, j;
    char *value;

    if (!name)
        return (NULL);
    for (i = 0; environ[i]; i++)
    {
        j = 0;
        if (name[j] == environ[i][j])
        {
            while (name[j])
            {
                if (name[j] != environ[i][j])
                    break;

                j++;
            }
            if (name[j] == '\0')
            {
                value = (environ[i] + j + 1);
                return (value);
            }
        }
    }
    return (NULL);
}

list_path *add_node_end(list_path **head, char *str)
{
    list_path *tmp;
    list_path *new;

    new = malloc(sizeof(list_path));
    if (!new || !str)
    {
        return (NULL);
    }

    new->dir = str;
    new->p = NULL;
    if (!*head)
    {
        *head = new;
    }
    else
    {
        tmp = *head;
        while (tmp->p)
        {
            tmp = tmp->p;
        }
        tmp->p = new;
    }
    return (*head);
}

/**
 * exitt - exits the shell with or without a return of status n
 * @arv: array of words of the entered line
 */
void exitt(char **arv)
{
    int i, n;

    if (arv[1])
    {
        n = _atoi(arv[1]);
        if (n <= -1)
            n = 2;
        free(arv);
        exit(n);
    }
    for (i = 0; arv[i]; i++)
        free(arv[i]);
    free(arv);
    exit(0);
}

/**
 * _atoi - converts a string into an integer
 *@s: pointer to a string
 *Return: the integer
 */
int _atoi(char *s)
{
    int i, integer, sign = 1;

    i = 0;
    integer = 0;
    while (!((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'))
    {
        if (s[i] == '-')
        {
            sign = sign * (-1);
        }
        i++;
    }
    while ((s[i] >= '0') && (s[i] <= '9'))
    {
        integer = (integer * 10) + (sign * (s[i] - '0'));
        i++;
    }
    return (integer);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_DELIMITER ":"

/**
 * find_executable - Find the full path of an executable file
 * @command: The name of the command to search for
 *
 * Return: On success, the full path of the executable file. On failure, NULL.
 */
char *find_executable(const char *command) {
    char *path_env = _getenv("PATH");
    char *path_copy;
    char *path_token;

    if (path_env == NULL) {
        fprintf(stderr, "Error: PATH environment variable not found\n");
        return NULL;
    }

    path_copy = _strdup(path_env);
    if (path_copy == NULL) {
        perror("strdup");
        return NULL;
    }

    path_token = strtok(path_copy, PATH_DELIMITER);
    while (path_token != NULL) {
        char *executable_path = concat_all(path_token, "/", command);
        if (executable_path == NULL) {
            perror("concat_all");
            free(path_copy);
            return NULL;
        }

        if (access(executable_path, F_OK | X_OK) == 0) {
            free(path_copy);
            return executable_path;
        }

        free(executable_path);
        path_token = strtok(NULL, PATH_DELIMITER);
    }

    free(path_copy);
    return NULL;
}
