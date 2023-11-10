#include "shell.h"
/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: Arguments passed to function
 *
 * Return: 0 (Success)
 */
int main(int argc, char **argv)
{
	name = argv[0];
	addycount = 0;
	if (signal(SIGINT, sig_h) == SIG_ERR)
	{
		env_cleanup();
		exit(EXIT_FAILURE);
	}

	/*fflush(stdout);*/
	run_input();
	env_cleanup();
	(void)argc;
	return (0);
}
