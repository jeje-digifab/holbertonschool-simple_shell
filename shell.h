<<<<<<< HEAD
#ifndef SHELL_H
#define SHELL_H

#define DELIMITER " \t"
=======
#ifndef MAIN_H
#define MAIN_H
>>>>>>> matrix

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
<<<<<<< HEAD
#include <errno.h>
#include <stdarg.h>

/*display_prompt.c*/
void display_prompt(void);

/*exit_function.c*/
int _atoi(char *s);
void exitt(char **arv);

/*exec_com.c*/
int custom_execlp(const char *file, const char *arg0, ...);
void execute_command(const char *command);

/*exit_function.c*/
int _atoi(char *s);
void exitt(char **arv);

/*user_input.c*/
void user_input(char *command, size_t size);
void read_command(char *command, size_t size);
void sigint_handler(int signum);

#endif /* SHELL_H */
=======
#include <fcntl.h>
#include <stdarg.h> 

#define MAX_LINE_LENGTH 1024
#define MAX_TOKENS 64
#define MAX_ARGS 64
#define DELIMITER " \t\n"
#define MAX_COMMAND_LENGTH 1024
#define MAX_PATH_LENGTH 4096
#define DELIM ":"

extern char **environ;

/**
 * struct node - A structure to represent a node in a linked list of
 *               directories
 * @dir: A string containing the path of the directory represented by the node
 * @next: A pointer to the next node in the linked list
 */
struct node
{
    char *dir;
    struct node *next;
};

/*main.c*/
void _isatty(void);

/*interactive.c*/
char *read_input(char **input, size_t *len);
void process_input(char *input);
void print_env(void);
void execute_command(const char *command);
void exitt(char **arv);
void freearv(char **arv);
int process_sig(void);


/*non_interactive.c*/
int non_interactive(void);
int parse_input(char *input);
struct node *create_path_list(char *path);
void sigint_handler(int signum);

/*fork.c*/
int create_fork(char **args);
int my_wait(int *status);
int my_execvp(void);
char *get_file_path(void);
char *_getpid(void);


#endif
>>>>>>> matrix
