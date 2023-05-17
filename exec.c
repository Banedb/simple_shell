#include "shell.h"
/**
 * cmdexe - calls in the execve function to enable command execution
 * @argv: Arguments passed to function
 *
 * Return: 0 (Success)
 */
int cmdexe(char **argv)
{
	char *cmd = NULL;
	int exex = -1;

	if (argv && argv[0])
	{
		cmd = argv[0];
		exex = execve(cmd, argv, NULL);
		if (exex == -1)
		{
		        if (errno == ENOENT)
				printf("hsh: %s: command not found\n", cmd);
			return (-1);
		}
	}
	else
	{
		printf("Enter a Command");
		return (-1);
	}
	return (exex);
}
