#include "shell.h"
/**
 * cmdexe - calls in the execve function to enable command execution
 * @argv: Arguments passed to function
 * @envp: an array of pointers to strings,
 * @ln: err
 * storing environment varibles and their values
 * Return: 0 (Success)
 */
int cmdexe(char **argv, char **envp, int ln)
{
	char *cmd = NULL, *cmdpath = NULL, *path;
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
				if (exex == -1)
				{
					fprintf(stderr, "./hsh: %d: %s: not found\n", ln, cmd);
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
		else if (_strcmp(cmd, "exit") == 0)
			exitShell();
		else if (_strcmp(cmd, "cd") == 0)
		{
			if (!argv[1])
			{
				path = _cd(argv[1]);
				chdir(path);
			}
			else
				_cd(argv[1]);
		}
		else if (exex == -1)
		{
			fprintf(stderr, "./hsh: %d: %s: not found\n", ln, cmd);
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
/* use _put instead of printf*/
