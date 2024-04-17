#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

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
	/*char node *next;*/
	struct node *next;
};

/*main.c*/
int main(void);

/*interactive.c*/
char *read_input(char **input, size_t *len);
void process_input(char *input);
void print_env(void);
int interactive(void);

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



#endif
