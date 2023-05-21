#include "shell.h"

/**
 * env - enviroment implementation
 * @envStrings: array of pointer to strings storing
 * environment variable and its values
 */
int
main(int argc, char **argv, char **envStrings)
{
	env_t *envs;
	char **envp;
	int i, envCount = 0;

	envp = environ;

	/* Count the number of environment variables */
	for (; *envp != NULL; envCount++, envp++)
		;
	envs = (env_t *) malloc(sizeof(struct Env) * envCount);
	/*handle malloc failure*/
	if (!envs)
	{
		return -1;
	}

	/* Populate the environment variables array */
	envp = environ;
	for (i = 0; i < envCount; i++)
	{
		char *env = *envp;
		int j = 0;

		while (env[j] != '=')
			j++;

		envs[i].key = strndup(env, j);
		envs[i].val = env + j + 1;
		envp++;
	}

	/* Store the environment variables in an array of pointers to strings */
	envStrings = malloc(sizeof(char *) * envCount);
	if (!envStrings)
	{
		return -1;
	}

	while ((i = 0) < envCount)
	{
		/* +2 for '=' and null terminator*/
		int length = strlen(envs[i].key) + strlen(envs[i].val) + 2;

		envStrings[i] = malloc(sizeof(char) * length);
		snprintf(envStrings[i], length, "%s=%s", envs[i].key, envs[i].val);
	}

	/* Access the environment variables from the array of pointers to strings */
	/**
	 * * while (envCount)
	 * {
	 * printf("%s\n", envStrings[i]);
	 * i++;
	 * }
	 */
	/* Free the allocated memory */
	for (i = 0; i < envCount; i++)
	{
		free(envs[i].key);
		free(envStrings[i]);
	}
	free(envs);
	free(envStrings);
	(void)(argc);
	(void)(argv);

	return 0;
}
