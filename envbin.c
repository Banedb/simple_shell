#include "shell.h"
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
 * mysetenv - custom setenv
 * @name: environment variable name
 * @value: value
 *
 * Return: 0 on success
 */
int mysetenv(char *name, char *value)
{
	char **env, *env_var = NULL, **new_environ = NULL;
	int i, size = 0;

	env_var = malloc(_strlen(name) + _strlen(value) + 2);
	addFunction(env_var);
	if (env_var == NULL)
	{
		perror("malloc");
		return (-1);
	}
	_strcpy(env_var, name);
	_strcat(env_var, "=");
	_strcat(env_var, value);
	/* Iterate through the environ and update if it exists */
	for (env = environ; *env; env++)
	{
		if (_strncmp(*env, name, strlen(name)) == 0 &&
		    (*env)[_strlen(name)] == '=')
		{/* Found an existing environment variable, replace it */
			*env = env_var;
			return (0);
		}
	} /* If the variable doesn't exist, append it to the environment */
	for (env = environ; *env; env++)
		size++;
	new_environ = malloc((size + 2) * sizeof(char *));
	addFunction(new_environ);
	if (new_environ == NULL)
	{
		perror("malloc");
		return (-1);
	} /* Copy existing environment variables */
	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];
	new_environ[i] = env_var;/* Add the new envs and terminate the list */
	new_environ[i + 1] = NULL;
	environ = new_environ;
	return (0);
}


/**
 * printEnv - print environment variables
 * @envp: pointer to environment variables
 */

void printEnv(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		write(STDOUT_FILENO, envp[i], strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
