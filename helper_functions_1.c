#include "shell.h"
/**
 * is_interactive - checks if stdin is interactive
 *
 * Return: 1 if interactive, 0 otherwise
 */
int is_interactive(void)
{
return (isatty(STDIN_FILENO));
}
/**
 * is_delim - checks if character is a delimeter
 * @c: character to check
 * @delim: delimeter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, const char *delim)
{
int i;
for (i = 0; delim[i] != '\0'; i++)
{
if (c == delim[i])
return (1);
}
return (0);
}
