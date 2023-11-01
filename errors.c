#include "shell.h"
/**
 * err_gen - sends custom error message to stderr
 * @argv: ..
 * @err_no: error code
 *
 * Return: error code
 */
int err_gen(char **argv, int err_no)
{
	int exit_status = 0;
	char *errmsg = NULL;

	switch (err_no)
	{	case 127:
		errmsg = error_127(argv);
		exit_status = 127;
		break;
	}

	if (errmsg)
	{
		write(STDERR_FILENO, errmsg, _strlen(errmsg));
		free(errmsg);
	}
	return (exit_status);

}

/**
 * cd_error - can't cd to specified location
 * @args: array of input command
 *
 */

void cd_error(char *args)
{
	char *errmsg, *ic;
	int len;

	ic = myitoa(hist);
	if (!ic)
		return;

	len = _strlen(name) + _strlen(ic) + _strlen(args) + 23;
	errmsg = malloc(sizeof(char) * (len + 1));
	if (!errmsg)
	{
		free(ic);
		return;
	}

	_strcpy(errmsg, name);
	_strcat(errmsg, ": ");
	_strcat(errmsg, ic);
	_strcat(errmsg, ": cd: can't cd to ");
	_strcat(errmsg, (args));
	_strcat(errmsg, "\n");

	free(ic);
	write(STDERR_FILENO, errmsg, _strlen(errmsg));
	free(errmsg);
	free(args);
}

/**
 * cd_error2 - can't cd to specified location
 * @args: array of input command
 *
 */

void cd_error2(char *args)
{
	write(2, "cd : error retrieving current directory\n", 42);
	free(args);
}
