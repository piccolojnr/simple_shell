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
 * replace_env_var - Replaces environment variable references in argv
 * @info: Pointer to the info_t structure
 */
void replace_env_var(info_t **info)
{
	int i;
	char *env_name, *env_value;

	for (i = 0; i < (*info)->argc; i++)
	{
		if ((*info)->argv[i][0] == '$' && (*info)->argv[i][1] != '\0' && (*info)->argv[i][1] != '\n')
		{
			env_name = (*info)->argv[i] + 1; /* Skip the '$' symbol */
			env_value = _getenv(env_name);

			if (env_value)
			{
				free((*info)->argv[i]);				   /* Free the original argument */
				(*info)->argv[i] = _strdup(env_value); /* Replace with the environment variable value */
				if (!(*info)->argv[i])
				{
					perror("strdup");
					exit(EXIT_FAILURE); /* Handle memory allocation failure */
				}
			}
			else
			{
				/* Environment variable not found, set the argument to NULL */
				free((*info)->argv[i]);
				(*info)->argv[i] = NULL;
			}
		}
	}
}
