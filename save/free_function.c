#include "shell.h"

void freearv(char **arv)
{
   int i;
   
    if (arv == NULL)
        return;

    for (i = 0; arv[i] != NULL; i++) {
        free(arv[i]);
    }
    free(arv);
}
