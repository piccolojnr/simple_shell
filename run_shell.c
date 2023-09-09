#include "shell.h"
/**
 * run_shell - Runs the shell
*/
void run_shell(void)
{
	int shell_status = 1;
	cmd_info *info = malloc(sizeof(cmd_info));

	while (shell_status)
	{
		printf("$ ");
		info->char_len = getline(&info->line, &info->line_len, stdin);
		if ((info->char_len == -1) && (feof(stdin)))
		{
			perror("Error reading input");
			free(info->line);
			exit(EXIT_FAILURE);
		}

		/* Remove newline */
		info->line[info->char_len - 1] = '\0';

		/* Split the input line into arguments */
		info->argc = split_str(info->line, &info->argv, " \n\t\r\v\f", 0);

		if (info->argv == NULL || info->argc == 0)
			continue; /* Ignore empty lines or input errors */

		/* Check if the command exists in the PATH and execute it */
		info->path = find_executable(info->argv[0]);
		if (info->path != NULL)
		{
			execute_command(info);
			free(info->path);
		} else
			printf("%s: command not found\n", info->argv[0]);
	}

	free(info->line);
}

/**
 * find_executable - Finds an executable in the PATH
 * @command: The command to find
 *
 * Return: The full path to the executable, or NULL if not found
 */
char *find_executable(const char *command)
{
	int i, path_len;
	char *path = _getenv("PATH");
	char **path_buffer;
	char *path_with_cmd;

	if (path == NULL || command == NULL)
		return (NULL);

	path_len = split_str(path, &path_buffer, ":", 0);

	for (i = 0; i < path_len; i++)
	{
		path_with_cmd = (char *)malloc(strlen(path_buffer[i]) + strlen(command) + 2);
		if (path_with_cmd == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		path_with_cmd = _strcpy(path_with_cmd, path_buffer[i]);
		path_with_cmd = _strcat(path_with_cmd, "/");
		path_with_cmd = _strcat(path_with_cmd, command);

		if (access(path_with_cmd, X_OK) == 0)
		{
			free_args(path_buffer); /* Clean up the path_buffer */
			return (path_with_cmd); /* Return the full path to the executable */
		}

		free(path_with_cmd);
	}

	free_args(path_buffer); /* Clean up the path_buffer */
	return (NULL);        /* Command not found in any PATH directory */
}
