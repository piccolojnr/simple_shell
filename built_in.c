#include "shell.h"
/**
 * which_builtin - looks for files in the current path
 * @info: the parameter struct
 *
 * Return: 1 if found, 0 if not
 */
int which_builtin(cmd_info *info)
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

	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not found.\n");
		return (EXIT_FAILURE);
	}

	j = split_str(path, &paths, ":", 0);

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
int exit_builtin(cmd_info *info)
{
	(void)info;

	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
