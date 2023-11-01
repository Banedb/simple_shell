#include "shell.h"

/**
*_puts - entry point
*@str: character passed as an argument
*Description: 'Write a function that prints a string,
*followed by a new line, to stdout.
*Prototype: void _puts(char *str)
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
 * _strcat - function that concatenates two strings
 * @dest: first argument
 * @src: second argument to be added to first
 *
 * Return: dest.
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}


/**
 * _strcpy - copies the string pointed to by src, including \0.
 * @dest: first pointer
 * @src: second pointer
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i, length;

	for (length = 0; src[length] != '\0'; length++)
		;
	for (i = 0; i <= length ; i++)
		dest[i] = src[i];
	return (dest);
}

/**
 * _strcmp -  function that compares two strings.
 * @s1: first string
 * @s2: second string
 * Return: 0
 */

int _strcmp(char *s1, char *s2)
{
	int res = 0;

	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	if (s1 != s2)
		res = *s1 - *s2;

	return (res);
}


/**
 * _strlen - calculate the length of a string.
 * @s: the string to calculate it's length.
 *
 * Return: length of the string.
 */
int _strlen(char *s)
{
	int i, length = 0;

	for (i = 0; s[i] != '\0'; i++)
		length++;
	return (length);
}
