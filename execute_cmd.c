#include "shell.h"
/**
 * execute_command - executes a command
 * @info: command info
 */
void execute_command(info_t *info)
{
	pid_t child_pid;

	/* check for built ins */
	if (info->is_built_in != -1)
		return;
	/* Fork and execute external commands */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(info->line);
		free_args(info->argv);
		exit_shell(info, EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		/* child process */
		if (execve(info->path, info->argv, environ) == -1)
		{
			perror(info->argv[0]);
			free(info->line);
			free_args(info->argv);
			exit_shell(info, EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		if (wait(&status) == -1)
		{
			perror("wait");
			free(info->line);
			free_args(info->argv);
			exit_shell(info, EXIT_FAILURE);
		}
	}
}
