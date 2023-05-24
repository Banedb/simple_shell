#include "shell.h"
/**
 * numdl - counts number digits
 * @num: Integer
 *
 * Return: number of digits
 */
int numdl(int n)
{
	unsigned int num;
	int len = 1;

	if (n < 0)
	{
		len++;
		num = n * -1;
	}
	else
		num = n;
	while (num > 9)
	{
		len++;
		num /= 10;
	}
	return (len);
}

/**
 * _itoa - convert integer to string
 * @n: Integer
 *
 * Return: converted string
 */

char *_itoa(int n)
{
	char *buffer;
	unsigned int num;
	int len = numdl(n);

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	buffer[len] = '\0';

	if (n < 0)
	{
		num = n * -1;
		buffer[0] = '-';
	}
	else
		num = n;
	len--;
	do {
		buffer[len] = (num % 10) + '0';
		num = num / 10;
		len--;
	} while (num > 0);
	return (buffer);
}
