#include "shell.h"
/**
 * _getline - gets input from stream.
 * @lineptr: input as a string
 * @n: size of input, resizable by the function
 * @fd: file descriptor
 *
 * Return: n of chars read || -1 on error
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	size_t pos = 0;
	size_t new_size;
	char *new_line;
	int c;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	if (*lineptr == NULL)
	{
		*lineptr = malloc(128);
		if (*lineptr == NULL)
			return (-1);
		*n = 128;
	}

	while ((c = mygetc(fd)) != EOF)
	{
		if (pos + 1 >= *n)
		{
			new_size = (*n) * 2;
			new_line = _realloc(*lineptr, *n, new_size);
			if (new_line == NULL)
				return (-1);
			*lineptr = new_line;
			*n = new_size;
		}

		(*lineptr)[pos++] = c;

		if (c == '\n')
		{
			(*lineptr)[pos] = '\0';
			return (pos);
		}
	}

	if (pos == 0)
		return (-1);

	(*lineptr)[pos] = '\0';
	return (pos);
}
