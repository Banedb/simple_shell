#include "shell.h"

/**
 * env_cleanup - cleanup malloc'ed memory from mysetenv
 */
void env_cleanup(void)
{
	int i;

	for (i = 0; i < addycount && envaddys[i] != NULL; ++i)
		free(envaddys[i]);
}

/**
 * free_args - free memory before abrupt exit
 * @args: strings array
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	if (args)
		free(args);
}

/**
 * cleaner - clean all malloc-ed  memory before exit
 * @args: strings array
 */

void cleaner(char **args)
{
	free_args(args);
	if (user_input)
		free(user_input);
	env_cleanup();
}
