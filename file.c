#include "shell.h"

/**
 * check_file - gets input from stdin using custom getline function
 * @path: path to file to be checked
 *
 * Return: 1 if a regular file || 0 if not
 */
int check_file(const char *path)
{
	struct stat check;

	stat(path, &check);
	return (S_ISREG(check.st_mode));
}


/**
 * run_file - gets input from file using custom getline function
 * @filename: file to read from
 */
void run_file(const char *filename)
{
	char *line = NULL, **envp;
	int fd, count, status = 0;
	size_t n = 0;
	ssize_t charc;

	if (!filename)
		return;
	fd =  open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	while ((charc = _getline(&line, &n, fd)) != -1)
	{
		builtpath = 0;
		path_unset = 1;/*assume PATH is unset*/
		if (line[charc - 1] == '\n')
			line[charc - 1] = '\0';
		count++;
		hist++;
		for (envp = environ; *envp; ++envp)
		{
			if (_strcmp(*envp, "PATH=") == 0)
			{
				path_unset = 0;  /* PATH is set */
				break;
			}
		}
		status = parser(line);
	}
	if (line)
		free(line);
	env_cleanup();
	close(fd);
	exit(status);
}


/**
 * repvar - replaces variables
 * @command: arg
 *
 * Return: 1 if a regular file || 0 if not
 */
char *repvar(char *command)
{/* Function to replace variables in the command */
	char *buff, *cmdcopy = command;
	size_t index = 0, check = 0;
	pid_t pid;

	buff = malloc(254);
	if (!buff)
		return (NULL);
	while (*command)
	{
		if (command[0] == '$' && command[1] == '$')
		{ /* Replace $$ with process ID */
			pid = getpid();
			varhelper(&buff, NULL, pid, &index);
			command += 2;  /* Move past $$ */
			check++;
		}
		else if (command[0] == '$' && command[1] == '?')
		{
			varhelper(&buff, NULL, exit_status, &index);
			command += 2;  /* Move past $? */
			check++;
			}
		else /* Copy other characters */
			buff[index++] = *command++;
	}
	buff[index] = '\0'; /* Null-terminate the expanded command */
	if (check)
		return (buff);
	if (cmdcopy[0] == '$' && cmdcopy[1])
		nullvar = 1;
	free(buff);
	return (NULL);
}
/**
 * varhelper - ..
 * @buff: ..
 * @str: ..
 * @num: ..
 * @index: ..
 */
void varhelper(char **buff, char *str, int num, size_t *index)
{
	char *iastr = NULL;

	if (!str || num)
	{
		if (num != 0)
		{
			iastr = myitoa(num);
			if (!iastr)
				return;
		}
		else
			iastr = "0";
		if (!*buff)
		{
			error_handler(NULL, 50);
			return;
		}
		_strcpy(*buff, iastr);
		*index += _strlen(iastr);
		if (num)
			free(iastr);
	}
	else
	{
		if (!buff)
		{
			error_handler(NULL, 50);
			return;
		}
		_strcpy(*buff, str);
		*index += _strlen(str);
		free(str);
	}
}
