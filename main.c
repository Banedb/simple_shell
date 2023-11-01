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
	prompt = "$ ";
	name = argv[0];
	if (signal(SIGINT, sig_h) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}

	/*fflush(stdout);*/
	run_input();
	(void)argc;
	return (0);
}
