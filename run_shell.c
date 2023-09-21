#include "shell.h"
/**
 * run_shell_interactive - Runs the shell
 * @info: A pointer to a info_t struct
 *
 * Return: 0 for success, 1 for failure
 */
int run_shell_interactive(info_t *info)
{
	int shell_status = 1;
	char *line;
	size_t char_len = 0;

	while (shell_status)
	{
		_printf("$ ");
		if (_fgets(info, &line, &char_len, stdin) == NULL)
		{
			perror("\n");
			break;
		}
		if (run_shell(info, line) == -2)
		{
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
/**
 * handle_logical_operators - Handles logical operators
 * @line: The logical operator string
 * @info: A pointer to a info_t struct
 *
 * Return: 1 on success, 0 on failure
 */
int handle_logical_operators(char *line, info_t *info)
{
	int exit_status = 0, success = EXIT_SUCCESS,
		is_and_operator = 0, start = 0, end = 0;
	char *tmp = NULL;

	while (line[end] != '\0')
	{
		if (is_logical_operator(line, end))
		{
			if (line[end + 1] == '&')
				is_and_operator = 1;
			else
				is_and_operator = 0;
			success = logical_operators_helper(info, &tmp, line, start,
											   end, is_and_operator, &exit_status, success);
			if (success == EXIT_FAILURE || success == -2)
				return (success);
			start = end + 2;
		}
		end++;
	}
	success = logical_operators_helper(info, &tmp, line, start,
									   end, is_and_operator, &exit_status, success);
	if (success == EXIT_FAILURE || success == -2)
		return (success);
	return (success);
}

/**
 * filter_comments - Removes comments from a string
 * @buf: The string to remove comments from
 *
 * Return: The string with comments removed
 */
char *filter_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	return (buf);
}
/**
 * start_process - Starts a process
 * @info: A pointer to a info_t struct
 *
 * Return: The exit status of the process
 */
int start_process(info_t *info)
{
	int exit_status;

	info->line[info->char_len - 1] = '\0';
	info->argc = split_str(info->line, &info->argv, " \t");
	if (info->argv == NULL || info->argc == 0)
		return (EXIT_FAILURE); /* Ignore empty lines or input errors */
	exit_status = replace_env_var(info);
	if (exit_status != EXIT_SUCCESS)
	{
		ffree(info->argv);
		return (exit_status);
	}
	if (info->argc == 0)
	{
		exit_status = EXIT_FAILURE;
	}
	if (find_executable(info) == EXIT_FAILURE)
	{
		exit_status = EXIT_FAILURE;
	}
	else
	{
		if (info->path != NULL && info->is_built_in == -1)
		{
			exit_status = execute_command(info);
			free(info->path);
		}
		else if (info->is_built_in == -2)
		{
			exit_status = EXIT_FAILURE;
		}
		else if (info->is_built_in != -1)
		{
			exit_status = EXIT_SUCCESS;
		}
		else
			_printf("%s: command not found\n", info->argv[0]);
	}
	ffree(info->argv);
	return (exit_status);
}

/**
 * find_executable - Finds an executable in the PATH
 * @info: A pointer to a info_t struct
 *
 * Return: The exit status of the process
 */
int find_executable(info_t *info)
{
	int i, path_len;
	char *path;
	char **path_buffer = NULL;
	char *path_with_cmd;

	/* check for built ins */
	info->is_built_in = find_builtin(info);
	if (info->is_built_in != -1)
		return (EXIT_SUCCESS);
	if (is_path(info->argv[0]))
	{
		info->path = _strdup(info->argv[0]);
		return (EXIT_SUCCESS);
	}
	path = _getenv("PATH");
	if (path == NULL || info->argv[0] == NULL)
		return (EXIT_FAILURE);
	path_len = split_str(path, &path_buffer, ":");
	free(path);
	if (path_len == -1)
		return (EXIT_FAILURE);
	for (i = 0; i < path_len; i++)
	{
		path_with_cmd = concat_path_and_cmd(path_buffer[i], info->argv[0]);
		if (path_with_cmd == NULL)
		{
			free(path_with_cmd);
			return (EXIT_FAILURE);
		}
		if (access(path_with_cmd, X_OK) == 0)
		{
			free_args(path_buffer); /* Clean up the path_buffer */
			info->path = path_with_cmd;
			return (EXIT_SUCCESS);
		}
		free(path_with_cmd);
	}
	free_args(path_buffer);
	return (EXIT_FAILURE);
}
