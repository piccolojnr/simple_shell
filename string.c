#include "shell.h"
/**
 * split_str - Splits a string into an array of words.
 * @str: The string to be split.
 * @args: A pointer to the array of words.
 * @delim: The delimiter used for splitting.
 *
 * Return: The number of words in the array or -1 on failure.
 */
int split_str(char *str, char ***args, char *delim)
{
	int word_count = 0;
	char *token, **temp, *str_copy = NULL;

	if (!str || !args || !delim)
		return (-1);

	*args = NULL;
	str_copy = _strdup(str);
	if (!str_copy)
	{
		perror("Memory allocation failed");
		return (-1);
	}

	token = _strtok(str_copy, delim);
	while (token)
	{
		word_count++;
		temp = _realloc2(temp, sizeof(char *) * (word_count - 1)
							, sizeof(char *) * (word_count + 1));
		if (!temp)
		{
			perror("Memory allocation failed");
			free(str_copy);
			return (-1);
		}
		*args = temp;
		(*args)[word_count - 1] = _strdup(token);
		if (!(*args)[word_count - 1])
		{
			perror("Memory allocation failed");
			free(str_copy);
			return (-1);
		}
		(*args)[word_count] = NULL;
		token = _strtok(NULL, delim);
	}
	free(str_copy);
	return (word_count);
}

/**
 * free_args - frees an array of arguments
 * @args: array of arguments
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
	{
		free(args[i]);
	}
	free(args);
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
