#include "shell.h"
/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(cmd_info **info)
{
	int i, j, built_in_ret = -1;
	char *env;
	builtin_table builtintbl[] = {
		{"_which", _which},
		{NULL, NULL}
	};
	/* find built-in command */
	for (j = 0; j < (*info)->argc; j++)
	{
		if ((*info)->argv[j][0] == '$')
		{
			env = _getenv((*info)->argv[j] + 1);
			free((*info)->argv[j]);
			if (env)
			{
				(*info)->argv[j] = env;
			}
			else
			{
				(*info)->argv[j] = NULL;
			}
		}
	}

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp((*info)->argv[0], builtintbl[i].type) == 0)
		{
			built_in_ret = builtintbl[i].func(*info);
			break;
		}
	}

	return (built_in_ret);
}
