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

	path = getenv("PATH");
	if (path)
	{
		pathcopy = strdup(path);
		cmdl = strlen(cmd);
		pt = strtok(pathcopy, ":");
		while (pt != NULL)
		{
			pathl = strlen(pt);
			cmdpath = malloc(cmdl + pathl + 2);
			strcpy(cmdpath, pt);
			strcat(cmdpath, "/");
			strcat(cmdpath, cmd);
			strcat(cmdpath, "\0");
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
