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
	char *cmd_copy = NULL, *token, **token_array, *tp, *tpa;

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
		token = _strtok_r(NULL, delim, &tpa);
	}
	token_array[tcount] = NULL;
	status = cmdexe(token_array);
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
	int ret = 0;
	char *cmd, *op = "h", *and_token = _strstr(line, "&&");
	char *or_token = _strstr(line, "||"), *ota, *ata;
	char *commands, *cmdptr;
	int status = 0;

	line = comment(line);
	if (!line)
		return (0);
	commands = _strtok_r(line, ";", &cmdptr);
	for (; commands != NULL;)
	{
		if (and_token && (or_token == NULL || and_token < or_token))
			status = checkAND(commands);
		else if (or_token && (and_token == NULL || or_token < and_token))
			status = checkOR(commands);
		else
			status = tokenizer(commands); */
		commands = _strtok_r(NULL, ";", &cmdptr);
	}
	return (status);
}


/**
 * andor - handles the || and && logical operators
 * @commands: line to be split
 * Return: 0 on success
 */
int andor(char *commands)
{
	int ret = 0;
	char *cmd, *op = "h", *and_token = _strstr(commands, "&&");
	char *or_token = _strstr(commands, "||"), *ota, *ata;

	if (and_token && (or_token == NULL || and_token < or_token))
	{ /* Tokenize based on "&&" */
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
	}
	else if (or_token && (and_token == NULL || or_token < and_token))
	{ /* Tokenize based on "||" */
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
	}
	else /* No "&&" or "||", just execute the command */
		ret = tokenizer(commands);
	return (ret);
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
