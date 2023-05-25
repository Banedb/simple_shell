#include "shell.h"

/**
 * readui - Reads user input
 *
 * Return: user input
 */
char *readui(void)
{
	char *prompt = "($) ", *user_input = NULL;
	size_t n = 0;
	ssize_t gret;

	_puts(prompt);
	gret = getline(&user_input, &n, stdin);
	/* Handling EOF and errors of getline function */
	if (gret < 0)
	{
		free(user_input);
		return (NULL);
	}
	return (user_input);
}

/**
 * splitui - tokenizes user input
 * @user_input: Arguments
 *
 * Return: Array of the arguments
 */
char **splitui(char *user_input)
{
	char *token, **argv, *ui_copy = NULL;
	const char *delim = " \n";
	int tcount, i;

	ui_copy = malloc(_strlen(user_input) + 1);
	/* Making copy to preserve user_input from strtok splits */
	_strcpy(ui_copy, user_input);
	/* To get number of arguments entered by user */
	token = strtok(ui_copy, delim);
	for (tcount = 1; token != NULL; tcount++)
		token = strtok(NULL, delim);
	argv = malloc(sizeof(char *) * tcount);
	/* To assign the arguments passed by user to array argv */
	token = strtok(user_input, delim);
	for (i = 0; token != NULL; i++)
	{
		argv[i] = token;
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	free(user_input);
	free(ui_copy);
	return (argv);
}
/**
 * main - Entry point
 * @argc: Number of arguments
 * @envp: Array of environment variables
 * @argv: arguments
 * Return: 0 (Success)
 */
int main(int argc, char **argv, char **envp)
{
	char *user_input = NULL;

	count = 1;
	name = argv[0];
	for (;;)
	{
		user_input = readui();
		if (user_input == NULL)
			break;
		argv = splitui(user_input);
		if (argv == NULL)
			continue;
		cmdexe(argv, envp);
		free(argv);
		count++;
	}
	free(user_input);
	(void)argc;
	return (0);
}
