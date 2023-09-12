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
		temp = _realloc(temp, sizeof(char *) *
			(word_count - 1), sizeof(char *) * (word_count + 1));
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
