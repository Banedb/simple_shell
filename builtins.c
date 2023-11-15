#include "shell.h"
/**
 * _cd - custom implementation of cd
 * @path: ..
 *
 * Return: path to destination dir
 */

void _cd(char *path)
{
	char *home = NULL, *prevd = getcwd(NULL, 0), *cwd = NULL, *pvd = NULL;

	addyarray(prevd);
	if (path == NULL || _strcmp(path, "") == 0)
	{/* If no path is provided, change to the home directory */
		home = _getenv("HOME");
		addyarray(home);
		if (chdir(home) != 0)
			return;
		cwd = getcwd(NULL, 0);
		addyarray(cwd);
	}
	else if (_strcmp(path, "-") == 0)
	{/* If the path is "-", change to the previous directory */
		pvd = _getenv("OLDPWD");
		addyarray(pvd);
		chdir(pvd);
		cwd = getcwd(NULL, 0);
		if (cwd)
			addyarray(cwd);
		write(1, cwd, _strlen(cwd));
		write(1, "\n", 1);
		if (pvd == NULL || chdir(pvd) == -1)
			return;
	}
	else
	{/* Change to the specified directory */
		if (chdir(path) != 0)
		{
			gen_cd_error(path, 2);
			return;
		}
		cwd = getcwd(NULL, 0);
		addyarray(cwd);
	} /* Overwrite existing value */
	mysetenv("PWD", cwd);
	mysetenv("OLDPWD", prevd);
}

/**
 * exitShell - exit cmd implementation
 * @argv: array of pointers
 *
 * Return: 2 on failure
 */

int exitShell(char **argv)
{
	int status;

	if (argv[1] == NULL)
	{
		cleaner(argv);
		exit(exit_status);
	}
	else
	{
		status = _atoi(argv[1]);
		if ((status == 0) && (_strcmp(argv[1], "0") == 0))
		{
			cleaner(argv);
			exit(status);
		}
		else if (status > 0)
		{
			cleaner(argv);
			exit(status);
		}
		else if (status < 1)
		{ /*atoi returns 0 on failure so if status 0 or < 1*/
			/* and argv[1] is not 0, num is an invalid arg */
			errexit(argv[1]);
		}
	}
	return (2);
}
