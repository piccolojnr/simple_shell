#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	t_env *env_list;
	(void)argc;
	(void)argv;

	if (!create_env_list(&env_list))
	{
		perror("main");
		exit(EXIT_FAILURE);
	}

	run_shell(&env_list);
	return (EXIT_SUCCESS);
}
