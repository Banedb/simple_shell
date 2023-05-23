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
	char **envp = environ;
	int i = 0, envCount = 0;
	char currentPath[MAX_PATH_LENGTH];

	/* get number of environ variables */
	for (; *envp != NULL; )
	{
		envp++;
		envCount++;
	}
	/* Populate the environment variables array */
	envp = environ;
	for ( ; i < envCount; i++)
	{
		char *env = *envp;
		int j = 0;

		while (env[j] != '=')
			j++;
		if (!path)
		{
			if (_strcmp(strndup(env, j), "HOME") == 0)
				return (env + j + 1);
		}
		envp++;
	}

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

	return (strdup(path));
}


