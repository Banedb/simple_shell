#include "shell.h"

/**
 * env - enviroment implementation
 * @envStrings: array of pointer to strings storing
 * environment variable and its values
 */

char **getEnv(char **envStrings)
{
	env_t *envs;
	char **envp;
	int i = 0, envCount = 0, len;

	envp = environ;

	/* get number of environ variables */
	for (; *envp != NULL; )
	{
		envp++;
		envCount++;
	}

	envs = malloc(sizeof(struct Env) * envCount);

	/* Populate the environment variables array */
	envp = environ;
	for ( ; i < envCount; i++)
	{
		char *env = *envp;
		int j = 0;

		while (env[j] != '=')
			j++;
		envs[i].key = strndup(env, j);
		envs[i].val = env + j + 1;
		envp++;
	}

	/* Store the environ variables in an array of pointers to strings */
	i = 0;
	while (i < envCount)
	{
		/*allocate mem for '=' and null terminator, hence + 2*/
		len = strlen(envs[i].key) + strlen(envs[i].val) + 2;
		envStrings[i] = malloc(sizeof(char) * len);
		snprintf(envStrings[i], len, "%s=%s", envs[i].key, envs[i].val);
		i++;
	}

	/* set last element of array: NULL*/
	envStrings[envCount] = NULL;

	/* avoid mem leaks, free allocated mem*/
	for (i = 0; i < envCount; i++)
		free(envs[i].key);

	free(envs);

	return (envStrings);
}
/*Over 40 lines*/
