#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELIMITER " \n\t"
#define COMMAND_SIZE 128

extern char **environ;

typedef struct list_path
{
    char *dir;
    struct list_path *p;
} list_path;

/* display_prompt.c */
void display_prompt(void);

/* exec_com.c */
int custom_execlp(const char *file, const char *arg0, ...);
void execute_command(char **args);

/* exit_function.c */
void exitt(char **arv);

/* user_input.c */
int read_command(char *command, size_t size);
void sigint_handler(int signum);

/* Utility functions */
char *_getenv(const char *name);
char *_strdup(char *str);
char *concat_all(char *name, char *sep, const char *value);
int _strlen(char *s);
int _atoi(char *s);
list_path *add_node_end(list_path **head, char *str);
char **parse_args(char *command);
char *find_executable(const char *command);

#endif /* SHELL_H */
