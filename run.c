#include "shell.h"
/**
 * cmdexe - coordinates command execution
 * @args: array of arguments passed to function
 *
 * Return: 0 (Success)
 */
int cmdexe(char **args)
{
	char **envp = environ, *check;
	int bic, i;

	for (i = 0; args[i] != NULL; i++)
	{
		check = find_alias(args[i], NULL);
		if (check && (_strcmp(args[0], "alias") != 0))
		{
			free(args[i]);
			args[i] = _strdup(check);
		}
	}
	if (args && args[0])
	{
		bic = corexec(args);
		if (bic != 1)
			return (bic);
		else
			return (extexec(args, envp));
	}
	else
		return (0);
}

/**
 * extexec - handles external commands execution
 * @argv: array of arguments passed to function
 * @envp: pointer to the environment variables
 * Return: 0 (Success)
 */

int extexec(char **argv, char **envp)
{
	char *cmdpath = _which(argv[0]);
	int status = 0;
	pid_t pid;

	if (cmdpath != NULL) /* fork only when command exists */
	{
		pid = fork();
		if (pid == 0)
		{/*child process */
			status = execve(cmdpath, argv, _env(envp));
			if (status == -1)
			{
				if (builtpath)
					free(cmdpath);
				perror("execve");
				return (-1);
			}
		}
		else if (pid == -1)/* fork failed */
		{
			if (builtpath)
				free(cmdpath);
			perror("fork");
			return (-1);
		}
		else
		{/* parent process */
			if (builtpath)
				free(cmdpath);
			return (parent_proc(pid, argv));
		}
	}
	else/* cannot locate exe */
		status = error_handler(argv, 127);
	return (status);
}

/**
 * parent_proc - handles parent proccess after fork
 * @argv: array of arguments passed to function
 * @pid: proccess id
 * Return: 0 (Success)
 */

int parent_proc(pid_t pid, char **argv)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (-1);
	}
	if (WIFEXITED(status)) /*Returns true if child process exited normally*/
	{
		exit_status = WEXITSTATUS(status);/*Retrieve status*/
		if (exit_status != 0)
			error_handler(argv, exit_status);
	}
	else if (WIFSIGNALED(status))/* child process exited due to a signal */
		exit_status = (128 + WTERMSIG(status));
	else/* child process did not exit normally */
		exit_status = 127;
	return (exit_status);
}
/**
 * corexec - executes builtin commands
 * @args: array of arguments passed to function
 *
 * Return: 0 (Success)
 */

int corexec(char **args)
{
	if (_strcmp(args[0], "alias") == 0)
	{
		alias_handler(args);
		return (0);
	}
	if (_strcmp(args[0], "cd") == 0)
	{
		_cd(args[1]);
		return (0);
	}
	else if (_strcmp(args[0], "env") == 0)
		return (printEnv(environ));
	else if (_strcmp(args[0], "exit") == 0)
		return (exitShell(args));
	else if (_strcmp(args[0], "setenv") == 0)
	{
		if ((args[1] == NULL) || (args[2] == NULL) || (args[3] != NULL))
		{
			write(2, "usage: setenv VARIABLE VALUE\n", 29);
			return (-1);
		}
		return (mysetenv(args[1], args[2]));
	}
	else if (_strcmp(args[0], "unsetenv") == 0)
	{
		if ((args[1] == NULL) || (args[2] != NULL))
		{
			write(2, "usage: unsetenv VARIABLE\n", 25);
			return (-1);
		}
		return (myunsetenv(args[1]));
	}
	return (1);
}
