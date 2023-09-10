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
int find_builtin(info_t **info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"which", which_builtin},
		{"exit", exit_builtin},
		{"env", env_builtin},
		{"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
		{NULL, NULL}};

	/* find and replace env var */
	replace_env_var(info);

	/* find built-in command */
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

/**
 * replace_env_var - finds and replaces environment variables
 * with their values
 * @info: ..
 */
void replace_env_var(info_t **info)
{
	int i;
	char *env;

	for (i = 0; i < (*info)->argc; i++)
	{
		if ((*info)->argv[i][0] == '$' &&
			(*info)->argv[i][1] != '\0' && (*info)->argv[i][1] != '\n')
		{
			env = _getenv((*info)->argv[i] + 1);
			free((*info)->argv[i]);
			if (env)
			{
				(*info)->argv[i] = env;
			}
			else
			{
				(*info)->argv[i] = NULL;
			}
		}
	}
}