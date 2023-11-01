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
 * _env - enviroment implementation
 * @envStrings: array of pointer to strings storing
 *
 * Return: array of pointers to strings
 */

char **_env(char **envStrings)
{
	env_t *envs;
	int envCount = 0, i = 0, j;
	char **envp = environ, *env;

	/* get number of environ variables */
	for (; *envp != NULL; envp++)
		envCount++;
	envs = malloc(sizeof(struct env) * envCount);
	/* Populate the environment variables array */
	envp = environ;
	for ( ; i < envCount; i++)
	{
		env = *envp;
		j = 0;

		while (env[j] != '=')
			j++;
		envs[i].key = _strndup(env, j);
		envs[i].val = env + j + 1;
		envp++;
	}
	/* Store the environ variables in an array of pointers to strings */
	i = 0;
	while (*envp != NULL)
	{
		/*allocate mem for '=' and null terminator, hence + 2*/
		_puts(*envp);
		envp++;
	}
	/* set last element of array: NULL*/
	envStrings[envCount] = NULL;
	/* avoid mem leaks, free allocated mem*/
	for (i = 0; i < envCount; i++)
		free(envs[i].key);
	free(envs);

	return (envStrings);
}

/**
 * exitShell - exit cmd implementation
 * @argv: array of pointers
 */

void exitShell(char **argv)
{
	int exit_status;

	if (argv[1] == NULL)
	{
		free_args(argv);
		if (user_input)
			free(user_input);
		exit(0);
	}
	else
	{
		exit_status = _atoi(argv[1]);
		free_args(argv);
		if (user_input)
			free(user_input);
		exit(exit_status);
	}
}
