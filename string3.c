#include "shell.h"

/**
 * _atoi - converts a string into an integer
 * @s: the string to convert
 *
 * Return: int res
 */
int _atoi(char *s)
{
	int sign = 1, i = 0;
	unsigned int res = 0;

	while (!(s[i] <= '9' && s[i] >= '0') && s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] <= '9' && (s[i] >= '0' && s[i] != '\0'))
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	res *= sign;
	return (res);
}

/**
 * _strncmp - compares s1 upto n size with s2
 * @s1: ..
 * @s2: ..
 * @n: ..
 *
 * Return: 0
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == '\0')
			return (0); /* Both strings are equal up to n chars */
		s1++;
		s2++;
		n--;
	}
	return (0); /* Both strings are equal up to n chars */
}
