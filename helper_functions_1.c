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
/**
 * isspace - Checks if a character is a space.
 * @c: The character to check.
 *
 * Return: 1 if the character is a space, otherwise 0.
 */
int isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
            c == '\f' || c == '\r' || c == '\0');
}
/**
 * is_only_spaces - checks if string only contains spaces
 * @str: string to check
 *
 * Return: 1 if only spaces, 0 otherwise
 */
int is_only_spaces(const char *str)
{
    int i;

    for (i = 0; str[i]; i++)
    {
        if (isspace(str[i]) == 0)
        {
            return (0);
        }
    }
    return (1);
}