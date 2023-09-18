#include "shell.h"
/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
/**
 * _strndup - duplicates a string
 * @str: the string to duplicate
 * @n: number of bytes to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strndup(const char *str, int n)
{
	int i;
	char *ret;

	if (str == NULL || n < 0)
		return (NULL);

	ret = malloc(sizeof(char) * (n + 1));

	if (!ret)
		return (NULL);

	for (i = 0; i < n && str[i] != '\0'; i++)
		ret[i] = str[i];

	ret[n] = '\0';

	return (ret);
}
/**
 * _strchr - locates a character ina string
 * @s: string to locate char
 * @c: charater to be located
 *
 * Return: first occurrence of the character c
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	if (*s == c)
	{
		return (s);
	}
	return (NULL);
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
/**
 * _strncmp  - compares two strangs.
 * @s1: the first strang
 * @s2: the second strang
 * @n: the number of bytes to compare
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (*s1 && *s2 && i < n - 1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		i++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
