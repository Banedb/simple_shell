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
