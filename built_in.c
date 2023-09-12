#include "shell.h"
/**
 * which_builtin - looks for files in the current path
 * @info: the parameter struct
 *
 * Return: 1 if found, 0 if not
 */
int which_builtin(info_t *info, t_env **env_list)
{
	int i, j, k;
	char *path;
	char **paths = NULL;
	struct stat file_stat;
	char filepath[1024]; /* Adjust the buffer size as needed */

	if (info->argc < 2)
	{
		fprintf(stderr, "Usage: %s filename ...\n", info->argv[0]);
		return (EXIT_FAILURE);
	}

	path = _getenv("PATH", *env_list);
	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not found.\n");
		return (EXIT_FAILURE);
	}

	j = split_str(path, &paths, ":");

	for (i = 0; i < j; i++)
	{
		for (k = 1; k < info->argc; k++)
		{
			snprintf(filepath, sizeof(filepath), "%s/%s", paths[i], info->argv[k]);

			if (stat(filepath, &file_stat) == 0)
			{
				if (S_ISREG(file_stat.st_mode))
					printf("%s\n", filepath);
			}
		}
	}

	return (EXIT_SUCCESS);
}
/**
 * exit_builtin - exits the shell
 * @info: the parameter struct
 *
 * Return: 0 on success, 1 on failure
 */
int exit_builtin(info_t *info, t_env **env_list)
{
	int exit_status;

	(void)env_list;

	if (info->argc > 2)
	{
		printf("exit: too many arguments.\n");
		return (-2);
	}

	if (info->argc == 2)
	{
		exit_status = _atoi(info->argv[1]);
		exit_shell(info, exit_status);

		return (EXIT_SUCCESS);
	}

	exit_shell(info, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
/**
 * env_builtin - prints the current environment
 * @info: the parameter struct
 *
 * Return: 0 on success, 1 on failure
 */
int env_builtin(info_t *info, t_env **env_list)
{
	t_env *current = *env_list;

	(void)info;

	if (*env_list == NULL)
		return (1);

	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}

	return (0);
}
/**
 * setenv_builtin - sets an environment variable
 * @info: the parameter struct
 *
 * Return: 0 on success, 1 on failure
 */
int setenv_builtin(info_t *info, t_env **env_list)
{
	if (info->argc != 3)
	{
		printf("Usage: setenv varname varvalue\n");
		return (EXIT_FAILURE);
	}

	if (!_setenv(info->argv[1], info->argv[2], 1, env_list))
	{
		printf("Error: setenv failed\n");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
/**
 * unsetenv_builtin - deletes an environment variable
 * @info: the parameter struct
 *
 * Return: 0 on success, 1 on failure
 */
int unsetenv_builtin(info_t *info, t_env **env_list)
{
	if (info->argc != 2)
	{
		printf("Usage: unsetenv varname\n");
		return (EXIT_FAILURE);
	}

	if (!_unsetenv(info->argv[1], env_list))
	{
		printf("Error: unsetenv failed\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
