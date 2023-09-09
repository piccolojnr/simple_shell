#include "shell.h"
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
