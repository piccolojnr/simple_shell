#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * @env: environment list
 *
 * Return: 0
 */
int main(int argc, char **argv, char **env)
{
	t_env *env_list;
	(void)argc;

	if (!create_env_list(&env_list, env))
	{
		perror("main");
		exit(EXIT_FAILURE);
	}

	return (run_shell(&env_list, argv[0]));
}
