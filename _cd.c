#include "shell.h"

/**
 * _cd - implementation of change working directory
 * @argv: array of pointers to string containing
 * parameters of cd, if argv is NULL, then change the
 * working directory to hone direcyory.
 * handle parameters ..(parent dir) and -(previous dir)
 * Return: path to destination dir
 */

char *_cd(char *argv)
{
	env_t *envs;
	char **envp, *envVar;
	int i = 0, envCount = 0;

	envp = environ;
	/* get number of environ variables */
	for (; *envp != NULL; )
	{

		envp++;
		envCount++;
	}

	envs = malloc(sizeof(struct env) * envCount);
	/* Populate the environment variables array */
	envp = environ;
	for ( ; i < envCount; i++)
	{
		char *env = *envp;
		int j = 0;

		while (env[j] != '=')
			j++;
		if (!argv)
		{
			if (_strcmp(strndup(env, j), "HOME") == 0)
			{
				/*printf ("%s=",strndup(env, j));*/
				return (env + j + 1);
			}
		}
		envp++;
	}
	envVar = '\0';
	(void)argv;
	(void)envs;

	return (envVar);
}
