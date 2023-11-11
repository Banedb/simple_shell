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

/**
 * _strtok_r - custom version of the strtok_r function
 * @str: line to be split into strings
 * @delim: the delimiter
 * @saveptr: adress of str
 * Return: split string
*/

char *_strtok_r(char *str, const char *delim, char **saveptr)
{
	char *token;

	/* If str is not NULL, update the saveptr */
	if (str != NULL)
		*saveptr = str;

	/* Skip leading delimiters */
	while (**saveptr != '\0' && _strchr(delim, **saveptr) != NULL)
		(*saveptr)++;

	/* If we've reached the end of the string, return NULL */
	if (**saveptr == '\0')
		return (NULL);

	/* Find the end of the token */
	token = *saveptr;
	while (**saveptr != '\0' && _strchr(delim, **saveptr) == NULL)
		(*saveptr)++;

	/* If this is not the end of the string, null-terminate the token */
	if (**saveptr != '\0')
	{
		**saveptr = '\0';
		(*saveptr)++;
	}

	return (token);
}

/**
 * _strchr - custom version of the strchr function
 * @str: string to search
 * @character: searched char
 *
 * Return: address of string
*/

char *_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == character)
			return ((char *)str); /* Found the character */
		str++;
	}
	return (NULL); /* Character not found */
}
