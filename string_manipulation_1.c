#include "shell.h"
/**
 * trimm_str - trim the string
 * @str: string
 *
 * Return: string
 */
char *trimm_str(char *str)
{
char *end, *tmp_str, *res;
tmp_str = str;
if (str == NULL)
return (NULL);
end = str + _strlen(str) - 1;
while (end >= str && *end == ' ')
{
*end = '\0';
end--;
}
while (*str && *str == ' ')
str++;
res = _strdup(str);
free(tmp_str);
return (res);
}
/**
 * _strlen - get the length of string
 * @str: string
 *
 * Return: length
 */
int _strlen(const char *str)
{
int i = 0;
char *p = (char *)str;
while (*p != '\0')
{
i++;
p++;
}
return (i);
}
/**
 * _strdup - duplicate string
 * @s: string
 *
 * Return: string
 */
char *_strdup(const char *s)
{
int len;
char *dup;
len = _strlen(s);
dup = malloc(sizeof(char) * (len + 1));
if (dup == NULL)
return (NULL);
_strcpy(dup, s);
return (dup);
}
/**
 * _strcpy - copy string
 * @dest: destination
 * @src: source
 *
 * Return: destination
 */
char *_strcpy(char *dest, const char *src)
{
int i;

if (src == NULL || dest == NULL)
return (NULL);

for (i = 0; src[i] != '\0'; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}

/**
 * count_substrings - get the length of string with delimiter
 * @str: string
 * @delim: delimiter
 *
 * Return: length
 */
int count_substrings(char *str, const char *delim)
{
int count = 0;

while (*str != '\0')
{
if (*str == '\0')
break;
if (!is_delim(*str, delim))
{
count++;
while (!is_delim(*str, delim) && *str != '\0')
str++;
}
else
{
str++;
}
}

return (count);
}
