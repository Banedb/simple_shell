#include "shell.h"

/**
 * readArg - Get user input
 * @argv: Array of pointers to store the arguments
 * Return: void
 */
void readArg(char **argv)
{
	char *user_input = NULL;
	char *ui_copy = NULL;
	char *token;
	const char *delim = " \n";
	int tcount, i;
	size_t n = 0;
	ssize_t gret;

	gret = getline(&user_input, &n, stdin);
	/* Handling EOF and errors of getline function */
	if (gret < 0)
	{
		free(user_input);
		return;
	}
	/* Making a copy to preserve user_input from strtok splits */
	ui_copy = malloc(sizeof(char) * gret);
	if (ui_copy == NULL)
	{
		_puts("Malloc for Copy of User-Input Failed\n");
		return;
	}
	_strcpy(ui_copy, user_input);
	/* To get the number of arguments entered by the user */
	token = strtok(ui_copy, delim);

	for (tcount = 1; token != NULL; tcount++)
		token = strtok(NULL, delim);
	/* To assign the arguments passed by the user to the array argv */
	token = strtok(user_input, delim);
	for (i = 0; token != NULL; i++)
	{
		argv[i] = token;
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
}
