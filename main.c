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
	(void)argc;
	(void)argv;

	if (!create_env_list())
	{
		perror("main");
		exit(EXIT_FAILURE);
	}

	run_shell();
	return (EXIT_SUCCESS);
}
