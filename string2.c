#include "shell.h"
/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * @str: string
 *
 * Return: pointer of an array of chars
 */
char *_strdup(const char *str)
{
	char *buf;
	unsigned int i, j;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		;

	buf = malloc(sizeof(char) * (i + 1));

	if (buf == NULL)
		return (NULL);

	for (j = 0; *(str + j) != '\0'; j++)
		buf[j] = str[j];
	buf[j] = '\0';
	return (buf);
}


/**
 * _strndup - sup n chars of str
 * @str: input str
 * @n: number chars to be dup
 * Return: duplicated str
 */

char *_strndup(const char *str, size_t n)
{
	char *new_str;
	size_t i, length = 0;

	while (length < n && str[length] != '\0')
		length++;

	new_str = malloc(length + 1);
	if (new_str != NULL)
	{
		for (i = 0; i < length; i++)
			new_str[i] = str[i];

		/* Add the null terminator at the end of the new string*/
		new_str[length] = '\0';
	}

	return (new_str);
}

/**
 * myitoa - converts integer to str
 * @num: num to convrt to string
 *
 * Return: pointer to converted string
 */
char *myitoa(int num)
{
	int temp = num, index, digits = 0;
	char *str;

	while (temp != 0)
	{
		temp /= 10;
		digits++;
	}
	if (num == 0)
		digits = 1;
	str = malloc((digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	index = digits - 1;
	while (num > 0)
	{
		str[index] = '0' + (num % 10);
		num /= 10;
		index--;
	}
	str[digits] = '\0';
	return (str);
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
	static size_t;
	static size_t;

	pos = 0;
	size = 0;
	if (pos >= size)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		pos = 0;

		if (size <= 0 || pos >= size)
			return (EOF);
	}
	return ((int)buffer[pos++]);
}

/**
 * _strtok - custom version of the strtok function
 * @line: line to be split into strings
 * @delim: the delimiter
 *
 * Return: split string
*/
char *_strtok(char *line, const char *delim)
{
	int j;
	static char *str;
	char *str_copy;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
				break;
		}
		if (delim[j] == '\0')
			break;
	}
	str_copy = str;
	if (*str_copy == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (str_copy);
			}
		}
	}
	return (str_copy);
}
