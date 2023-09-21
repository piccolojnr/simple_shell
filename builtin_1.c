#include "shell.h"
/**
 * which_builtin - looks for files in the current path
 * @info: the parameter struct
 *
 * Return: 1 if found, 0 if not
 */
int which_builtin(info_t *info)
{
	int i, j, k;
	char *path;
	char **paths = NULL;
	struct stat file_stat;
	char *filepath; /* Adjust the buffer size as needed */

	if (info->argc < 2)
	{
		_printf("Usage: %s filename ...\n", info->argv[0]);
		return (EXIT_FAILURE);
	}

	path = _getenv("PATH");
	if (path == NULL)
	{
		_printf("PATH environment variable not found.\n");
		return (EXIT_FAILURE);
	}

	j = split_str(path, &paths, ":");

	for (i = 0; i < j; i++)
	{
		for (k = 1; k < info->argc; k++)
		{
			filepath = concat_path_and_cmd(paths[i], info->argv[k]);
			if (filepath == NULL)
			{
				perror("which error");
				return (EXIT_FAILURE);
			}
			if (stat(filepath, &file_stat) == 0)
			{
				if (S_ISREG(file_stat.st_mode))
					_printf("%s\n", filepath);
			}
			free(filepath);
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
int exit_builtin(info_t *info)
{
	int exit_status;

	if (info->argc > 2)
	{
		_printf("exit: too many arguments.\n");
		return (EXIT_FAILURE);
	}

	if (info->argc == 2)
	{
		exit_status = _atoi(info->argv[1]);
		free_info(info);
		exit(exit_status);
		return (-2);
	}
	return (-2);
}
/**
 * env_builtin - prints the current environment
 * @info: the parameter struct
 *
 * Return: 0 on success, 1 on failure
 */
int env_builtin(info_t *info)
{
	int i;

	(void)info; /* Unused parameter */

	for (i = 0; environ[i]; i++)
	{
		_printf("%s\n", environ[i]);
	}

	return (EXIT_SUCCESS);
}
/**
 * setenv_builtin - sets an environment variable
 * @info: the parameter struct
 *
 * Return: 0 on success, 1 on failure
 */
int setenv_builtin(info_t *info)
{

	if (info->argc != 3)
	{
		_printf("Usage: setenv varname varvalue\n");
		return (EXIT_FAILURE);
	}

	if (!_setenv(info->argv[1], info->argv[2], 1, &(info->env)))
	{
		_printf("Error: setenv failed\n");
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
int unsetenv_builtin(info_t *info)
{

	if (info->argc != 2)
	{
		_printf("Usage: unsetenv varname\n");
		return (EXIT_FAILURE);
	}

	if (!_unsetenv(info->argv[1], &(info->env)))
	{
		_printf("Error: unsetenv failed\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
