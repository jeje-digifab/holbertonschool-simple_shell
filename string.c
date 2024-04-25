#include "shell.h"

/**
 * _strdup - Retorna um ponteiro para um espaço recém-alocado na memória, que
 * contém uma cópia da string fornecida como parâmetro.
 * @str: ponteiro para uma string
 * Return: ponteiro para uma string
 */
char *_strdup(char *str)
{
    int i, l;
    char *new;

    if (!str)
    {
        return (NULL);
    }
    for (l = 0; str[l] != '\0';)
    {
        l++;
    }
    new = malloc(sizeof(char) * (l + 1));
    if (!new)
    {
        return (NULL);
    }
    for (i = 0; i <= l; i++)
    {
        new[i] = str[i];
    }
    return (new);
}

char *concat_all(char *name, char *sep, const char *value) {
    char *result;
    int l1, l2, l3, i, k;

    l1 = _strlen(name);
    l2 = _strlen(sep);
    l3 = strlen(value);
    result = malloc(l1 + l2 + l3 + 1);
    if (!result)
        return NULL;

    for (i = 0; name[i]; i++)
        result[i] = name[i];
    k = i;

    for (i = 0; sep[i]; i++)
        result[k + i] = sep[i];
    k = k + i;

    for (i = 0; value[i]; i++)
        result[k + i] = value[i];
    k = k + i;

    result[k] = '\0';

    return result;
}

int _strlen(char *s)
{
    int i = 0;

    while (*(s + i) != '\0')
    {
        i++;
    }
    return (i);
}

#include "shell.h"

/**
 * parse_args - Parse a command string into an array of arguments
 * @command: A string representing the command to parse
 *
 * Return: On success, a dynamically allocated array of strings containing
 * the parsed arguments. On failure, NULL.
 */
char **parse_args(char *command)
{
    int i;
    char **args = NULL;
    char *token;
    int arg_count = 0;
     char **temp;

    args = malloc(sizeof(char *));
    if (args == NULL)
    {
        perror("malloc");
        return NULL;
    }

    token = strtok(command, DELIMITER);
    while (token != NULL)
    {
        char **temp;
        temp = realloc(args, (arg_count + 1) * sizeof(char *));
        if (temp == NULL)
        {
            perror("realloc");
            for (i = 0; i < arg_count; i++)
            {
                free(args[i]);
            }
            free(args);
            return NULL;
        }

        args = temp;

        args[arg_count] = strdup(token);
        if (args[arg_count] == NULL)
        {
            perror("strdup");
            for (i = 0; i < arg_count; i++)
            {
                free(args[i]);
            }
            free(args);
            return NULL;
        }

        token = strtok(NULL, DELIMITER);
        arg_count++;
    }

    temp = realloc(args, (arg_count + 1) * sizeof(char *));
    if (temp == NULL)
    {
        perror("realloc");
        for (i = 0; i < arg_count; i++)
        {
            free(args[i]);
        }
        free(args);
        return NULL;
    }
    args = temp;
    args[arg_count] = NULL;

    return args;
}
