#include "shell.h"
/**
 * parse_string - parse string
 * @str: string
 * @del: delimiter
 * @args: arguments
 *
 * Return: number of arguments
 */
int parse_string(char *str, const char *del, char ***args)
{
char *token, **tmp_args, *tmp, *trimmed_str, *tmp_str;
int len;
if (str == NULL || del == NULL || args == NULL)
return (-1);
if (str[0] == '\0')
return (0);
tmp_str = _strdup(str);
if (tmp_str == NULL)
return (-1);
len = count_substrings(tmp_str, del);
tmp_args = malloc(sizeof(char *) * (len + 1));
if (tmp_args == NULL)
{
free(tmp_str);
return (-1);
}
token = strtok(tmp_str, del);
len = 0;
while (token != NULL)
{
tmp = _strdup(token);
if (tmp == NULL)
{
ffree(tmp_args);
free(tmp_str);
return (-1);
}
trimmed_str = trimm_str(tmp);
tmp_args[len] = trimmed_str;
len++;
token = strtok(NULL, del);
}
tmp_args[len] = NULL;
*args = tmp_args;
free(tmp_str);
return (len);
}
