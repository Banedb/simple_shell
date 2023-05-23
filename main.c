#include "shell.h"

/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: Arguments passed to function
 * @envp: Array of environment variables
 *
 * Return: 0 (Success)
 */
int main(int argc, char **argv, char **envp)
{
	char *prompt = "($) ", *user_input = NULL, *ui_copy = NULL, *token;
	const char *delim = " \n";
	int tcount, i;
	size_t n = 0;
	ssize_t gret;

	for (;;)
	{
		printf("%s ", prompt);
		gret = getline(&user_input, &n, stdin);
		/* Handling EOF and errors of getline function */
		if (gret < 0)
		{
			printf("exit\n");
			free(user_input);
			return (-1);
		}
		/* Making copy to preserve user_input from strtok splits */
		ui_copy = malloc(sizeof(char) * gret);
		if (ui_copy == NULL)
		{
			printf("Malloc for Copy of User-Input Failed\n");
			return (-1);
		}
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
		cmdexe(argv, envp);

	}

	free(user_input);
	free(ui_copy);
	(void)argc;
	return (0);
	/* Should I nullterminate argv? */
}
/* NB: Betty error: File has over 40 lines of code so will have to split */
