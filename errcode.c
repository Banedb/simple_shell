#include "shell.h"
/**
 * error_127 - unable to locate command's executable
 * @args: array of input cmd
 *
 * Return: error message
 */

char *error_127(char **args)
{
	char *errmsg, *ic;
	int len;

	ic = myitoa(hist);
	if (!ic)
		return (NULL);

	len = _strlen(name) + _strlen(ic) + _strlen(args[0]) + 16;
	errmsg = malloc(sizeof(char) * (len + 1));
	if (!errmsg)
	{
		free(ic);
		return (NULL);
	}

	_strcpy(errmsg, name);
	_strcat(errmsg, ": ");
	_strcat(errmsg, ic);
	_strcat(errmsg, ": ");
	_strcat(errmsg, args[0]);
	_strcat(errmsg, ": not found\n");

	free(ic);
	return (errmsg);
}
