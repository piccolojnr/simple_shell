#include "shell.h"


/**
 * replace_env_var - Replaces environment variable references in argv
 * @info: Pointer to the info_t structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_env_var(info_t *info)
{
	int i;
	char *env_name;

	for (i = 0; i < info->argc; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		else if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		else if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		else
		{
			env_name = _getenv(info->argv[i] + 1);
			if (env_name)
				replace_string(&(info->argv[i]), _strdup(env_name));
			else
				replace_string(&(info->argv[i]), _strdup(""));
		}
	}
	return (EXIT_SUCCESS);
}
/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * logical_operators_helper - checks logical operators
 * @info: information
 * @tmp: temporary
 * @line: line
 * @start: start
 * @end: end
 * @is_and_operator: is_and_operator
 * @exit_status: exit_status
 * @success:
 *
 * Return: success
*/
int logical_operators_helper(info_t *info, char **tmp, char *line, int start,
							 int end, int is_and_operator, int *exit_status, int success)
{
	*tmp = extract_substring(line, start, end);
	info->line = *tmp;
	info->char_len = _strlen(*tmp) + 1;
	*exit_status = execute_logical_command(info, is_and_operator);
	if (*exit_status == -2)
	{
		free(*tmp);
		return (-2);
	}
	if (!*exit_status)
	{
		success = EXIT_FAILURE;
		free(*tmp);
		return (success);
	}
	free(*tmp);
	return (success);
}
