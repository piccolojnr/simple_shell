#include "shell.h"
/**
 * split_env - Splits environment variables into name and value.
 * @str: The string to split.
 *
 * Return: A pointer to an array of strings containing name and value.
 */
char **split_env(char *str)
{
char *str_copy, **result = NULL, *name = NULL,
*value = NULL, *token = NULL;
const char *delimiter = "=";

if (!str)
return (NULL);
str_copy = _strdup(str);
if (!str_copy)
{
return (NULL);
}
token = _strtok(str_copy, delimiter);
if (token)
{
name = _strdup(token);
if (!name)
{
perror("strdup"), free(str_copy);
return (NULL);
}
token = _strtok(NULL, delimiter);
if (token)
{
value = _strdup(token);
if (!value)
{
perror("strdup"), free(name), free(str_copy);
return (NULL);
}
}
}
result = (char **)malloc(sizeof(char *) * 2);
if (!result)
{
perror("malloc"), free(name), free(value), free(str_copy);
return (NULL);
}
result[0] = name, result[1] = value, result[2] = NULL;
free(str_copy);
return (result);
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
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}
/* Copy the path and add a '/' character */
_strcpy(result, path);
_strcat(result, "/");
/* Concatenate the command */
_strcat(result, cmd);
return (result);
}
/**
 * is_line_empty - Checks if a line is empty.
 * @line: The line to check.
 *
 * Return: 1 if the line is empty, otherwise 0.
 */
int is_line_empty(const char *line)
{
if (line == NULL || line[0] == '\0' || line[0] == ' '
|| line[0] == '\t' || line[0] == '\n')
return (1);
else
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
return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
|| c == '\f' || c == '\r' || c == '\0');
}

/**
 * int_to_string - Converts an integer to a string.
 * @num: The integer to convert.
 *
 * Return: The converted string.
 */
char *int_to_string(int num)
{
int i, j, is_negative = 0, num_digits = 0;
char *str;
/*Handle the case of a negative number*/
if (num < 0)
{
is_negative = 1;
num = -num;
num_digits++;
}
/*Calculate the number of digits*/
num_digits += count_digits(num);
/*Allocate memory for the string*/
str = (char *)malloc(sizeof(char) * (num_digits + 1));
if (str == NULL)
return (NULL);
/*Handle the case of 0 separately*/
if (num == 0)
{
str[0] = '0';
str[1] = '\0';
return (str);
}

for (i = num_digits - 1; i >= 0; i--)
{
str[i] = (num % 10) + '0';
num /= 10;
}

str[num_digits] = '\0';
if (is_negative)
{
for (j = num_digits; j >= 0; j--)
{
str[j + 1] = str[j];
}
str[0] = '-';
}
return (str);
}
