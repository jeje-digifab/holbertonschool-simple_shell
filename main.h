#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE_LENGTH 80

extern char **environ;


int main(void);
char *read_input(char **input, size_t *len);
void process_input(char *input);
void print_env(void);
int interactive(void);


#endif
