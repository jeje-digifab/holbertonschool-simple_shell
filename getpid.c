#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/**
 * _getpid - obtém o PID do processo em execução
 *
 * Return: string do PID
 */
char *_getpid(void)
{
    size_t len;
    char *s = NULL;
    char *pid = NULL;
    int fd;
    char *name;
    char *file = "/proc/self/status";

    FILE *file_ptr;

    s = malloc(256);
    if (s == NULL) {
        perror("malloc");
        return NULL;
    }

    fd = open(file, O_RDONLY);
    if (fd == -1) {
        perror("open");
        free(s);
        return NULL;
    }

    file_ptr = fdopen(fd, "r");
    if (file_ptr != NULL) {
        len = 256;
        if (fgets(s, len, file_ptr) != NULL) {
            name = strtok(s, ":");
            if (name != NULL && strcmp(name, "Pid") == 0) {
                pid = strdup(strtok(NULL, "\n \t"));
            }
        }
        fclose(file_ptr);
    } else {
        perror("fdopen");
    }

    free(s);

    return pid;
}
