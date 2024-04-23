#ifndef __SHELL__
#define __SHELL__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * struct path_node - node of the path
 *
 * @directory: contains a directory
 * Each directory is a pointer to the first node of a linked list
 * @next: pointer to the next node
*/
typedef struct path_node
{
	char *directory;
	struct path_node *next;
} path_list;

extern char **environ;

char *get_path();
int main(__attribute__((unused)) int argc, char *argv[]);
char **parse_user_input(char *input);
path_list *create_path_list (char *path);
char *search_executable_files(path_list *head, const char *user_input);
void execute_command(char **input, char *program_name);
int handle_command(char *command, char *program_name);
int read_user_input(char **input);
int print_environnement(void);
void free_path_list(path_list *head);
void free_tokens(char **tokens);
char *_getenv(const char *name);
int check_access(const char *path);

#endif
