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
	alias_t *alias_list;

	if (!create_env_list(&env_list, env))
	{
		perror("main");
		exit(EXIT_FAILURE);
	}

	if (argc == 1)
	return (run_shell_interactive(&env_list, &alias_list));
	else if (argc == 2)
	return (run_shell_non_interactive(&env_list, &alias_list, argv[1]));
	else
	return (0);
}
