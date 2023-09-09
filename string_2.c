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
 * _strcpy - Copy a string.
 * @dest: Destination string where the copy is stored.
 * @src: Source string to be copied.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strcpy(char *dest, const char *src)
{
	char *result = dest;

	while (*src)
		*dest++ = *src++;

	/* Null-terminate the destination string */
	*dest = '\0';

	return (result);
}
/**
 * _strncpy - Copy a string.
 * @dest: Destination string where the copy is stored.
 * @src: Source string to be copied.
 * @n: Number of bytes to copy.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strncpy(char *dest, const char *src, int n)
{
	char *result = dest;
	int i = 0;

	while (*src && i < n)
	{
		*dest++ = *src++;
		i++;
	}

	/* Null-terminate the destination string if there's space left */
	while (i < n)
	{
		*dest++ = '\0';
		i++;
	}

	return (result);
}
/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
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
