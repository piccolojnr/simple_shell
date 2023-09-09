#include "shell.h"
/**
 * execute_command - executes a command
 * @info: command info
 */
void execute_command(cmd_info *info)
{
	int built_in_ret;
	pid_t child_pid;

	/* check for built ins */
	built_in_ret = find_builtin(&info);
	if (built_in_ret != -1)
		return;
	/* Fork and execute external commands */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(info->line);
		free_args(info->argv);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		/* child process */
		if (execve(info->path, info->argv, environ) == -1)
		{
			perror(info->argv[0]);
			free(info->line);
			free_args(info->argv);
			exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
		}
	}
}
