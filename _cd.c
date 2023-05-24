#include "shell.h"

/**
 * _cd - implementation of change working directory
 * @path: array of pointers to string containing
 * parameters of cd, if argv is NULL, then change the
 * working directory to hone direcyory.
 * handle parameters ..(parent dir) and -(previous dir)
 * Return: path to destination dir
 */
char *_cd(const char *path)
{
	char **envp = environ, currentPath[MAX_PATH_LENGTH], *prevDir;
	int i = 0, envCount = 0;

	/* get number of environ variables */
	for (; *envp != NULL; )
	{
		envp++;
		envCount++;
	}
	/* Populate the environment variables array */
	envp = environ;
	for ( ; i < envCount; i++, envp++)
	{
		char *env = *envp;
		int j = 0;

		while (env[j] != '=')
			j++;
		if (!path)
		{
			if (_strcmp(_strndup(env, j), "HOME") == 0)
				return (env + j + 1);
		}
		else if (_strcmp(_strndup(env, j), "PWD") == 0)
			prevDir = env + j + 1;
	}
	if (_strcmp(_strdup(path), "-") == 0)
		path = prevDir;
	if (chdir(path) != 0)
	{
		fprintf(stderr, "cd: Failed to change directory to %s\n", path);
		return (NULL);
	}
	if (getcwd(currentPath, sizeof(currentPath)) == NULL)
	{
		fprintf(stderr, "cd: Failed to get current directory\n");
		return (NULL);
	}
	return (_strdup(path));
}
