#include "shell.h"
/**
 * run_shell - Runs the shell
 */
int run_shell(t_env **env_list, char *name)
{
	int shell_status = 1, i;
	info_t *info = malloc(sizeof(info_t));
	char *line, *filtered_line, **args, *trimmed, *delim = ";";
	size_t char_len = 0;
	(void)name;

	while (shell_status)
	{
		_printf("piccolojnr@:~$ ");

		get_input(info, &line, &char_len, fileno(stdin));

		if (is_line_empty(line))
			continue;

		filtered_line = filter_comments(line);
		if (filtered_line == NULL)
			continue;

		free(line);

		split_str(filtered_line, &args, delim);
		if (args == NULL)
			continue;

		for (i = 0; args[i] != NULL; i++)
		{
			trimmed = trimWhitespace(args[i]);

			free(args[i]);
			args[i] = trimmed;

			if (args[i] != NULL && !is_line_empty(args[i]))
			{
				info->line = args[i];
				info->char_len = _strlen(args[i]) + 1;
				start_process(&info, env_list);
			}
		}
	}
	exit_shell(info, EXIT_SUCCESS);
	return (0);
}
/**
 * handle_logical_operators - Handles logical operators
 * @line: The logical operator string
 * @info: A pointer to a info_t struct
 * @env_list: A pointer to a env_t struct
 *
 * Return: 1 on success, 0 on failure
 */
int handle_logical_operators(char *line, info_t **info, t_env **env_list)
{
	int success = EXIT_SUCCESS, is_and_operator, len, start = 0, end = 0;
	char *tmp;

	while (line[end] != '\0')
	{
		if ((line[end] == '&' && line[end + 1] == '&') || (line[end] == '|' && line[end + 1] == '|'))
		{
			if (line[end + 1] == '&')
				is_and_operator = 1;
			else
				is_and_operator = 0;

			len = end - (start + 1);
			tmp = _strndup(line + start, len);

			(*info)->line = tmp;
			(*info)->char_len = _strlen(tmp) + 1;
			if (!execute_logical_command(info, env_list, is_and_operator))
			{
				success = EXIT_FAILURE;
				free(tmp);
				return (success);
			}
			free(tmp);
			start = end + 2;
		}

		end++;
	}

	len = end - start;
	tmp = _strndup(line + start, len);

	(*info)->line = tmp;
	(*info)->char_len = _strlen(tmp) + 1;
	if (!execute_logical_command(info, env_list, is_and_operator))
	{
		success = EXIT_FAILURE;
		free(tmp);
		return (success);
	}
	free(tmp);

	return (success);
}
/**
 * filter_comments - Removes comments from a string
 * @line: The string to remove comments from
 *
 * Return: The string with comments removed
 */
char *filter_comments(const char *line)
{
	const char *commentPos;
	char *new_line;
	size_t len;

	if (line == NULL)
		return NULL;

	/*Find the position of the '#' character in the string*/
	commentPos = (const char *)_strchr((char *)line, '#');

	if (commentPos == NULL)
		return _strdup(line);
	else
	{
		/*Calculate the length of the portion before the comment character*/
		len = commentPos - line;

		/*Allocate memory for the new string (excluding the comment and null terminator)*/
		new_line = (char *)malloc(len + 1);

		if (new_line != NULL)
		{
			/*Copy the portion before the comment character*/
			strncpy(new_line, line, len);
			new_line[len] = '\0'; /*Null-terminate the new string*/
		}

		return new_line;
	}
}
/**
 * start_process - Starts a process
 * @info: A pointer to a info_t struct
 * @env_list: A pointer to a env_t struct
 *
 * Return: The exit status of the process
 */
int start_process(info_t **info, t_env **env_list)
{
	int exit_status;
	/* Remove newline */
	(*info)->line[(*info)->char_len - 1] = '\0';

	/* Split the input line into arguments */
	(*info)->argc = split_str((*info)->line, &(*info)->argv, " \n\t\r\v\f");

	if ((*info)->argv == NULL || (*info)->argc == 0)
		return (EXIT_FAILURE); /* Ignore empty lines or input errors */

	replace_env_var(info, *env_list);
	
	if ((*info)->argc == 0)
		return (EXIT_FAILURE);

	/* Check if the command exists in the PATH and execute it */
	find_executable(info, env_list);
	if ((*info)->path != NULL && (*info)->is_built_in == -1)
	{
		exit_status = execute_command(info);
		free((*info)->path);
	}
	else if ((*info)->is_built_in != -1)
	{
		return (EXIT_FAILURE);
	}
	else
		_printf("%s: command not found\n", (*info)->argv[0]);

	return (exit_status);
}

/**
 * find_executable - Finds an executable in the PATH
 * @info: A pointer to a info_t struct
 */
void find_executable(info_t **info, t_env **env_list)
{
	int i, path_len;
	char *path;
	char **path_buffer;
	char *path_with_cmd;

	/* check for built ins */
	(*info)->is_built_in = find_builtin(*info, env_list);
	if ((*info)->is_built_in != -1)
		return;
	path = _getenv("PATH", *env_list);
	if (path == NULL || (*info)->argv[0] == NULL)
		return;

	path_len = split_str(path, &path_buffer, ":");
	if (path_len == -1)
		exit_shell(*info, EXIT_FAILURE);

	for (i = 0; i < path_len; i++)
	{
		path_with_cmd = (char *)malloc(strlen(path_buffer[i]) + strlen((*info)->argv[0]) + 2);
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
