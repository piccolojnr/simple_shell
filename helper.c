#include "shell.h"
/**
 * allocate_and_copy - allocates memory for a copy of a string
 * @str: string to be copied
 * @length: length of string
 *
 * Return: pointer to allocated memory
 */
char *allocate_and_copy(const char *str, int length)
{
	char *copy = (char *)malloc(length + 1);

	if (copy == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	_strncpy(copy, (char *)str, length);
	copy[length] = '\0';
	return (copy);
}
/**
 * count_words - counts the number of words in a string
 * @str: string to be counted
 * @delim: delimiter
 *
 * Return: number of words
*/
int count_words(const char *str, char *delim)
{
	int word_count = 0, k;

	for (k = 0; str[k] != '\0'; k++)
	{
		if (!is_delim(str[k], delim) &&
		(is_delim(str[k + 1], delim) || str[k + 1] == '\0'))
			word_count++;
	}
	return (word_count);
}
/**
 * is_delim - checks if a character is a delimiter
 * @c: character to be checked
 * @delim: delimiter
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	int i, res = 0;

	for (i = 0; delim[i]; i++)
	{
		if (c == delim[i])
		{
			res = 1;
			break;
		}
	}

	return (res);
}
