#include "shell.h"

/**
 * _strdup - duplicate a constant str
 * @str: string to be duplicated
 * Return: duplicated str
 */

char *_strdup(const char *str)
{
	char *new_str;
	size_t length, i;

	if (!str)
		return (NULL);

	length = 0;
	while (str[length] != '\0')
	{
		/* Determine the length of the string*/
		length++;
	}

	/* Allocate memory for the new string*/
       /*(plus one for the null terminator)*/
	new_str = malloc(length + 1);

	if (new_str != NULL)
	{
		for (i = 0; i < length; i++)
		{
			/* Copy each character from the original str to the new str*/
			new_str[i] = str[i];
		}

		/* Add the null terminator at the end of the new string*/
		new_str[length] = '\0';
	}

	return (new_str);
}

/**
*_puts - entry point
*@str: character passed as an argument
*Description: 'Write a function that prints a string,
*followed by a new line, to stdout.
*Prototype: void _puts(char *str)'
*/
void _puts(char *str)
{
	char newLine = '\n';

	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
	(void)newLine;
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
	{
		/* actual length of the string within the specified limit*/
		length++;
	}

	/* Allocate memory for the new string (plus one for the null terminator)*/
	new_str = malloc(length + 1);
	if (new_str != NULL)
	{
		for (i = 0; i < length; i++)
		{
			/* Copy each character from the original string to the new string*/
			new_str[i] = str[i];
		}

		/* Add the null terminator at the end of the new string*/
		new_str[length] = '\0';
	}

	return (new_str);
}

/**
*_strcpy - entry point
*@dest: 'string"
*@src: 'string
*Description: 'Prototype: char *_strcpy(char *dest, char *src);
*Write a function that copies the string pointed to by src,
*including the terminating null byte (\0), to the buffer pointed to by dest'
*Return: value the pointer to dest
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
*_strcat - entry point
*@dest: 'string'
*@src: 'string'
*Description: 'Write a function that concatenates two strings.
*Prototype: char *_strcat(char *dest, char *src)
*This function appends the src string to the dest string,
*overwriting the terminating null byte (\0)
*at the end of dest, and then adds a terminating null byte'
*Return: a pointer to the resulting string dest
*/
char *_strcat(char *dest, char *src)
{
	/*first get length of dest*/
	int lenDest = 0, i;

	while (dest[lenDest] != '\0')
		lenDest++;

	/*from the */
	for (i = 0; src[i] != '\0'; i++)
		dest[lenDest + i] = src[i];
	dest[lenDest + i] = '\0';

	return (dest);
}
