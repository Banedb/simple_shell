#include "shell.h"
/**
 * addyarray - add address of given ptr to array of size < 100
 * @ptr: ptr whose address is stored in the array envaddys
 */

void addyarray(void *ptr)
{
	char message[] = "MAX env variables exceeded\n";

	if (addycount < 100)
		envaddys[addycount++] = ptr;
	else
		write(2, message, _strlen(message));
}

/**
 * comment - checks for comment in the line string
 * @line: ...
 *
 * Return: string without comment either modified or unmodified
 */

char *comment(char *line)
{
	size_t i;
	char *pos, *clean = NULL;

	if (*line == '#')
		return (NULL);
	pos = _strchr(line, '#');
	if (pos)
	{
		i = pos - line;
		if (i > 0 && line[i - 1] == ' ')
		{
			clean = _strndup(line, i);
			clean[i] = '\0';
			addyarray(clean);
			line = clean;
		}
	}
	return (line);
}

/**
 * sig_h - handle reception of SIGINT signal
 * @signum: signal number
 */
void sig_h(int signum)
{
	write(STDIN_FILENO, "\n$ ", 3);
	(void) signum;
}


/**
 * _realloc - h
 * @ptr: input as a string
 * @old_size: stream to be read from
 * @new_size: ..
 * Return: pointer to new address
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	void *buff;
	char *dupp, *tide;

	if (new_size == old_size)
		return (ptr);
	if (!ptr)
	{
		buff = malloc(new_size);
		if (buff == NULL)
			return (NULL);
		return (buff);
	}
	if (!new_size && ptr)
		return (free(ptr), NULL);
	dupp = ptr;
	buff = malloc(sizeof(*dupp) * new_size);
	if (buff == NULL)
		return (free(ptr), NULL);
	tide = buff;
	for (i = 0; i < old_size && i < new_size; i++)
		tide[i] = *dupp++;
	free(ptr);
	return (buff);
}
