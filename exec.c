#include "shell.h"
/**
 * cmdexe - calls in the execve function to enable command execution
 * @argv: Arguments passed to function
 * @envp: an array of pointers to strings,
 * storing environment varibles and their values
 * Return: 0 (Success)
 */
int cmdexe(char **argv, char **envp)
{
	char *cmd = NULL, *cmdpath = NULL;
	int exex = -1;
	pid_t pid;

	if (argv && argv[0])
	{
		cmd = argv[0];
		cmdpath = pathfinder(cmd);
		/* To fork only when command exists */
		if (cmdpath != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				exex = execve(cmdpath, argv, getEnv(envp));
			}
			else if (pid == -1)
			{
				perror("Error:");
				return (1);
			}
			else
				wait(NULL);
		}
		else if (_strcmp(cmd, "exit") == 0)
			exitShell();
		else if (_strcmp(cmd, "cd") == 0)
		{
			if (!argv[1])
			{
				char *path = _cd(argv[1]);
				chdir(path);
			}
			else
				_cd(argv[1]);
		}
		else if (exex == -1)
		{
			printf("./hsh: 1: %s: not found\n", cmd);
			/* printf("hsh: %s: not found\n", cmd);*/
			return (-1);
		}
	}
	else
		/* Handle when nothing is input eg just enter */
		return (-1);
	return (exex);
}
/* NB: Handle error for complex charaters being input */
/* ie bash substitution failed message */
/* Remember to pass environ to execve */
/* use _put instead of printf*/
