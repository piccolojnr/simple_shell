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
/**
 * concat_path_and_cmd - Concatenates a path and command.
 * @path: The path to concatenate.
 * @cmd: The command to concatenate.
 *
 * Return: A pointer to the concatenated string.
 */
char *concat_path_and_cmd(const char *path, const char *cmd)
{
    /* Calculate the total length needed for the result */
    size_t path_len = _strlen((char *)path);
    size_t cmd_len = _strlen((char *)cmd);
    /* +1 for '/' and +1 for '\0' */
    size_t result_len = path_len + 1 + cmd_len + 1;
    /* Allocate memory for the result */
    char *result = (char *)malloc(result_len);
    if (result == NULL)
    {
        perror("concat path");
        return (NULL);
    }
    /* Copy the path and add a '/' character */
    _strcpy(result, path);
    _strcat(result, "/");
    /* Concatenate the command */
    _strcat(result, cmd);
    return (result);
}