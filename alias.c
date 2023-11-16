#include "shell.h"
/**
 * alias_handler - implements the builtin alias cmd
 * @args: array of arguments passed to program
 */
void alias_handler(char **args)
{
	int i, j = 1, index = 0, make = 0, argcount = -1, namelen;
	char *check, *valstart, *names[MAX_ALIASES], *values[MAX_ALIASES];

	for (i = 0; args[i]; i++)
		argcount++;
	if (argcount == 0)
	{/* No arguments, print all aliases */
		for (i = 0; i < aliascount; i++)
			list_alias(i);
		return;
	}
	for (; index < argcount; j++, index++)
	{
		check = _strchr(args[j], '=');
		if (check)
		{
			namelen = check - args[j];
			valstart = args[j] + (namelen + 1);
			names[make] = _strndup(args[j], namelen);
			addyarray(names[make]);
			values[make] = _strdup(valstart);
			addyarray(values[make]);
			create_alias(names[make], values[make]);
			make++;
		}
		else /* print specific aliases */
		{
			for (i = 0; i <= aliascount; i++)
				if ((aliases[i].name)
				    && (_strcmp(args[j], aliases[i].name) == 0))
				{
					list_alias(i);
					break;
				}
		}
	}
	names[make] = NULL;
	values[make] = NULL;
}

/**
 * create_alias - creates alias
 * @names: ..
 * @values: ..
 */
void create_alias(char *names, char *values)
{
	int index;
	char *check;

	check = find_alias(names, &index);
		if (check) /* Alias already exists, replace the value */
			aliases[index].val = values;
		else
		{/* New alias, add it to the array */
			aliases[aliascount].name = names;
			aliases[aliascount].val = values;
			aliascount++;
		}
}

/**
 * list_alias - lists alias
 * @i: ..
 */
void list_alias(int i)
{
	char *aliaslist = NULL;

	aliaslist = malloc(sizeof(char) * (_strlen(aliases[i].name)
					   + _strlen(aliases[i].val) + 5));
	_strcpy(aliaslist, aliases[i].name);
	_strcat(aliaslist, "='");
	_strcat(aliaslist, aliases[i].val);
	_strcat(aliaslist, "'\n");
	write(STDOUT_FILENO, aliaslist, _strlen(aliaslist));
	free(aliaslist);
}
