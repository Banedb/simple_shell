#include "shell.h"
/**
 * find_alias - creates alias
 * @name: ..
 * @index: ..
 * Return: ..
 */
char *find_alias(char *name, int *index)
{
	int j;
	char *check, *buffer;

	for (j = 0; aliases[j].name != NULL; j++)
	{
		if (_strcmp(name, aliases[j].name) == 0)
		{
			if (index != NULL)
				*index = j;
			buffer = aliases[j].val;
			check = find_alias(aliases[j].val, index);
			if (check)
				return (check);
			else
				return (buffer);
		}
	}
	return (NULL);
}
