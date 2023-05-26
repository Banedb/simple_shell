#include "shell.h"
/**
 * pathfinder - find right command path
 * @cmd: command whose path is found
 *
 * Return: path of cmd || NULL (Failure)
 */
char *pathfinder(char *cmd)
{
	char *path, *pathcopy, *cmdpath, *pt;
	int cmdl, pathl;
	struct stat temp;

	path = _getenv("PATH");
	if (path)
	{
		pathcopy = _strdup(path);
		cmdl = _strlen(cmd);
		pt = strtok(pathcopy, ":");
		while (pt != NULL)
		{
			pathl = _strlen(pt);
			cmdpath = malloc(cmdl + pathl + 2);
			_strcpy(cmdpath, pt);
			_strcat(cmdpath, "/");
			_strcat(cmdpath, cmd);
			_strcat(cmdpath, "\0");
			if (stat(cmdpath, &temp) == 0)
			{
				free(pathcopy);
				return (cmdpath);
			}
			else
			{
				free(cmdpath);
				pt = strtok(NULL, ":");
			}
		}
		free(pathcopy);
		if (stat(cmd, &temp) == 0)
			return (cmd);
		return (NULL);
	}
	return (NULL);
}
