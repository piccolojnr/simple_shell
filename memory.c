#include "shell.h"
/**
 * ffree - frees a double pointer
 * @ar: double pointer to free
 */
void ffree(char **ar)
{
int i;

for (i = 0; ar[i] != NULL; i++)
{
free(ar[i]);
}
free(ar);
}
