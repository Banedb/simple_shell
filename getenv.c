#include "shell.h"
/**
 * _getenv - get enviroment viariables
 * @name: input str
 * Return: ..
 */
char *_getenv(const char *name)
{
	int i, j;
	char **envp = environ;

	if (!name || !environ)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; name[j] != '\0' && name[j] == envp[i][j]; j++)
		{
			/*compare characters until they differ or name[j] is null terminator*/
		}
		if (name[j] == '\0' && envp[i][j] == '=')
		{
			/* Found a matching environment variable*/
			char *value_start = &envp[i][j + 1];
			size_t value_length = _strlen(value_start);

			char *value = malloc(value_length + 1);

			if (value)
			{
				_strcpy(value, value_start);
				return (value);
			}
		}
	}

	return (NULL); /* No matching environment variable found*/
}

/**
 * _env - enviroment implementation
 * @envStrings: array of pointer to strings storing
 * environment variable and its values
 * Return: array of pointers to string, containing
 * environ variables and theri values.
 */

char **_env(char **envStrings)
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
 /* we wanna have another function that will have access to the*/
 /* use _puts instead of printf*/
 /* implement my own strbdup*/
