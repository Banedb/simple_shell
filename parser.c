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

	user_input = NULL;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, prompt, 2);
	while ((charc = _getline(&user_input, &n, STDIN_FILENO)) != -1)
	{
		builtpath = 0;
		nullvar = 0;
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
		status = parser(user_input);
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
 * @command: line to be split
 *
 * Return: 0
 */
int tokenizer(char *command)
{
	int tcount, status = 0;
	const char *delim = " \n\t&|";
	char *cmd_copy = NULL, *token, **token_array, *check, *tp, *tpa;

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
	token = _strtok_r(command, delim, &tpa);
	for (tcount = 0; token != NULL; tcount++)
	{ /* store each token in the token_array */
		token_array[tcount] = _strdup(token);
		check = handle_vars(token_array[tcount]);
		if (check)
		{
			free(token_array[tcount]);
			token_array[tcount] = check;
		}
		token = _strtok_r(NULL, delim, &tpa);
	}
	token_array[tcount] = NULL;
	if (nullvar == 0)
		status = cmdexe(token_array);
	else
		write(1, "\n", 1);
	free_args(token_array);
	return (status);
}

/**
 * parser - parses multiple commands
 * @line: line to be split
 *
 * Return: 0
 */
int parser(char *line)
{
	char *cmdptr, *and_tok, *or_token, *commands;
	int status = 0;

	line = comment(line);
	if (!line)
		return (0);
	commands = _strtok_r(line, ";", &cmdptr);
	for (; commands != NULL;)
	{
		and_tok = _strstr(commands, "&&");
		or_token = _strstr(commands, "||");
		if (and_tok && (or_token == NULL || and_tok < or_token))
			status = checkAND(commands);
		else if (or_token && (and_tok == NULL || or_token < and_tok))
			status = checkOR(commands);
		else
			status = tokenizer(commands);
		commands = _strtok_r(NULL, ";", &cmdptr);
	}
	return (status);
}


/**
 * checkAND - handles when first operator is &&
 * @commands: line to be split
 * Return: 0 on success
 */
int checkAND(char *commands)
{
	int ret = 0;
	char *cmd, *op = "", *and_token = _strstr(commands, "&&");
	char *or_token = _strstr(commands, "||"), *ata;

	if (or_token == NULL)
	{
		cmd = _strtok_r(commands, "&", &ata);
		while (cmd != NULL)
		{
			ret = tokenizer(cmd);
			if (ret != 0)
				return (ret);
			cmd = _strtok_r(NULL, "&", &ata);
		}
	}
	else
	{
		cmd = _strtok_r(commands, "&", &ata);
		while (cmd != NULL)
		{
			ret = tokenizer(cmd);
			if (((ret == 0) && (_strcmp(op, "||") == 0))
			    || ((ret != 0) && (_strcmp(op, "&&") == 0)))
				return (ret);
			or_token = _strstr(commands, "||");
			and_token = _strstr(commands, "&&");
			if (and_token == NULL || and_token > or_token)
				op = "|";
			else
				op = "&";
			cmd = _strtok_r(NULL, op, &ata);
		}
	}
	return (ret);
}

/**
 * checkOR - handles when first operator is ||
 * @commands: line to be split
 * Return: 0 on success
 */
int checkOR(char *commands)
{
	int ret = 0;
	char *cmd, *op = "", *and_token = _strstr(commands, "&&");
	char *or_token = _strstr(commands, "||"), *ota;

	if (and_token == NULL)
	{
		cmd = _strtok_r(commands, "|", &ota);
		while (cmd != NULL)
		{
			/* printf("command3 is %s\n", cmd); */
			ret = tokenizer(cmd);
			if (ret == 0)
				return (ret);
			cmd = _strtok_r(NULL, "|", &ota);
		}
	}
	else
	{
		cmd = _strtok_r(commands, "|", &ota);
		while (cmd != NULL)
		{
			/* printf("command4 is %s\n", cmd); */
			ret = tokenizer(cmd);
			if (((ret == 0) && (_strcmp(op, "||") == 0))
			    || ((ret != 0) && (_strcmp(op, "&&") == 0)))
				return (ret);
			or_token = _strstr(commands, "||");
			and_token = _strstr(commands, "&&");
			if (or_token == NULL || and_token < or_token)
				op = "&";
			else
				op = "|";
			cmd = _strtok_r(NULL, op, &ota);
		}
	}
	return (ret);
}
