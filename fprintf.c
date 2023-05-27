#include "shell.h"
/**
 * _fprintf - function writes formatted output
 * to the specified file descriptor fd.
 * @fd: The file descriptor to write the output to.
 * @format: The format string specifying the output format.
 * Return: number of bytes written on success, or -1 if an error occurs.
*/

int _fprintf(int fd, const char *format, ...)
{
	va_list args;
	const char *c = format;
	int bytes_written = 0;

	va_start(args, format);
	while (*c != '\0')
	{
		if (*c == '%')
		{
			c++;
			if (*c == 'd')
			{
				char buffer[32];
				int num = va_arg(args, int), length = int_to_string(num, buffer);
				ssize_t result = write(fd, buffer, length);

				if (result < 0)
					return (-1);
				bytes_written += result;
			}
			else if (*c == 's')
			{
				char *str = va_arg(args, char *);
				ssize_t result = write(fd, str, _strlen(str));

				if (result < 0)
					return (-1);
				bytes_written += result;
			}
		}
		else
		{
			ssize_t result = write(fd, c, 1);

			if (result < 0)
				return (-1);
			bytes_written += result;
		}
		c++;
	}
	va_end(args);
	return (bytes_written);
}

/**
 * int_to_string - function converts an integer num to a string
 * representation and stores it in the provided buffer.
 * @num: The integer to convert to a string
 * @buffer: The buffer to store the resulting string.
 * Return: The length of the resulting string.
*/

int int_to_string(int num, char *buffer)
{
	int length = 0, is_negative = 0;

	if (num == 0)
	{
		buffer[0] = '0';
		return (1);
	}

	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}

	while (num != 0)
	{
		int digit = num % 10;

		buffer[length] = '0' + digit;
		length++;
		num /= 10;
	}

	if (is_negative)
	{
		buffer[length] = '-';
		length++;
	}

	reverse_string(buffer, length);

	return (length);
}

/**
 * reverse_string -function reverses the characters
 * in a string str of a specified length length in-place.
 * @str: The string to reverse.
 * @length: The length of the string.
*/

void reverse_string(char *str, int length)
{
	int start = 0, end = length - 1;

	while (start < end)
	{
		char temp = str[start];

		str[start] = str[end];
		str[end] = temp;

		start++;
		end--;
	}
}
