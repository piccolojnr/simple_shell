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
int find_builtin(info_t *info, t_env **env_list)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"which", which_builtin},
		{"exit", exit_builtin},
		{"env", env_builtin},
		{"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
		{"cd", chdir_builtin},
		{NULL, NULL}};

	/* find built-in command */
	for (i = 0; builtintbl[i].type; i++)
	{
		if (info->argv[0] && _strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			built_in_ret = builtintbl[i].func(info, env_list);
			break;
		}
	}

	return (built_in_ret);
}

/**
 * replace_env_var - Replaces environment variable references in argv
 * @info: Pointer to the info_t structure
 */
void replace_env_var(info_t **info, t_env *env_list)
{
	int i;
	char *env_name, *env_value, *new_arg;
	pid_t shell_pid = getpid();

	for (i = 0; i < (*info)->argc; i++)
	{
		if ((*info)->argv[i][0] == '$' && (*info)->argv[i][1] != '\0' && (*info)->argv[i][1] != '\n')
		{
			env_name = (*info)->argv[i] + 1; /* Skip the '$' symbol */
			if (_strcmp(env_name, "$"))
			{
				new_arg = int_to_string((int)shell_pid);
				if (new_arg == NULL)
				{
					perror("int_to_string");
					exit_shell(*info, EXIT_FAILURE);
				}
				free((*info)->argv[i]);
				(*info)->argv[i] = new_arg;
			}
			else if (_strcmp(env_name, "?"))
			{
				new_arg = int_to_string((*info)->status);
				if (new_arg == NULL)
				{
					perror("int_to_string");
					exit_shell(*info, EXIT_FAILURE);
				}
				free((*info)->argv[i]);
				(*info)->argv[i] = new_arg;
			}
			else
			{
				env_value = _getenv(env_name, env_list);

				if (env_value)
				{
					new_arg = _strdup(env_value);
					if (!new_arg)
					{
						perror("strdup");
						exit_shell(*info, EXIT_FAILURE); /* Handle memory allocation failure */
					}
					free((*info)->argv[i]);		/* Free the old argument */
					(*info)->argv[i] = new_arg; /* Assign the new argument */
				}
				else
				{
					/* Environment variable not found, set the argument to NULL */
					free((*info)->argv[i]); /* Free the old argument */
					(*info)->argv[i] = NULL;
				}
			}
		}
	}
	replace_args(info); /* Replace $n references in argv */
}
/**
 * replace_args - Replaces $n references in argv with their
 * @info: Pointer to the info_t structure
 */
void replace_args(info_t **info)
{
	int i, j, k, new_argc = 0;
	char **new_argv;

	for (i = 0; i < (*info)->argc; i++)
	{
		if ((*info)->argv[i])
			new_argc++;
	}

	new_argv = malloc(sizeof(char *) * new_argc);
	if (!new_argv)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	for (j = 0, k = 0; k < (*info)->argc; k++)
	{
		if ((*info)->argv[k])
		{
			new_argv[j++] = (*info)->argv[k];
		}
	}
	/* Free the old argv array */
	new_argv[j] = NULL;

	free((*info)->argv);
	(*info)->argv = new_argv;
	(*info)->argc = new_argc;
}
