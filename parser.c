#include "shell.h"

/**
 * run_input - gets input from stdin using custom getline function
 *
 * Return: pointer to the input
 */
int run_input(void)
{
	int count = 0, status = 1;
	size_t n = 0; /*initial bufsize resizable by gl to accommodate input*/
	ssize_t charc/* actual n of chars gl read from the input stream */;
	char **envp, *prompt = "$ ";

	hist = 0;
	user_input = NULL;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, prompt, 2);
	while ((charc = _getline(&user_input, &n, STDIN_FILENO)) != -1)
	{
		builtpath = 0;
		path_unset = 1;/*assume PATH is unset*/
		if (user_input[charc - 1] == '\n')
			user_input[charc - 1] = '\0';
		count++;
		hist++;
		for (envp = environ; *envp; ++envp)
		{
			if (_strcmp(*envp, "PATH=") == 0)
			{
				path_unset = 0;  /* PATH is set */
				break;
			}
		}
		status = tokenizer(user_input);
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, prompt, 2);
			fflush(stdout);
		}
	}
	if (user_input)
		free(user_input);
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "\n", 2);
	env_cleanup();
	exit(status);
}

/**
 * tokenizer - splits line into an array of tokens
 * @line: line to be split
 *
 * Return: pointer to the array
 */
int tokenizer(char *line)
{
	int tcount, status = 0;
	const char *delim = " \n\t", *separator = ";";
	char *cmd_copy = NULL, *token, **token_array, *command, *cp, *tp, *tpr;

	line = comment(line);
	if (!line)
		return (0);
	command = _strtok_r(line, separator, &cp);
	for (; command != NULL;)
	{
		cmd_copy = _strdup(command);
		if (cmd_copy != NULL)
		{/* count tokens ie n of strings */
			token = _strtok_r(cmd_copy, delim, &tp);
			for (tcount = 0; token != NULL; tcount++)
				token = _strtok_r(NULL, delim, &tp);
			free(cmd_copy);
		}
		else
			return (-1);

		/* allocate space to hold the array of strings */
		token_array = malloc(sizeof(char *) * (tcount + 1));
		if (!token_array)
			return (error_handler(NULL, 50));
		token = _strtok_r(command, delim, &tpr);
		for (tcount = 0; token != NULL; tcount++)
		{ /* store each token in the token_array */
			token_array[tcount] = _strdup(token);
			token = _strtok_r(NULL, delim, &tpr);
		}
		token_array[tcount] = NULL;
		status = cmdexe(token_array);
		free_args(token_array);
		command = _strtok_r(NULL, separator, &cp);
	}
	return (status);
}


/**
 * comment - checks for comment in the line string
 * @line: ...
 *
 * Return: string without comment either modified or unmodified
 */

char *comment(char *line)
{
	size_t i;
	char *pos, *clean = NULL;

	if (*line == '#')
		return (NULL);
	pos = _strchr(line, '#');
	if (pos)
	{
		i = pos - line;
		if (i > 0 && line[i - 1] == ' ')
		{
			clean = _strndup(line, i);
			clean[i] = '\0';
			addyarray(clean);
			line = clean;
		}
	}
	return (line);
}
