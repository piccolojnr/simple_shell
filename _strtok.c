#include "shell.h"

/**
 * _strtok - splits a string into tokens
 * @str: string to split
 * @delim: delimiter
 *
 * Return: pointer to the next token
 */
char *_strtok(char *str, const char *delim)
{
static char *next;
char *token, *tmp;
int i, j;
if (str != NULL)
next = str;
if (next == NULL || *next == '\0')
return (NULL);
while (*next != '\0' && _strchr((char *)delim, *next) != NULL)
next++;
tmp = next;
i = 0;
while (*next != '\0' && _strchr((char *)delim, *next) == NULL)
{
i++;
next++;
}
if (i == 0)
return (NULL);
token = malloc(sizeof(char) * (i + 1));
if (token == NULL)
return (NULL);
for (j = 0; j < i; j++)
token[j] = tmp[j];
token[j] = '\0';
next = tmp + i;
return (token);
}
