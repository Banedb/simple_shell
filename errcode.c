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

	if (hist != 0)
	{
		ic = myitoa(hist);
		if (!ic)
			return (NULL);
	}
	else
		ic = "0";

	len = _strlen(name) + _strlen(ic) + _strlen(args[0]) + 17;
	errmsg = malloc(sizeof(char) * (len));
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

	if (hist)
		free(ic);
	return (errmsg);
}

/**
 * ferror_127 - unable to open file
 * @args: array of input cmd
 */
void ferror_127(char **args)
{
	char *errmsg, *ic;
	int len;

	if (hist != 0)
	{
		ic = myitoa(hist);
		if (!ic)
			return;
	}
	else
		ic = "0";

	len = _strlen(args[0]) + _strlen(ic) + _strlen(args[1]) + 17;
	errmsg = malloc(sizeof(char) * (len));
	if (!errmsg)
	{
		if (hist)
			free(ic);
		return;
	}

	_strcpy(errmsg, args[0]);
	_strcat(errmsg, ": ");
	_strcat(errmsg, ic);
	_strcat(errmsg, ": ");
	_strcat(errmsg, "Can't open ");
	_strcat(errmsg, args[1]);
	_strcat(errmsg, "\n");

	if (hist)
		free(ic);
	write(STDERR_FILENO, errmsg, _strlen(errmsg));
	free(errmsg);
	exit_status = 127;
	exit(exit_status);
}
