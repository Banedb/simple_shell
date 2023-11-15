#include "shell.h"
/**
 * _env - enviroment implementation
 * @envStrings: array of pointer to strings storing
 *
 * Return: array of pointers to strings
 */

char **_env(char **envStrings)
{
	PAIR *envs = NULL;
	int envCount = 0, i = 0, j;
	char **envp = environ, *env;

	/* get number of environ variables */
	for (; *envp != NULL; envp++)
		envCount++;
	envs = malloc(sizeof(struct form) * envCount);
	if (envs == NULL)
	{
		(error_handler(NULL, 50));
		return (NULL);
	}
	/* Populate the environment variables array */
	envp = environ;
	for ( ; i < envCount; i++)
	{
		env = *envp;
		j = 0;

		while (env[j] != '=')
			j++;
		envs[i].name = _strndup(env, j);
		envs[i].val = env + j + 1;
		envp++;
	}
	i = 0;
	while (*envp != NULL)
	{
		_puts(*envp);
		envp++;
	}
	/* set last element of array: NULL*/
	envStrings[envCount] = NULL;
	for (i = 0; i < envCount; i++)
		free(envs[i].name);
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

	if ((_strchr(name, '=') != NULL) || (_strlen(name) == 0))
		return (error_handler(NULL, 22));
	env_var = malloc(_strlen(name) + _strlen(value) + 2);
	if (env_var == NULL)
		return (error_handler(NULL, 50));
	addyarray(env_var);
	_strcpy(env_var, name);
	_strcat(env_var, "=");
	_strcat(env_var, value);
	for (env = environ; *env; env++)
	{/* Iterate through the environ and update if it exists */
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
	if (new_environ == NULL)
		return (error_handler(NULL, 50));
	addyarray(new_environ);
	/* Copy existing environment variables */
	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];
	new_environ[i] = env_var;/* Add the new envs and terminate the list */
	new_environ[i + 1] = NULL;
	environ = new_environ;
	return (0);
}

/**
 * myunsetenv - custom unsetenv
 * @name: environment variable name
 *
 * Return: 0 on success
 */

int myunsetenv(char *name)
{
	char **env, **shift;

	if ((_strchr(name, '=') != NULL) || (_strlen(name) == 0))
		return (error_handler(NULL, 22));
	/* Iterate through the environ and remove if it exists */
	for (env = environ; *env; env++)
	{
		if (_strncmp(*env, name, _strlen(name)) == 0 &&
		    (*env)[_strlen(name)] == '=')
		{
			/* Found the environment variable, remove it */
			for (shift = env; *shift; ++shift)
				*shift = *(shift + 1);
			return (0);
		}
	}

	/* If the variable doesn't exist, no need to do anything */
	return (0);
}
/**
 * printEnv - print environment variables
 * @envp: pointer to environment variables
 * Return: Always 0
 */

int printEnv(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		write(STDOUT_FILENO, envp[i], strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
