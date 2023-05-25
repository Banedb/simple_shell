#include "shell.h"
/**
 * cmdnf - Error 127
 * @argv: Arguments passed to function
 *
 * Return: Error string
 */
char *cmdnf(char **argv)
{
	char *error, *str;
	int len;

	str = _itoa(count);
	len = _strlen(name) + _strlen(str) + _strlen(argv[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(str);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, argv[0]);
	_strcat(error, "not found\n");
	_strcat(error, "\0");
	free(str);
	return (error);
}

/**
 * _fork - calls in child process
 * @argv: Arguments passed to function
 * @envp: an array of pointers to strings,)
 */
void _fork(char **argv, char **envp)
{
	char *cmdpath = NULL, *err;
	int exex = -1;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		exex = execve(cmdpath, argv, _env(envp));
		if (exex == -1)
		{
			err = cmdnf(argv);
			if (err != NULL)
			{
				write(STDERR_FILENO, err, _strlen(err));
				free(err);
			}
			else
				perror("Malloc Error");
		}
	}
	else if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
/**
 * cmdexe - calls in the execve function to enable command execution
 * @argv: Arguments passed to function
 * @envp: an array of pointers to strings,
 * storing environment varibles and their values
 * Return: 0 (Success)
 */
int cmdexe(char **argv, char **envp)
{
	char *cmd = NULL, *cmdpath = NULL, *path, *err;
	int exex = -1;

	if (argv && argv[0])
	{
		cmd = argv[0];
		cmdpath = pathfinder(cmd);
		if (cmdpath != NULL)
			_fork(argv, envp);
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
			err = cmdnf(argv);
			write(STDERR_FILENO, err, _strlen(err));
			return (-1);
		}
	}
	else
		/* Handle when nothing is input eg just enter */
		return (-1);
	return (exex);
}
