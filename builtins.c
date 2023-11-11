#include "shell.h"
/**
 * _cd - custom implementation of cd
 * @path: ..
 *
 * Return: path to destination dir
 */
char *_cd(const char *path)
{
	char **envp, currentPath[MAXPATH_LEN], *prevd, *pathcopy, *env, *envcpy;
	int j;

	for (envp = environ; *envp != NULL; envp++)/*populate env var array*/
	{
		j = 0;
		env = *envp;
		while (env[j] != '=')
			j++;
		envcpy = _strndup(env, j);
		if (!path)
		{
			if (_strcmp(envcpy, "HOME") == 0)
			{
				free(envcpy);
				return (env + j + 1);
			}
		}
		else if (_strcmp(envcpy, "PWD") == 0)
			prevd = env + j + 1;
		free(envcpy);
	}
	pathcopy = _strdup(path);
	if (_strcmp(pathcopy, "-") == 0)
	{
		path = prevd;
		write(1, prevd, _strlen(prevd) + 1);
		write(1, "\n", 2);
	}
	if (chdir(path) != 0)
	{
		cd_error(pathcopy);
		return (NULL);
	}
	if (getcwd(currentPath, sizeof(currentPath)) == NULL)
	{
		cd_error2(pathcopy);
		return (NULL);
	}
	return (pathcopy);
}


/**
 * exitShell - exit cmd implementation
 * @argv: array of pointers
 *
 * Return: 2 on failure
 */

int exitShell(char **argv)
{
	int status;

	if (argv[1] == NULL)
	{
		cleaner(argv);
		exit(exit_status);
	}
	else
	{
		status = _atoi(argv[1]);
		if ((status == 0) && (_strcmp(argv[1], "0") == 0))
		{
			cleaner(argv);
			exit(status);
		}
		else if (status > 0)
		{
			cleaner(argv);
			exit(status);
		}
		else if (status < 1)
		{ /*atoi returns 0 on failure so if status 0 or < 1*/
			/* and argv[1] is not 0, num is an invalid arg */
			errexit(argv[1]);
		}
	}
	return (2);
}
