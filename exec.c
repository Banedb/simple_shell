#include "shell.h"
/**
 * cmdexe - Execute the command
 * @argv: Arguments passed to the function
 * @envp: Array of environment variables
 * @ln: Line number
 *
 * Return: 0 (Success)
 */
int cmdexe(char **argv, char **envp, int ln)
{
	char *cmd = NULL, *cmdpath = NULL, *path;
	int exex = -1;
	pid_t pid;

	if (!argv || !argv[0])
		return (-1);

	cmd = argv[0];
	cmdpath = pathfinder(cmd);
	if (cmdpath != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			exex = execve(cmdpath, argv, _env(envp));
			if (exex == -1)
			{
				_fprintf(2, "./hsh: %d: %s: not found\n", ln, cmd);
				exit(127);
			}
		}
		else if (pid == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}
	else if (exex == -1)
	{
		_fprintf(2, "./hsh: %d: %s: not found\n", ln, cmd);
		return (-1);
	}
	return (exex);
}
