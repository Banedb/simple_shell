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
	int i;
	const char *filename;

	name = argv[0];
	hist = 0;
	addycount = 0;
	exit_status = 0;
	if (signal(SIGINT, sig_h) == SIG_ERR)
	{
		env_cleanup();
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < MAX_ALIASES; ++i)
	{
		aliases[i].name = NULL;
		aliases[i].val = NULL;
	}
	aliascount = 0;

	if (argc == 2)
	{
		filename = argv[1];
		if (check_file(filename))
			run_file(filename);
		else
			ferror_127(argv);
	}
	else
		run_input();
	env_cleanup();
	(void)argc;
	return (0);
}
