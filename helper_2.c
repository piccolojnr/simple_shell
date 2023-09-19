#include "shell.h"
/**
 * count_digits - Counts the number of digits in an integer.
 * @num: The integer to count.
 *
 * Return: The number of digits in the integer.
 */
int count_digits(int num)
{
	int count = 0;

	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}
/**
 * execute_logical_command - Executes a logical command.
 * @info: A pointer to the info structure.
 * @env_list: ...
 * @alias_list: ...
 * @and_operator: The operator of the logical command.
 *
 * Return: The exit status of the logical command.
 */
int execute_logical_command(info_t **info, t_env **env_list,
		alias_t **alias_list, int and_operator)
{
	int exit_status = start_process(info, env_list, alias_list);

	if ((and_operator && exit_status == 0) ||
			(!and_operator && exit_status != 0))
		return (1);
	else
		return (0);
}

