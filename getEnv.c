#include "shell.h"
/**
 * getEnv - enviroment implementation
 * @envStrings: array of pointer to strings storing
 * environment variable and its values
 * Return: array of pointers to string, containing
 * environ variables and theri values.
 */

char **getEnv(char **envStrings)
{
	env_t *envs;
	int envCount = 0, i = 0;
	char **envp = environ;

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
		envs[i].key = strndup(env, j);
		envs[i].val = env + j + 1;
		envp++;
	}
	/* Store the environ variables in an array of pointers to strings */
	i = 0;
	while (*envp != NULL)
	{
		/*allocate mem for '=' and null terminator, hence + 2*/
		printf("%s\n", *envp);
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
 /* we wanna have another function that will have access to the*/
 /* use _puts instead of printf*/
 /* implement my own strbdup*/
