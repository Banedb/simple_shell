#include "shell.h"

/**
 * handle_vars - replaces variables
 * @command: arg
 *
 * Return: variable's value on success
 */
char *handle_vars(char *command)
{/* Function to replace variables in the command */
	char *name, *buff, *value = NULL, *cmdcopy = command;

	if (command[0] == '$')
	{ /* Replace $$ with process ID */
		name = ++command;
		buff = _getenv(name);
		if (buff != NULL)
		{
			value = malloc(strlen(buff) + 1);
			_strcpy(value, buff);
			free(buff);
			return (value);
		}
		free(buff);
		return (repvar(cmdcopy));
	}
	return (NULL);
}
