#include "shell.h"
/**
 * run_shell - Runs the shell
 */
void run_shell(void)
{
	int shell_status = 1;
	info_t *info = malloc(sizeof(info_t));

	while (shell_status)
	{
		printf("piccolojnr$ ");

		get_input(info);

		/* Remove newline */
		info->line[info->char_len - 1] = '\0';

		/* Split the input line into arguments */
		info->argc = split_str(info->line, &info->argv, " \n\t\r\v\f");

		if (info->argv == NULL || info->argc == 0)
			continue; /* Ignore empty lines or input errors */

		replace_env_var(&info);

		/* Check if the command exists in the PATH and execute it */
		find_executable(&info);
		if (info->path != NULL && info->is_built_in == -1)
		{
			execute_command(info);
			free(info->path);
		}
		else if (info->is_built_in != -1)
		{
			continue;
		}
		else
			printf("%s: command not found tt\n", info->argv[0]);
	}

	exit_shell(info, EXIT_SUCCESS);
}

/**
 * find_executable - Finds an executable in the PATH
 * @info: A pointer to a info_t struct
 */
void find_executable(info_t **info)
{
	int i, path_len;
	char *path = _getenv("PATH");
	char **path_buffer;
	char *path_with_cmd;

	/* check for built ins */
	(*info)->is_built_in = find_builtin(info);
	if ((*info)->is_built_in != -1)
		return;

	if (path == NULL || (*info)->argv[0] == NULL)
		return;

	path_len = split_str(path, &path_buffer, ":");
	if (path_len == -1)
		exit_shell(*info, EXIT_FAILURE);

	for (i = 0; i < path_len; i++)
	{
		path_with_cmd = (char *)malloc(strlen(path_buffer[i])
			+ strlen((*info)->argv[0]) + 2);
		if (path_with_cmd == NULL)
		{
			perror("Memory allocation error");
			exit_shell(*info, EXIT_FAILURE);
		}

		path_with_cmd = concat_path_and_cmd(path_buffer[i], (*info)->argv[0]);

		if (access(path_with_cmd, X_OK) == 0)
		{
			free_args(path_buffer); /* Clean up the path_buffer */
			(*info)->path = path_with_cmd;
			return;
		}
		free(path_with_cmd);
	}
	return; /* Command not found in any PATH directory */
}
