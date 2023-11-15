#include "shell.h"
/**
 * error_handler - sends custom error message to stderr
 * @argv: ..
 * @err_no: error code
 *
 * Return: error code
 */
int error_handler(char **argv, int err_no)
{
	int exit_status = 0;
	char *errmsg = NULL;

	switch (err_no)
	{
	case 22:
		write(STDERR_FILENO, "Invalid Argument\n", 17);
		errno = EINVAL;
		exit_status = -1;
		break;
	case 50:
		write(STDERR_FILENO, "Error: Unable to allocate memory\n", 33);
		exit_status = -1;
		break;
	case 127:
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
 * Return: ..
 */

char *cd_error(char *args)
{
	char *errmsg, *ic;
	int len;

	ic = myitoa(hist);
	if (!ic)
		return (NULL);

	len = _strlen(name) + _strlen(ic) + _strlen(args) + 23;
	errmsg = malloc(sizeof(char) * (len + 1));
	if (!errmsg)
	{
		free(ic);
		return (NULL);
	}

	_strcpy(errmsg, name);
	_strcat(errmsg, ": ");
	_strcat(errmsg, ic);
	_strcat(errmsg, ": cd: can't cd to ");
	_strcat(errmsg, (args));
	_strcat(errmsg, "\n");

	free(ic);
	return (errmsg);
}

/**
 * gen_cd_error  - can't cd to specified location
 * @args: array of input command
 * @err_no: ..
 */

void gen_cd_error(char *args, int err_no)
{
	char *errmsg = NULL;

	switch (err_no)
	{
	case 2: /* ENOENT */
		errmsg = cd_error(args);
		/* exit_status = 2; */
		break;
	}

	if (errmsg)
	{
		write(STDERR_FILENO, errmsg, _strlen(errmsg));
		free(errmsg);
	}
	return;


	/* write(2, "cd : error retrieving current directory\n", 42);  */
}

/**
 * errexit - generate error when unable to exit with num specified
 * @args: array of input command
 *
 */

void errexit(char *args)
{
	char *errmsg, *ic;
	int len;

	ic = myitoa(hist);
	if (!ic)
		return;

	len = _strlen(name) + _strlen(ic) + _strlen(args) + 29;
	errmsg = malloc(sizeof(char) * (len + 1));
	if (!errmsg)
	{
		free(ic);
		return;
	}

	_strcpy(errmsg, name);
	_strcat(errmsg, ": ");
	_strcat(errmsg, ic);
	_strcat(errmsg, ": exit: Illegal number: ");
	_strcat(errmsg, (args));
	_strcat(errmsg, "\n");

	free(ic);
	write(STDERR_FILENO, errmsg, _strlen(errmsg));
	free(errmsg);
}
