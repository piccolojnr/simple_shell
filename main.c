#include "shell.h"

t_env *env_list = NULL;

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	create_env_list();

	run_shell();
	return (EXIT_SUCCESS);
}
