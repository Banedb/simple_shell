#include "shell.h"

/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: Arguments passed to function
 * @envp: Array of environment variables
 *
 * Return: 0 (Success)
 */
int main(int argc, char **argv, char **envp)
{
	char *prompt = "($) ", *user_input = NULL;
	int ln = 1;
	size_t n = 0;
	ssize_t gret;

	for (;;)
	{
		_puts(prompt);
		gret = getline(&user_input, &n, stdin);
		/* Handling EOF and errors of getline function */
		if (gret < 0)
		{
			free(user_input);
			return (-1);
		}
		argv = tokenizeLine(user_input);
		cmdexe(argv, envp, ln);
		ln++;

	}

	free(user_input);
	(void)argc;
	return (0);
	/* Should I nullterminate argv? */
}
/* NB: Betty error: File has over 40 lines of code so will have to split */
