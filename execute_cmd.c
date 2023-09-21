#include "shell.h"
/**
 * execute_command - executes a command
 * @info: command info
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int execute_command(info_t *info)
{
	pid_t child_pid;

	/* check for built ins */
	if (info->is_built_in != -1)
		return (info->is_built_in);

	/* Fork and execute external commands */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		handle_execution_error(info);
		return (-2);
	}

	if (child_pid == 0)
	{
		/* child process */
		if (execve(info->path, info->argv, environ) == -1)
		{
			handle_execution_error(info);
			return (-2);
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		/* Parent process */

		if (wait(&info->status) == -1)
		{
			perror("wait");
			handle_execution_error(info);
			return (-2);
		}

		return (WEXITSTATUS(info->status));
	}
}
/**
 * handle_execution_error - handles errors from execute_command
 * @info: command info
 */
void handle_execution_error(info_t *info)
{
	perror(info->argv[0]);
	free(info->line);
	free_args(info->argv);
}
