#include "shell.h"

/**
 * run_input - gets input from stdin using getline
 *
 * Return: pointer to the input
 */
int run_input(void)
{
	int exit_status = -1, count = 0;
	size_t n = 0; /*initial bufsize resizable by gl to accommodate input*/
	ssize_t charc/* actual n of chars gl read from the input stream */;

	hist = 0;
	user_input = NULL;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, prompt, 2);
	while ((charc = _getline(&user_input, &n, STDIN_FILENO)) != -1)
	{
		is_absolute_path = 0;
		if (user_input[charc - 1] == '\n')
			user_input[charc - 1] = '\0';
		count++;
		hist++;
		exit_status = tokenizer(user_input);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
	}
	if (user_input)
		free(user_input);
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "\n", 2);
	exit(exit_status);
}

/**
 * tokenizer - splits line into an array of tokens
 * @line: line to be split
 *
 * Return: pointer to the array
 */
int tokenizer(char *line)
{
	int tcount, exit_status = 0;
	const char *delim = " \n\t";
	char *line_copy = NULL, *token, **token_array, **envp = environ;

	line_copy = _strdup(line);
	if (line_copy != NULL)
	{
		token = _strtok(line_copy, delim);
		/* count tokens ie n of strings */
		for (tcount = 0; token != NULL; tcount++)
			token = _strtok(NULL, delim);
		free(line_copy);
	}
	else
		return (-1);

	/* allocate space to hold the array of strings */
	token_array = malloc(sizeof(char *) * (tcount + 1));
	if (!token_array)
		return (-1);
	/* store each token in the token_array */
	token = _strtok(line, delim);
	for (tcount = 0; token != NULL; tcount++)
	{
		token_array[tcount] = _strdup(token);
		token = _strtok(NULL, delim);
	}
	token_array[tcount] = NULL;
	exit_status = cmdexe(token_array, envp);
	free_args(token_array);
	return (exit_status);
}
