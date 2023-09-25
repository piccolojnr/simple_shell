#include "shell.h"
/**
 * replace_char - replaces a char in a string
 * @str: the string to modify
 * @oldChar: the char to replace
 * @newChar: the char to replace with
 */
void replace_char(char *str, char oldChar, char newChar)
{
int i, length = strlen(str);
printf("result: %s\n", str);
for (i = 0; i < length; i++)
{
if (str[i] == oldChar)
{
str[i] = newChar;
}
}
printf("result: %s\n", str);
}
/**
 * find_num_sub - finds the number of occurences of a substring
 * @str: the string to search
 * @sub: the substring to find
 *
 * Return: the number of occurences of the substring
 */
int find_num_sub(char *str, char *sub)
{
char *tokenized = NULL, *new = NULL;
int i = 0;

if (_strlen(sub) > _strlen(str))
return (0);

new = _strdup(str);
tokenized = strtok(new, sub);
while (tokenized != NULL)
{
i++;
tokenized = strtok(NULL, sub);
}
free(new);
if (_strcmp(str + _strlen(str) - _strlen(sub), sub) == 0)
i++;
return (i - 1);
}
/**
 * _strcat - Concatenate two strings.
 * @dest: Destination string where the result is stored.
 * @src: Source string to be concatenated to the destination.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strcat(char *dest, const char *src)
{
char *result = dest;
/* Move dest pointer to the end of the destination string */
while (*dest)
dest++;
/* Copy characters from src to dest */
while (*src)
*dest++ = *src++;
/* Null-terminate the result string */
*dest = '\0';
return (result);
}
/**
 * _strncat - Concatenate two strings.
 * @dest: Destination string where the result is stored.
 * @src: Source string to be concatenated to the destination.
 * @n: Number of bytes to be copied from src to dest.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strncat(char *dest, const char *src, int n)
{
char *result = dest;
int i = 0;
/* Move dest pointer to the end of the destination string */
while (*dest)
dest++;
/* Copy characters from src to dest */
while (*src && i < n)
{
*dest++ = *src++;
i++;
}
/* Null-terminate the result string */
*dest = '\0';
return (result);
}
/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}
