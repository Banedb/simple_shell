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
	size_t pos = 0, new_size;
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
/**
 * initialize_buffer - initialize mygetc
 * @fd: file descriptor
 * @buffer: ..
 * @pos: ..
 * @size: ..
 */

void initialize_buffer(int fd, char *buffer, size_t *pos, size_t *size)
{
	*pos = 0;
	*size = read(fd, buffer, BUFFER_SIZE);
}

/**
 * mygetc - custom getc
 * @fd: file descriptor
 *
 * Return: gotten char
 */
int mygetc(int fd)
{
	static char buffer[BUFFER_SIZE];
	static size_t pos;
	static size_t size;

	if (pos >= size)
	{
		initialize_buffer(fd, buffer, &pos, &size);

		if (size <= 0 || pos >= size)
			return (EOF);
	}

	return ((int)buffer[pos++]);
}

int is_absolute_path(const char *path)
{
	char *slash;

	slash = _strchr(path, '/');
/* If '/' is found and it's at the beginning of the string = absolute path */
	if (slash != NULL && slash == path)
		return (1); /* It's an absolute path */
	else
		return (0); /* It's not an absolute path */
}
