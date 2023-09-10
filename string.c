#include "shell.h"
/**
 *  split_str - splits a string and returns an array
 * of each word of the string
 * @str: string to be split
 * @args: array of words
 * @delim: delimiter
 * @word_count: number of words
 *
 * Return: word_count
 */
int split_str(char *str, char ***args, char *delim,
			  int word_count)
{
	int i, count, word_index, remaining_length;

	if (!str)
		return (0);
	if (word_count == 0)
		word_count = count_words(str, delim);
	if (word_count == 0)
		return (0);
	*args = malloc(sizeof(char *) * (word_count + 1));
	if (*args == NULL)
	{
		perror("Memory allocation failed");
		return (0);
	}
	word_index = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		while (is_delim(str[i], delim))
			i++;
		count = 0;
		while ((!is_delim(str[i + count], delim) || word_index == word_count) &&
			   str[i + count] != '\0')
			count++;
		(*args)[word_index] = allocate_and_copy(str + i, count);
		if ((*args)[word_index] == NULL)
			return (-1);
		word_index++;
		i += count;
		if (word_index == word_count - 1)
		{
			remaining_length = strlen(str + i);
			(*args)[word_index] = allocate_and_copy(str + i + 1, remaining_length);
			if ((*args)[word_index] == NULL)
				return (-1);
			break;
		}
	}
	(*args)[word_count] = NULL;
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
